#include <stdio.h>

struct node {
	int a;
	int b;
};

int main() {
	struct node p;
    int* intptr; char* charptr;

    int intVar = 99;

    int *ptrIntVar = &intVar; //& what it points to, * value of what & points to - contained within
    int **ptrPtrIntVar = &ptrIntVar;
    int ***ptrPtrPtrIntVar = &ptrPtrIntVar;
    int ****ptrPtrPtrPtrIntVar = &ptrPtrPtrIntVar;

	printf("Address of node = %p\n",&p);
	printf("Address of member variable a = %p\n", &(p.a));
	printf("Address of member variable b = %p\n", &(p.b));
    puts("");

	printf("Address of intVar = %p\n",              &intVar);
	printf("Address of ptrIntVar = %p\n",           &ptrIntVar);
	printf("Address of ptrPtrIntVar = %p\n",        &ptrPtrIntVar);
	printf("Address of ptrPtrPtrIntVar = %p\n",     &ptrPtrPtrIntVar);
	printf("Address of ptrPtrPtrPtrIntVar = %p\n",  &ptrPtrPtrPtrIntVar);
	printf("Value of ptrPtrPtrPtrIntVar (addr of ptrPtrPtrIntVar) = %p\n",  ptrPtrPtrPtrIntVar);
	printf("Value of ptrPtrPtrIntVar (addr of ptrPtrIntVar) = %p\n",        ptrPtrPtrIntVar);
	printf("Value of ptrPtrIntVar (addr of ptrIntVar) = %p\n",              ptrPtrIntVar);
	printf("Value of ptrIntVar (addr of IntVar) = %p\n",                    ptrIntVar);
	printf("Value of intVar (%d) = %d\n",                                   intVar, intVar);
	printf("Value of *ptrPtrPtrPtrIntVar (addr of ptrPtrIntVar) = %p\n",    *ptrPtrPtrPtrIntVar);
	printf("Value of *ptrPtrPtrIntVar (addr of ptrIntVar) = %p\n",          *ptrPtrPtrIntVar);
	printf("Value of *ptrPtrIntVar (addr of IntVar) = %p\n",                *ptrPtrIntVar);
	printf("Value of *ptrIntVar (value of intVar) = %d\n",                  *ptrIntVar);
	printf("Value of intVar = %d\n",                                        intVar);

	return 0;
}

