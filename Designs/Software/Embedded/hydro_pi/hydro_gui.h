#ifndef _HYDRO_GUI_H
#define _HYDRO_GUI_H

/**
 * @file hydro_gui.h
 * Controls the display of difference scenes for setting references
 * and controls.
 */

// Screen width and height
int width, height;

int framerate;
#define FRAME_PERIOD (1.0 / framerate)
/**
 * Delays until it's time to draw the next frame.
 */
int waitForNextFrame();

/**
 * Initializes components and builds scenes.
 * @param createThread If set to 1 creates a thread that coninuously draws
 * the gui.
 */
void HYDRO_GUI_Init(int createThread);

/**
 * Waits for the next frame then. Draws the gui
 */
void HYDRO_GUI_Draw();

int displayIP();

#endif
