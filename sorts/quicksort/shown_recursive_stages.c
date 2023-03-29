#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int* start, int* end) // receives two addresses and swaps the values of them
{
    int temp = *end;
    *end = *start;
    *start = temp;
}


void partition (int* startPointer, int* endPointer, int* iterationPointer)
{
    int iteration = *iterationPointer;
    iteration++;

    int* pivot = endPointer;
    int* tempStart = startPointer;
    while (*tempStart < *pivot) { // this ensures that all the elements before the start pointer are below the pivot
        tempStart++;
    }
    int* searching = tempStart + 1;


    // ##### PARTITIONING ####

    if (tempStart != pivot) {
        while (searching < pivot) {
            if (*searching < *pivot) { // the searching pointer skips over all the values that are higher/equal but moves the ones that are lower to the bottom of the array
                swap(searching, tempStart);
                tempStart++;
            }
            searching++;
        }
    }

    // ########


    swap(tempStart, pivot);

    printf("\nPass %d\n", iteration);
    printf("%d", *startPointer);
    for(int i = 1; i < (endPointer - startPointer + 1); i++) {
        printf(", %d", *(startPointer + i));
    }
    printf("\n");

    // #### RECURSING ####

    // both sides of the pivot only get partitioned if they are at least 2 elements in length
    if (startPointer < tempStart - 1) {
        if (startPointer == tempStart - 2) { // if it's only 2 in length, it just swaps them if they're out of order
            if (*startPointer > *(startPointer + 1)) {
                swap(startPointer, startPointer + 1);
            }
            iteration++;
            printf("\nPass %d\n", iteration);
            printf("%d, %d\n", *startPointer, *(startPointer + 1));
        } else {
            partition(startPointer, tempStart - 1, &iteration);
        }
    } else {
        iteration++;
        printf("\nPass %d\n", iteration);
        printf("%d\n", *startPointer);
    }

    if (endPointer > tempStart + 1) {
        if (endPointer == tempStart + 2) {
            if (*endPointer < *(endPointer - 1)) {
                swap(endPointer, endPointer - 1);
            }
            iteration++;
            printf("\nPass %d\n", iteration);
            printf("%d, %d\n", *(endPointer - 1), *endPointer);
        } else {
            partition(tempStart + 1, endPointer, &iteration);
        }
    } else {
        iteration++;
        printf("\nPass %d\n", iteration);
        printf("%d\n", *endPointer);
    }

    // ########

    *iterationPointer = iteration;
}


int main()
{
    int iteration = 0;
    int arrayLength = 10000;
    int arrayRange = 100;
    int array[arrayLength];
    int i;

    srand(time(NULL));

    array[0] = rand() % (arrayRange + 1);
    printf("%d", array[0]);
    for(i = 1; i < arrayLength; i++) {
        array[i] = rand() % (arrayRange + 1);
        printf(", %d", array[i]);
    }
    printf("\n");


    partition(array, array + arrayLength - 1, &iteration);

    printf("\nFinished array:\n");
    printf("%d", array[0]);
    for(int i = 1; i < arrayLength; i++) {
        printf(", %d", array[i]);
    }
    printf("\n");

    return 0;
}
