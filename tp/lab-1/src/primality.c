
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>

bool isPrime_A1(long long N)
{
    if (N <= 1)
        return false;
    if (N == 2)
        return true;

    for (long long i = 2; i < N; i++)
    {
        if (N % i == 0)
            return false;
    }
    return true;
}

bool isPrime_A2(long long N)
{
    if (N <= 1)
        return false;
    if (N == 2)
        return true;

    for (long long i = 2; i <= N / 2; i++)
    {
        if (N % i == 0)
            return false;
    }
    return true;
}

bool isPrime_A3(long long N)
{
    if (N <= 1)
        return false;
    if (N == 2)
        return true;

    long long sqrtN = (long long)sqrt((double)N);
    for (long long i = 2; i <= sqrtN; i++)
    {
        if (N % i == 0)
            return false;
    }
    return true;
}

bool isPrime_A4(long long N)
{
    if (N <= 1)
        return false;
    if (N == 2)
        return true;
    if (N % 2 == 0)
        return false;

    long long sqrtN = (long long)sqrt((double)N);
    for (long long i = 3; i <= sqrtN; i += 2)
    {
        if (N % i == 0)
            return false;
    }
    return true;
}

double measureTime(bool (*func)(long long), long long N, int iterations)
{
    clock_t start, end;

    start = clock();
    for (int i = 0; i < iterations; i++)
    {
        func(N);
    }
    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC / iterations;
}

int main(int argc, char *argv[])
{

    long long testNumbers[] = {
        1000003, 2000003, 4000037, 8000009, 16000057,
        32000011, 64000031, 128000003, 256000001,
        512000009, 1024000009, 2048000011};
    int numTests = sizeof(testNumbers) / sizeof(testNumbers[0]);

    bool csvMode = (argc > 1 && strcmp(argv[1], "-csv") == 0);

    if (csvMode)
    {
        printf("N,A1,A2,A3,A4\n");
    }
    else
    {
        printf("=== Lab 1: Primality Test ===\n\n");

        printf("Verifying numbers are prime:\n");
        for (int i = 0; i < numTests; i++)
        {
            bool result = isPrime_A4(testNumbers[i]);
            printf("  %lld: %s\n", testNumbers[i], result ? "PRIME" : "NOT PRIME");
        }
        printf("\n");

        printf("%-15s %-12s %-12s %-12s %-12s\n",
               "N", "A1 (s)", "A2 (s)", "A3 (s)", "A4 (s)");
        printf("%-15s %-12s %-12s %-12s %-12s\n",
               "---------------", "------------", "------------", "------------", "------------");
    }

    for (int i = 0; i < numTests; i++)
    {
        long long N = testNumbers[i];
        double t1, t2, t3, t4;

        int iter_slow = 1;
        int iter_fast = 10000;

        if (N <= 2000003)
            iter_slow = 5;
        else if (N <= 8000009)
            iter_slow = 1;

        if (N <= 8000009)
        {
            t1 = measureTime(isPrime_A1, N, iter_slow);
            t2 = measureTime(isPrime_A2, N, iter_slow);
        }
        else
        {
            t1 = -1;
            t2 = -1;
        }

        t3 = measureTime(isPrime_A3, N, iter_fast);
        t4 = measureTime(isPrime_A4, N, iter_fast);

        if (csvMode)
        {
            if (t1 >= 0)
            {
                printf("%lld,%.6f,%.6f,%.6f,%.6f\n", N, t1, t2, t3, t4);
            }
            else
            {
                printf("%lld,,,%.6f,%.6f\n", N, t3, t4);
            }
        }
        else
        {
            if (t1 >= 0)
            {
                printf("%-15lld %-12.6f %-12.6f %-12.6f %-12.6f\n", N, t1, t2, t3, t4);
            }
            else
            {
                printf("%-15lld %-12s %-12s %-12.6f %-12.6f\n", N, "SKIP", "SKIP", t3, t4);
            }
        }
    }

    if (!csvMode)
    {
        printf("\n=== Complexity Analysis ===\n");
        printf("Algorithm  | Best Case | Worst Case | Description\n");
        printf("-----------|-----------|------------|---------------------------\n");
        printf("A1 (Naive) | O(1)      | O(N)       | Tests 2 to N-1\n");
        printf("A2 (N/2)   | O(1)      | O(N/2)     | Tests 2 to N/2\n");
        printf("A3 (sqrt)  | O(1)      | O(sqrt(N)) | Tests 2 to sqrt(N)\n");
        printf("A4 (odd)   | O(1)      | O(sqrt(N)/2)| Tests odd numbers only\n");
        printf("\nBest case: N is even (detected immediately)\n");
        printf("Worst case: N is prime (must test all candidates)\n");
    }

    return 0;
}
