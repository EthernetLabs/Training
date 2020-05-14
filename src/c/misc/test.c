#include <stdio.h>

int main(void) {
    
    int customers, fee=1;
    double total_cost, gas_cost;
    
    scanf("%d %lf", &customers, &gas_cost);
    if (customers > 0) {
        total_cost = (fee + gas_cost) / (customers+1);
    }
    else {
        total_cost = gas_cost;
    }
    printf("%.2lf\n", total_cost);
}
