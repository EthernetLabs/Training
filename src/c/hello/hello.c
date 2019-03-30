#include "hello.h"

void main(void) {
    unsigned char temperature;
    temperature = 200;
    printf ("%d\xD\xA", temperature);
    
}

