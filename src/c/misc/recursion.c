#include <stdio.h>

int sumOfDigits(int);

int main(void) {
    int n, sum;
    
    scanf("%d", &n);
    
    sum = sumOfDigits(n);
    printf("%d\n", sum);

	return 0;
}

int sumOfDigits(int num) {
    if (num <= 0) return 0;
    else {
        return ((num % 10) + sumOfDigits(num /= 10));
    }
}
