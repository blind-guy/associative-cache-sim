/*----------------------------------------------------------------------------*/
/*                                  SET.C                                     */
/*----------------------------------------------------------------------------*/
/* contains function code for printing set
 *
 * AUTHOR: hvi604@my.utsa.edu
 */

#include "set.h"

/**
 * print out the contents of a set including its index, and blocks with their
 * tags and access time
 * PARAMETERS: a ponter to a Set struct
 */
void print_set(struct Set *mySet)
{
    int count;
    for(count = 0; count < mySet->blockCount; count++) {
        fprintf(stdout, "%lx\(%lu\)",
                mySet->blocks[count].tag, mySet->blocks[count].accessTime);
        if(count + 1 != mySet->blockCount)
            fprintf(stdout, ",");
    }
    fprintf(stdout, "\n");
}
