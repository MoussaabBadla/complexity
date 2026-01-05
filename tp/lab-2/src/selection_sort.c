
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void selectionSort(int arr[], long n)
{
    for (long i = 0; i < n - 1; i++)
    {
        long minIdx = i;
        for (long j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIdx])
            {
                minIdx = j;
            }
        }
        if (minIdx != i)
        {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

void generateSorted(int arr[], long n)
{
    for (long i = 0; i < n; i++)
    {
        arr[i] = (int)i;
    }
}

void generateReverse(int arr[], long n)
{
    for (long i = 0; i < n; i++)
    {
        arr[i] = (int)(n - i);
    }
}

void generateRandom(int arr[], long n)
{
    for (long i = 0; i < n; i++)
    {
        arr[i] = rand() % (n * 10);
    }
}

void copyArray(int src[], int dest[], long n)
{
    for (long i = 0; i < n; i++)
    {
        dest[i] = src[i];
    }
}

double measureTime(int arr[], long n)
{
    clock_t start, end;

    start = clock();
    selectionSort(arr, n);
    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main(int argc, char *argv[])
{

    long sizes[] = {
        50000, 100000, 200000, 400000, 800000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    srand(time(NULL));

    int csvMode = (argc > 1 && strcmp(argv[1], "-csv") == 0);

    if (csvMode)
    {
        printf("Size,Sorted,Random,Reverse\n");
    }
    else
    {
        printf("=== Lab 2: Selection Sort ===\n\n");
        printf("Time Complexity: O(n^2) in all cases\n");
        printf("Space Complexity: O(1)\n\n");
        printf("%-12s %-12s %-12s %-12s\n", "Size (n)", "Sorted (s)", "Random (s)", "Reverse (s)");
        printf("%-12s %-12s %-12s %-12s\n", "------------", "------------", "------------", "------------");
    }

    for (int i = 0; i < numSizes; i++)
    {
        long n = sizes[i];

        int *arr = (int *)malloc(n * sizeof(int));
        int *work = (int *)malloc(n * sizeof(int));

        if (!arr || !work)
        {
            fprintf(stderr, "Memory allocation failed for n=%ld\n", n);
            continue;
        }

        double t_sorted, t_random, t_reverse;

        generateSorted(arr, n);
        copyArray(arr, work, n);
        t_sorted = measureTime(work, n);

        generateRandom(arr, n);
        copyArray(arr, work, n);
        t_random = measureTime(work, n);

        generateReverse(arr, n);
        copyArray(arr, work, n);
        t_reverse = measureTime(work, n);

        if (csvMode)
        {
            printf("%ld,%.6f,%.6f,%.6f\n", n, t_sorted, t_random, t_reverse);
        }
        else
        {
            printf("%-12ld %-12.6f %-12.6f %-12.6f\n", n, t_sorted, t_random, t_reverse);
        }

        free(arr);
        free(work);
    }

    if (!csvMode)
    {
        printf("\n=== Analysis ===\n");
        printf("Selection sort has O(n^2) comparisons regardless of input order.\n");
        printf("The number of swaps varies: 0 for sorted, O(n) for others.\n");
        printf("When n doubles, time should quadruple (T ~ n^2).\n");
    }

    return 0;
}
