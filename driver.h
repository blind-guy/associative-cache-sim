/*------------------------------------------------------------------------------
 *                                DRIVER.H
 *------------------------------------------------------------------------------
 * contains includes and configurations for the driver functions
 *
 * AUTHOR: hvi604@my.utsa.edu
 */

#ifndef  DRIVER_H
    #define DRIVER_H

    #include    <stdio.h>
    #include    <stdlib.h>
    #include    <string.h>
    #include    <math.h>

    #include     "cache.h"

    struct cache;

    void access_addresses(FILE *, struct cache *);
    unsigned long get_address(char *);
    FILE *retrieve_file(char *);
    int validate_args(int, char**);
#endif
