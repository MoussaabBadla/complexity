#include "bucketSort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    float value;
    struct Node *next;
} Node;

Node* insertSorted(Node *head, float value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed in insertSorted\n");
        return head;
    }
    newNode->value = value;
    newNode->next = NULL;

    if (head == NULL || head->value >= value) {
        newNode->next = head;
        return newNode;
    }

    Node *current = head;
    while (current->next != NULL && current->next->value < value) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;

    return head;
}

void freeList(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

double bucketSort(long size, float a[]) {
    clock_t start, end;

    start = clock();

    Node **buckets = (Node **)calloc(size, sizeof(Node *));
    if (buckets == NULL) {
        fprintf(stderr, "Memory allocation failed for buckets\n");
        return -1;
    }

    for (long i = 0; i < size; i++) {
        int bucketIndex = (int)(size * a[i]); 
        if (bucketIndex >= size) bucketIndex = size - 1; 
        buckets[bucketIndex] = insertSorted(buckets[bucketIndex], a[i]);
    }

    long index = 0;
    for (long i = 0; i < size; i++) {
        Node *current = buckets[i];
        while (current != NULL) {
            a[index++] = current->value;
            current = current->next;
        }
        freeList(buckets[i]);
    }

    free(buckets);

    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}
