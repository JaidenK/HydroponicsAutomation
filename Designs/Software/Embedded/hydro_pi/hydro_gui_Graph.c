#include "hydro_gui_Graph.h"
#include "hydro_gui_GuiElement.h"

#include <stdlib.h>
#include <stdio.h>

// Graphics
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>

typedef struct GraphPoint GraphPoint;
struct GraphPoint {
  struct SensorData *sd;
  GraphPoint *next;
};

GraphPoint *firstPoint;
GraphPoint *lastPoint;

void drawGraph(void *graph);
void drawGraph2(void *parent);

Graph *newGraph(int x, int y, int w, int h) {
  Graph *newObj = malloc(sizeof(Graph));
  GuiElement *baseObj = newGuiElement(x,y,newObj);
  newObj->gui_base = baseObj;
  newObj->w = w;
  newObj->h = h;
  newObj->draw = drawGraph;
  baseObj->draw = drawGraph2;

  firstPoint = malloc(sizeof(GraphPoint));
  lastPoint = firstPoint;
  return newObj;
}

void addGraphPoint(struct SensorData *sd) {
  lastPoint->next = malloc(sizeof(GraphPoint));
  lastPoint = lastPoint->next;
  lastPoint->sd = sd;
}

void clickGraph2(void *btn_) {
   GuiElement *gui_elem = btn_;
   ((Graph *)gui_elem->child)->click(gui_elem->child);
}
void clickGraph(void *btn_) {
   Graph *btn = btn_;
   printf("The \"%s\" Graph has not been assigned a click function.\n",btn->label);
}

// A hack to make the parent element pass the child
void drawGraph2(void *btn_) {
  GuiElement *gui_elem = btn_;
  drawGraph(gui_elem->child);
}

void drawGraph(void *graph_) {
  Graph *graph = graph_;
  GraphPoint *currPoint = firstPoint;
  printf("Graph:\n");
  while(currPoint) {
    printf("%d\n", currPoint->sd->flow_measured);
  }
}
