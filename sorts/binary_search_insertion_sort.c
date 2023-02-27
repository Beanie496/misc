#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void Insert(int* startPointer, int* endPointer) // this inserts the value at endPointer into startPointer
{
    int temp = *endPointer;
    while (endPointer > startPointer) {
        endPointer--;
        *(endPointer + 1) = *endPointer;
    }
    *endPointer = temp;
}


int* Search(int* startPointer, int* endPointer)
{
    int* search = startPointer + (endPointer - startPointer)/2;
    int temp = *endPointer;

    // while there is still part of the array left to search, it repeatedly focuses on the half of the array that contains the value
    while (*search != temp && endPointer > startPointer) {
        if (*search < temp) {
            startPointer = search + 1;
            search = startPointer + (endPointer - startPointer)/2;
        } else if (*search > temp) {
            endPointer = search;
            search = startPointer + (endPointer - startPointer)/2;
        }
    }
    
    return search; // when there is nothing left to search or it's found the value, it returns the address that the value needs to be inserted in
}   


void Insertion_sort(int* startPointer, int length)
{
    int* search = startPointer;
    int i = 1;

    while (i < length) {
        search++;
        Insert(Search(startPointer, search), startPointer + i);
        i++;
    }
}


int main()
{
    int arrayLength = 100000; // set these
    int arrayRange = 1000;    // to whatever 
    int* array = malloc(arrayLength*4);
    int i;
    
    srand(time(0));
    
    
    *array = rand() % (arrayRange + 1);
    printf("%d", *array);
    for (i = 1; i < arrayLength; i++)
    {
        array[i] = rand() % (arrayRange + 1);
        printf(", %d", array[i]);
    }
    printf("\nSorting...\n");


    Insertion_sort(array, arrayLength);
    
     
    printf("\nSorted array:\n");
    printf("%d", *array);
    for (i = 1; i < arrayLength; i++)
    {
        printf(", %d", array[i]);
    }
    printf("\n[arrayLength = %d]\n", arrayLength);

    free(array);
    
    return 0;
}
