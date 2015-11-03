/*------------------------------------------------------------------------------
 *                                BLOCK.C
 *------------------------------------------------------------------------------
 * contains function code for handling blocks
 *
 * AUTHOR: hvi604@my.utsa.edu
 */

#include    "block.h"

/**
 * initialize a block and fill its tag with the assigned value
 * PARAMETER: the value of the tag for this block
 * RETURNS: a pointer to the new block or NULL on failure
 */
struct block *init_block(unsigned long tag)
{
    struct block tmp;

    tmp = malloc(sizeof(struct block));

    if(tmp == NULL) {
        fprintf(stderr, "EROR: malloc error");
        return NULL;
    }

    tmp->tag = tag;

    tmp->prev = NULL;
    tmp->next = NULL;

    return tmp;
}
