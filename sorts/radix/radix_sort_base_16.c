#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void Counting_sort(int array[], int length, int digit)
{
    int valuesTotal[16] = {0};
    int* secondaryArray = malloc(length*4);
    int i;

    // This counts how many there are of each of the LSDs of the numbers
    for (i = 0; i < length; i++) {
	valuesTotal[(array[i] / digit) % 0x10]++;
    }
    
    for (i = 1; i < 16; i++) {
	valuesTotal[i] += valuesTotal[i - 1];
    }

    for (i = 14; i >= 0; i--) {
	valuesTotal[i + 1] = valuesTotal[i];
    }
    valuesTotal[0] = 0;

    for (i = 0; i < length; i++) {
        secondaryArray[valuesTotal[(array[i] / digit) % 0x10]] = array[i]; // I am so, so sorry
        valuesTotal[(array[i] / digit) % 0x10]++;
    }
    
    for (i = 0; i < length; i++) {
        array[i] = secondaryArray[i];
    } 
    free(secondaryArray);
}


void Radix_sort(int array[], int length)
{
    int maxNumber = 0;
    int i;
    
    // This finds the highest number so it knows how many times to iterate
    for (i = 0; i < length; i++) {
	if (array[i] > maxNumber) {
	    maxNumber = array[i];
	}
    }
    

    for (i = 1; i < maxNumber + 1; i *= 0x10) {
	Counting_sort(array, length, i);
    }
}


int main()
{
    int arrayLength = 100000000; // set these
    int arrayRange = 1000;       // to whatever
    int* array = malloc(arrayLength*4);
    int i;
    
    srand(time(0));
    
    
    *array = rand() % (arrayRange + 1);
    printf("%d", *array);
    for (i = 1; i < arrayLength; i++) {
        array[i] = rand() % (arrayRange + 1);
	    printf(", %d", array[i]);
    }
    printf("\nSorting...\n");


    Radix_sort(array, arrayLength);
    

    printf("\nSorted array:\n");
    printf("%d", *array);
    for (i = 1; i < arrayLength; i++) {
   	    printf(", %d", array[i]);
    }
    printf("\n[arrayLength = %d]\n", arrayLength);

    free(array);

    return 0;
}
