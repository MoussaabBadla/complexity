
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int **allocateMatrix(int rows, int cols)
{
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)calloc(cols, sizeof(int));
    }
    return matrix;
}

void freeMatrix(int **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void randomMatrix(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = rand() % 100;
        }
    }
}

void matrixMultiply(int **A, int **B, int **C, int n, int m, int p)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < m; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

bool subMat1(int **A, int n, int m, int **B, int np, int mp)
{
    for (int i = 0; i <= n - np; i++)
    {
        for (int j = 0; j <= m - mp; j++)
        {
            bool found = true;
            for (int ii = 0; ii < np && found; ii++)
            {
                for (int jj = 0; jj < mp && found; jj++)
                {
                    if (A[i + ii][j + jj] != B[ii][jj])
                    {
                        found = false;
                    }
                }
            }
            if (found)
                return true;
        }
    }
    return false;
}

bool subMat2(int **A, int n, int m, int **B, int np, int mp)
{
    for (int i = 0; i <= n - np; i++)
    {
        for (int j = 0; j <= m - mp; j++)
        {

            if (A[i][j] != B[0][0])
                continue;

            bool found = true;
            for (int ii = 0; ii < np && found; ii++)
            {
                for (int jj = 0; jj < mp && found; jj++)
                {
                    if (A[i + ii][j + jj] != B[ii][jj])
                    {
                        found = false;
                    }

                    else if (jj < mp - 1 && A[i + ii][j + jj] > B[ii][jj + 1])
                    {
                        found = false;
                    }
                }
            }
            if (found)
                return true;
        }
    }
    return false;
}

void generateSortedMatrix(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        int val = rand() % 10;
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = val;
            val += rand() % 5 + 1;
        }
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int csvMode = (argc > 1 && strcmp(argv[1], "-csv") == 0);

    int matrixSizes[] = {100, 200, 300, 400, 500, 600, 700, 800};
    int numMatrixSizes = sizeof(matrixSizes) / sizeof(matrixSizes[0]);

    if (csvMode)
    {
        printf("n,Time\n");
    }
    else
    {
        printf("=== Lab 4: Polynomial Complexity ===\n\n");
        printf("=== Exercise 1: Matrix Multiplication ===\n\n");
        printf("Time Complexity: O(n^3) for square matrices\n");
        printf("Space Complexity: O(n^2) for result matrix\n\n");
        printf("%-10s %-12s\n", "Size (n)", "Time (s)");
        printf("%-10s %-12s\n", "----------", "------------");
    }

    for (int i = 0; i < numMatrixSizes; i++)
    {
        int n = matrixSizes[i];

        int **A = allocateMatrix(n, n);
        int **B = allocateMatrix(n, n);
        int **C = allocateMatrix(n, n);

        randomMatrix(A, n, n);
        randomMatrix(B, n, n);

        clock_t start = clock();
        matrixMultiply(A, B, C, n, n, n);
        clock_t end = clock();

        double time = (double)(end - start) / CLOCKS_PER_SEC;

        if (csvMode)
        {
            printf("%d,%.6f\n", n, time);
        }
        else
        {
            printf("%-10d %-12.6f\n", n, time);
        }

        freeMatrix(A, n);
        freeMatrix(B, n);
        freeMatrix(C, n);
    }

    if (!csvMode)
    {
        printf("\n=== Exercise 2: Submatrix Search ===\n\n");
        printf("%-8s %-8s %-12s %-12s\n", "A size", "B size", "subMat1 (s)", "subMat2 (s)");
        printf("%-8s %-8s %-12s %-12s\n", "--------", "--------", "------------", "------------");
    }

    if (csvMode)
    {
        printf("\nA_size,B_size,subMat1,subMat2\n");
    }

    int aSizes[] = {500, 1000, 1500, 2000};
    int bSizes[] = {10, 20, 30, 50};
    int numASizes = sizeof(aSizes) / sizeof(aSizes[0]);

    for (int i = 0; i < numASizes; i++)
    {
        int n = aSizes[i];
        int np = bSizes[i];

        int **A = allocateMatrix(n, n);
        int **B = allocateMatrix(np, np);

        generateSortedMatrix(A, n, n);
        generateSortedMatrix(B, np, np);

        clock_t start, end;

        start = clock();
        subMat1(A, n, n, B, np, np);
        end = clock();
        double t1 = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        subMat2(A, n, n, B, np, np);
        end = clock();
        double t2 = (double)(end - start) / CLOCKS_PER_SEC;

        if (csvMode)
        {
            printf("%d,%d,%.6f,%.6f\n", n, np, t1, t2);
        }
        else
        {
            printf("%-8d %-8d %-12.6f %-12.6f\n", n, np, t1, t2);
        }

        freeMatrix(A, n);
        freeMatrix(B, np);
    }

    if (!csvMode)
    {
        printf("\n=== Complexity Analysis ===\n");
        printf("Matrix Multiplication: O(n*m*p), O(n^3) for square\n");
        printf("subMat1 (Naive): O(n*m*n'*m')\n");
        printf("subMat2 (Optimized): Better average case with early termination\n");
    }

    return 0;
}
