#include <stdio.h>
#include <stdint.h>

int main(void) {
    __complex__ float _x = 45 + 3i;
    __int128 jumboint = 99;
    uint32_t x = 0;
    uint32_t y = (0 - 1);
    uint32_t z = 0xFFFF1100;
    uint64_t wx = 0xFFFFFFFFFFFF1100;
    char w = 0x00;
    float a = __real__ _x;
    float b = __imag__ _x;
    printf ("%f\t%f\n", a, b);
    printf ("size of _x is %lu\n", sizeof(_x));
    printf ("size of int is %lu\n", sizeof(int));
    printf ("size of jumboint is %lu\n", sizeof(jumboint));
    printf ("size of 64 int is %lu\n", sizeof(wx));
    printf ("z = %x\n", z);
    printf ("w = %x\n", w);
    printf ("y wrapped = %d\n", y);
    printf ("\xD\xA");
}

