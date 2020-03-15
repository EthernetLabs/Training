#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

struct STATES {
    u_int state1: 2; //4 
    u_int state2: 2; //1
    int32_t state3: 2; //4
    int32_t state4: 2; //4
};

struct BYTE {
    unsigned char bit0: 1; //LSB
    unsigned char bit1: 1;
    u_char bit2: 1;
    u_char bit3: 1;
    u_char bit4: 1;
    u_char bit5: 1;
    u_char bit6: 1;
    u_char bit7: 1; //MSB
}__attribute__ ((packed));

typedef struct BYTE _BYTE_;

struct STATES object = { 1, 0, 1, 1 };

struct STATES get_states()
//int get_states()
{
    object.state1 = 1, object.state4 = 0;
    return object;
};

u_char getbyte(unsigned int hex) {
    int mask = 0x000000FF;
    return hex&mask;
};

/*
 * _bit:    no. of bit to set - 0-7
 * _byte:   ptr to _byte to be modified 
 */

int set_bit(u_char _bit, u_char * _byte)
{
    printf("_bit to set is: %d\n", _bit);
    *_byte |= 1u << _bit; //*_byte = *byte | 1 << _bit;

};

int main(void) {
    _BYTE_ byte;
    byte.bit0 = 0b0;
    byte.bit1 = 0b0;
    byte.bit2 = 0b0;
    byte.bit3 = 0b0;
    byte.bit4 = 0b0;
    byte.bit5 = 0b0;
    byte.bit6 = 0b0;
    byte.bit7 = 0b0;

    _BYTE_ * byte_ptr = &byte;

    u_char x = 0b00110101;
    u_char y = 0b00100101;
    printf ("\xD\xA");
    printf ("WORDSIZE is: %d\n", __WORDSIZE);
    printf ("sizeof struct is: %lu\n", sizeof(object));
    printf ("struct3.state1 is: %d\n", object.state1);
    printf ("struct3.state4 is: %d\n", object.state4);
    printf ("struct3.state2 is: %c\n", object.state2);
    printf ("get_states() is: %d\n", get_states().state1);
    printf ("sizeof int: %lu, char: %lu, double: %lu, float: %lu\n", sizeof(int), sizeof(char), sizeof(double), sizeof(float));
    printf("binary z = %d\n", x&y);

    printf("Byte respresenting 255 is: %d\n", getbyte(255));

    byte.bit0 = 0b0;

    set_bit(3, (u_char *) byte_ptr);

    printf("custom_byte bit0 = %d\n", byte.bit0);
    printf("custom_byte bit1 = %d\n", byte.bit1);
    printf("custom_byte bit2 = %d\n", byte.bit2);
    printf("custom_byte bit3 = %d\n", byte.bit3);
    printf("custom_byte bit4 = %d\n", byte.bit4);
    printf("custom_byte bit5 = %d\n", byte.bit5);
    printf("custom_byte bit6 = %d\n", byte.bit6);
    printf("custom_byte bit7 = %d\n", byte.bit7);
    printf("size of custom_byte = %lu\n", sizeof(byte));

    return 0;
}

