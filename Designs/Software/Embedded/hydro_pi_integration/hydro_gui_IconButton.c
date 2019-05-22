#include "hydro_gui_IconButton.h"
#include "hydro_gui_GuiElement.h"

#include <stdlib.h>
#include <stdio.h>

#include <math.h>

// Graphics
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>

// Radius of button corners
#define BTN_RAD 30 
// Depth of button shadow
#define BTN_DEP 10

/**
 * Generates a gear polygon centered in the bounding box
 * @param x Bottom left of bounding box
 * @param y Bottom left of bounding box
 */
void generatePointsList_Gear(int x, int y, int w, int h, int *pointCount, VGfloat **xPoints, VGfloat **yPoints) {
  // int teeth = 4;
  int xCenter = x+w/2;
  int yCenter = y+h/2;
  double radius = (w>h)?h/2:w/2;
  radius *= 0.7;

  *pointCount = 32;
  *xPoints = malloc((*pointCount) * sizeof(VGfloat));
  *yPoints = malloc((*pointCount) * sizeof(VGfloat));

  for(int i = 0; i < *pointCount/2; i++) {
    double r1 = radius * (i%2==0?1.0:0.7);
    double r2 = radius * (i%2==0?0.7:1.0);
    (*xPoints)[2*i] = xCenter + r1*cos(i*M_PI/((*pointCount)/4.0));
    (*yPoints)[2*i] = yCenter + r1*sin(i*M_PI/((*pointCount)/4.0));
    (*xPoints)[2*i+1] = xCenter + r2*cos(i*M_PI/((*pointCount)/4.0));
    (*yPoints)[2*i+1] = yCenter + r2*sin(i*M_PI/((*pointCount)/4.0));
  }
}


void drawIconButton(void *btn);
void drawIconButton2(void *parent);

void clickIconButton(void *btn);
void clickIconButton2(void *parent);

IconButton *newIconButton(int x, int y, int w, int h, enum IconButtonType bType) {
  IconButton *newObj = malloc(sizeof(IconButton));
  GuiElement *baseObj = newGuiElement(x,y,newObj);
  newObj->gui_base = baseObj;
  newObj->w = w;
  newObj->h = h;
  newObj->draw = drawIconButton;
  newObj->click = clickIconButton;
  baseObj->draw = drawIconButton2;
  baseObj->click = clickIconButton2;

  switch(bType) {
    case IB_GEAR:
      generatePointsList_Gear(x,y,w,h, &(newObj->pointCount), &(newObj->xPoints), &(newObj->yPoints));
      break;
  }

  // the click function for this Iconbutton must be defined elsewhere.
  return newObj;
}

void clickIconButton2(void *btn_) {
   GuiElement *gui_elem = btn_;
   ((IconButton *)gui_elem->child)->click(gui_elem->child);
}
void clickIconButton(void *btn_) {
   // IconButton *btn = btn_;
   printf("The Iconbutton has not been assigned a click function.\n");
}

// A hack to make the parent element pass the child
void drawIconButton2(void *btn_) {
  GuiElement *gui_elem = btn_;
  drawIconButton(gui_elem->child);
}

void drawIconButton(void *btn_) {
  IconButton *btn = btn_; // Typecast to avoid void * dereferencing 
  StrokeWidth(0);
  Stroke(255,255,255,1);
  // 3D portion of Iconbutton
  if(btn->gui_base->isSelected){
    Fill(105,105,105,1);
  }else{
    Fill(85,85,85,1);
  }
  Roundrect(btn->gui_base->xPos, btn->gui_base->yPos-BTN_DEP, btn->w, btn->h, BTN_RAD, BTN_RAD);
  
  // Flat part of Iconbutton
  if(btn->gui_base->isSelected){
    StrokeWidth(5);
    Fill(149,149,149,1);
  }else{
    StrokeWidth(0);
    Fill(129,129,129,1);
  }
  Roundrect(btn->gui_base->xPos, btn->gui_base->yPos, btn->w, btn->h, BTN_RAD, BTN_RAD);

  // Icon
  Fill(255,255,255,1);
  Polygon(btn->xPoints, btn->yPoints, btn->pointCount);
}
