#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define SIZE 32768
int is_prime(int n)
{
    if (n <= 1)
        return 0;
    if (n == 2)
        return 1;
    if (n % 2 == 0)
        return 0;
    for (int i = 3; i <= sqrt(n); i += 2)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}
int is_prime_digit(int d)
{
    return d == 2 || d == 3 || d == 5 || d == 7;
}
int count_prime_digits(int n)
{
    int count = 0;
    while (n > 0)
    {
        int digit = n % 10;
        if (is_prime_digit(digit))
        {
            count++;
        }
        n /= 10;
    }
    return count;
}
int compare(int a, int b)
{
    int a_is_prime = is_prime(a);
    int b_is_prime = is_prime(b);
    if (a_is_prime && !b_is_prime)
        return -1;
    if (!a_is_prime && b_is_prime)
        return 1;
    if (a_is_prime && b_is_prime)
        return a - b;
    int prime_digits_a = count_prime_digits(a);
    int prime_digits_b = count_prime_digits(b);
    if (prime_digits_a != prime_digits_b)
    {
        return prime_digits_a - prime_digits_b;
    }
    return a - b;
}
void merge(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (compare(L[i], R[j]) <= 0)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void merge_sort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
int main()
{
    int arr[SIZE];
    srand(time(0));
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = rand() % SIZE + 1;
    }
    merge_sort(arr, 0, SIZE - 1);
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}