/* Authors: Nathalie K, Vishwa V */

#include "my_malloc.h"

int main(int argc, const char * argv[]) {
    mem_init();
    
    void* test_use_all_empty = myMalloc(340);
    assert(test_use_all_empty != NULL);
    myFree(test_use_all_empty);

    void* test_zero = myMalloc(0);
    assert(test_zero != NULL);

    void* test_negative = myMalloc(-1); 
    assert(test_negative == NULL);
    
    void* test_small = myMalloc(5);
    assert(test_small != NULL);

    void* test_big = myMalloc(120);
    assert(test_big != NULL);

    myFree(test_small);
    myFree(test_big);

    void* test_overload = myMalloc(2000);
    assert(test_overload == NULL);

    void* test_free_blocks_joined = myMalloc(340);
    assert(test_free_blocks_joined != NULL);
    myFree(test_free_blocks_joined);

    return 0;
}

