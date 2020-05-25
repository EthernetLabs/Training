#include <stdio.h>

int main(void) {
    int val, totalbytes, megabytes=0, kilobytes=0, bytes=0;
    char dType;

    scanf("%c %d", &dType, &val);

        switch(dType) {
            case 'i':
                totalbytes = sizeof(int) * val;
                megabytes = totalbytes/(1000*1000);
                kilobytes = (totalbytes%1000000)/1000;
                bytes = totalbytes%1000;
                if (megabytes !=0) printf("%d MB and ", megabytes);
                if (kilobytes !=0) printf("%d KB and ", kilobytes);
                printf("%d B", bytes);
                break;
            case 'd':
                totalbytes = sizeof(double) * val;
                megabytes = totalbytes/(1000*1000);
                kilobytes = (totalbytes%1000000)/1000;
                bytes = totalbytes%1000;
                if (megabytes !=0) printf("%d MB and ", megabytes);
                if (kilobytes !=0) printf("%d KB and ", kilobytes);
                printf("%d B", bytes);
                break;
            case 'c':
                totalbytes = sizeof(char) * val;
                megabytes = totalbytes/(1000*1000);
                kilobytes = (totalbytes%1000000)/1000;
                bytes = totalbytes%1000;
                if (megabytes !=0) printf("%d MB and ", megabytes);
                if (kilobytes !=0) printf("%d KB and ", kilobytes);
                printf("%d B", bytes);
                break;
            case 's':
                totalbytes = sizeof(short) * val;
                megabytes = totalbytes/(1000*1000);
                kilobytes = (totalbytes%1000000)/1000;
                bytes = totalbytes%1000;
                if (megabytes !=0) printf("%d MB and ", megabytes);
                if (kilobytes !=0) printf("%d KB and ", kilobytes);
                printf("%d B", bytes);
                break;
            default:
                break;
        }
    puts(""); 
	return 0;
}

