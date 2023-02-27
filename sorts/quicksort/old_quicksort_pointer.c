#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void swap(int* start, int* end) // receives two addresses and swaps the values of them
{
    int temp = *end;
    *end = *start;
    *start = temp;
}


void partition(int* startPointer, int* endPointer)
{
    int* pivot = startPointer;
    // printf("\npivot is %d", *pivot);
    int* tempStart = startPointer;
    // printf("\nstartPointer is %p", startPointer);
    int* tempEnd = endPointer;
    // printf("\nendPointer is %p", endPointer);
    
    while (tempStart != tempEnd)
    {
        
        if (*tempStart > *tempEnd)
        {
            swap(tempStart, tempEnd);
        }
        
        if (tempStart < pivot)
        {
            tempStart++;
        }
        
        if (tempEnd > pivot)
        {
            tempEnd--;
        }
        
    }
    
    // printf("\ntempStart is %d, address is %p", *tempStart, tempStart);
    // printf("\ntempEnd is %d, address is %p\n", *tempEnd, tempEnd);
    
    // both sides of the pivot only get partitioned if they are at least 2 elements in length
    if (startPointer < tempEnd - 1)
    {
        partition(startPointer, tempEnd - 1);
    }
    
    if (endPointer > tempStart + 1)
    {
        partition(tempStart + 1, endPointer);
    }
}


int main()
{
    int arrayLength = 100000; //set these
    int arrayRange = 1000;       // to whatever 
    int array[arrayLength];
    int i;
    srand(time(0));
    
    *array = rand() % (arrayRange + 1);
    printf("%d", *array);
    for (i = 1; i < arrayLength; i++) {
        array[i] = rand() % (arrayRange + 1);
	printf(", %d", array[i]);
    }
    printf("\n[Finished printing array]");
    printf("\nSorting...\n");


    partition(array, array + arrayLength - 1);
    

    printf("\nSorted array:\n");
    printf("%d", *array);
    for (i = 1; i < arrayLength; i++) {
   	printf(", %d", array[i]);
    }
    printf("\n[arrayLength = %d]\n", arrayLength);

    return 0;
}
