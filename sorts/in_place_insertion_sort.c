#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void Insert(int* startPointer, int* searchingPointer)
{
    int temp = *searchingPointer;
    while((searchingPointer > startPointer) && (temp < *(searchingPointer - 1))) // this goes through the sorted list, starting at the end, looking for the right place
    {
	searchingPointer--;
        *(searchingPointer + 1) = *searchingPointer; // this moves up each item in the array that is larger than the value being sorted
    }
    *searchingPointer = temp; // aand inserts it
}


void Insertion_sort(int* startPointer, int length)
{
    int* search = startPointer;
    int i = 1; 
    while(i < length) //'i' is just a counter to tell the program when to stop
    {
	search++;
        if(*search < *(search - 1)) // the list is split into 2 — 'startPointer' is the start of the first (sorted) list, 'search' is the start of the second
	{
	    Insert(startPointer, search);
	}
	i++;
    }
}


int main ()
{
    int arrayLength = 100000; // set these
    int arrayRange = 1000;    // to whatever 
    int array[arrayLength];
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

    return 0;
}
