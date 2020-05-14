#include <stdio.h>

#define MAX 100

int min(int , int);


int main(void) {

    int numInts, i=0, j=0, tmp, intArray[MAX] = {-1}, minNum;

    scanf("%d", &numInts);

	while (i < numInts) {
    	scanf("%d", &intArray[i]);
		i++;
	}
    
    minNum = intArray[0];
    for (i=0; i < numInts-1; i++) {
        tmp = min(intArray[i], intArray[i+1]);
        if (tmp < minNum)
            minNum = tmp;
    }

    printf("%d\n", minNum);

    return 0;
}


int min(int x, int y) {
	if (x < y) return x;
    else if (x > y) return y;
    else return x;
}

