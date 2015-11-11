/*----------------------------------------------------------------------------*/
/*                                CACHE.H                                     */
/*----------------------------------------------------------------------------*/
/* struct definition, includes, and function prototypes for the cache struct
 *
 * AUTHOR: hvi604@my.utsa.edu
 */

#ifndef CACHE_H
    #define CACHE_H

    // includes
    #include   <string.h>
    #include   <stdlib.h>
    #include   <stdio.h>

    #include    "set.h"

    // struct cache
    struct Cache{
        unsigned long blockSize;
        unsigned long setCount;
        char *replacementMode;
        struct Set *sets;
    };

    // function prototypes
    unsigned long get_tag(struct Cache *, unsigned long);
    void write_cache(struct Cache *, struct Set *, unsigned long, unsigned long);
    struct Block *block_lookup(struct Cache*, unsigned long, struct Set *);
    struct Set *cache_lookup(struct Cache *, unsigned long);
    struct Cache *init_cache(unsigned long, unsigned long, int, char *);
#endif
