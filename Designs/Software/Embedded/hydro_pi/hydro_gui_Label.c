#include "hydro_gui_Button.h"
#include "hydro_gui_GuiElement.h"

#include <stdlib.h>
#include <stdio.h>

// Graphics
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>

// Radius of button corners
#define BTN_RAD 30 
// Depth of button shadow
#define BTN_DEP 10

void drawButton(void *btn);
void drawButton2(void *parent);

void clickButton(void *btn);
void clickButton2(void *parent);

Button *newButton(int x, int y, int w, int h, char *label) {
  Button *newObj = malloc(sizeof(Button));
  GuiElement *baseObj = newGuiElement(x,y,newObj);
  newObj->gui_base = baseObj;
  newObj->w = w;
  newObj->h = h;
  sprintf(newObj->label,label);
  newObj->draw = drawButton;
  baseObj->draw = drawButton2;
  baseObj->click = clickButton2;
  // the click function for this button must be defined elsewhere.
  return newObj;
}

void clickButton2(void *btn_) {
   GuiElement *gui_elem = btn_;
   ((Button *)gui_elem->child)->click(gui_elem->child);
}

// A hack to make the parent element pass the child
void drawButton2(void *btn_) {
  GuiElement *gui_elem = btn_;
  drawButton(gui_elem->child);
}

void drawButton(void *btn_) {
  Button *btn = btn_; // Typecast to avoid void * dereferencing 
  StrokeWidth(0);
  Stroke(255,255,255,1);
  // 3D portion of button
  if(btn->gui_base->isSelected){
    Fill(105,105,105,1);
  }else{
    Fill(85,85,85,1);
  }
  Roundrect(btn->gui_base->xPos, btn->gui_base->yPos-BTN_DEP, btn->w, btn->h, BTN_RAD, BTN_RAD);
  
  // Flat part of button
  if(btn->gui_base->isSelected){
    StrokeWidth(5);
    Fill(149,149,149,1);
  }else{
    StrokeWidth(0);
    Fill(129,129,129,1);
  }
  Roundrect(btn->gui_base->xPos, btn->gui_base->yPos, btn->w, btn->h, BTN_RAD, BTN_RAD);

  // Text
  Fill(255,255,255,1);
  TextMid(btn->gui_base->xPos+btn->w/2, btn->gui_base->yPos+btn->h/4, btn->label, SerifTypeface, btn->h/2);   
}
