#include <stdio.h>

#define MAX 51

int main(void) {
    int i=0, j, found = 0, counter = 0, strlen = 0; 
    char _word[MAX] = {'\0'}, tmp = '\0', counted[MAX/2] = {'\0'};

    scanf("%s", _word);
    
    while (_word[i] != '\0') {
        strlen++;
        i++;
    }

    for (j=0; j < strlen-1; j++) {
        for (i=0; i < strlen-1; i++) {
            if (_word[i] > _word[i+1]) {
                tmp = _word[i];
                _word[i] = _word[i+1];
                _word[i+1] = tmp;
            }
        }
    }
    
    for (i=0; i<strlen-1; i++) {
        if(_word[i]==_word[i+1]) {

            for (j=0; j<strlen-1; j++) {
                if ((_word[i] == counted[j]) && (_word[i] != '\0')) {
                    found = 1;
                    break;
                }
            }

            if (found != 1) {
                counted[counter] = _word[i];
                counter++;
            }
            
            found = 0;

        }
    };

    printf("%d\n", counter);

    return 0;   
}
