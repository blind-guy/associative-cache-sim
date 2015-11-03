/*------------------------------------------------------------------------------
 *                                 CACHE.C
 *------------------------------------------------------------------------------
 * functions for handling our cache struct
 *
 * AUTHOR: hvi604@my.utsa.edu
 */

#include    "cache.h"

/**
 * initialize a cache and set its size, blockSize, associativity, and sets
 * members
 *
 * PARAMETERS: int, int, int
 * RETURN: pointer to new cache on success or NULL on failure
 */
struct cache* init_cache(int size, int blockSize, int associativity)
{
    struct cache *temp;
    temp = malloc(sizeof(struct cache));
    if (temp == NULL){
        fprintf(stderr, "ERROR: could not malloc cache\n");
        return NULL;
    }

    // clean up memory to make sure we have no garbage stored
    memset(temp, 0, sizeof(struct cache));

    temp->size = (int) pow(2.0, size);
    temp->blockSize = (int) pow(2.0, blockSize);
    temp->associativity = (int) pow(2.0, associativity);
    temp->setCount = temp->size / (temp->blockSize * temp->associativity);

    return temp;
}

/**
 * free a cache
 *
 * PARAMETERS: struct cache*
 */
void free_cache(struct cache *myCache)
{
    free(myCache);
}

/**
 * print information representative of the cache's fields
 *
 * PARAMETERS: struct cache *
 */
void print_cache_info(struct cache *myCache)
{
    fprintf(stdout, "Cache size: %lu\n", myCache->size);
    fprintf(stdout, "Cache block size: %lu\n", myCache->blockSize);
    fprintf(stdout, "Cache associativity: %d\n", myCache->associativity);
    fprintf(stdout, "Cache set count: %lu\n", myCache->setCount);
}

/**
 * given an address return pointer to a block in the cache if it exists or NULL
 * it's not available
 *
 * PARAMETERS: struct cache *, unsigned long
 * RETURN: struct block *
 */
struct block *cache_lookup(struct cache *myCache, unsigned long address)
{
    if(myCache == NULL || myCache->sets == NULL)
        return NULL;

	unsigned long offset, blockAddress, index, tag;
    offset = address % myCache->blockSize;
    blockAddress = address / (myCache->blockSize * myCache->associativity);
    index = blockAddress % myCache->setCount;
    tag = blockAddress / myCache->setCount;

	return block_lookup(myCache->sets[index], tag);
}
