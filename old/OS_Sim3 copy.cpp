#include <iostream>
#include <thread>
#include <unistd.h>
#include <mutex> // std::mutex, std::unique_lock
#include <condition_variable>
#include <cstdlib>

#define PROCESS_READY 0
#define PROCESS_RUN 1
#define PROCESS_SLEEP 2

#define MAX_ASSIGNMENTS 5

std::condition_variable cv;
std::mutex cv_m;
int turn;
bool interested[2];

struct proc_tbl_t
{
    int id;
    int priority;
    int state;
    int time_quantum;
    std::thread th;
    std::mutex mu_lock;
    struct proc_tbl_t *prev;
    struct proc_tbl_t *next;
} proc_tbl[10];

struct assignment
{
    int id;
    int difficulty;
    bool done;
    struct assignment *prev;
    struct assignment *next;
} assignments[MAX_ASSIGNMENTS];

int nAssn;
int nRun;
int run_proc0, run_proc1;
struct proc_tbl_t sleep_q;
struct proc_tbl_t ready_q;
struct assignment assn_q;

void Put_Tail_Q(proc_tbl_t *, proc_tbl_t *);
proc_tbl_t *Get_Head_Q(proc_tbl_t *head);
void Put_Assignment_Q(assignment *, assignment *);
assignment *Get_Assignment_Q(assignment *head);
template <typename Item>
void Print_Q(Item *);
void syscall_sleep(int id);
void syscall_wakeup();
void sys_scheduler();

void enter_region(int process);
void leave_region(int process);

void proc_timer_int(int id); // Process 0: Timer Interrupt Generator
void proc_1(int id);         // Process 1: Producer process
void proc_2(int id);         // Process 2: Consumer Process
void proc_3(int id);         // Idle process
void proc_4(int id);         // Idle process

void proc_timer_int(int id) /* Process 0: Timer Interrupt Genrator */
{
    proc_tbl_t *p;
    int sched_required;
    usleep(100000);
    for (;;)
    {
        sched_required = 0;

        if (run_proc0 != -1)
        {
            p = &(proc_tbl[run_proc0]);
            p->time_quantum--;
            if (p->time_quantum <= 0)
                sched_required = 1;
        }
        if (run_proc1 != -1)
        {
            p = &(proc_tbl[run_proc1]);
            p->time_quantum--;
            if (p->time_quantum <= 0)
                sched_required = 1;
        }
        if (run_proc0 == -1 && run_proc1 == -1)
            sched_required = 1;
        if (sched_required)
        {
            sys_scheduler();
        }
        /* do Time Service */
        usleep(100000);
    }
}

void proc_1(int id) /* Process 1: Producer Process */
{
    proc_tbl_t *p;
    std::unique_lock<std::mutex> lk(cv_m);
    int assnid = 0;
    p = &(proc_tbl[id]);
    for (;;)
    {
        if (nAssn < MAX_ASSIGNMENTS)
        {
            assignment *assn = &(assignments[assnid % MAX_ASSIGNMENTS]);
            assn->difficulty = (1 + std::rand() % 10) * 1000;
            assn->id = assnid++;
            if (assnid > 99)
                assnid = 0;
            assn->done = false;
            usleep(200000);
            enter_region(id);
            nAssn++;
            Put_Assignment_Q(&assn_q, assn);
            if (nAssn == 1)
            {
                syscall_wakeup();
                std::cout << "학생 과제하세요" << std::endl;
            }
            leave_region(id);
            // Print_Q(&assn_q);
            std::cout << "새로운 과제 " << assn->id << ", 난이도: " << assn->difficulty << std::endl;
            std::cout << "현재 과제 수: " << nAssn << std::endl;
            if (nAssn == MAX_ASSIGNMENTS)
            {
                std::cout << "과제 너무 많음, 더 안 냄" << std::endl;
                syscall_sleep(id);
            }
        }
        cv.wait(lk, [=]
                { return p->state == PROCESS_RUN; });
        // std::cout << "produce: " << id << std::endl;
    }
}

