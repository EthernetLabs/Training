#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>


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

//int main(int cliargsnum, char *cliargs[]) {
int main(int argc, char *argv[]) {
    struct3 _str;
    printf ("\xD\xA");
    printf ("cli args num: %d \n", argc);
    assert ((argc >= 2) && (argc <=4));
    _str = get_states();
    printf ("%d", _str.state4);

}

