#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


void process(void) {
    printf ("\xD\xA");
    printf("Process %d waits for someone to send it SIGSEGV\n", getpid());
    while (1) {
    };
}

void main(void) {
    pid_t pid;

    printf ("\xD\xAstart\xD\xA");
    printf ("PID is: %d\n", getpid());
    printf ("\xD\xA forking\xD\xA");

    pid = fork();
    printf ("PID is: %d\n", pid);
    printf ("getPID is: %d\n", getpid());
    printf ("getPPID is: %d\n", getppid());

}

