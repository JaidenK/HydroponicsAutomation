#ifndef _HYDRO_GUI_H
#define _HYDRO_GUI_H

#include "sensor_data.h"
#include "hydro_gui_Scene.h"
#include "hydro_gui_Boke.h"

/**
 * @file hydro_gui.h
 * Controls the display of difference scenes for setting references
 * and controls.
 */

// Screen width and height
int width, height;

// A pointer to the same struct used in the main program.
SensorData *gui_sd;

// We reuse this boke between multiple scenes, so just make it global
Boke *boke;
 
Scene *currentScene;
// For drawing the old scene during transitions
Scene *backgroundScene;

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
void HYDRO_GUI_Init(int createThread, struct SensorData *sd);

/**
 * Waits for the next frame then. Draws the gui
 */
void HYDRO_GUI_Draw();

#endif
