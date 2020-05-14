#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>


static inline void __inc(int *p)
{
    (*p)++;
} 

void (*fptr)(int *); //define func pointer


int main(void) {
    fptr = __inc; //or &__inc;

    int x = 5;
    int *p = &x;

    printf("X = %d\n", x);
    (void) fptr(p);
    printf("X = %d\n", x);

    return 0;
}

