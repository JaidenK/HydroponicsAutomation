#ifndef _HYDRO_GUI_ICONBUTTON_H
#define _HYDRO_GUI_ICONBUTTON_H

#include "hydro_gui_GuiElement.h"

#include <shapes.h>

/**
 * @file hydro_gui_IconButton.h
 * A button for the gui
 */

enum IconButtonType {
   IB_GEAR
};

typedef struct {
  GuiElement *gui_base;
  int w;
  int h;
  VGfloat *xPoints;
  VGfloat *yPoints;
  int pointCount;
  void (*draw)(void *self); // These are the same pointers as the base obj
  void (*click)(void *self);
} IconButton;

IconButton *newIconButton(int x, int y, int w, int h, enum IconButtonType bType);

#endif