void proc_2(int id) /* Process 2: Consumer Process */
{
    proc_tbl_t *p;
    assignment *assn;
    std::unique_lock<std::mutex> lk(cv_m);

    p = &(proc_tbl[id]);
    assn = NULL;
    for (;;)
    {
        if (assn == NULL)
        {
            enter_region(id);
            assn = Get_Assignment_Q(&assn_q);
            if (nAssn == MAX_ASSIGNMENTS - 1)
            {
                syscall_wakeup();
                std::cout << "교수님 과제 내주세요" << std::endl;
            }
            leave_region(id);
            if (assn == NULL)
            {
                std::cout << "과제 없음, 놀러감" << std::endl;
                syscall_sleep(id);
            }
            else
            {
                std::cout << "과제 " << assn->id << " 선택, 난이도: " << assn->difficulty << std::endl;
            }
        }
        if (assn != NULL)
        {
            assn->difficulty--;
            if (assn->difficulty <= 0)
            { // 과제 끝냈으면
                assn->done = true;
                std::cout << "과제 " << assn->id << " 완료!" << std::endl;
                assn = NULL;
                nAssn--;
            }
            else
            { /*
                 if (assn->difficulty % 1000 == 0)
                 {
                     std::cout << "과제 " << assn->id << " 하는중";
                     for (int i = 0; i < assn->difficulty / 1000; i++)
                         std::cout << '.';
                     std::cout << std::endl;
                 }*/
            }
        }
        cv.wait(lk, [=]
                { return p->state == PROCESS_RUN; });
        // std::cout << "consume: " << id << std::endl;
    }
}

void proc_3(int id) /* Process 3: Idle Process */
{
    proc_tbl_t *p;
    std::unique_lock<std::mutex> lk(cv_m);

    p = &(proc_tbl[id]);
    for (;;)
    {
        cv.wait(lk, [=]
                { return p->state == PROCESS_RUN; });
        std::cout << "idle: " << id << std::endl;
        std::cout << "run0:" << run_proc0 << ", run1:" << run_proc1 << std::endl;
        std::cout << "readyQ: ";
        Print_Q<proc_tbl_t>(&ready_q);

        std::cout << "sleepQ: ";
        Print_Q<proc_tbl_t>(&sleep_q);
    }
}

void proc_4(int id) /* Process 4: Idle Process */
{
    proc_tbl_t *p;
    std::unique_lock<std::mutex> lk(cv_m);

    p = &(proc_tbl[id]);
    for (;;)
    {
        cv.wait(lk, [=]
                { return p->state == PROCESS_RUN; });
        std::cout << "idle: " << id << std::endl;
        std::cout << "run0:" << run_proc0 << ", run1:" << run_proc1 << std::endl;
        std::cout << "readyQ: ";
        Print_Q<proc_tbl_t>(&ready_q);

        std::cout << "sleepQ: ";
        Print_Q<proc_tbl_t>(&sleep_q);
    }
}

int main() // Main thread: id = 0
{
    int main_state;
    proc_tbl_t *p;
    std::unique_lock<std::mutex> lk(cv_m);

    nRun = 0;
    run_proc0 = run_proc1 = -1;
    ready_q.next = ready_q.prev = &(ready_q);
    sleep_q.next = sleep_q.prev = &(sleep_q);
    assn_q.next = assn_q.prev = &(assn_q);

    p = &(proc_tbl[0]);
    p->id = 0;
    p->priority = 0;
    p->state = PROCESS_READY;
    p->th = std::thread(proc_timer_int, 0);
    p->th.hardware_concurrency();

    p = &(proc_tbl[1]);
    p->id = 1;
    p->priority = 4;
    p->state = PROCESS_READY;
    p->th = std::thread(proc_1, 1);
    Put_Tail_Q(&ready_q, p);
    p->th.hardware_concurrency();

    p = &(proc_tbl[2]);
    p->id = 2;
    p->priority = 3;
    p->state = PROCESS_READY;
    p->th = std::thread(proc_2, 2);
    Put_Tail_Q(&ready_q, p);
    p->th.hardware_concurrency();

    p = &(proc_tbl[3]);
    p->id = 3;
    p->priority = 0;
    p->state = PROCESS_READY;
    p->th = std::thread(proc_3, 3);
    Put_Tail_Q(&ready_q, p);
    p->th.hardware_concurrency();

    p = &(proc_tbl[4]);
    p->id = 4;
    p->priority = 1;
    p->state = PROCESS_READY;
    p->th = std::thread(proc_4, 4);
    Put_Tail_Q(&ready_q, p);
    p->th.hardware_concurrency();

    std::cout << "run0:" << run_proc0 << ", run1:" << run_proc1 << std::endl;
    std::cout << "readyQ: ";
    Print_Q<proc_tbl_t>(&ready_q);

    std::cout << "sleepQ: ";
    Print_Q<proc_tbl_t>(&sleep_q);
    sys_scheduler();

    main_state = PROCESS_SLEEP;
    for (;;)
    { // Main() thread will sleep forever
        cv.wait(lk, [=]
                { return main_state == PROCESS_RUN; });
    }
    return 0;
}

