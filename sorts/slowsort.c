#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int* start, int* end)
{
    int temp = *end;
    *end = *start;
    *start = temp;
}


void slowsort(int array[], int length)
{
    if (length > 2) {
        
        slowsort(array, length/2);
        slowsort(array + length/2, (length + 1)/2);

        if (array[length/2 - 1] > array[length - 1])
            swap(array + length/2 - 1, array + length - 1);

        slowsort(array, length - 1);

    } else 
        if (array[0] > array[1])
            swap(array, array + 1);
         
}


int main()
{
    int arrayLength = 300;
    int arrayRange = 100;
    int array[arrayLength];
    int i;
    
    srand(time(NULL));


    array[0] = rand() % (arrayRange + 1);
    printf("%d", array[0]);
    for (i = 0; i < arrayLength; i++) {
        array[i] = rand() % (arrayRange + 1);
        printf(", %d", array[i]);
    }
    printf("\nSorting...\n");


    slowsort(array, arrayLength);


    printf("\nSorted array:\n");
    printf("%d", array[0]);
    for (i = 0; i < arrayLength; i++)
        printf(", %d", array[i]);
    printf("\n[arrayLength = %d]\n", arrayLength);

    return 0;
}
