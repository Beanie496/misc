#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int* start, int* end) // receives two addresses and swaps the values of them
{
    int temp = *end;
    *end = *start;
    *start = temp;
}


void partition (int* startPointer, int* endPointer)
{
    int* pivot = endPointer;
    int* tempStart = startPointer;
    
    while (*tempStart < *pivot) { // this ensures all the elements below tempStart are smaller than the array
		tempStart++;
	}
    
    int* searching = tempStart + 1;
    
    
    // this partitions the array
    while (searching < pivot) {
        if (*searching < *pivot) {
            swap(searching, tempStart);
            tempStart++;
        }
        searching++;
    }
    
    
    // there's a chance they're the same but it would probably be more expensive to check
    swap(tempStart, pivot);



    // both sides of the pivot only get partitioned if they are at least 2 elements in length
    if (startPointer < tempStart - 1) {
        if (startPointer == tempStart - 2) { // if this half is only 2 in length, it just swaps them if they're out of order

            if (*startPointer > *(startPointer + 1))
                swap(startPointer, startPointer + 1);
        }
	    else
            partition(startPointer, tempStart - 1);
    }
    
    if (endPointer > tempStart + 1) {
	    if (endPointer == tempStart + 2) { // again, if that half is only 2 in length, it just swaps them if needed

	        if (*endPointer < *(endPointer - 1))
		        swap(endPointer, endPointer - 1);
        }
	    else
            partition(tempStart + 1, endPointer);
    }
}


int main()
{
    int arrayLength = 1000000; // set these
    int arrayRange = 1000;     // to whatever 
    int* array = malloc(arrayLength*4);
    int i;
    
    
    srand(time(0));

    
    array[0] = rand() % (arrayRange + 1);
    printf("%d", array[0]);
    for(i = 1; i < arrayLength; i++)
    {
        array[i] = rand() % (arrayRange + 1);
        printf(", %d", array[i]);
    } // initialising array with random numbers from 0 to 100
    printf("\nSorting...\n"); 
     

    partition(array, array + arrayLength - 1);
   

    printf("Sorted array is:\n");
    printf("%d", array[0]);
    for(i = 1; i < arrayLength; i++)
    {
        printf(", %d", array[i]);
    }
    printf("\n[arrayLength = %d]\n", arrayLength);


    free(array);


    return 0;
}
