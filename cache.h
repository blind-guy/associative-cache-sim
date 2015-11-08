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

    // struct cache
    struct Cache{
        unsigned long blockSize;
        unsigned long setCount;
        char *replacementMode;
    };

    struct Cache *init_cache(unsigned long, unsigned long, int, char *);
#endif
