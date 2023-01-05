#include <stdio.h>
#define PRINT(x) printf("%s = %d\n", #x, x)

int main(void){
    int x = 1 , y = 1 , z = 1;
    x+=y+=z;
    PRINT(x<y?x++:y++);
}