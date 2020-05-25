#include <stdio.h>

#define STRMAX 68
#define WORDMAX 40

int main(void) {
    int i;
    char strarray[STRMAX][WORDMAX] = {'\0'};
    
    for (i=0; i<STRMAX; i++) {
        scanf("%s", strarray[i]);
    }
    
    for (i=STRMAX-1; i>=0; i--) {
        printf("%s ", strarray[i]);
    }
 	
	puts("");

	return 0;
}
