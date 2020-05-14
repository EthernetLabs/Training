#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>


static inline void __inc(int *p)
{
    (*p)++;
} 

typedef void (*fptr)(int *); //define func pointer

typedef struct _fps {
    fptr callfunc;
}__fptr;


int main(void) {

    int x = 5;
    int *p = &x;

    printf("X = %d\n", x);

    __fptr __fptr_ptr;
    __fptr_ptr.callfunc = __inc;
    __fptr_ptr.callfunc(p);

    printf("X = %d\n", x);

    return 0;
}


