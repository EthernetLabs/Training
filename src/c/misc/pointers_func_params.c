#include <stdio.h>

#define FEET 3.2808
#define POUNDS 0.002205
#define fmacro(val) (32 + 1.8 * val)

void m2f(double *, double *);
void g2p(double *, double *);
void c2f(double *, double *);


int main(void) {

    int numUnits, i=0;
	double meters, grams, celcius, valueIn, valueOut;
	unsigned char unit;

    scanf("%d", &numUnits);

	while (i < numUnits) {
    	scanf("%lf %c", &valueIn, &unit);
		switch(unit) {
			case 'm':
				m2f(&valueIn, &valueOut);
				printf("%.6lf %s\n", valueOut, "ft");
				break;
			case 'g':
				g2p(&valueIn, &valueOut);
				printf("%.6lf %s\n", valueOut, "lbs");
				break;
			case 'c':
				c2f(&valueIn, &valueOut);
				printf("%.6lf %s\n", valueOut, "f");
				break;
			default:
				printf("ERROR\n");
				break;
		}
		i++;
	}

    return 0;
}


void m2f(double *in, double *out) {
	*out = *in * 3.2808; 	
}


void g2p(double *in, double *out) {
	*out = *in * 0.002205; 
}

void c2f(double *in, double *out) {
	*out = fmacro(*in);
}
