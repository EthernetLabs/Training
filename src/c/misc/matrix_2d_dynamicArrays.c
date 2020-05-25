#include <stdio.h>
#include <malloc.h>

#define FIRE_THRESHOLD 1001
#define WATCH_THRESHOLD_START 100
#define WATCH_THRESHOLD_END 1000

int * allocateIntArray(int);
int ** allocateIntStarArray(int);
void freeMem(int, int **);

int main(void) {
    //row       -> width
    //column    -> length
    int i, j, zone_length, zone_width, total_zones;
    int **avg_temperatures;
    
    scanf("%d", &zone_length);
    scanf("%d", &zone_width);

    //malloc avg_temperatures[width/row][length/column]
    avg_temperatures = allocateIntStarArray(zone_width);
    for (i=0; i<zone_width; i++)
        avg_temperatures[i] = allocateIntArray(zone_length);
        //avg_temperatures[i] = (int *) malloc(zone_length * sizeof(int));

    for (i=0; i<zone_width; i++) {
        for (j=0; j<zone_length; j++)
            scanf("%d", &avg_temperatures[i][j]);
    }

    for (i=0; i<zone_width; i++) {
        for (j=0; j<zone_length; j++)
            if (avg_temperatures[i][j] >= FIRE_THRESHOLD)
                printf("[X]");
            else if ((avg_temperatures[i][j] >= WATCH_THRESHOLD_START) && (avg_temperatures[i][j] <= WATCH_THRESHOLD_END))
                printf("[*]");
            else
                printf("[ ]");
        printf("\xD\xA");
    }
    printf("\xD\xA");

    freeMem(zone_width, avg_temperatures);

    return 0;
}

int * allocateIntArray(int num){
    int * ptr = (int *) malloc(num * sizeof(int));
    return ptr;
}

int ** allocateIntStarArray(int num){
    int ** ptr = (int **) malloc(num * sizeof(int *));
    return ptr;
}

void freeMem(int rows, int **array) {
    int i;
    for(i=0; i<rows; i++)
        free(array[i]);
    free(array);
}
