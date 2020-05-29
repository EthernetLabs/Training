#include <stdio.h>
#include <stdlib.h>

struct point{
    int x;
    int y;
    struct point * next;
};

void printPoints(struct point *);
void * appendNode(struct point *, struct point *);
void appendToList(struct point *, struct point *);
void insertToList(struct point *, struct point *);
void delFromList(struct point *, struct point *);

int main(void) {
   
    int num, i;
    struct point * head, * tail, * node;
   
    scanf("%d", &num);

    //malloc
    head = (struct point *) malloc (num * sizeof(struct point));
    tail = head;

    for (i=0; i<num; i++) {
        printf("i: %d\n", i);
        printf("DEBUG>> addr head: %p: \n", head);
        printf("DEBUG>> addr tail: %p: \n", tail);
        printf("x: ");
        scanf("%d", &tail->x);         
        printf("y: ");
        scanf("%d", &tail->y);
        
        if (i == (num-1)) {
            tail->next = NULL;
            printf("DEBUG>> addr of last tail: %p\n", tail);
        }
        else {
            tail->next = tail+1;
            printf("DEBUG>> addr of tail+1: %p\n", tail);
            tail++;
            printf("DEBUG>> addr of mid tail++: %p\n", tail);
        }
        puts("");
    }
    
    //insertToList(&pt2, &ptx);

    //delFromList(head, &pt4);

    printPoints(head);
    
	return 0;
}

void * appendNode(struct point *tail, struct point *dst) {
    (*tail).next = dst;
    tail = dst;
    return (void *) tail;
}

void insertToList(struct point *src, struct point *node) {
    node->next = src->next;
    src->next = node;
}

/*
 * Head = start
 * Find the node while saving pointer to previous node
 *  if node found
 *      set the previous->next to node->next
 *      free(node)
 *
 *      Ref: https://learning.oreilly.com/library/view/the-garbage-collection/9781315388007/xhtml/14_Chapter01.xhtml
 *    
 *      Premature deletion of an object may lead to errors. Here B has been freed. 
 *      The live object A now contains a dangling pointer. The space occupied by C has leaked: 
 *      C is not reachable but it cannot be freed.
 *
 */
void delFromList(struct point *head, struct point *node) {
    int flag=0;

    for (;flag != 1;) {
        if (head->next == node) {
            head->next = (head->next)->next; //head->next = (*(head->next)).next;
            flag = 1;
        }
        head = (*head).next;
    }
}

void printPoints(struct point *head) {
    struct point *tail;

    tail = head;

    while (tail != NULL) {
		printf("(%d, %d)\n", (*tail).x, (*tail).y);
        tail = (*tail).next;
    }
}

