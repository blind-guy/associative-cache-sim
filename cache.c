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
    temp->sets = temp->size / (temp->blockSize * temp->associativity);

    return temp;
}

/**
 * free a cache
 *
 * PARAMETERS: struct cache*
 */
void free_cache(struct cache *mycache)
{
    free(mycache);
}

/**
 * print information representative of the cache's fields
 *
 * PARAMETERS: struct cache *
 */
void print_cache_info(struct cache *mycache)
{
    fprintf(stdout, "Cache size: %lu\n", mycache->size);
    fprintf(stdout, "Cache block size: %lu\n", mycache->blockSize);
    fprintf(stdout, "Cache associativity: %d\n", mycache->associativity);
    fprintf(stdout, "Cache set count: %lu\n", mycache->sets);
}
