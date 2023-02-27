#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int *start, int* end) // receives two addresses and swaps the values of them
{
	int temp = *end;
	*end = *start;
	*start = temp;
}


void partition (int *start, int* end)
{
	if (start >= end - 1)
		return;

	int *pivot = end;
	int *p1 = start;
	int *p2 = p1;

	// this partitions the array
	while (++p2 < pivot)
		if (*p2 < *pivot)
			swap(p1++, p2);
	
	swap(++p1, pivot);

	partition(start, p1 - 1);
	partition(p1 + 1, end);
}


int main()
{
	int arrayLength = 1000000; // set these
	int arrayRange = 1000;     // to whatever 
	int *array = malloc(arrayLength*4);
	int i;
	
	
	srand(time(0));

	
	array[0] = rand() % (arrayRange + 1);
	printf("%d", array[0]);
	// initialising array with random numbers from 0 to arrayRange
	for (i = 1; i < arrayLength; i++) {
		array[i] = rand() % (arrayRange + 1);
		printf(", %d", array[i]);
	}
	printf("\nSorting...\n"); 
	 

	partition(array, array + arrayLength - 1);
   

	printf("Sorted array is:\n");
	printf("%d", array[0]);
	for(i = 1; i < arrayLength; i++)
		printf(", %d", array[i]);
	printf("\n[arrayLength = %d]\n", arrayLength);


	free(array);


	return 0;
}
