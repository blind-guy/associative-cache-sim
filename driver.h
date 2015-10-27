/*------------------------------------------------------------------------------
 *                                DRIVER.H
 *------------------------------------------------------------------------------
 * contains includes and configurations for the driver functions
 *
 * AUTHOR: hvi604@my.utsa.edu
 */

#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <math.h>

unsigned long get_address(char *);
FILE *retrieve_file(char *);
int validate_args(int, char**);

