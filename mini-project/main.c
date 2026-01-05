#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "./bubbleSort/bubblesort.h"
#include "./gnomeSort/gnomeSort.h"
#include "./radixSort/radixSort.h"
#include "./quickSort/quickSort.h"
#include "./heapSort/heapSort.h"
#include "./bucketSort/bucketSort.h"

#define DEFAULT_MAX_VALUE 100
#define MAX_ARRAY_SIZE 10000000
#define NUM_RUNS 5
#define NUM_ALGORITHMS 7

typedef double (*SortFuncInt)(long, int[]);
typedef double (*SortFuncFloat)(long, float[]);

typedef enum {
    CASE_RANDOM,
    CASE_BEST,
    CASE_WORST
} TestCase;

const char *algorithmNames[NUM_ALGORITHMS] = {
    "BubbleSort",
    "BubbleSortOpt",
    "GnomeSort",
    "QuickSort",
    "HeapSort",
    "RadixSort",
    "BucketSort"
};

const char *caseNames[] = {"Random", "Best", "Worst"};

void printUsage(const char *programName) {
    printf("USAGE: %s [OPTIONS] <size1> <size2> ...\n", programName);
    printf("\nOptions:\n");
    printf("  -r <max>    Set maximum random value (default: %d)\n", DEFAULT_MAX_VALUE);
    printf("  -c <file>   Export results to CSV file\n");
    printf("  -h          Show this help message\n");
    printf("\nExamples:\n");
    printf("  %s 100 1000 5000\n", programName);
    printf("  %s -r 1000 -c results.csv 100 500 1000\n", programName);
}

int parseSize(const char *str, long *result) {
    char *endptr;
    errno = 0;
    long value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        fprintf(stderr, "Error: '%s' is not a valid number.\n", str);
        return 0;
    }
    if (errno == ERANGE || value > MAX_ARRAY_SIZE || value <= 0) {
        fprintf(stderr, "Error: Size must be between 1 and %d.\n", MAX_ARRAY_SIZE);
        return 0;
    }
    *result = value;
    return 1;
}

// Generate array based on test case
void generateArray(int *array, long size, int maxValue, TestCase testCase) {
    switch (testCase) {
        case CASE_BEST:  // Already sorted (best case)
            for (long i = 0; i < size; i++) {
                array[i] = (int)i;
            }
            break;
        case CASE_WORST:  // Reverse sorted (worst case)
            for (long i = 0; i < size; i++) {
                array[i] = (int)(size - i);
            }
            break;
        case CASE_RANDOM:
        default:
            for (long i = 0; i < size; i++) {
                array[i] = rand() % maxValue;
            }
            break;
    }
}

// Generate float array for bucket sort [0, 1)
void generateFloatArray(float *array, long size, TestCase testCase) {
    switch (testCase) {
        case CASE_BEST:
            for (long i = 0; i < size; i++) {
                array[i] = (float)i / size;
            }
            break;
        case CASE_WORST:
            for (long i = 0; i < size; i++) {
                array[i] = (float)(size - 1 - i) / size;
            }
            break;
        case CASE_RANDOM:
        default:
            for (long i = 0; i < size; i++) {
                array[i] = (float)rand() / (float)RAND_MAX * 0.9999f;
            }
            break;
    }
}

// Run sorting algorithm multiple times and return average time
double runIntSort(SortFuncInt sortFunc, int *original, long size, int numRuns) {
    double totalTime = 0.0;
    int *testArray = (int *)malloc(size * sizeof(int));
    if (!testArray) return -1;

    for (int run = 0; run < numRuns; run++) {
        memcpy(testArray, original, size * sizeof(int));
        totalTime += sortFunc(size, testArray);
    }

    free(testArray);
    return totalTime / numRuns;
}

