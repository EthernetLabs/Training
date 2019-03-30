#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <inttypes.h>

struct STATES {
    int state1; //4 
    //char state2; //8 (1 + 7padding)
    float state3; //4
    int state4; //4
    double state5; //8
    int state6; //4
    char *ptr; //8
    int  *ptri;
//} __attribute__ ((packed));
} struct3;

struct food {
    short salmon;//2
    short salmon2;//2
    int pizza;//4
    char can;//8 = 1 + 7padding
} _food;

struct BITS {
    struct STATES states;
    int flag;
} __attribute__ ((packed));

//struct STATES struct3 = { 10, 'x', 20.9, 30 };

int _array[12] = { [0 ... 9] = 100 };

void PointerTarget(const int *p, int y)
{
    *((int *) p) = y;
}

int main(void) {

    unsigned int num = 0x00FFFFDD;
    int *pi;
    uint8_t bit8;
    pi = (int *)num;
    struct3.ptri = NULL;
    printf ("\xD\xA");
    int x = 5;
    int * const p = &x;
    int * _array_ptr = &_array;
    int * *q = (void *) &p; // (deref q) is a (ptr to int) = deref (addr of p) -> addr of x
    printf("X = %d\n", x);
    *p = 1; /* will cause an error at compile time */
    printf("p = %p\n", (void *)p);
    printf("p = 0x%" PRIXMAX "\n", (uintptr_t)p);
    printf("X = %d\n", x);
    **q = 3;  /* also changes *p, but will not cause an error */
    printf("X = %d\n", x);
    PointerTarget(&x, 22);
    printf("X = %d\n", x);
    printf("pi = %p\n", (void *)pi);
    goto labelx;
    printf("_array[3] = %d\n", 7[_array]);
    return 0;

labelx:
        printf("labelx executed\n");
}


