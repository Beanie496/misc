#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int* Merge(int* l1Start, int* l2Start, int length)
{
    int* secondaryArray = malloc(4*length); // 4 because it's an array of ints
    // these are so the two arrays can be freed after they have been merged
    int* l1TempStart = l1Start;
    int* l2TempStart = l2Start;
    int* l1End = l1Start + (length >> 1) - 1;
    int* l2End = l2Start + (length - 1 >> 1);
    int i = 0;


    while ((l1TempStart <= l1End) && (l2TempStart <= l2End)) {

        if (*l2TempStart < *l1TempStart) {
	        secondaryArray[i] = *l2TempStart;
	        l2TempStart++;
	    } else {
	        secondaryArray[i] = *l1TempStart;
	        l1TempStart++;
	    }

	    i++;

    }

    if (l2TempStart > l2End) { // If all of one list has been exhausted, this if statement dumps the rest of the other list in the secondary array.

        while (!(l1TempStart > l1End)) {
	        secondaryArray[i] = *l1TempStart;
	        l1TempStart++;
	        i++;
	    }

    } else {

        while (!(l2TempStart > l2End)) {
	        secondaryArray[i] = *l2TempStart;
	        l2TempStart++;
	        i++;
	    }

    }
    
    if (length > 2) {
        if (length > 3)
            free(l1Start);
        free(l2Start);
    }
    

    return (secondaryArray);
}


int* MergeSort(int* startPointer, int length)
{
    int halfOfLength = length >> 1; // This saves computing it every time. Also, I want the floor of 'length/2' which why it's of type 'int'.
    int* firstArray = startPointer;
    int* secondArray = startPointer + halfOfLength;

    if (length > 2) {
        if (length > 3)
            firstArray = MergeSort(firstArray, halfOfLength); // 'length/2' ensures it will be half of or a little under half of the total length... 

        secondArray = MergeSort(secondArray, (length + 1) >> 1); // ...'(length + 1)/2' ensures it will be a half of or a little over half of the total length.
     }
    
    return Merge(firstArray, secondArray, length);
}


int main ()
{
    int arrayLength = 10000000; // set these
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

    
    array = MergeSort(array, arrayLength);

 
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
