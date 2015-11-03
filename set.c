/*------------------------------------------------------------------------------
 *                                  SET.C
 *-----------------------------------------------------------------------------
 * contains function codes for handling sets within the simulated cache
 *
 * AUTHOR: hvi604@my.utsa.edu
 */

#include    "set.h"

/**
 * initializes a cache set given a size and index
 * PARAMETERS: the value of the maximum size, the value of the set's index
 * RETURNS: a pointer to the new set struct or NULL on failure
 */
struct set *init_set(unsigned long index, int maxCount, char *mode)
{
    if(maxCount < 0) {
        fprintf(stderr, "ERROR: tried to initialize a set with a negative");
        fprintf(stderr, " count\n");
        return NULL;
    }

    struct set tmp;

    tmp = malloc(sizeof(struct set));
    
    if(tmp == NULL) {
        fprintf(stderr, "ERROR: malloc error\n");
        return NULL;
    }

    set->index = index;
    set->maxCount = maxCount;
    set->count = 0;
    strcpy(set->replacementMode, mode);
    set->header = NULL;
    set->footer = NULL;

    return set;
}

/**
 * given a set struct we need to free the memory it points to including
 * the doubly linked list for blocks
 * PARAMETERS: the set we want to free
 */
void free_set(struct set *myset)
{
    if(set == NULL)
        return;
    
    struct block *next = set->header;
    
    while(next != NULL) {
        struct block *current = next;
        next = current->next;
        free(current);
    }

    free(set);

    return;
}

/**
 * given a set and a tag we check to see if the block associated with that
 * tag is in the set
 * PARAMETERS: a set to search, a tag to search for
 * RETURNS: a pointer to the block if it exists in the set or NULL
 */
struct block *block_search(struct set *myset, unsigned long tag)
{
    if(set == NULL)
        return NULL;
    if(set->count == 0)
        return NULL;
    struct block *next = myset->header;
    while(tmp != NULL){
        if(tmp->tag == tag)
            return tmp; 
        tmp = tmp->next;
    }
    return tmp;
}


