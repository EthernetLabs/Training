#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <inttypes.h>

int main(void) {
    printf ("\xD\xA");
    int x = 5;
    int *q = &x;
    printf("q = %p\n", q); // q = 0x(address)
    printf("*q = %d\n", *q); // *q = 5
    x = 99;
    printf("*q = %d\n", *q); // *q = 99
    printf("x = %d\n", x); // x = 99
    printf("*q is same as x\n");
    printf("&x = %p\n", &x); // &x = 0x(address)

    int **ptr2 = &q;
    printf("**ptr2 = %d\n", *(*ptr2)); // **ptr2 = 99
    printf("ptr2 = %p\n", ptr2); // ptr2 = 0x(address) of ptr2
    printf("&q = %p\n", &q); // &q = 0x(address) of q
    printf("*ptr2 = %p\n", *ptr2); // *ptr2 = 0x(address) of q
    printf("**ptr2 = %d\n", **ptr2); // **ptr2 = 99
    printf ("\xD\xA");
}


