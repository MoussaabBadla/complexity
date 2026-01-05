#include "bubblesort.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

double bubbleSort(long size, int a[]) {
    clock_t start, end;

    start = clock();

    bool change = true;
    while (change) {
        change = false;
        for (long j = 0; j < (size - 1); j++) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                change = true;
            }
        }
    }

    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

double bubbleSortOpt(long size, int a[]) {
    clock_t start, end;

    start = clock();

    long m = size - 1;
    bool change = true;
    while (change) {
        change = false;
        for (long i = 0; i < m; i++) {
            if (a[i] > a[i + 1]) {
                int tmp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = tmp;
                change = true;
            }
        }
        m = m - 1;
    }

    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}
