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
    struct Cache *temp;
    temp = malloc(sizeof(struct Cache));
    if(temp == NULL) {
        fprintf(stderr, "ERROR: could not malloc Cache struct\n");
        return NULL;
    }

    temp->blockSize = blockSize;
    if(associativity >= 0)
        temp->setCount = cacheSize / (blockSize * associativity);
    else
        temp->setCount = 1;
    temp->replacementMode = malloc(sizeof(char) * 5);
    if(temp->replacementMode == NULL) {
        fprintf(stderr, "ERROR: could not set block replacement mode\n");
        free(temp);
        return NULL;
    }
    strcpy(temp->replacementMode, mode);

    return temp;
}
