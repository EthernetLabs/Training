#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

//Macros
#define BITS_PER_BYTE (8)

unsigned char x = 0xFF;
unsigned char y = 0x00;
size_t a = 0, b = 0;
unsigned char halfmask = 0x0F;

//divide
int shift_right(void) {
    return x >> 2;
}

//mul
int shift_left(void) {
    return x << y;
}

/*
Test whether at least one of a and b equals zero with
if ( !(a && b) )

This works for both signed and unsigned integers. Check whether both are zero with
if ( (a|b)==0 )

This obviously generalizes for several variables as
if ( (a|b|c|..|z)==0 )

Test whether exactly one of two variables is zero using
if ( (!a) ^ (!b) )
*/

int test_zero(void) {
    if (!(x && y)) {
        printf ("yes zero\n");
    }
}

int test_both_zero(void) {
    if ((a|b)==0) {
        printf ("True\n");
    }
    else {
        printf ("False\n");
    }
}

int main(void) {
    int y = 0;
    char z = 0x0f;
    printf ("\xD\xA");
    printf ("WORDSIZE is: %d\n", __WORDSIZE);
    printf("shift right = %d\n", shift_right());
    printf("shift left = %d\n", shift_left());
    //printf("GET BIT 0 = %d\n", GET_BIT(x, 0));
    test_zero();
    test_both_zero();
    return 0;
}

