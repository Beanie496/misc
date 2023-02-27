#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>


struct inputArrayInfo {
    int* arrayStartPointer;
    int arrayLength;
};

int threadsAvailable;


void Merge(int* l1Start, int* l2Start, int length)
{
    int* secondaryArray = malloc(4*length);
    
    int* mainArrayStart = l1Start;
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

    // If the second list's start pointer has gone past its end, that means that it's gone through all its elements. That means that list 1 still has elements in it.
    if (l2Start > l2End) {

        while (l1Start <= l1End)
        {
            secondaryArray[i] = *l1Start;
            l1Start++;
            i++;
        }

    // And vice versa.
    } else {
    
        while (l2Start <= l2End)
        {
            secondaryArray[i] = *l2Start;
            l2Start++;
            i++;
        }
    }


    for (i = 0; i < length; i++)
        mainArrayStart[i] = secondaryArray[i];

    free(secondaryArray);
}


void MergeSort(int* startPointer, int length)
{
    int halfOfLength = length/2; // I want the floor of 'length/2' which why it's of type 'int'.

    // If 'length' is exactly 2, it just needs to merge the two items
    if (length > 2) {

        // If 'length' is exactly 3, this first function doesn't need to be called because the list (which is length 1) is already sorted
        if (length > 3) {

            // 'length/2' (halfOfLength) ensures it will be half of or a little under half of the total length...
            MergeSort(startPointer, halfOfLength);
        }
        // ...and '(length + 1)/2' ensures it will be a half of or a little over half of the total length.
        MergeSort(startPointer + halfOfLength, (length + 1)/2);
    }

    Merge(startPointer, startPointer + halfOfLength, length);
}


void* threaded_merge_sort_init(void* inputArgsVoidPointer)
{
    struct inputArrayInfo *inputArgs = inputArgsVoidPointer;

    int* startPointer = inputArgs->arrayStartPointer;
    int length = inputArgs->arrayLength;


    MergeSort(startPointer, length);
}


void* thread_node_tree_initialisation(void* inputArgsVoidPointer)
{
    /* Each time this function is called, it either performs a merge sort on the part
     * of the array it's given, or, if there still aren't enough recursed functions
     * (there will be 2**depth currently-running functions, thanks to each function
     * creating a thread when recursed) it calls a thread to sort one half of the array
     * (by recursion, if depth is not high enough, or just by sorting it)  while it
     * sorts the other half. When a given thread has finished, it just terminates.
     */
    
    struct inputArrayInfo *inputArgs = inputArgsVoidPointer; // You can't dereference the void pointer directly

    
    if (threadsAvailable > 0) {;

        threadsAvailable--; // It's effectively reserving the thread before it creates it


        struct inputArrayInfo l1ArrayParameters;
        struct inputArrayInfo l2ArrayParameters;

        l1ArrayParameters.arrayStartPointer =  inputArgs->arrayStartPointer;
        l1ArrayParameters.arrayLength       =  inputArgs->arrayLength/2;
        
        l2ArrayParameters.arrayStartPointer =  inputArgs->arrayStartPointer + l1ArrayParameters.arrayLength;
        l2ArrayParameters.arrayLength       = (inputArgs->arrayLength + 1)/2;


        pthread_t thread;
        pthread_create(&thread, NULL, thread_node_tree_initialisation, &l1ArrayParameters);

        thread_node_tree_initialisation(&l2ArrayParameters); // Calling the function for the other half directly

        pthread_join(thread, NULL);
        
        Merge(l1ArrayParameters.arrayStartPointer,
              l2ArrayParameters.arrayStartPointer,
              inputArgs->arrayLength);

    } else
        threaded_merge_sort_init(inputArgs); // Calling the function for the whole array, not just the second half

    return NULL;
}


int main ()
{
    int arrayLength = 10000000; //set these
    int arrayRange = 1000;       // to whatever
    int* array = malloc(arrayLength*4);

    int i;

    FILE* tempFile;
    char tempStr[5];

    tempFile = popen("/usr/bin/nproc", "r");
    fgets(tempStr, 5, tempFile); // As far as I know, there are no regular systems that have over 8192 cores. But just in case...
    pclose(tempFile);
    threadsAvailable = atoi(tempStr);


    srand(time(0));


    // === Initialising array while printing it
    array[0] = rand() % (arrayRange + 1);
    printf("%d", array[0]);
    for (i = 1; i < arrayLength; i++)
    {
        array[i] = rand() % (arrayRange + 1);
        printf(", %d", array[i]);
    }
    printf("\nSorting...\n");
    // ===


    struct inputArrayInfo initialArguments;

    initialArguments.arrayStartPointer = array;
    initialArguments.arrayLength       = arrayLength;
    
    threadsAvailable--; // for the main thread

    pthread_t thread;
    pthread_create(&thread, NULL, thread_node_tree_initialisation, &initialArguments);
    pthread_join(thread, NULL);


    // === Same thing as earlier but it's just printing it
    printf("\nSorted array:\n");
    printf("%d", array[0]);
    for (i = 1; i < arrayLength; i++)
    {
        printf(", %d", array[i]);
    }
    printf("\n[arrayLength = %d]\n", arrayLength);
    // ===

    free(array);

    return 0;
}
