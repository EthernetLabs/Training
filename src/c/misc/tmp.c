#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct point{
	int x;
	int y;
};

void printPoint(struct point);
void printPoly(struct point *, int);
//void initializePoly(struct point *, int);
struct point * initializePoly(struct point *, int);

int main(void) {
	int i, vertices;
	struct point *arrayPoints;

    scanf("%d", &vertices);

	arrayPoints = initializePoly(arrayPoints, vertices);

	for (i=0; i<vertices; i++) {
		//arrayPoints[i].x = -i; 
		//arrayPoints[i].y = i*i;
		(*(arrayPoints+i)).x = -i; 
		(*(arrayPoints+i)).y = i*i;
	}	

	printPoly(arrayPoints, vertices);
    
    free(arrayPoints);

    return 0;
}

void printPoint(struct point pt) {
    printf("(%d, %d)\n", pt.x, pt.y);
}

void printPoly(struct point *ptr, int N) {
    int i;
    for (i=0; i<N; i++) {
        printPoint(ptr[i]);
    }
}

// Write your initializePoly() function here
//void initializePoly(struct point *arrayPoints, int vertices) {
struct point * initializePoly(struct point *arrayPoints, int vertices) {
	return ((struct point *) malloc (vertices * sizeof(struct point)));
}
