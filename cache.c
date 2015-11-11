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
 * given a cache and an address translate get the tag
 * PARAMATERS: a Cache struct and an unsigned long address
 * RETURNS: an unsigned long representing a block tag
 */
unsigned long get_tag(struct Cache *myCache, unsigned long address)
{
    unsigned long blockAddress = address / myCache->blockSize;
    unsigned long tag = blockAddress / myCache->setCount;
    return tag;
}

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

/**
 * given a cache with a set replacement scheme, an address and a Set we insert
 * a block corresponding to the information given by the address
 * PARAMETERS: a Cache struct, a Set struct, an unsigned long address,
 *             unsigned long access time
 * RETURNS: nothing
 */
void write_cache
(
    struct Cache *myCache, struct Set *mySet, unsigned long address,
    unsigned long accessTime
)
{
    unsigned long blockAddress = address / myCache->blockSize;
    unsigned long tag = blockAddress / myCache->setCount;
    if(mySet->blockCount < mySet->maxBlockCount) {
        mySet->blocks[mySet->blockCount].tag = tag;
        mySet->blocks[mySet->blockCount].accessTime = accessTime;
        mySet->blockCount++;
    } else {
        int count;
        struct Block block = mySet->blocks[0];
        for(count = 0; count < mySet->blockCount; count++){
            if(mySet->blocks[count].accessTime < block.accessTime)
                block = mySet->blocks[count];
        }
    }
}

/**
 * given a cache, address, and set lookup the block referenced by the address if
 * it exists
 * PARAMETERS: pointer to our cache, an unsigned long address, a set
 * RETURNS: a pointer to the Block or NULL if not found
 */
struct Block *block_lookup
(
    struct Cache *myCache, unsigned long address, struct Set *mySet
)
{
    unsigned long blockAddress = address / myCache->blockSize;
    unsigned long tag = blockAddress / myCache->setCount;
    int count;
    for(count = 0; count < mySet->blockCount; count++) {
        if(mySet->blocks[count].tag == tag)
            return &(mySet->blocks[count]);
    }
    return NULL;
}

/**
 * given a cache and an address return a pointer to the set in the cache
 * PARAMETERS: a pointer to our cache and an unsigned long representing
 * the address for lookup
 * RETURNS: a pointer to the set identified by the address
 */
struct Set *cache_lookup(struct Cache *myCache, unsigned long address)
{
    unsigned long blockOffset = address % myCache->blockSize;
    unsigned long blockAddress = address / myCache->blockSize;
    unsigned long index = blockAddress % myCache->setCount;
    return &(myCache->sets[index]);
}

