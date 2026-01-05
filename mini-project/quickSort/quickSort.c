#include "quickSort.h"
#include <stdio.h>
#include <time.h>

long partition(int a[], long d, long f) {
    int eltPivot = a[d];  
    long i = d - 1;
    long j = f + 1;

    while (1) {
        do {
            j--;
        } while (a[j] > eltPivot);

        do {
            i++;
        } while (a[i] < eltPivot);

        if (i >= j) {
            return j;
        }

        int x = a[i];
        a[i] = a[j];
        a[j] = x;
    }
}

void quickSortRecursive(int a[], long p, long r) {
    if (p < r) {
        long q = partition(a, p, r);
        quickSortRecursive(a, p, q);
        quickSortRecursive(a, q + 1, r);
    }
}

double quickSort(long size, int a[]) {
    clock_t start, end;

    start = clock();

    quickSortRecursive(a, 0, size - 1);

    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}
