#include <stdio.h>
#include <unistd.h>
#include <signal.h>

struct STATES {
    int state1; //4 
    //char state2; //8 (1 + 7padding)
    float state3; //4
    int state4; //4
    double state5; //8
    int state6; //4
    char *ptr; //8
    int  *ptri;
//} __attribute__ ((packed));
} struct3;

struct food {
    short salmon;//2
    short salmon2;//2
    int pizza;//4
    char can;//8 = 1 + 7padding
} _food;

struct BITS {
    struct STATES states;
    int flag;
} __attribute__ ((packed));

//struct STATES struct3 = { 10, 'x', 20.9, 30 };

struct STATES get_states()
//int get_states()
{
    struct3.state1 = 100, struct3.state4 = 200, struct3.state6 = 300, struct3.state5 = 8888;
    //return struct3.state1;
    return struct3;
};

void sighandler(int signum)
{
    printf("Process %d got signal %d\n", getpid(), signum);
    signal(signum, SIG_DFL);
    kill(getpid(), signum);
}

int main(void) {
    struct3.ptri = NULL;
    printf ("\xD\xA");
    printf ("sizeof struct struct3 is: %lu\n", sizeof(struct3));
    printf ("sizeof struct food is: %lu\n", sizeof(_food));
    printf ("struct3.state1 is: %d\n", struct3.state1);
    printf ("struct3.state4 is: %d\n", struct3.state4);
    //printf ("struct3.state2 is: %c\n", struct3.state2);
    printf ("get_states() is: %d\n", get_states().state1);
    printf ("sizeof int: %lu, char: %lu, double: %lu, float: %lu\n", sizeof(int), sizeof(char), sizeof(double), sizeof(float));
    signal(SIGSEGV, sighandler);
    printf("Process %d waits for someone to send it SIGSEGV\n", getpid());
    while (1) {
    };
    return 0;
}

