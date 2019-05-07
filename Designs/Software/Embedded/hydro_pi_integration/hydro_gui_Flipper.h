#ifndef _HYDRO_GUI_FLIPPER_H
#define _HYDRO_GUI_FLIPPER_H

#include "hydro_gui_GuiElement.h"

/**
 * @file hydro_gui_Flipper.h
 * A flipper number input.
 */

typedef struct {
  GuiElement *gui_base;
  int w; // Pixel width
  int h; // Pixel height
  int wholeDigits; // # digits before decimal point
  int decimalDigits; // # digits after decimal point
  double value;
  double delta;
  int units;
  int pos; // Selected position
  void (*draw)(void *self); 
} Flipper;

Flipper *newFlipper(int x, int y, int w, int h, int wholeDigits, int decimalDigits, double initialValue);

#endif
