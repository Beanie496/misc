#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
    int item;
    void* nodePtr;
} Node;


void* create_linked_list(int length);
void* reverse_linked_list(void* start);
void print_linked_list(void* start);


int main ()
{
    srand(time(NULL));

    int length = 10;
    int i;
    
    void* voidPtr = create_linked_list(length);
    Node* linkedListStart = voidPtr;
    
    print_linked_list(linkedListStart);
    printf("\nNow reversing.\n\n");

    voidPtr = reverse_linked_list(linkedListStart);
    linkedListStart = voidPtr;

    print_linked_list(linkedListStart);
    
    return 0;
}


void* create_linked_list(int length)
{
    Node* firstItem = malloc(sizeof(void*));
    
    Node* lastItem;
    
    firstItem->item = rand() % 11;
    lastItem = firstItem;

    for (int i = 1; i < length; i++) {
        Node* node = malloc(sizeof(void*));

        node->item = rand() % 11;
        lastItem->nodePtr = node;
        lastItem = node;
    }
    lastItem->nodePtr = 0;

    return firstItem;
}


void* reverse_linked_list(void* start)
{
    void** nextNodePtr;
    void** prevNodePtr;
    Node* currentItem = start;
    
    prevNodePtr = 0;

    while (currentItem->nodePtr != 0) {
        nextNodePtr = currentItem->nodePtr;
        currentItem->nodePtr = prevNodePtr;
        prevNodePtr = currentItem;
        currentItem = nextNodePtr;
    }

    currentItem->nodePtr = prevNodePtr;

    return currentItem;
}


void print_linked_list(void* start)
{
    Node* currentItem;
    currentItem = start;

    while (currentItem->nodePtr != 0) {
        printf("Item of the linked list is %d\n", currentItem->item);
        printf("Points to %p\n", currentItem->nodePtr);
        currentItem = currentItem->nodePtr;
    }
    printf("Item of the linked list is %d\n", currentItem->item);
    printf("Points to %d\n", currentItem->nodePtr);
}
