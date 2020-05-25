#include <stdio.h>

struct inner_node {
	int a;
	int b;
};

struct node {
    int *a;
    int *b;
    struct inner_node* in_node;
};

int main() {
	struct node xnode;
	printf("Address of node = %p\n",&xnode);
	printf("Address of member variable a = %p\n", &(p.a));
	printf("Address of member variable b = %p\n", &(p.b));
	return 0;
}

