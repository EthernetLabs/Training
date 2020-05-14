/*
http://web.mit.edu/iap-security/www/problem.pdf
*/

#include <stdio.h>

int main() {
	int leet=0;
	char buf[4];

	puts("Hello, What’s your name?");
	gets(buf);

	printf("Hello, %s\n", buf);

	
	printf("leet is %d\n", leet);

    //Ctrl_,  , !
	if(leet == 313233) {
		printf("Congratulations! If this did something nasty, like change grades, you would have won!\n");
	}

	return 0;
}
