#ifndef _HYDRO_GUI_GRAPH_H
#define _HYDRO_GUI_GRAPH_H

#include "hydro_gui_GuiElement.h"
#include "sensor_data.h"

/**
 * @file hydro_gui_Graph.h
 * A linegraph for displaying SensorData
 */

typedef struct {
  GuiElement *gui_base;
  int w;
  int h;  
  void (*draw)(void *self);
  void (*click)(void *self);
} Graph;

Graph *newGraph(int x, int y, int w, int h);

void addGraphPoint(struct SensorData *sd);

#endif
