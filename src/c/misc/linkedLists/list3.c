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
    
	struct point pt1 = {1, 2, NULL};
    struct point pt2 = {-2, 3, NULL};
    struct point pt3 = {5, -4, NULL};
    struct point pt4 = {9, -9, NULL};
    struct point pt5 = {29, -19, NULL};
    struct point pt6 = {6, -6, NULL};
    struct point ptx = {4, 24, NULL};
    struct point * head, * tail;
    
    head = tail = &pt1;
    
    printf("DEBUG>> %p: \n", tail);
    tail = (struct point *) appendNode(tail, &pt2);
    printf("DEBUG>> %p: \n", tail);
    tail = (struct point *) appendNode(tail, &pt3);
    printf("DEBUG>> %p: \n", tail);
    tail = (struct point *) appendNode(tail, &pt4);
    printf("DEBUG>> %p: \n", tail);
    tail = (struct point *) appendNode(tail, &pt5);
    printf("DEBUG>> %p: \n", tail);
    tail = (struct point *) appendNode(tail, &pt6);
    printf("DEBUG>> %p: \n", tail);

    insertToList(&pt2, &ptx);

    delFromList(head, &pt4);

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

