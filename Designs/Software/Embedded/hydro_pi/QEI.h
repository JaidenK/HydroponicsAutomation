#ifndef _QEI_H
#define _QEI_H
/**
 * @file QEI.h
 * @author Jaiden King
 * 
 * API for the clicky turny dial
 * 
 */


/**
 * Sets up the Quadrature Encoder Interface
 * @param chA Pin number for the wiringPi pin of channel A
 * @param chB Pin number for the wiringPi pin of channel B
 * @note wiringPiSetup() must be called before this.
 */
void QEI_Init(int chA, int chB);

/**
 * @return The position of the QEI. 4x the physical clicks.
 * 
 */
int QEI_GetPosition();

#endif
