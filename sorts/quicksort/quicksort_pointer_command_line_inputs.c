#include <stdio.h>
#include <stdlib.h>


void swap(int* start, int* end) // receives two addresses and swaps the values of them
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


int main(int argc, char* argv[])
{
    const int arrayLength = argc - 1;
    int highest = 0;
    int i;
    int trueHighestValue;
    int* array = malloc(arrayLength*sizeof(int));
    float mean = 0;


    for (i = 1; i < argc; i++)
        array[i - 1] = atoi(argv[i]);


    partition(array, array + arrayLength - 1);


    printf("Sorted array is:\n");
    printf("%d", *array);
    for(i = 1; i < arrayLength; i++)
        printf(", %d", array[i]);
    printf("\n[arrayLength = %d]\n", arrayLength); 
    
    
    for (i = 0; i < arrayLength; i++)
       mean += array[i];
    mean /= arrayLength;
    printf("Mean is %f", mean);


    for (i = 0; i < arrayLength; i++)
        if (array[i] > highest)
            highest = array[i];
    int* modeCounter = malloc(sizeof(int)*highest);

    for (i = 0; i < arrayLength; i++)
        modeCounter[array[i]]++;
   
    highest = 0;
    for (i = 0; i < sizeof(modeCounter)/4; i++)
        if (modeCounter[i] > highest) {
            highest = array[i];
            trueHighestValue = i + 1;
        }
    printf("Mode is %d", trueHighestValue);


    printf("Lower quartile is %d\n", array[arrayLength/4]); // array[n] is the (n + 1)th item of data

    if (arrayLength % 2 == 1)
        printf("Median is %d\n", array[arrayLength/2]);
    else
        printf("Median is %f\n", (float)(array[arrayLength/2 - 1] + array[arrayLength/2])/2);
    
    printf("Upper quartile is %d\n", array[3*arrayLength/4]);
    printf("IQ range is %d\n", array[3*arrayLength/4] - array[arrayLength/4]);
    printf("Range is %d\n", array[arrayLength - 1] - array[0]);


    free(array);

    return 0;
}
