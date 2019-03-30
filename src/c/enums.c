#include <stdio.h>

enum STATES {
    state1 = 200, 
    state2 = 300, 
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
    printf ("size of enum: %d \xD\xA", sizeof(_ENUM_TYPE)); 
    printf ("current state is: %d\n", get_states()); 
    printf ("enum is: %d\n", state5); 
    return 0;
}

