/*----------------------------------------------------------------------------*/
/*                                DRIVER.H                                    */
/*----------------------------------------------------------------------------*/
/* the header file for our associative cache simulator containing a cache
 * parameter struct definition, includes, and prototypes for our driver
 * program
 *
 * AUTHOR: hvi604@my.utsa.edu
 */

#ifndef DRIVER_H
    #define DRIVER_H

    // defines
    #define NAME    "Elijah Arnold"

    // include statements
    #include    <stdio.h>
    #include    <stdlib.h>
    #include    <math.h>
    #include    <string.h>

    #include    "cache.h"
    
    // the typedef 
    struct CacheParameters{
        unsigned long cacheSize;
        unsigned long blockSize;
        int associativity;
        int traceFlag;
        char *replacementMode;
    };

    // function prototypes
    int set_parameters(int, char **, struct CacheParameters *);
    void print_usage();
    unsigned long get_address(char *);
#endif   
