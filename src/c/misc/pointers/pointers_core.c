#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <inttypes.h>

int main(void) {
    printf ("\xD\xA");
    int var = 5;
    int *varPtr = &var; //contains address of var
    int **ptrToVarPtr = &varPtr; //contains address of varPtr
    int ***ptrToptrToVarPtr = &ptrToVarPtr; //contains address of ptrToVarPtr

    printf("addr of var = %p\n", &var);
    printf("addr of varPtr = %p\n", &varPtr);
    printf("addr of ptrToVarPtr = %p\n", &ptrToVarPtr);

    printf("contents of varPtr (addr  of var) = %p\n", varPtr);
    printf("deref varPtr (value  of var) = %d\n", *varPtr);
    printf ("\xD\xA");
    
    printf("contents of ptrToVarPtr (addr of varPtr) = %p\n", ptrToVarPtr);
    printf("deref of ptrToVarPtr (value of varPtr -> addr of var) = %p\n", *ptrToVarPtr);
    printf("deref deref of ptrToVarPtr (value of varPtr -> addr of var -> contents of var) = %d\n", **ptrToVarPtr);
    printf ("\xD\xA");

    printf("contents of ptrToptrToVarPtr (addr of ptrToVarPtr) = %p\n", ptrToptrToVarPtr);
    printf("deref of ptrToptrToVarPtr (value of ptrToVarPtr -> addr of ptrTovarPtr) = %p\n", *ptrToptrToVarPtr);
    printf("deref deref of ptrToptrToVarPtr (value of ptrToVarPtr -> value of varPtr -> addr of var -> contents of var) = %p\n", **ptrToptrToVarPtr);
    printf("deref deref of ptrToptrToVarPtr (value of ptrToVarPtr -> value of varPtr -> addr of var -> contents of var) = %d\n", ***ptrToptrToVarPtr);
    printf ("\xD\xA");
}


