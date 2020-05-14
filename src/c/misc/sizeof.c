#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main(void) {
    printf ("\xD\xA");
    printf ("WORDSIZE is: %d\n", __WORDSIZE);
    printf("size of INT = %d\n", sizeof(int));
    printf("size of FLOAT = %d\n", sizeof(float));
    printf("size of DOUBLE = %d\n", sizeof(double));
    printf("size of LONG = %d\n", sizeof(long));
    printf("size of LONG INT = %d\n", sizeof(long int));
    printf("size of LONG LONG INT = %d\n", sizeof(long long int));
    return 0;
}