double runBucketSort(float *original, long size, int numRuns) {
    double totalTime = 0.0;
    float *testArray = (float *)malloc(size * sizeof(float));
    if (!testArray) return -1;

    for (int run = 0; run < numRuns; run++) {
        memcpy(testArray, original, size * sizeof(float));
        totalTime += bucketSort(size, testArray);
    }

    free(testArray);
    return totalTime / numRuns;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    int maxRandomValue = DEFAULT_MAX_VALUE;
    char *csvFile = NULL;
    int startIndex = 1;

    // Parse options
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            printUsage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-r") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: -r requires a value.\n");
                return 1;
            }
            long value;
            if (!parseSize(argv[++i], &value)) return 1;
            maxRandomValue = (int)value;
            startIndex = i + 1;
        } else if (strcmp(argv[i], "-c") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: -c requires a filename.\n");
                return 1;
            }
            csvFile = argv[++i];
            startIndex = i + 1;
        } else if (argv[i][0] != '-') {
            startIndex = i;
            break;
        }
    }

    if (startIndex >= argc) {
        fprintf(stderr, "Error: No array sizes specified.\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    int numSizes = argc - startIndex;
    long *sizes = (long *)malloc(numSizes * sizeof(long));
    int validSizes = 0;

    for (int i = startIndex; i < argc; i++) {
        if (parseSize(argv[i], &sizes[validSizes])) {
            validSizes++;
        }
    }

    if (validSizes == 0) {
        fprintf(stderr, "Error: No valid sizes provided.\n");
        free(sizes);
        return 1;
    }

    // Results storage: [size][case][algorithm]
    double ***results = (double ***)malloc(validSizes * sizeof(double **));
    for (int s = 0; s < validSizes; s++) {
        results[s] = (double **)malloc(3 * sizeof(double *));
        for (int c = 0; c < 3; c++) {
            results[s][c] = (double *)malloc(NUM_ALGORITHMS * sizeof(double));
        }
    }

    SortFuncInt intSorts[] = {bubbleSort, bubbleSortOpt, gnomeSort, quickSort, heapSort, radixSort};

    printf("=== Sorting Algorithms Benchmark ===\n");
    printf("Runs per test: %d | Max random value: %d\n\n", NUM_RUNS, maxRandomValue);

    // Run tests for each size and case
    for (int s = 0; s < validSizes; s++) {
        long size = sizes[s];
        printf("Testing size: %ld\n", size);
        printf("%-15s", "Algorithm");
        printf("%12s %12s %12s\n", "Random(s)", "Best(s)", "Worst(s)");
        printf("-----------------------------------------------------------\n");

        for (TestCase tc = CASE_RANDOM; tc <= CASE_WORST; tc++) {
            // Allocate arrays
            int *intArray = (int *)malloc(size * sizeof(int));
            float *floatArray = (float *)malloc(size * sizeof(float));

            if (!intArray || !floatArray) {
                fprintf(stderr, "Memory allocation failed for size %ld\n", size);
                free(intArray);
                free(floatArray);
                continue;
            }

            generateArray(intArray, size, maxRandomValue, tc);
            generateFloatArray(floatArray, size, tc);

            // Run integer sorts (algorithms 0-5)
            for (int a = 0; a < 6; a++) {
                results[s][tc][a] = runIntSort(intSorts[a], intArray, size, NUM_RUNS);
            }

            // Run bucket sort (algorithm 6)
            results[s][tc][6] = runBucketSort(floatArray, size, NUM_RUNS);

            free(intArray);
            free(floatArray);
        }

        // Print results for this size
        for (int a = 0; a < NUM_ALGORITHMS; a++) {
            printf("%-15s", algorithmNames[a]);
            for (int c = 0; c < 3; c++) {
                printf("%12.6f ", results[s][c][a]);
            }
            printf("\n");
        }
        printf("\n");
    }

    // Export to CSV if requested
    if (csvFile) {
        FILE *fp = fopen(csvFile, "w");
        if (fp) {
            // Header
            fprintf(fp, "Size,Case");
            for (int a = 0; a < NUM_ALGORITHMS; a++) {
                fprintf(fp, ",%s", algorithmNames[a]);
            }
            fprintf(fp, "\n");

            // Data
            for (int s = 0; s < validSizes; s++) {
                for (int c = 0; c < 3; c++) {
                    fprintf(fp, "%ld,%s", sizes[s], caseNames[c]);
                    for (int a = 0; a < NUM_ALGORITHMS; a++) {
                        fprintf(fp, ",%.6f", results[s][c][a]);
                    }
                    fprintf(fp, "\n");
                }
            }
            fclose(fp);
            printf("Results exported to: %s\n", csvFile);
        } else {
            fprintf(stderr, "Error: Could not create CSV file '%s'\n", csvFile);
        }
    }

    // Cleanup
    for (int s = 0; s < validSizes; s++) {
        for (int c = 0; c < 3; c++) {
            free(results[s][c]);
        }
        free(results[s]);
    }
    free(results);
    free(sizes);

    return 0;
}
