#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#define LinkedListFree(ptr) _Free((void**)&(ptr))

int _ERR = ENOMEM;

//Function prototypes
typedef void *data;

/*
Node:
	Contains data and pointer to next node
*/
struct _node {
    data* _data;
    struct _node *next;
};

typedef struct _node Node;

struct _linkedList {
	Node* head;
};

typedef struct _linkedList LinkedList;

//Function prototypes
void * allocateMem();
void addNode(LinkedList*, data);
data removeNode(LinkedList*);
uint64_t newList();
uint8_t delList();

/*
Several issues surround the free function that encourage some
programmers to create their own version of this function. 
The free function does not check the pointer passed to see whether 
it is NULL and does not set the pointer to NULL before it returns. 
Setting a pointer to NULL after freeing is a good practice.
*/
void _Free(void **ptr) {
}

void * allocateMem() {
    static LinkedList *ListNode;
    ListNode = (LinkedList *) malloc(sizeof(LinkedList));
    ListNode->head = NULL;
	if(ListNode != NULL) {
        printf ("returning ListNode addr = %p\n", ListNode);
		return ListNode;
	} 
	else {
        return &_ERR;
	}
}

void addNode(LinkedList* list, data _data) {    
	Node *node = (Node*)malloc(sizeof(Node));    
	node->_data = (data *)_data;    
	if(list->head == NULL) {        
		list->head = node;        
		node->next = NULL;    
	} 
	else {        
		node->next = list->head;        
		list->head = node;    
	}
}


int main(void) {

    LinkedList *ListNode = NULL;
    ListNode = (LinkedList *) allocateMem();
    printf ("addr of ListNode addr = %p\n", ListNode);
    //ListNode = (LinkedList *) malloc(sizeof(LinkedList));
    //ListNode->head->_data = 100;
    //printf ("data is %d\n", ListNode->head->data);
}


