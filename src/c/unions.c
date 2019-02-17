#include <stdio.h>

union STATES {
    int state1, statex, statey; 
    char state2; 
    float state3; 
    int state4; 
    double state5; 
    int state6;
} union1, union2;

int get_states()
{
    union1.state4 = 40;
    return union1.state4;
};

int set_states()
{
    union2.state4 = 709;
    return union2.state4;
};

int main(void) {
    printf ("\xD\xA");
    printf ("sizeof union is: %lu\n", sizeof(union1));
    printf ("sizeof char is: %lu\n", sizeof(int));
    printf ("union1.state1 is: %d\n", union1.state1);
    printf ("current state is: %d\n", get_states());
    printf ("union2.state4 is: %d\n", set_states());
    printf ("union1.statey is: %d\n", union1.statey);
    return 0;
}

