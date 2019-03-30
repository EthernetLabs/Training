#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <inttypes.h>

//inline void __inc(int *p) __attribute__((always_inline));

static inline void __inc(int *p)
{
    (*p)++;
} 


int main(void) {
    printf ("\xD\xA");
    int x = 5;
    int *p = &x;
    int * *q = (void *) &p; //q is a pointer to (pointer to int) 
    printf("X = %d\n", x);
    *p = 1; /* will cause an error at compile time */
    printf("p = %p\n", (void *)p);
    printf("p = 0x%" PRIXMAX "\n", (uintptr_t)p);
    printf("X = %d\n", x);
    *(*q) = 3;  //deref q = &p
    printf("X = %d\n", x);
    __inc(p);
    printf("X = %d\n", x);
    printf("address of x = %p\n", &x);
    printf("address of p = %p\n", p);
    printf("address of q = %p\n", *q);
    return 0;
}


