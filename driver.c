/*----------------------------------------------------------------------------*/
/*                                DRIVER.C                                    */
/*----------------------------------------------------------------------------*/
/* This is the main code for managing an associative cache simulator including
 * processing arguments, initializing requisite variables for cache properties
 * and processing accesses.
 * 
 * The format for the command to invoce this program is as follows:
 * $driver n m p fifo/lru on/off filename
 *
 * n, m, and p are integer arguments representing the cache size, block size,
 * and associativity respectively. These are given in log base 2 of the desired
 * values so p=2 would represent an associativity of 4 and p=0 would represent
 * a direct mapped cache.
 *
 * NOTE: if p is negative or p > n - m then the cache is fully associative
 *
 * n and m must be positive integers and due to the nature of caches m must
 * be greater than or equal to n.
 *
 * The 4th argument to the program represents the replacement scheme given as
 * as fifo or lru.
 * 
 * The 5th argument is set to either on or off for tracing.
 * 
 * The filename refers to a file containing a series of 32 bit addresses listed
 * one per line and given as either integers or hex values with the preceding
 * 0x notation.
 *
 * AUTHOR: hvi604@my.utsa.edu
 */

#include    "driver.h"

int main(int argc, char* argv[])
{
    // initialize a parameters struct to hold our converted arguments
    // and fill it using what's been given on the command line
    Parameters *cacheParameters; 
    cacheParameters = malloc(sizeof(Parameters));
    if(set_parameters(argc, argv, cacheParameters) != 0){
        fprintf(stderr, "ERROR: could not set cache parameters\n");
        fprintf(stderr, "TERMINATING SIMULATION\n");
        exit(1);
    }
    print_parameters(cacheParameters);
}

/**
 * validate the command line arguments and set the members of the Parameters
 * struct 
 * PARAMETERS: the arguments array and a pointer to the Parameters struct
 * RETURNS: 0 on success or -1 on failure
 */
int set_parameters(int argCount, char *arguments[], Parameters *myParameters)
{
    // ensure we have the right number of arguments
    if(argCount != 7) {
        fprintf(stderr, "ERROR: incorrect number of arguments in invocation\n");
        print_usage();
        return -1;
    }

    // convert the cache and block size arguments to integers and validate them
    int cacheArg, blockArg;
    cacheArg = atoi(arguments[1]);
    blockArg = atoi(arguments[2]);
    if(cacheArg <= 0) {
        fprintf(stderr, "ERROR: first argument is log base two of cache size ");
        fprintf(stderr, "and must be an integer greater than zero\n");
        return -1;
    }
    if(blockArg <= 0) {
        fprintf(stderr, "ERROR: second argument is log base two of cache size");
        fprintf(stderr, " and must be an integer greater than zero\n");
        return -1;
    }
    if(blockArg > cacheArg) {
        fprintf(stderr, "ERROR: cannot set block size to be larger than cache");
        fprintf(stderr, " size\n");
        return -1;
    }

    // convert the associativity argument to an integer
    int associativityArg = atoi(arguments[3]);

    // set the cacheSize and blockSize members of the Parameters struct
    myParameters->cacheSize = (unsigned long) pow(2.0, cacheArg);
    myParameters->blockSize = (unsigned long) pow(2.0, blockArg);

    // set the associativity member of the Parameters struct
    if(associativityArg < 0 || associativityArg > cacheArg - blockArg) {
        myParameters->associativity = -1;
    } else {
        myParameters->associativity = (int) pow(2.0, associativityArg);
    }

    // validate the replacement mode and set it
    if(strcmp("fifo", arguments[4]) != 0 && strcmp("lru", arguments[4]) != 0) {
        fprintf(stderr, "ERROR: replacement mode must be either fifo or lru\n");
        print_usage();
        return -1;
    }
    myParameters->replacementMode = malloc(5 * sizeof(char));
    strcpy(myParameters->replacementMode, arguments[4]);

    // validate trace flag argument and set the trace flag member of the
    // Parameters struct appropriately
    if(strcmp("on", arguments[5]) != 0 && strcmp("off", arguments[5]) != 0) {
        fprintf(stderr, "ERROR: trace mode must be set to either on or off\n");
        print_usage();
        return -1;
    }
    if(strcmp("on", arguments[5]) == 0) {
        myParameters->traceFlag = 1;
    } else {
        myParameters->traceFlag = 0;
    }
    return 0;    
}

/**
 * print simulation program invocation information
 */
void print_usage()
{
    fprintf(stderr, "PROPER USAGE:\n\t$./driver n m p lru/fifo on/off ");
    fprintf(stderr, "filename\n\nn, m, and p are log base two values ");
    fprintf(stderr, "representing cache size, block size, and associativity.");
    fprintf(stderr, " n and m must be greater than zero and cache size must ");
    fprintf(stderr, "be greater than block size. Any value of p less than 0 ");
    fprintf(stderr, "or greater than n - m sets the cache to being fully ");
    fprintf(stderr, "assciative.\n\nEither fifo or lru is typed to indicate");
    fprintf(stderr, "block replacement scheme.\n\nTrace output is set to ");
    fprintf(stderr, "on or off.\n\nThe file containing access addresses is ");
    fprintf(stderr, "indicated by filename.\n\n");
}

/**
 * prints out the cache simulation parameters after they have been converted
 * PARAMETERS: a Parameters struct containing our cache parameters
 */
print_parameters(Parameters *myParameters)
{
    fprintf(stderr, "Cache size: %lu\n", myParameters->cacheSize);
    fprintf(stderr, "Block size: %lu\n", myParameters->blockSize);
    fprintf(stderr, "Associaitivity: ");
    if(myParameters->associativity < 0)
        fprintf(stderr, "fully associative\n");
    else
        fprintf(stderr, "%d\n", myParameters->associativity);
    fprintf(stderr, "Replacement scheme: %s\n", myParameters->replacementMode);
    fprintf(stderr, "Tracing is ");
    if(myParameters->traceFlag)
        fprintf(stderr, "on\n");
    else
        fprintf(stderr, "off\n");
}
