#include <stdio.h>

enum STATES {
    state1 = 100, 
    state2, 
    state3,
    state4,
    state5,
    state6
};

enum STATES _ENUM_TYPE;

enum STATES get_states()
{
      return state2;
};

int main(void) {
    printf ("\xD\xA");
    printf ("size of enum: %ul \xD\xA", sizeof(_ENUM_TYPE)); 
    printf ("current state is: %d\n", get_states()); 
    return 0;
}

