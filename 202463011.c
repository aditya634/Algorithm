#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
const int MAX_NUM = 1 << 15;
int num_array[MAX_NUM];
bool prime_flags[MAX_NUM + 1];
int prime_digit_count[MAX_NUM + 1];

bool custom_compare(int a, int b)
{
    int prime_count_a = prime_digit_count[a], prime_count_b = prime_digit_count[b];

    if (prime_count_a == prime_count_b)
    {
        return a <= b;
    }
    return prime_count_a < prime_count_b;
}

void merge_halves(int left, int mid, int right)
{
    int left_size = mid - left + 1;
    int right_size = right - mid;

    int left_part[left_size], right_part[right_size];

    for (int i = 0; i < left_size; ++i)
        left_part[i] = num_array[left + i];
    for (int i = 0; i < right_size; ++i)
        right_part[i] = num_array[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < left_size && j < right_size)
    {
        if (custom_compare(left_part[i], right_part[j]))
        {
            num_array[k++] = left_part[i++];
        }
        else
        {
            num_array[k++] = right_part[j++];
        }
    }

    while (i < left_size)
        num_array[k++] = left_part[i++];

    while (j < right_size)
        num_array[k++] = right_part[j++];
}

void merge_sort(int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    merge_sort(left, mid);
    merge_sort(mid + 1, right);

    merge_halves(left, mid, right);
}

void sieve_of_eratosthenes()
{
    prime_flags[0] = prime_flags[1] = false;
    for (int i = 2; i <= MAX_NUM; ++i)
        prime_flags[i] = true;
    for (int i = 2; i <= MAX_NUM; ++i)
    {
        if (prime_flags[i])
        {
            for (int j = i * i; j <= MAX_NUM; j += i)
                prime_flags[j] = false;
        }
    }
}

void calculate_prime_digit_counts()
{
    for (int i = 1; i <= MAX_NUM; ++i)
    {
        if (prime_flags[i])
        {
            prime_digit_count[i] = -1;
            continue;
        }

        int number = i;
        int prime_digit_counter = 0;
        while (number > 0)
        {
            int digit = number % 10;
            if (prime_flags[digit])
                ++prime_digit_counter;
            number /= 10;
        }
        prime_digit_count[i] = prime_digit_counter;
    }
}

int main()
{
    sieve_of_eratosthenes();
    calculate_prime_digit_counts();

    unsigned int seed = time(0);
    for (int i = 0; i < MAX_NUM; ++i)
        num_array[i] = rand_r(&seed) % MAX_NUM + 1;

    printf("Array before sorting: {");
    for (int i = 0; i < MAX_NUM; ++i)
        printf("%d ", num_array[i]);
    printf("}\n");

    merge_sort(0, MAX_NUM - 1);

    printf("Array after sorting: {");
    for (int i = 0; i < MAX_NUM; ++i)
        printf("%d ", num_array[i]);
    printf("}\n");

    return 0;
}