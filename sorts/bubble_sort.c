#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // I want boolean types ok
#include <time.h>

void swap(int* pointer1, int* pointer2)
{
    asm("push %0\n\t"
        "movl %1 %0\n\t"
        "pop %1\n\t"
        : "+r" (pointer1), "+r" (pointer2));
    /* int temp = *pointer2;
    *pointer2 = *pointer1;
    *pointer1 = temp;
    */
    
}


void sort(int* startPointer, int length)
{
    int* tempStart = startPointer;
    bool sorted = 1;
    
    for (int i = 0; i < length - 1; i++)
    {
        if (*(tempStart + i) > *(tempStart + i + 1))
        {
            swap(tempStart + i, tempStart + i + 1);
            sorted = 0;
        }
    }
    
    if (!sorted)
    {
        sort(startPointer, length);
    }
}


int main()
{
    int arrayLength = 10000; //set these
    int arrayRange = 1000;   // to whatever 
    int array[arrayLength];
    

    srand(time(0));

    *array = rand() % (arrayRange + 1);
    printf("%d", *array);
    for (int i = 1; i < arrayLength; i++)
    {
        array[i] = rand() % (arrayRange + 1);
        printf(", %d", array[i]);
    }
    printf("\nSorting...\n");


    sort(array, arrayLength);
    

    printf("\nSorted array is:\n");
    printf("%d", *array); 
    for (int i = 1; i < arrayLength; i++)
    {
        printf(", %d", array[i]);
    }
    printf("\n[arrayLength = %d]\n", arrayLength);
    
    return 0;
}
