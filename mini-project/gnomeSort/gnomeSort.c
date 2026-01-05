#include "gnomeSort.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

double gnomeSort(long size, int a[]) {
    clock_t start, end;

    start = clock();

    long index = 0;
    while (index < size) {
        if (index == 0 || a[index] >= a[index - 1]) {
            index++;
        } else {
            int temp = a[index];
            a[index] = a[index - 1];
            a[index - 1] = temp;
            index--;
        }
    }

    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}
