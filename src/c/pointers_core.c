#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <inttypes.h>

int main(void) {
    printf ("\xD\xA");
    int x = 5;
    int *q = &x;
    printf("q = %p\n", q);
    printf("*q = %d\n", *q);
    x = 99;
    printf("*q = %d\n", *q);
    printf("x = %d\n", x);
    printf("*q is same as x\n");
    printf("&x = %p\n", &x);
    int **ptr2 = &q;
    printf("**ptr2 = %d\n", *(*ptr2));
    printf("ptr2 = %p\n", ptr2);
    printf("&q = %p\n", &q);
    printf("*ptr2 = %p\n", *ptr2);
    printf("**ptr2 = %d\n", **ptr2);
    printf ("\xD\xA");
}


