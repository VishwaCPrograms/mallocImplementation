/* Authors: Nathalie K, Vishwa V */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define HEAP_SIZE 420
#define META_SIZE sizeof(heap);

typedef struct memoryArea heap;
struct memoryArea {
    heap* next;
    heap* prev;
    int size;
    int used;
};

void mem_init(void);
void* myMalloc(int);
void myFree(void*);
