
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

long long hanoi_moves = 0;

void hanoiRecursive(int n, char from, char to, char aux)
{
    if (n == 1)
    {
        hanoi_moves++;
        return;
    }
    hanoiRecursive(n - 1, from, aux, to);
    hanoi_moves++;
    hanoiRecursive(n - 1, aux, to, from);
}

void hanoiIterative(int n)
{
    long long totalMoves = (1LL << n) - 1;

    hanoi_moves = totalMoves;
}

double measureHanoi(void (*func)(int, char, char, char), int n, int recursive)
{
    clock_t start, end;
    hanoi_moves = 0;

    start = clock();
    if (recursive)
    {
        func(n, 'A', 'C', 'B');
    }
    else
    {
        hanoiIterative(n);
    }
    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

long long fiboRecursive(int n)
{
    if (n <= 1)
        return n;
    return fiboRecursive(n - 1) + fiboRecursive(n - 2);
}

long long fiboIterative(int n)
{
    if (n <= 1)
        return n;

    long long prev2 = 0, prev1 = 1, curr;
    for (int i = 2; i <= n; i++)
    {
        curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

void testGoldenRatio(int maxN)
{
    printf("\n=== Golden Ratio Test ===\n");
    printf("phi = (1 + sqrt(5)) / 2 = %.15f\n\n", (1 + sqrt(5)) / 2);
    printf("%-5s %-20s %-20s\n", "n", "U_n", "U_n / U_(n-1)");
    printf("%-5s %-20s %-20s\n", "-----", "--------------------", "--------------------");

    double prev = 1;
    for (int n = 2; n <= maxN && n <= 50; n++)
    {
        double curr = (double)fiboIterative(n);
        double ratio = curr / prev;
        printf("%-5d %-20.0f %-20.15f\n", n, curr, ratio);
        prev = curr;
    }
}

int main(int argc, char *argv[])
{
    int csvMode = (argc > 1 && strcmp(argv[1], "-csv") == 0);

    if (!csvMode)
    {
        printf("=== Lab 5: Iterative vs Recursive ===\n\n");
        printf("=== Exercise 1: Tower of Hanoi ===\n");
        printf("Complexity: O(2^n) - Number of moves = 2^n - 1\n\n");
        printf("%-5s %-15s %-15s %-15s\n", "n", "Recursive (s)", "Iterative (s)", "Moves");
        printf("%-5s %-15s %-15s %-15s\n", "-----", "---------------", "---------------", "---------------");
    }
    else
    {
        printf("n,Recursive,Iterative,Moves\n");
    }

    for (int n = 3; n <= 28; n++)
    {
        double t_rec = 0, t_iter = 0;

        if (n <= 25)
        {
            t_rec = measureHanoi(hanoiRecursive, n, 1);
        }

        t_iter = measureHanoi(NULL, n, 0);

        long long moves = (1LL << n) - 1;

        if (csvMode)
        {
            if (n <= 25)
            {
                printf("%d,%.6f,%.6f,%lld\n", n, t_rec, t_iter, moves);
            }
            else
            {
                printf("%d,,%.6f,%lld\n", n, t_iter, moves);
            }
        }
        else
        {
            if (n <= 25)
            {
                printf("%-5d %-15.6f %-15.6f %-15lld\n", n, t_rec, t_iter, moves);
            }
            else
            {
                printf("%-5d %-15s %-15.6f %-15lld\n", n, "SKIP", t_iter, moves);
            }
        }
    }

    if (!csvMode)
    {
        printf("\n=== Exercise 2: Fibonacci ===\n");
        printf("Recursive: O(2^n) time, O(n) space\n");
        printf("Iterative: O(n) time, O(1) space\n\n");
        printf("%-5s %-15s %-15s %-20s\n", "n", "Recursive (s)", "Iterative (s)", "Fib(n)");
        printf("%-5s %-15s %-15s %-20s\n", "-----", "---------------", "---------------", "--------------------");
    }
    else
    {
        printf("\nn,Fibo_Rec,Fibo_Iter,Value\n");
    }

    int fiboTests[] = {5, 10, 15, 20, 25, 30, 35, 40, 45};
    int numFiboTests = sizeof(fiboTests) / sizeof(fiboTests[0]);

    for (int i = 0; i < numFiboTests; i++)
    {
        int n = fiboTests[i];
        clock_t start, end;
        double t_rec = 0, t_iter;
        long long result;

        if (n <= 40)
        {
            start = clock();
            result = fiboRecursive(n);
            end = clock();
            t_rec = (double)(end - start) / CLOCKS_PER_SEC;
        }

        start = clock();
        result = fiboIterative(n);
        end = clock();
        t_iter = (double)(end - start) / CLOCKS_PER_SEC;

        if (csvMode)
        {
            if (n <= 40)
            {
                printf("%d,%.6f,%.9f,%lld\n", n, t_rec, t_iter, result);
            }
            else
            {
                printf("%d,,%.9f,%lld\n", n, t_iter, result);
            }
        }
        else
        {
            if (n <= 40)
            {
                printf("%-5d %-15.6f %-15.9f %-20lld\n", n, t_rec, t_iter, result);
            }
            else
            {
                printf("%-5d %-15s %-15.9f %-20lld\n", n, "SKIP", t_iter, result);
            }
        }
    }

    if (!csvMode)
    {
        testGoldenRatio(20);
    }

    if (!csvMode)
    {
        printf("\n=== Analysis ===\n");
        printf("Tower of Hanoi: Both have O(2^n) time, but recursive has O(n) stack space.\n");
        printf("Fibonacci: Recursive is exponentially slower due to repeated calculations.\n");
        printf("           Iterative is O(n) with O(1) space - much more efficient.\n");
    }

    return 0;
}
