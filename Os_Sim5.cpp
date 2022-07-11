#include <iostream>
#include <thread>
#include <unistd.h>
#include <mutex> // std::mutex, std::unique_lock
#include <condition_variable>

#define PROCESS_READY 0
#define PROCESS_RUN 1
#define PROCESS_SLEEP 2

#define MAX_ASSIGNMENTS 100

#define PRODUCER 0
#define CONSUMER 1

struct proc_tbl_t
{
    int id;
    int priority;
    volatile int state;
    int time_quantum;
    std::thread th;
    std::mutex mu_lock;
    std::condition_variable cv;
    std::mutex cv_lock;
    struct proc_tbl_t *prev;
    struct proc_tbl_t *next;
} proc_tbl[10];

struct assignment
{
    int id;
    struct assignment *prev;
    struct assignment *next;
} assignments[MAX_ASSIGNMENTS];

volatile int turn;
volatile bool interested[2];
volatile int nAssn;
int nRun;
int run_proc0, run_proc1;
struct proc_tbl_t sleep_q;
struct proc_tbl_t ready_q;
struct assignment assn_q;

void Put_Tail_Q(proc_tbl_t *, proc_tbl_t *);
proc_tbl_t *Get_Head_Q(proc_tbl_t *head);
void Put_Assignment_Q(assignment *, assignment *);
assignment *Get_Assignment_Q(assignment *head);
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

        std::cout << 't' << std::endl;
        ;
        if (run_proc0 != -1)
        {
            p = &(proc_tbl[run_proc0]);
            p->time_quantum--;
            if (p->time_quantum <= 0 && p->state == PROCESS_RUN)
                sched_required = 1;
        }
        if (run_proc1 != -1)
        {
            p = &(proc_tbl[run_proc1]);
            p->time_quantum--;
            if (p->time_quantum <= 0 && p->state == PROCESS_RUN)
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
    proc_tbl_t *p = &proc_tbl[id];
    std::unique_lock<std::mutex> lk(p->cv_lock);
    int assnid = 0;
    for (;;)
    {
        while (p->state != PROCESS_RUN)
        {
            p->cv.wait(lk);
        }
        enter_region(PRODUCER);
        if (nAssn < MAX_ASSIGNMENTS)
        {
            assignment *assn = &(assignments[assnid % MAX_ASSIGNMENTS]);
            assn->id = assnid++;
            if (assnid > 300)
                assnid = 0;
            ++nAssn;
            Put_Assignment_Q(&assn_q, assn);
            if (nAssn == 1)
            {
                syscall_wakeup();
                std::cout << "학생 과제하세요" << std::endl;
            }
            std::cout << "새로운 과제 " << assn->id << ", 현재 과제 수:" << nAssn << std::endl;
            if (nAssn == MAX_ASSIGNMENTS)
            {
                std::cout << "과제 너무 많음, 더 안 냄" << std::endl;
                syscall_sleep(id);
            }
        }
        leave_region(PRODUCER);
        usleep(10000);
        // std::cout << id;
    }
}

void proc_2(int id) /* Process 2: Consumer Process */
{
    proc_tbl_t *p = &proc_tbl[id];
    assignment *assn;
    std::unique_lock<std::mutex> lk(p->cv_lock);

    for (;;)
    {
        while (p->state != PROCESS_RUN)
        {
            p->cv.wait(lk);
        }
        enter_region(CONSUMER);
        assn = Get_Assignment_Q(&assn_q);
        if (assn != NULL)
        {
            std::cout << "과제 " << assn->id << " 완료!" << std::endl;
            assn = NULL;
            --nAssn;
            if (nAssn == MAX_ASSIGNMENTS - 1)
            {
                syscall_wakeup();
                std::cout << "교수님 과제 내주세요" << std::endl;
            }
            else if (nAssn == 0)
            {
                std::cout << "과제 없음, 놀러감" << std::endl;
                syscall_sleep(id);
            }
        }
        leave_region(CONSUMER);
        usleep(10000);
        // std::cout << id;
    }
}

