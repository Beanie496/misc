#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void Merge(int* l1Start, int* l2Start, int length)
{
    int* secondaryArray = malloc(4*length); // 4 because it's an array of ints
    int* arrayStart = l1Start;
    int* l1End = l2Start - 1;
    int* l2End = l1Start + length - 1;
    int i = 0;

    while ((l1Start <= l1End) && (l2Start <= l2End)) {

        if (*l2Start < *l1Start) {
	        secondaryArray[i] = *l2Start;
	        l2Start++;
	    } else {
	        secondaryArray[i] = *l1Start;
	        l1Start++;
	    }

	    i++;

    }

    if (l2Start > l2End) { // If all of one list has been exhausted, this if statement dumps the rest of the other list in the secondary array.

        while (!(l1Start > l1End)) {
	        secondaryArray[i] = *l1Start;
	        l1Start++;
	        i++;
	    }

    } else {

        while (!(l2Start > l2End)) {
	        secondaryArray[i] = *l2Start;
	        l2Start++;
	        i++;
	    }

    }

    for (i = 0; i < length; i++)
        arrayStart[i] = secondaryArray[i];

    free(secondaryArray);
}


void MergeSort(int* startPointer, int length)
{

    int halfOfLength = length/2; // This saves computing it every time. Also, I want the floor of 'length/2' which why it's of type 'int'.

    if (length > 2) {

        if (length > 3) // If 'length' is exactly 3, this first function doesn't need to be called because the list (which is length 1) is already sorted.
            MergeSort(startPointer, halfOfLength); // 'length/2' ensures it will be half of or a little under half of the total length... 

	    MergeSort(startPointer + halfOfLength, (length + 1)/2); // ...'(length + 1)/2' ensures it will be a half of or a little over half of the total length.
    }
    
    Merge(startPointer, startPointer + halfOfLength, length);
}


int main ()
{
    int arrayLength = 10000000; //set these
    int arrayRange = 1000;      // to whatever 
    int* array = malloc(arrayLength*4);
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

    
    MergeSort(array, arrayLength);
    
       
    printf("\nSorted array:\n");
    printf("%d", array[0]);
    for (i = 1; i < arrayLength; i++)
    {
   	    printf(", %d", array[i]);
    }  
    printf("\n[arrayLength = %d]\n", arrayLength);

    free(array);

    return 0;
}