void sys_scheduler()
{
    proc_tbl_t *p;
    // Print_Q<proc_tbl_t>(&ready_q);
    if (run_proc0 == -1)
    {
        p = Get_Head_Q(&ready_q);
        if (p != NULL)
        {
            p->time_quantum = p->priority + 1;
            p->state = PROCESS_RUN;
            run_proc0 = p->id;
            nRun++;
            cv.notify_all(); // switch to process p->id and run */
        }
    }
    else
    {
        p = &(proc_tbl[run_proc0]);
        if (p->time_quantum <= 0)
        {
            p->state = PROCESS_READY;
            Put_Tail_Q(&ready_q, p);

            p = Get_Head_Q(&ready_q);
            if (p == NULL)
            {
                run_proc0 = -1;
                nRun--;
            }
            else
            {
                p->time_quantum = p->priority + 1;
                p->state = PROCESS_RUN;
                run_proc0 = p->id;
                cv.notify_all(); // switch to process p->id and run */
            }
        }
    }
    if (run_proc1 == -1)
    {
        p = Get_Head_Q(&ready_q);
        if (p != NULL)
        {
            p->time_quantum = p->priority + 1;
            p->state = PROCESS_RUN;
            run_proc1 = p->id;
            nRun++;
            cv.notify_all(); // switch to process p->id and run */
        }
    }
    else
    {
        p = &(proc_tbl[run_proc1]);
        if (p->time_quantum <= 0)
        {
            p->state = PROCESS_READY;
            Put_Tail_Q(&ready_q, p);

            p = Get_Head_Q(&ready_q);
            if (p == NULL)
            {
                run_proc1 = -1;
                nRun--;
            }
            else
            {
                p->time_quantum = p->priority + 1;
                p->state = PROCESS_RUN;
                run_proc1 = p->id;
                cv.notify_all(); // switch to process p->id and run */
            }
        }
    }
}

void syscall_sleep(int id)
{
    proc_tbl_t *p;

    p = &(proc_tbl[id]);
    p->state = PROCESS_SLEEP;
    if (p->id == run_proc0)
    {
        run_proc0 = -1;
        nRun--;
    }
    if (p->id == run_proc1)
    {
        run_proc1 = -1;
        nRun--;
    }
    Put_Tail_Q(&sleep_q, p);
    cv.notify_all(); // switch to process p->id and run */
}

void syscall_wakeup()
{
    proc_tbl_t *p;

    p = Get_Head_Q(&sleep_q);

    if (p == NULL)
        return;
    p->state = PROCESS_READY;
    Put_Tail_Q(&ready_q, p);
    cv.notify_all(); // switch to process p->id and run */
}

void Put_Tail_Q(proc_tbl_t *head, proc_tbl_t *item)
{
    (head->mu_lock).lock();
    item->prev = head->prev;
    head->prev->next = item;
    item->next = head;
    head->prev = item;
    (head->mu_lock).unlock();
}

proc_tbl_t *Get_Head_Q(proc_tbl_t *head)
{
    proc_tbl_t *item;

    (head->mu_lock).lock();
    if (head->next == head)
    {
        (head->mu_lock).unlock();
        return NULL;
    }
    item = head->next;

    item->next->prev = head;
    head->next = item->next;

    (head->mu_lock).unlock();
    return item;
}

void Put_Assignment_Q(assignment *head, assignment *item)
{
    item->prev = head->prev;
    head->prev->next = item;
    item->next = head;
    head->prev = item;
}

assignment *Get_Assignment_Q(assignment *head)
{
    assignment *item;

    if (head->next == head)
    {
        return NULL;
    }
    item = head->next;

    item->next->prev = head;
    head->next = item->next;
    return item;
}

template <typename Item>
void Print_Q(Item *head)
{
    Item *item;

    item = head->next;
    while (item != head)
    {
        usleep(50000);
        std::cout << item->id << ' ';
        item = item->next;
    }
    std::cout << '\n';
}

void enter_region(int process)
{
    int other = 1 - process;
    interested[process] = true;
    turn = process;
    while (turn == process && interested[other] == true)
        ;
}

void leave_region(int process)
{
    interested[process] = false;
}