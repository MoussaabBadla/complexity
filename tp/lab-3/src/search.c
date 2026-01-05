
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int linearSearch_Unsorted(int arr[], long n, int x)
{
    for (long i = 0; i < n; i++)
    {
        if (arr[i] == x)
            return i;
    }
    return -1;
}

int linearSearch_Sorted(int arr[], long n, int x)
{
    for (long i = 0; i < n; i++)
    {
        if (arr[i] == x)
            return i;
        if (arr[i] > x)
            return -1;
    }
    return -1;
}

int binarySearch_Sorted(int arr[], long n, int x)
{
    long left = 0, right = n - 1;

    while (left <= right)
    {
        long mid = left + (right - left) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

void maxMinA(int arr[], long n, int *max, int *min, long *comparisons)
{
    *comparisons = 0;
    *max = arr[0];
    *min = arr[0];

    for (long i = 1; i < n; i++)
    {
        (*comparisons)++;
        if (arr[i] > *max)
            *max = arr[i];

        (*comparisons)++;
        if (arr[i] < *min)
            *min = arr[i];
    }
}

void maxMinB(int arr[], long n, int *max, int *min, long *comparisons)
{
    *comparisons = 0;
    long i;

    if (n % 2 == 0)
    {
        (*comparisons)++;
        if (arr[0] > arr[1])
        {
            *max = arr[0];
            *min = arr[1];
        }
        else
        {
            *max = arr[1];
            *min = arr[0];
        }
        i = 2;
    }
    else
    {
        *max = arr[0];
        *min = arr[0];
        i = 1;
    }

    while (i < n - 1)
    {
        (*comparisons)++;
        if (arr[i] > arr[i + 1])
        {
            (*comparisons)++;
            if (arr[i] > *max)
                *max = arr[i];
            (*comparisons)++;
            if (arr[i + 1] < *min)
                *min = arr[i + 1];
        }
        else
        {
            (*comparisons)++;
            if (arr[i + 1] > *max)
                *max = arr[i + 1];
            (*comparisons)++;
            if (arr[i] < *min)
                *min = arr[i];
        }
        i += 2;
    }
}

void generateSorted(int arr[], long n)
{
    for (long i = 0; i < n; i++)
    {
        arr[i] = (int)(i + 1);
    }
}

void generateRandom(int arr[], long n)
{
    for (long i = 0; i < n; i++)
    {
        arr[i] = rand() % (n * 10);
    }
}

double measureSearchTime(int (*searchFunc)(int[], long, int), int arr[], long n, int x, int iterations)
{
    clock_t start, end;

    start = clock();
    for (int i = 0; i < iterations; i++)
    {
        searchFunc(arr, n, x);
    }
    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC / iterations;
}

int main(int argc, char *argv[])
{

    long sizes[] = {100000, 200000, 400000, 600000, 800000,
                    1000000, 1200000, 1400000, 1600000, 1800000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    srand(time(NULL));

    int csvMode = (argc > 1 && strcmp(argv[1], "-csv") == 0);

    if (csvMode)
    {
        printf("Size,LinearUnsorted_Best,LinearUnsorted_Worst,LinearSorted_Best,LinearSorted_Worst,Binary_Best,Binary_Worst\n");
    }
    else
    {
        printf("=== Lab 3: Search Algorithms ===\n\n");
        printf("=== Part A: Element Search ===\n\n");
    }

    if (!csvMode)
    {
        printf("%-10s | %-24s | %-24s | %-24s\n",
               "", "Linear Unsorted", "Linear Sorted", "Binary Search");
        printf("%-10s | %-12s %-12s | %-12s %-12s | %-12s %-12s\n",
               "Size", "Best(s)", "Worst(s)", "Best(s)", "Worst(s)", "Best(s)", "Worst(s)");
        printf("-----------|--------------------------|--------------------------|-------------------------\n");
    }

    for (int i = 0; i < numSizes; i++)
    {
        long n = sizes[i];
        int *arr = (int *)malloc(n * sizeof(int));
        if (!arr)
            continue;

        generateSorted(arr, n);
        int iterations = 1000;

        int x_best = arr[0];

        int x_worst = -1;

        double t_lu_best = measureSearchTime(linearSearch_Unsorted, arr, n, x_best, iterations);
        double t_lu_worst = measureSearchTime(linearSearch_Unsorted, arr, n, x_worst, iterations);
        double t_ls_best = measureSearchTime(linearSearch_Sorted, arr, n, x_best, iterations);
        double t_ls_worst = measureSearchTime(linearSearch_Sorted, arr, n, x_worst, iterations);
        double t_bs_best = measureSearchTime(binarySearch_Sorted, arr, n, x_best, iterations);
        double t_bs_worst = measureSearchTime(binarySearch_Sorted, arr, n, x_worst, iterations);

        if (csvMode)
        {
            printf("%ld,%.9f,%.9f,%.9f,%.9f,%.9f,%.9f\n",
                   n, t_lu_best, t_lu_worst, t_ls_best, t_ls_worst, t_bs_best, t_bs_worst);
        }
        else
        {
            printf("%-10ld | %-12.9f %-12.9f | %-12.9f %-12.9f | %-12.9f %-12.9f\n",
                   n, t_lu_best, t_lu_worst, t_ls_best, t_ls_worst, t_bs_best, t_bs_worst);
        }

        free(arr);
    }

    if (!csvMode)
    {
        printf("\n=== Part B: MaxMin Search ===\n\n");
        printf("%-10s | %-12s %-12s | %-12s %-12s\n",
               "Size", "MaxMinA(s)", "Comps", "MaxMinB(s)", "Comps");
        printf("-----------|--------------------------|-------------------------\n");
    }

    if (csvMode)
    {
        printf("\nSize,MaxMinA_Time,MaxMinA_Comps,MaxMinB_Time,MaxMinB_Comps\n");
    }

    for (int i = 0; i < numSizes; i++)
    {
        long n = sizes[i];
        int *arr = (int *)malloc(n * sizeof(int));
        if (!arr)
            continue;

        generateRandom(arr, n);

        int max, min;
        long compsA, compsB;
        clock_t start, end;

        start = clock();
        maxMinA(arr, n, &max, &min, &compsA);
        end = clock();
        double t_A = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        maxMinB(arr, n, &max, &min, &compsB);
        end = clock();
        double t_B = (double)(end - start) / CLOCKS_PER_SEC;

        if (csvMode)
        {
            printf("%ld,%.9f,%ld,%.9f,%ld\n", n, t_A, compsA, t_B, compsB);
        }
        else
        {
            printf("%-10ld | %-12.9f %-12ld | %-12.9f %-12ld\n", n, t_A, compsA, t_B, compsB);
        }

        free(arr);
    }

    if (!csvMode)
    {
        printf("\n=== Complexity Analysis ===\n");
        printf("Linear Search (Unsorted): Best O(1), Worst O(n)\n");
        printf("Linear Search (Sorted):   Best O(1), Worst O(n)\n");
        printf("Binary Search (Sorted):   Best O(1), Worst O(log n)\n");
        printf("MaxMinA (Naive):          2(n-1) comparisons\n");
        printf("MaxMinB (Efficient):      ~3n/2 comparisons\n");
    }

    return 0;
}
