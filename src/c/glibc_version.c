#include <stdio.h>
#include <unistd.h>
#include <gnu/libc-version.h>
#include <string.h>

int main(void) {

    _file = "bogus.c"

    printf("glibc version = %s\n", gnu_get_libc_version());
    return 0;

}


