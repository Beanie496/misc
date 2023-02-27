#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void sift_down(int array[], int* startPosPoint, int length)
{
    int pos = startPosPoint - array;
    int curEl; // Current element
    int posOfFirstChild = (pos << 1) + 1;


    /*
     * This loop swaps the current element with the higher of
     * its two children. If the current position in the binary
     * tree is such that there aren't two children, this loop stops.
     * After that, it checks if there was only one child and swaps
     * with it if needed.
     *
     * Logic behind this logical statement:
     * If there is only one child, the right-hand side will be
     * equal to pos. If there are two, the right-hand side will
     * be one less. This ensures the loop is broken as soon as
     * there are fewer than two children.
     */

    while (pos < length - 1 >> 1) {

        curEl = array[pos];
        

        if (array[pos] < array[posOfFirstChild] || array[pos] < array[posOfFirstChild + 1]) {
            if (array[posOfFirstChild + 1] > array[posOfFirstChild]) {

                array[pos] = array[posOfFirstChild + 1];
                array[posOfFirstChild + 1] = curEl;
                pos = posOfFirstChild + 1;

            } else {

                array[pos] = array[posOfFirstChild];
                array[posOfFirstChild] = curEl;
                pos = posOfFirstChild;

            }
            

            posOfFirstChild = (pos << 1) + 1;
        } else
            break;
        
    }


    if (posOfFirstChild == length - 1) {

        if (array[posOfFirstChild] > array[pos]) {

            curEl = array[pos];
            array[pos] = array[posOfFirstChild];
            array[posOfFirstChild] = curEl;

        }
    }
            
}


void heapify(int array[], int length)
{
    // I am decrementing it before I check, so I have to increment it by one beforehand. -1 + 1 = 0.
    int* end = array + length/2;

    while (end > array) {
        end--;
        sift_down(array, end, length);
    }
}


void heapsort(int array[], int length)
{
    int temp;
    int* end = array + length - 1;

    heapify(array, length);

    while (array < end) {

        temp = *end;
        *end = array[0];
        array[0] = temp;

        length--;
        end--;
        
        sift_down(array, array, length);

    }
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

    
    heapsort(array, arrayLength);
    
     
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
