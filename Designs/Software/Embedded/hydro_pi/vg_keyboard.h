#ifndef _VG_KEYBOARD_H
#define _VG_KEYBOARD_H

/**
 * @file vg_keyboard.h
 * Creates an on-screen keyboard that can be navigated with up/down/left/right
 * commands.
 * 
 */

/**
 * Initializes the keyboard
 */
void VG_KB_Init();

/**
 * Frees any memory associated with the keyboard
 */
void VG_KB_Destroy();

/**
 * "Presses" the currently selected key and either swaps the character 
 * set (like if Shift was presssed) or returns the selected char.
 * @return A character if one is selected or NULL if a control key was pressed.
 */
char VG_KB_KeyPress();

/**
 * Moves the cursor around the keyboard.
 */
void VG_KB_Up();
void VG_KB_Down();
void VG_KB_Left();
void VG_KB_Right();

/**
 * Draws the keyboard centered within these bounds, keeping its aspect ratio.
 */
void VG_KB_Draw(int x, int y, int w, int h);


#endif
