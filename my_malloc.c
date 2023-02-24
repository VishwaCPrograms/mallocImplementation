/* Authors: Nathalie K, Vishwa V */

#include "my_malloc.h"

static char heapArray[HEAP_SIZE];
static heap* myHeap;
static heap* biggestBlock;
static int metaSize = META_SIZE;
static int heapSize = HEAP_SIZE;

void mem_init() {
	myHeap = (heap*) heapArray;
	biggestBlock = (heap*) heapArray;
	biggestBlock->size = 0;
	myHeap->size = heapSize - metaSize;
	myHeap->next = NULL;
	myHeap->prev = NULL;
}

static void splitBlocks(heap* currentBlock, int size) {
	heap* remainingBlock = (heap*)((void*)currentBlock + size + metaSize);
	remainingBlock->size = currentBlock->size - size - metaSize;
	remainingBlock->used = 0;
	biggestBlock = remainingBlock;
	currentBlock->size = size;
	currentBlock->used = 1;
	
	remainingBlock->next = currentBlock->next;
	if (currentBlock->next) {
		currentBlock->next->prev = remainingBlock;
	}
	
	currentBlock->next = remainingBlock;
	remainingBlock->prev = currentBlock;
}

void* myMalloc(int size) {
	void* result = NULL;
	if (size >= 0 && size <= heapSize) {
		heap* currentBlock = myHeap;
		if (biggestBlock->size >= size + metaSize) {
			currentBlock = biggestBlock;
			if (currentBlock->size > size + metaSize) {
				splitBlocks(currentBlock, size);
			}
			result = (void*)(currentBlock + metaSize);
			printf("Allocated size of %d bytes!\n\n", size);
		} else {
			heap* bestFitBlock = NULL;
			int bestFitSize = heapSize;
			while (currentBlock) {
				if (currentBlock->used == 0 && (currentBlock->size >= size + metaSize)) {
					if (currentBlock->size < bestFitSize) {
						bestFitBlock = currentBlock;
						bestFitSize = currentBlock->size;
					}
				}
				currentBlock = currentBlock->next;
			}
			if (bestFitBlock) {
				currentBlock = bestFitBlock;
				if (currentBlock->size > size + metaSize) {
					splitBlocks(currentBlock, size);
				}
				result = (void*)(currentBlock + metaSize);
				printf("Allocated size of %d bytes!\n\n", size);
			} else {
				printf("Sorry, memory not available!\n\n");
			}
		}
	}
	return result;
}

static void mergeBlocks(heap* currentBlock) {
	heap* prevBlock = currentBlock->prev;
	heap* nextBlock = currentBlock->next;
	
	currentBlock->used = 0;
	if (prevBlock && prevBlock->used == 0) {
		currentBlock->size += prevBlock->size + metaSize;
		currentBlock->prev = prevBlock->prev;
		if (prevBlock->prev) {
			prevBlock->prev->next = currentBlock;
		}
	}

	if (nextBlock && nextBlock->used == 0) {
		currentBlock->size += nextBlock->size + metaSize;
		currentBlock->next = nextBlock->next;
		if (currentBlock->next) {
			currentBlock->next->prev = currentBlock;
		}
	}

	biggestBlock = currentBlock;
}

void myFree(void* ptr) {
	if (((void*)((heap*) heapArray) <= ptr) && (ptr >= ((void*)((heap*) heapArray) + heapSize)) && ptr) {
		mergeBlocks((heap*)ptr - metaSize);
		printf("Successfully freed!\n\n");
	} else {
		printf("Invalid pointer!\n\n");
	}
}
