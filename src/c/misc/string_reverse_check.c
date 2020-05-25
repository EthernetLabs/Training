#include <stdio.h>
#include <string.h>

#define MAX 100

int isReverse(char *, char *);

int main() {
    char src[MAX], dst[MAX];

    scanf("%s", src);
    scanf("%s", dst);

    if (isReverse(src, dst) == 1) {
        printf("%s is the reverse of %s\n", src, dst);
    }
    else {
        printf("%s is not the reverse of %s\n", src, dst);
    }

    puts("");
    return 0;
}

int isReverse(char *src, char *dst){
    int i;

    if (strlen(src) != strlen(dst))
        return 0;

    for (i=1; i<strlen(dst); i++) {
        if (src[i-1] != dst[strlen(dst)-i])
            return 0;
    }

    return 1;
}
