#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void Counting_sort(int array[], int length)
{
    int* secondaryArray = malloc(length*4);
    int maxNumber = 0;
    int i;
    
    // This finds the highest number so it knows how long to make the counting list
    for (i = 0; i < length; i++) {
	if (array[i] > maxNumber) {
	    maxNumber = array[i];
	}
    }
    int countingList[maxNumber + 1]; // '+1' because it's 0-maxNumber, not 1-

    for (i = 0; i < maxNumber + 1; i++) {
	countingList[i] = 0;
    }

    for (i = 0; i < length; i++) {
	countingList[array[i]]++;
    }

    for (i = 1; i < maxNumber + 1; i++) {
	countingList[i] += countingList[i - 1];
    }

    for (i = maxNumber; i >= 0; i--) {
	countingList[i + 1] = countingList[i];
    }
    countingList[0] = 0;

    for (i = 0; i < length; i++) {
        secondaryArray[countingList[array[i]]] = array[i];
        countingList[array[i]]++;
    }
    
    for (i = 0; i < length; i++) {
        array[i] = secondaryArray[i];
    }
    free(secondaryArray);
}


int main()
{
    int arrayLength;
    printf("Enter length of array: ");
    scanf("%d", &arrayLength);
    printf("\n");
    int arrayRange = 1000; // set this to whatever 
    int* array = malloc(arrayLength*4);
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


    Counting_sort(array, arrayLength);
    

    printf("\nSorted array:\n");
    printf("%d", *array);
    for (i = 1; i < arrayLength; i++) {
   	printf(", %d", array[i]);
    }
    printf("\n[arrayLength = %d]\n", arrayLength);

    free(array); // this is pointless because the program ends here anyway but whatever

    return 0;
}
