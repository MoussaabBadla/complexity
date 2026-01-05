#include "radixSort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int key(int x, int i) {
    int divisor = 1;
    for (int j = 0; j < i; j++) {
        divisor *= 10;
    }
    return (x / divisor) % 10;
}

int getMax(int a[], long size) {
    int max = a[0];
    for (long i = 1; i < size; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}


void sortAux(int a[], long n, int i) {
    int *output = (int *)malloc(n * sizeof(int));
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed in sortAux\n");
        return;
    }
    int count[10] = {0};


    for (long j = 0; j < n; j++) {
        count[key(a[j], i)]++;
    }

    for (int j = 1; j < 10; j++) {
        count[j] += count[j - 1];
    }

    for (long j = n - 1; j >= 0; j--) {
        int digit = key(a[j], i);
        output[count[digit] - 1] = a[j];
        count[digit]--;
    }

    for (long j = 0; j < n; j++) {
        a[j] = output[j];
    }

    free(output);
}

double radixSort(long size, int a[]) {
    clock_t start, end;

    start = clock();

    int max = getMax(a, size);

    int k = 0;
    int temp = max;
    while (temp > 0) {
        k++;
        temp /= 10;
    }
    if (k == 0) k = 1; 

    for (int i = 0; i < k; i++) {
        sortAux(a, size, i);
    }

    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}
