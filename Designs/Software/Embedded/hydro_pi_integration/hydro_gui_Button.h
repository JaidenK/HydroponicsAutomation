#ifndef _HYDRO_GUI_BUTTON_H
#define _HYDRO_GUI_BUTTON_H

#include "hydro_gui_GuiElement.h"

/**
 * @file hydro_gui_Button.h
 * A button for the gui
 */

typedef struct {
  GuiElement *gui_base;
  int w;
  int h;
  char label[64];
  void (*draw)(void *self); // These are the same pointers as the base obj
  void (*click)(void *self);
} Button;

Button *newButton(int x, int y, int w, int h, char *label);

#endif
