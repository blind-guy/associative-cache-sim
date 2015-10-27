/*------------------------------------------------------------------------------
 *                                 DRIVER.C                                    
 *------------------------------------------------------------------------------
 * AUTHOR: hvi604@my.utsa.edu
 *
 * Simulate an associative cache, the size, block size, and associativity of
 * which are  given on the command line. Replacement scheme is also specified as
 * either being lru or fifo. Tracing is specified as on or off and a file
 * containing the 32 bit addresses is given. These are written one per line and
 * may be in either hex with the preceding 0x or decimal.
 *
 * An example invocation of the program is as follows:
 * $ driver 16 6 3 fifo on addresslist.txt
 *
 * The above indicates a cache of size 2^16 bytes containing blocks of 2^6 bytes
 * with sets containing 2^3 blocks. The replacement scheme used is fifo with
 * tracing on and the addresses contained in the file "addreslist.txt"
 */

#include    "driver.h"

int main(int argc, char* argv[])
{
    if(validate_args(argc, argv) != 0)
        exit(1);

    FILE *fin;
	if((fin = retrieve_file(argv[6])) == NULL)
        exit(1);

    fclose(fin);
    return 0;
}

/**
 * retrieve the file argument
 * 
 * PARAMETERS: char *
 * RETURNS: FILE pointer on success or NULL
 */
FILE *retrieve_file(char* token)
{
    FILE *tmp = fopen(token, "r");
	if(tmp == NULL) {
        fprintf(stderr, "ERROR: could open input file %s\n", token);
        fprintf(stderr, "TERMINATING SIMULATION\n");
    }
	return tmp;
}

/**
 * validate arguments by confirming the following:
 * -there are exactly 6 arguments excluding the program name
 * -both the cache and block size are greater than 0
 * -assocaitivity is greater than or equal to 0
 * -the cache size is greater than or equal to the block size
 * -the assocativity multiplied by the block size is equal or less than the
 *  block size
 * -the replacement scheme is either fifo or lru
 * -trace is either on or off
 *
 * PARAMETERS: int, char**
 * RETURN: 0 indicating success and 1 indicating arguments were not valid
 */
int validate_args(int count, char* arguments[])
{
    // check the number of arguments
    if(count != 7) {
        fprintf(stderr, "ERROR: could not validate command line arguments\n");
        fprintf(stderr, "INFO: invalid number of arguments\n");
        fprintf(stderr, "PROPER USAGE:\n");
        fprintf(stderr, "$ driver n m p fifo/lru on/off filename\n");
        fprintf(stderr, "TERMINATING SIMULATION\n");
        return 1;
    }

	int val1, val2, val3;

    // check that the cache and block size arguments are valid
    if((val1 = atoi(arguments[1])) <= 0 ||
       (val2 = atoi(arguments[2])) <= 0 ||
        val1 < val2) {
        fprintf(stderr, "ERROR: could not validate command line arguments\n");
        fprintf(stderr, "PROPER USAGE:\n");
        fprintf(stderr, "$ driver n m p fifo/lru on/off filename\n");
        fprintf(stderr, "INFO: n, m, and p are the log base 2 values of cache");
        fprintf(stderr, " size, block size, and associativity respectively.\n");
        fprintf(stderr, "INFO: cache size and block size must be greater");
        fprintf(stderr, " than zero and the cache size must be greater than");
        fprintf(stderr, " or equal to the the block size\nTERMINATING");
        fprintf(stderr, " SIMULATION\n");
        return 1;
    }

    // ensure that the associativity argument is valid
    if((val3 = atoi(arguments[3])) < 0) {
        fprintf(stderr, "ERROR: could not validate command line arguments\n");
        fprintf(stderr, "INFO: assocativity must be greater than or equal to");
        fprintf(stderr, " zero\nTERMINATING SIMULATION\n");
        return 1;
    }

    // ensure that the cache size, block size, and associativy arguments
    // play nicely with eacher other
    if (pow(2.0, (double) val2) * pow(2.0, (double) val3) >
        pow(2.0, (double) val1)) {
        fprintf(stderr, "ERROR: could not validate command line arguments\n");
        fprintf(stderr, "INFO: the associativity multiplied by the block size");
        fprintf(stderr, " cannot be greater than the size of the cache\n");
        fprintf(stderr, "TERMINATING SIMULATION\n");
        return 1;
    }

    // validate the replacement scheme argument
    if(strcmp("fifo", arguments[4]) != 0 && strcmp("lru", arguments[4]) != 0) {
        fprintf(stderr, "ERROR: could not validate command line arguments\n");
        fprintf(stderr, "PROPER USAGE:\n");
        fprintf(stderr, "$ driver n m p fifo/lru on/off filename\n");
        fprintf(stderr, "INFO: replacement scheme must be either lru or");
        fprintf(stderr, " fifo\nTERMINATING SIMULATION\n");
        return 1;
    }

    // validate the trace argument
    if(strcmp("on", arguments[5]) != 0 && strcmp("off", arguments[5]) != 0) {
        fprintf(stderr, "ERROR: could not validate command line arguments\n");
        fprintf(stderr, "PROPER USAGE:\n");
        fprintf(stderr, "$ driver n m p fifo/lru on/off filename\n");
        fprintf(stderr, "INFO: tracing must be set to either on or off\n");
        fprintf(stderr, "TERMINATING SIMULATION\n");
        return 1;
    }

    return 0;
}

