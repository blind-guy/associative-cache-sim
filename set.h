/*------------------------------------------------------------------------------
 *                                  SET.H
 *------------------------------------------------------------------------------
 * contins struct definition for a set within a cache which is implemented as a
 * double linked list base node
 *
 * AUTHOR: hvi604@my.utsa.edu
 */

#ifndef SET_H
    #define SET_H

    #include   "block.h"

    struct set{
        unsigned long index;
        unsigned long maxCount;
        unsigned long count;
        char replacementMode[5];
        struct block *header;
        struct block *footer;
    }

    struct set *init_set(unsigned long, int, char *);
    void free_set(struct set *);
    struct block *block_search(struct set *, unsigned long);
#endif
