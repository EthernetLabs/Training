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
//} __attribute__ ((packed));

struct STATES object = { 1, 0, 1, 1 };

struct STATES get_states()
//int get_states()
{
    object.state1 = 1, object.state4 = 0;
    //return struct3.state1;
    return object;
};

void sighandler(int signum)
{
    printf("Process %d got signal %d\n", getpid(), signum);
    signal(signum, SIG_DFL);
    kill(getpid(), signum);
}

int main(void) {
    printf ("\xD\xA");
    printf ("WORDSIZE is: %d\n", __WORDSIZE);
    printf ("sizeof struct is: %lu\n", sizeof(object));
    printf ("struct3.state1 is: %d\n", object.state1);
    printf ("struct3.state4 is: %d\n", object.state4);
    printf ("struct3.state2 is: %c\n", object.state2);
    printf ("get_states() is: %d\n", get_states().state1);
    printf ("sizeof int: %lu, char: %lu, double: %lu, float: %lu\n", sizeof(int), sizeof(char), sizeof(double), sizeof(float));
    signal(SIGSEGV, sighandler);
    signal(SIGINT, sighandler);
    printf("Process %d waits for someone to send it SIGSEGV\n", getpid());
    //while (1) {
    //};
    return 0;
}

