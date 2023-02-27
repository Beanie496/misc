#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int counter = 0;


void bogo_sort(int array[], int length)
{
    int i;
    int temp;
    int randItem;
    int sorted;

    do {
        sorted = 1;

        for (i = 1; i < length; i++) {
            if (array[i] < array[i - 1]) {
                sorted = 0;
                break;
            }
        }

        if (sorted == 1)
            return;

        for (i = 0; i < length - 1; i++) { // no point swapping the last item with itself
            randItem = random() % (length - i) + i;
            temp = array[i];
            array[i] = array[randItem];
            array[randItem] = temp;
        }
        
        counter++;

    } while (1);

}


int main ()
{
    int arrayLength = 12; // set these
    int arrayRange = 10;  // to whatever 
    int array[arrayLength];
    int i;

    srandom(time(0));
    
    
    array[0] = random() % (arrayRange + 1);
    printf("%d", array[0]);
    for (i = 1; i < arrayLength; i++)
    {
        array[i] = random() % (arrayRange + 1);
	    printf(", %d", array[i]);
    }
    printf("\nSorting...\n");

    
    bogo_sort(array, arrayLength);
    
    
    printf("\nSorted. It took %d iterations.\n", counter);
    printf("Sorted array:\n");
    printf("%d", array[0]);
    for (i = 1; i < arrayLength; i++)
    {
   	    printf(", %d", array[i]);
    }
    printf("\n[arrayLength = %d]\n", arrayLength);

    return 0;
}
