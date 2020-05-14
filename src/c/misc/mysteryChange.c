#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
main(int argc, char **argv)
{
    int x;
    int a[4];
    int i;

    //x = 5;

    printf("addr of i = %p\n", (void*) &i); 
    printf("addr of a = %p\n", (void*) d); 
    printf("addr of a = %p\n", (void*) d++); 
    printf("addr of a = %p\n", (void*) d++); 
    printf("addr of a = %p\n", (void*) d++); 
    printf("addr of x = %p\n", (void*) &x); 

    for(i = -1; i < 11; i++) {
        a[i] = 37;
        printf("x = %d\n", x);
    }

    //assert(x == 5);

    return 0;
}
