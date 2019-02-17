#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


struct STATES {
    u_int state1: 2; //4 
    u_int state2: 2; //1
    int32_t state3: 2; //4
    int32_t state4: 2; //4
} __attribute__ ((packed));

struct STATES struct3 = { 1, 0, 1, 1 };

struct STATES get_states()
{
    struct3.state1 = 1, struct3.state4 = 0;
    return struct3;
};

void sighandler(int signum)
{
    printf("Process %d got signal %d\n", getpid(), signum);
    signal(signum, SIG_DFL);
    kill(getpid(), signum);
}

int main(void) {
    printf ("\xD\xA");
    printf ("get_states() is: %d\n", get_states().state1);
    signal(SIGSEGV, sighandler);
    
    signal(SIGINT, sighandler);
    printf("Process %d waits for someone to send it SIGSEGV\n", getpid());
    while (1) {
    };
    return 0;
}

