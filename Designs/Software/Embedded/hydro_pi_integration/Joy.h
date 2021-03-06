#ifndef _JOY_H
#define _JOY_H
/**
 * @file Joy.h
 * @author Jaiden King
 * 
 * API for the 2 axis joystick
 * 
 */


/**
 * Sets up the Joystick interface
 * @param chXpos, chXneg, chYpos, chYneg Pin numbers for the wiringPi pins of the joystick
 * @param func_up, func_down, func_left, func_right Call-back functions which are called in the ISR
 * @note wiringPiSetup() must be called before this.
 */
void JOY_Init(int chXpos, int chXneg, int chYpos, int chYneg, int sw, void (*func_up)(), void (*func_down)(), void (*func_left)(), void (*func_right)(), void (*func_click)());

/**
 * @return The x position of the Joystick.
 */
int JOY_GetXPosition();
/**
 * @return The y position of the Joystick.
 */
int JOY_GetYPosition();

/**
 * Determines whether or not a negative position is allowed.
 */
void JOY_PreventNegativePositions();

#endif
