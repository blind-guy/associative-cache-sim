/*----------------------------------------------------------------------------*/
/*                                 SET.H                                      */
/*----------------------------------------------------------------------------*/
/* contains struct definition, includes, and function prototypes for handiling
 * Set structs
 *
 * AUTHOR: hvi604@my.utsa.edu
 */

#ifndef SET_H
    #define SET_H

    // includes
    #include   "block.h"

    // struct Set containing its max count, current count, and index
    struct Set{
        unsigned long blockCount;
        unsigned long maxBlockCount;
        unsigned long index;
        struct Block *blocks;
    };

    // prototypes
#endif
