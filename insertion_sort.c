#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void display(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int array[size];

    // Initialize random number generator
    srand(time(0));

    // Generate random numbers for the array
    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % 100; // Generates random numbers between 0 and 99
    }

    printf("Before Insertion sort: \n");
    display(array, size);

    // Measure the time before sorting
    clock_t start, end;
    double time_taken;

    start = clock();

    // Insertion Sort Algorithm
    int i, key, j;
    for (i = 1; i < size; i++)
    {
        key = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }

    // Measure the time after sorting
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("After Insertion sort: \n");
    display(array, size);

    printf("Time taken to sort the array: %f seconds\n", time_taken);

    return 0;
}