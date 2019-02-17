#include <stdio.h>

int main(void) {
    __complex__ float _x = 45 + 3i;
    __int128 jumboint = 99;
    float a = __real__ _x;
    float b = __imag__ _x;
    printf ("%f\t%f\n", a, b);
    printf ("size of _x is %lu\n", sizeof(_x));
    printf ("size of int is %lu\n", sizeof(int));
    printf ("size of jumboint is %lu\n", sizeof(jumboint));
    printf ("\xD\xA");
}

