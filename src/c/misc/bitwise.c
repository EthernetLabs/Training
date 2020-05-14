#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

//Macros
#define BITS_PER_BYTE (8)
#define ERROR -1
#define SUCCESS 0

struct BYTEstruct {
    u_char bit0: 1;
    u_char bit1: 1;
    u_char bit2: 1;
    u_char bit3: 1;
    u_char bit4: 1;
    u_char bit5: 1;
    u_char bit6: 1;
    u_char bit7: 1;
}__attribute__ ((packed));

typedef struct BYTEstruct BYTE;

unsigned char x = 0xFF;
unsigned char z = 0x08;
unsigned char y = 0x00;
size_t a = 0, b = 0;
unsigned char halfmask = 0x0F;

//divide
u_char shift_right(u_char pos) {
    return x >> pos;
}

//mul
u_char shift_left(u_char pos) {
    return x << pos;
}


// Test whether exactly one of two variables is zero using
// if ( (!a) ^ (!b) )

// Test whether at least one of a and b equals zero with
// if ( !(a && b) )
int test_zero(void) {
    if (!(x && y)) {
        printf ("yes zero\n");
    }
}

// This works for both signed and unsigned integers. Check whether both are zero with
// if ( (a|b)==0 )
int test_both_zero(void) {
    if ((a|b)==0) {
        printf ("True\n");
    }
    else {
        printf ("False\n");
    }
}

static inline u_char test_bit(u_char * _src, u_char _bit)
// Return zero if bit[i] is zero else return one-bit word with bit[i] set.
{
    printf("(u_char)1 << _bit: %d\n", (u_char)0x01 << _bit);
    printf("src is: 0x%x\n", *_src);
    printf("(u_char)1: 0x%x\n", (u_char)0x01);
    return (u_char)(*_src & ((u_char)1 << _bit));
};


int main(void) {
    int y = 0;
    //char z = 0x0f;
    printf ("\xD\xA");
    printf ("WORDSIZE is: %d\n", __WORDSIZE);
    printf("shift right = %d\n", shift_right(2));
    printf("shift left = %d\n", shift_left(2));
    //printf("GET BIT 0 = %d\n", GET_BIT(x, 0));
    test_zero();
    test_both_zero();
    printf("bit is: %d\n", test_bit(&z, 3));
    return 0;
}