void proc_3(int id) /* Process 3: Idle Process */
{
    proc_tbl_t *p = &proc_tbl[id];
    std::unique_lock<std::mutex> lk(p->cv_lock);

    for (;;)
    {
        while (p->state != PROCESS_RUN)
        {
            p->cv.wait(lk);
        }
        // std::cout << id;
    }
}

void proc_4(int id) /* Process 4: Idle Process */
{
    proc_tbl_t *p = &proc_tbl[id];
    std::unique_lock<std::mutex> lk(p->cv_lock);

    for (;;)
    {
        while (p->state != PROCESS_RUN)
        {
            p->cv.wait(lk);
        }
        // std::cout << id;
    }
}

int main() // Main thread: id = 0
{
    int main_state;
    proc_tbl_t *p;
    std::mutex mtx_main;
    std::unique_lock<std::mutex> lk(mtx_main);
    std::condition_variable main_cv;

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

    p = &(proc_tbl[1]);
    p->id = 1;
    p->priority = 4;
    p->state = PROCESS_READY;
    p->th = std::thread(proc_1, 1);
    Put_Tail_Q(&ready_q, p);

    p = &(proc_tbl[2]);
    p->id = 2;
    p->priority = 3;
    p->state = PROCESS_READY;
    p->th = std::thread(proc_2, 2);
    Put_Tail_Q(&ready_q, p);

    p = &(proc_tbl[3]);
    p->id = 3;
    p->priority = 0;
    p->state = PROCESS_READY;
    p->th = std::thread(proc_3, 3);
    Put_Tail_Q(&ready_q, p);

    p = &(proc_tbl[4]);
    p->id = 4;
    p->priority = 1;
    p->state = PROCESS_READY;
    p->th = std::thread(proc_4, 4);
    Put_Tail_Q(&ready_q, p);

    sys_scheduler();

    main_state = PROCESS_SLEEP;
    for (;;)
    { // Main() thread will sleep forever
        main_cv.wait(lk, [=]
                     { return main_state == PROCESS_RUN; });
    }
    return 0;
}

void sys_scheduler()
{
    std::cout << "run0:" << run_proc0 << ", run1:" << run_proc1 << std::endl;
    proc_tbl_t *p;

    if (run_proc0 == -1)
    {
        p = Get_Head_Q(&ready_q);
        std::cout << p->id << "를 run_proc0으로" << std::endl;
        if (p != NULL)
        {
            p->time_quantum = p->priority + 1;
            p->state = PROCESS_RUN;
            run_proc0 = p->id;
            nRun++;
            p->cv.notify_one(); // switch to process p->id and run */
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
                p->cv.notify_one(); // switch to process p->id and run */
            }
        }
    }
    if (run_proc1 == -1)
    {
        p = Get_Head_Q(&ready_q);
        std::cout << p->id << "를 run_proc1로" << std::endl;
        if (p != NULL)
        {
            p->time_quantum = p->priority + 1;
            p->state = PROCESS_RUN;
            run_proc1 = p->id;
            nRun++;
            p->cv.notify_one(); // switch to process p->id and run */
        }
    }
    else
    {
        p = &(proc_tbl[run_proc1]);
        if (p->time_quantum <= 0 && p->state == PROCESS_RUN)
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
                p->cv.notify_one(); // switch to process p->id and run */
            }
        }
    }
}

void syscall_sleep(int id)
{
    proc_tbl_t *p;

    p = &(proc_tbl[id]);
    if (p->state != PROCESS_RUN)
        return;
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
    std::cout << "프로세스 " << p->id << " 슬립" << std::endl;
}

void syscall_wakeup()
{
    proc_tbl_t *p;
    p = Get_Head_Q(&sleep_q);
    if (p == NULL)
        return;
    p->state = PROCESS_READY;
    Put_Tail_Q(&ready_q, p);
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

void enter_region(int process)
{
    volatile int other = 1 - process;
    interested[process] = true;
    std::atomic_thread_fence(std::memory_order_seq_cst);
    turn = process;
    while (turn == process && interested[other] == true)
        ;
}

void leave_region(int process)
{
    interested[process] = false;
}