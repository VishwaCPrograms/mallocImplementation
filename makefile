# Author: Vishwa Venkateshwaran, Nathalie Kaspar

all: mem_test

mem_test: my_malloc.c mem_test.c my_malloc.h
	gcc my_malloc.c mem_test.c -o mem_test

cleanO:
	rm -rf *.o

clean:
	rm -rf memMan *.o
