#include <stdio.h>

struct date {
        int year;
        int month;
        int day;
    };

void readDate(struct date *);
void printDate(struct date);
struct date advanceDay(struct date);

int main(void) {
	struct date today, tomorrow;
	readDate(&today);
	printDate(today);
    tomorrow = advanceDay(today);
    printDate(tomorrow);
	return 0;
}

void readDate(struct date *dateObject) {
	scanf("%d %d %d", &dateObject->year, &dateObject->month, &dateObject->day);
}

void printDate(struct date dateObject) {
	printf("%02d/%02d/%02d\n", dateObject.month, dateObject.day, dateObject.year);
}

struct date advanceDay(struct date dateObject) {
    if ((dateObject.month == 12) && (dateObject.day >= 31)) {
        dateObject.year++;
        dateObject.day = 1;
        dateObject.month = 1;
    }
    else if (dateObject.day == 31) {
        dateObject.month++;
        dateObject.day = 1;
    }

    return dateObject;
}

