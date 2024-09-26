#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

int heap[MAX];
int size = 0;

// Swap function to swap two elements in the heap
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Function to maintain heap property after insertion (Heapify up)
void heapify_up(int index)
{
    while (index > 0 && heap[(index - 1) / 2] > heap[index])
    {
        swap(&heap[(index - 1) / 2], &heap[index]);
        index = (index - 1) / 2;
    }
}

// Function to maintain heap property after removal (Heapify down)
void heapify_down(int index)
{
    int smallest = index;
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;

    if (left_child < size && heap[left_child] < heap[smallest])
    {
        smallest = left_child;
    }
    if (right_child < size && heap[right_child] < heap[smallest])
    {
        smallest = right_child;
    }
    if (smallest != index)
    {
        swap(&heap[index], &heap[smallest]);
        heapify_down(smallest);
    }
}

// Insert an element into the heap
void insert(int element)
{
    if (size == MAX)
    {
        printf("Heap is full!\n");
        return;
    }
    heap[size] = element;
    heapify_up(size);
    size++;
    printf("Element %d inserted.\n", element);
}

// Pop the smallest element from the heap
int pop()
{
    if (size <= 0)
    {
        printf("Heap is empty!\n");
        return -1;
    }
    int root = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapify_down(0);
    return root;
}

// Build heap from an array of integers
void build_heap(int arr[], int n)
{
    size = n;
    for (int i = 0; i < n; i++)
    {
        heap[i] = arr[i];
    }
    for (int i = (size / 2) - 1; i >= 0; i--)
    {
        heapify_down(i);
    }
    printf("Heap built successfully.\n");
}

// Display the heap
void display_heap()
{
    if (size == 0)
    {
        printf("Heap is empty.\n");
        return;
    }
    printf("Heap: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

// Heap sort
void heap_sort(int arr[], int n)
{
    build_heap(arr, n);
    for (int i = n - 1; i > 0; i--)
    {
        swap(&heap[0], &heap[i]);
        size--;
        heapify_down(0);
    }
}

// Comparison function for qsort()
int compare_custom(const void *a, const void *b)
{
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;

    if (int_a < int_b)
        return -1;
    else if (int_a > int_b)
        return 1;
    else
        return 0;
}

// Generate a random array of integers with the same number of digits
void generate_random_array(int arr[], int n, int digit_length)
{
    int lower_bound = 1;
    for (int i = 1; i < digit_length; i++)
    {
        lower_bound *= 10;
    }
    int upper_bound = lower_bound * 10 - 1;

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % (upper_bound - lower_bound + 1) + lower_bound;
    }
}

int main()
{
    int choice, element, n, arr[MAX];
    srand(time(0));

    while (1)
    {
        printf("\nOptions:\n");
        printf("1. Create an empty min heap.\n");
        printf("2. Input a list of positive integers and build heap.\n");
        printf("3. Insert an element into the heap.\n");
        printf("4. Pop an element from the heap.\n");
        printf("5. Display integers in heap using heap sort.\n");
        printf("6. Generate random array, sort with heap sort and compare with standard sorting.\n");
        printf("7. Quit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            size = 0;
            printf("Created an empty min heap.\n");
            break;

        case 2:
            printf("Enter the number of elements: ");
            scanf("%d", &n);
            printf("Enter the elements: ");
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &arr[i]);
            }
            build_heap(arr, n);
            display_heap();
            break;

        case 3:
            printf("Enter the element to insert: ");
            scanf("%d", &element);
            insert(element);
            display_heap();
            break;

        case 4:
            element = pop();
            if (element != -1)
            {
                printf("Popped element: %d\n", element);
            }
            display_heap();
            break;

        case 5:
            printf("Sorting the heap using heap sort...\n");
            heap_sort(heap, size);
            display_heap();
            break;

        case 6:
            printf("Enter the length of the random array: ");
            scanf("%d", &n);
            generate_random_array(arr, n, 5); // Fixed digit length of 5 for the example
            printf("Generated array: ");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", arr[i]);
            }
            printf("\n");

            // Measure time for heap sort
            clock_t start = clock();
            heap_sort(arr, n);
            clock_t end = clock();
            double heap_sort_time = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Heap sort time: %.6f seconds\n", heap_sort_time);

            // Measure time for standard sorting
            start = clock();
            qsort(arr, n, sizeof(int), compare_custom);
            end = clock();
            double lib_sort_time = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Library sort time: %.6f seconds\n", lib_sort_time);
            break;

        case 7:
            printf("Exiting program.\n");
            exit(0);
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
