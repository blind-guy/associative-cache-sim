/*------------------------------------------------------------------------------
 *                                CACHE.H
 *------------------------------------------------------------------------------
 * contains definition and prototypes for handling cache struct
 *
 * AUTHOR: hvi604@my.utsa.edu
 */

#ifndef     DRIVER_H
    #define     DRIVER_H

    #include    <stdlib.h>
    #include    <stdio.h>
    #include    <math.h>
    #include    <string.h>

    struct cache{
        unsigned long size;
        unsigned long blockSize;
        unsigned long sets;
        int associativity;
    };

    struct cache* init_cache(int, int, int);
    void free_cache(struct cache *);
    void print_cache_info(struct cache *);
#endif
