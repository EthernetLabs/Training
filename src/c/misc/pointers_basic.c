#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <inttypes.h>

int _array[12] = { [0 ... 9] = 100 };

void PointerTarget(const int *p, int y)
{
    *((int *) p) = y;
}

int *pi __attribute__((section(".ocm")));

int main(void) {

    printf ("addr of main is: %p\n", &main);
    printf ("addr of _array is: %p\n", &_array);
    unsigned int num = 0x00FFFFDD;
    //int *pi;
    pi = &num;
    printf ("pi is: %p\n", pi);
    printf ("*pi is: %x\n", *pi);

    int x = 5;
    uintptr_t *zptr;
    zptr = (uintptr_t *) &_array;
    int * _array_ptr = (int *)&_array; // & causes compile time warning
    
    int * p1;
    printf("p1 > %p\n", p1);
    p1 = &x;
    printf("sizeof p1 = %lu\n", sizeof(p1));
    printf("p1 = %p\n", p1);
    int ** q1 = &p1;          
                            /*
                               (deref q) is a (ptr to int) = deref (addr of p) -> addr of x
                                deref q gives p
                                deref (deref q) 
                            */
    printf("deref q1 -> *q1: %p\n", *q1);
    printf("addr of x _> &x = %p\n", &x);
    printf("x = %d\n", x);
    printf("deref (deref q1) -> **q1: %d\n", **q1);
    
    //int * *q = (void *) &p; /*
    int * const p = &x;
    int * const *q = &p;          
                            /*
                               (deref q) is a (ptr to int) = deref (addr of p) -> addr of x
                                deref q gives p
                                deref (deref q) 
                            */
    printf("deref q -> *q: %p\n", *q);
    printf("addr of x _> &x = %p\n", &x);
    printf("x = %d\n", x);
    printf("deref (deref q) -> **q: %d\n", **q);

    *p = 1;
    printf("p = %p\n", (void *)p);
    printf("p PRIMAX = 0x%" PRIXMAX "\n", (uintptr_t)p);
    printf("x = %d\n", x);
    **q = 3;  /* also changes *p, but will not cause an error */
    printf("x = %d\n", x);
    PointerTarget(&x, 22);
    printf("x = %d\n", x);
    printf("pi = %p\n", (void *)pi);
    goto labelx;

labely:
    printf("_array[3] = %d\n", 7[_array]);
    return 0;

labelx:
        printf("labelx executed\n");
        goto labely;
}


