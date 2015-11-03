/*------------------------------------------------------------------------------
 *                                 BLOCK.H
 *------------------------------------------------------------------------------
 * contains struct for block implemented as a node in a double linked list
 *
 * AUTHOR: hvi604@my.utsa.edu
 */

#ifndef BLOCK_H
    #define BLOCK_H

    struct block{
        unsigned long tag;
        struct block *prev;
        struct block *next;
    };

    struct block *init_block(unsigned long);
    
#endif
