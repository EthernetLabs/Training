#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

struct STATES {
    int state1; 
    //char state2; 
    //float state3; 
    int state4; 
    //double state5; 
    int state6;
};
    
struct STATES struct3 = { 10, 20, 30 };

//struct STATES get_states()
int get_states()
{
    struct3.state1 = 100, struct3.state4 = 200, struct3.state6 = 300;
    return struct3.state1;
};


void sighandler(int signum)
{
    printf("Process %d got signal %d\n", getpid(), signum);
    signal(signum, SIG_DFL);
    kill(getpid(), signum);
}


void main(void) {
    printf ("\xD\xA");
    printf ("sizeof struct is: %lu\n", sizeof(struct3));
    printf ("struct1.state1 is: %d\n", struct3.state1);
    printf ("struct1.state4 is: %d\n", struct3.state4);
    printf ("get_states() is: %d\n", get_states());
    signal(SIGSEGV, sighandler);
    printf("Process %d waits for someone to send it SIGSEGV\n", getpid());
    while (1) {
    };
}

