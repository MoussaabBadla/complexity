CC = gcc
CFLAGS = -Wall -O2

SRCS = main.c \
       ./bubbleSort/bubblesort.c \
       ./gnomeSort/gnomeSort.c \
       ./radixSort/radixSort.c \
       ./quickSort/quickSort.c \
       ./heapSort/heapSort.c \
       ./bucketSort/bucketSort.c

mini:
	$(CC) $(CFLAGS) $(SRCS) -o project

clean:
	rm -f project

run: mini
	./project 100 500 1000 5000

test: mini
	./project -c results.csv 100 500 1000 5000 10000
