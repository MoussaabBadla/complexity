#include "heapSort.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void heapify(int a[], long size, long i) {
    long largest = i;
    long left = 2 * i + 1;
    long right = 2 * i + 2;

    if (left < size && a[left] > a[largest]) {
        largest = left;
    }

    if (right < size && a[right] > a[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        heapify(a, size, largest);
    }
}

double heapSort(long size, int a[]) {
    clock_t start, end;

    start = clock();

    for (long i = size / 2 - 1; i >= 0; i--) {
        heapify(a, size, i);
    }

    for (long i = size - 1; i >= 0; i--) {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        heapify(a, i, 0);
    }

    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}
