#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

//Macros
#define BITS_PER_BYTE (8)

/* extract the n-th bit of x */
#define GET_BIT(x, n) ((((x)[(n) / BITS_PER_BYTE]) & (0x1 << ((n) % BITS_PER_BYTE))) != 0)

/* set the n-th bit of x to 1 */
#define SET_BIT(x, n) ((x)[(n) / BITS_PER_BYTE]) |= (0x1 << ((n) % BITS_PER_BYTE))

/* set the n-th bit of x to 0 */
#define RESET_BIT(x, n) ((x)[(n) / BITS_PER_BYTE]) &= ~(0x1 << ((n) % BITS_PER_BYTE))

unsigned char x = 0xFF;
unsigned char y = 0x00;
//int y = 1;

//divide
int shift_right(void) {
    return x >> y;
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

int test_var(void) {
    if (y) {
        printf ("True\n");
    }
}

int main(void) {
    printf ("\xD\xA");
    printf ("WORDSIZE is: %d\n", __WORDSIZE);
    printf("shift right = %d\n", shift_right());
    printf("shift left = %d\n", shift_left());
    //printf("GET BIT 0 = %d\n", GET_BIT(x, 0));
    test_zero();
    test_var();
    return 0;
}

