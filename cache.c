/*----------------------------------------------------------------------------*/
/*                                CACHE.C                                     */
/*----------------------------------------------------------------------------*/
/* function code for handling cache struct including initialization, freeing,
 * set and block lookup
 *
 * AUTHOR: hvi604@my.utsa.edu
 */

#include    "cache.h"

/**
 * given a cache size, block size, associativity, and replacement mode
 * initialize and fill the members of a Cache struct
 *
 * NOTE: a negative associativity indicates a fully associative cache
 * PARAMETERS: block size, cache size, associativity and mode
 * RETURNS: a pointer to a newly initialized cache
 */
struct Cache *init_cache
(
    unsigned long blockSize, unsigned long cacheSize,
    int associativity,       char *mode
)
{
    // initialize and allocate cache struct
    struct Cache *temp;
    temp = malloc(sizeof(struct Cache));
    if(temp == NULL) {
        fprintf(stderr, "ERROR: could not malloc Cache struct\n");
        return NULL;
    }

    // set number members of Cache struct
    temp->blockSize = blockSize;
    if(associativity >= 0)
        temp->setCount = cacheSize / (blockSize * associativity);
    else
        temp->setCount = 1;
    
    // set replacement mode member of Cache struct
    temp->replacementMode = malloc(sizeof(char) * 5);
    if(temp->replacementMode == NULL) {
        fprintf(stderr, "ERROR: could not set block replacement mode\n");
        free(temp);
        return NULL;
    }
    strcpy(temp->replacementMode, mode);

    // initialize sets
    temp->sets = malloc(sizeof(struct Set) * temp->setCount);
    if(temp->sets == NULL) {
        fprintf(stderr, "ERROR: could not malloc sets for Cache\n");
        free(temp->replacementMode);
        free(temp);
        return NULL;
    }

    // set members of Set structs
    unsigned long count;
    for(count = 0; count < temp->setCount; count++){
        temp->sets[count].index = count;
        temp->sets[count].blockCount = 0;
        if(associativity >= 0)
            temp->sets[count].maxBlockCount = associativity;
        else
            temp->sets[count].maxBlockCount = cacheSize / blockSize;
        temp->sets[count].blocks = malloc(sizeof(struct Block) * 
                                           temp->sets[count].maxBlockCount);
    }

    return temp;
}

void test_cache(struct Cache *myCache)
{
    fprintf(stderr, "Cache Block Size: %lu\n", myCache->blockSize);
    fprintf(stderr, "Cache Set Count: %lu\n", myCache->setCount);
    fprintf(stderr, "Block Replacement Mode: %s\n", myCache->replacementMode);
    unsigned long count;
    for(count = 0; count < myCache->setCount; count++) {
        fprintf(stderr, "SET: %lu\n", myCache->sets[count].index);
        fprintf(stderr, "\tBlock Count: %lu\n", myCache->sets[count].blockCount);
        fprintf(stderr, "\tMax Block Count: %lu\n", myCache->sets[count].maxBlockCount);
    }
}
