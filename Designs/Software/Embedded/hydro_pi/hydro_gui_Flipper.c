#include "hydro_gui_Flipper.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Graphics
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>

// Radius of button corners
#define FLIP_RAD 30 
// Depth of button shadow
#define FLIP_DEP 10

int flipperMargin = 10;

GuiElement *flipperMoveUp(void *self);
GuiElement *flipperMoveDown(void *self);
GuiElement *flipperMoveLeft(void *self);
GuiElement *flipperMoveRight(void *self);

void drawFlipper(void *flipper);
void drawFlipper2(void *parent);

Flipper *newFlipper(int x, int y, int w, int h, int wholeDigits, int decimalDigits, double initialValue) {
  Flipper *newObj = malloc(sizeof(Flipper));
  GuiElement *baseObj = newGuiElement(x,y,newObj);
  newObj->gui_base = baseObj;
  newObj->w = w;
  newObj->h = h;
  newObj->pos = 0;
  newObj->value = initialValue;
  newObj->wholeDigits = wholeDigits;
  newObj->decimalDigits = decimalDigits;
  newObj->units = 2*h/3;
  newObj->delta = pow(10,wholeDigits - 1);
  newObj->draw = drawFlipper;
  baseObj->draw = drawFlipper2;
  baseObj->moveUp = flipperMoveUp;
  baseObj->moveDown = flipperMoveDown;
  baseObj->moveLeft = flipperMoveLeft;
  baseObj->moveRight = flipperMoveRight;
  return newObj;
}

void drawFlipper2(void *parent) {
  GuiElement *gui_elem = parent;
  drawFlipper(gui_elem->child);
}

void drawFlipper(void *flipper_) {
  Flipper *flipper = flipper_; // Typecast to avoid void * dereferencing 
  
  Fill(20,20,100,0.8);
  Stroke(0,0,0,0);
  Roundrect(flipper->gui_base->xPos,flipper->gui_base->yPos,(flipper->units+flipperMargin)*(flipper->wholeDigits+flipper->decimalDigits)+flipperMargin,3*flipper->units/2,FLIP_RAD,FLIP_RAD);

  char s[30];
  sprintf(s,"%f",flipper->value);
  Fill(255,255,255,0);
  int xPos = 0;
  // Draw the digits 
  for (int i = 0; i < flipper->wholeDigits + flipper->decimalDigits; i++) {
    double mask = pow(10,(flipper->wholeDigits - i - 1)); // 10, 1, etc
    int digit = ((int)(flipper->value / mask)) % 10; // Get the digit from the val
    sprintf(s,"%d",digit); // store the digit in a string for printing

    if(flipper->gui_base->isSelected && i == flipper->pos) {
      // Change stroke to yellow if you're on the selected position
      Stroke(255,255,0,1);
    }else{
      // no stroke for unselected digits
      Stroke(255,255,255,0); 
    }
    xPos = flipper->gui_base->xPos+i*(flipper->units+flipperMargin)+flipperMargin*(i>=flipper->wholeDigits);
    StrokeWidth(2);
    Fill(255,255,255,0);
    Roundrect(xPos, flipper->gui_base->yPos, flipper->units, 3*flipper->units/2, flipperMargin, flipperMargin);
    Fill(255,255,255,1);
    TextMid(xPos + flipper->units/2, flipper->gui_base->yPos+flipper->units/4, s, SerifTypeface, flipper->units);   
  }
  // Finished drawing all the digits. Draw the decimal point.
  if(flipper->decimalDigits>0) {
    StrokeWidth(0);
    Fill(255,255,255,1);
    Circle(flipper->gui_base->xPos+flipper->wholeDigits*(flipper->units+flipperMargin),flipper->gui_base->yPos+(2*flipperMargin),flipper->units/4);
  }
  Fill(255,255,255,0);

  StrokeWidth(0);  
}


GuiElement *flipperMoveUp(void *self) {
  Flipper *flipper = ((GuiElement *)self)->child;
  if(flipper->value + flipper->delta < pow(10,flipper->wholeDigits)) {
    flipper->value += flipper->delta;
  }else{
    printf("Flipper value too high: %f\n", flipper->value + flipper->delta);
  }
  return self;
}
GuiElement *flipperMoveDown(void *self) { 
  Flipper *flipper = ((GuiElement *)self)->child;
  flipper->value -= flipper->delta;
  if(flipper->value < 0) {
    flipper->value = 0;
  }
  return self;
}
GuiElement *flipperMoveLeft(void *self) {
  Flipper *flipper = ((GuiElement *)self)->child;
  flipper->pos -= 1;
  if (flipper->pos < 0) {
    flipper->pos = 0;
    return ((GuiElement *)self)->left;
  }else{
    flipper->delta = pow(10,flipper->wholeDigits - flipper->pos - 1);
  }
  return self;
}   
GuiElement *flipperMoveRight(void *self) {
  Flipper *flipper = ((GuiElement *)self)->child;
  flipper->pos += 1;
  flipper->delta = pow(10,flipper->wholeDigits - flipper->pos - 1);
  if (flipper->pos > flipper->wholeDigits + flipper->decimalDigits - 1) {
    flipper->pos = flipper->wholeDigits + flipper->decimalDigits - 1;
    return ((GuiElement *)self)->right;
  }
  return self;
}

