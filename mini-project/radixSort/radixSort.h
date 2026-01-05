#ifndef RADIXSORT_H_
#define RADIXSORT_H_

int key(int x, int i);
int getMax(int a[], long size);
void sortAux(int a[], long n, int i);
double radixSort(long size, int a[]);

#endif // RADIXSORT_H_
