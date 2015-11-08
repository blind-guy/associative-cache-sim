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

    // include statements
    #include    <stdio.h>
    #include    <stdlib.h>
    #include    <math.h>
    #include    <string.h>

    // the typedef 
    typedef struct{
        unsigned long cacheSize;
        unsigned long blockSize;
        int associativity;
        int traceFlag;
        char *replacementMode;
    } Parameters;

    // function prototypes
    int set_parameters(int, char **, Parameters *);
    void print_usage();
#endif   
