#ifndef _VG_FLIPPER_H
#define _VG_FLIPPER_H

/**
 * @file vg_flipper.h
 * Creates an on-screen flipper-like number display with 
 * variable width
 * 
 */

/**
 * Initializes the keyboard.
 * @param width The number of digits before the decimal point
 * @param decimalPlaces The number of digits after the decimal point
 * @param initialValue The initial value...
 */
void VG_FLIPPER_Init(int width, int decimalPlaces, double initialValue);

/**
 * Enables the flipper so that moving the joystick has an effect.
 */
void VG_FLIPPER_Enable();
/**
 * Disables the flipper so that moving the joystick has no effect.
 */ 
void VG_FLIPPER_Disable();

/**
 * Frees any memory associated with the flipper
 */
void VG_FLIPPER_Destroy();

/**
 * Returns the current value of the flipper.
 */
double VG_FLIPPER_GetValue();

/**
 * Sets the current value.
 */
void VG_FLIPPER_SetValue(double newValue);

/**
 * Moves the cursor around the flipper.
 * For the left/right, it returns 1 if it moves off the 
 * flipper.
 */
void VG_FLIPPER_Up();
void VG_FLIPPER_Down();
int VG_FLIPPER_Left();
int VG_FLIPPER_Right();

/**
 * Draws the flipper 
 */
void VG_FLIPPER_Draw(int x, int y, int w, int h);


#endif
