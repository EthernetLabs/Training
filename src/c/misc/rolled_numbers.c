#include <stdio.h>
#include <stdlib.h>

/*
int ones = n%10;
int tens = (n/10)%10;
int hundreds = (n/100)%10
int thousands = (n/1000);
*/

int main(void) {

    int i, red, yellow, green, rolls, total = 0;
	int *avg_array;

    //G Y R
    scanf("%d", &rolls);
    avg_array = (int*) malloc(rolls * sizeof(int));

    for (i=0; i < rolls; i++) {
        scanf("%d %d %d", &red, &yellow, &green);
		if ((green > 6) || (yellow > 6) || (red > 6)) {
			printf ("Invalid input\n");
			return 1;
		};
		*(avg_array + i) = (green * 100) + (yellow * 10) + (red * 1);

    };
    
    for (i=0; i < rolls; i++) {
		double curr_avg = 0;
        total += *(avg_array + i);
		curr_avg = (double) total/(i + 1);
        printf("you rolled: %d, current average: %.1lf\n", avg_array[i], curr_avg);
    };
        
    return 0;
}
