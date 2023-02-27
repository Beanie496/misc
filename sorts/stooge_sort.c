#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap (int* startPointer, int* endPointer)
{
    int temp = *startPointer;
    *startPointer = *endPointer;
    *endPointer = temp;
}


void stooge_sort(int array[], int arrayLength)
{
    if (arrayLength > 2) {
        stooge_sort(array, 2*(arrayLength + 1)/3);
        stooge_sort(array + (arrayLength)/3, 2*(arrayLength + 1)/3);
        stooge_sort(array, 2*(arrayLength + 1)/3);
    } else {
        if (array[0] > array[1])
            swap(array, array + 1);
    }
}


int main ()
{
    int arrayLength = 2000; // set these
    int arrayRange = 100;   // to whatever 
    int array[arrayLength];
    int i;
    
    srand(time(0));
    
    
    array[0] = rand() % (arrayRange + 1);
    printf("%d", array[0]);
    for (i = 1; i < arrayLength; i++)
    {
        array[i] = rand() % (arrayRange + 1);
        printf(", %d", array[i]);
    }
    printf("\nSorting...\n");

    
    stooge_sort(array, arrayLength);
    
     
    printf("\nSorted array:\n");
    printf("%d", array[0]);
    for (i = 1; i < arrayLength; i++)
        printf(", %d", array[i]);
    printf("\n[arrayLength = %d]\n", arrayLength);

    return 0;
}
