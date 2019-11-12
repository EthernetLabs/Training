#include <stdio.h>
#include <stdlib.h>

enum STATES {
    state1 = 200, 
    state2 = 300, 
    state3,
    state4,
    state5,
    state6
};

//enum STATES _ENUM_TYPE;

enum STATES get_states()
{
      return state1;
};

int main(void) {
    printf ("\xD\xA");
    size_t _x = 3500;
    //printf ("size of enum: %d \xD\xA", sizeof(_ENUM_TYPE)); 
    printf ("current state is: %d\n", get_states()); 
    printf ("enum is: %d\n", state5); 
    printf ("sizeof _x is: %d\n", sizeof(_x)); 
    return 0;
}

