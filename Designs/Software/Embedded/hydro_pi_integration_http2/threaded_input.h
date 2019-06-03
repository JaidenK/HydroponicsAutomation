#ifndef THREADED_INPUT_H
#define THREADED_INPUT_H


/**
 * @file threaded_input.h
 * Allows non-blocking reading of the input terminal.
 */

/**
 * Creates a thread for reading input.
 */
void ThreadedInput_Init();

/**
 * @return a pointer to the last line entered by the user. NULL if there
 *         has not been a line entered since the last call to this 
 *         function.
 * @warning It's possible to miss a line of input if this isn't called
 *          before the next line is entered.
 */ 
char *getstr_nonblocking();

#endif
