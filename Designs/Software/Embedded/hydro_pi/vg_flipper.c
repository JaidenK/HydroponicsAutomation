#include "vg_flipper.h"

#include <stdint.h>
#include <stdio.h>
#include <math.h>

// Graphics
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>

// Value being displayed
double val = 0;

// The position selected
int pos = 0;
// The amount an up/down changes the value. Based on position.
// Values are 10, 1, 0.1, 0.01 etc
double delta = 1;

int flipper_width = 0;
int decimalPlaces = 0;

int isEnabled = 1;

int flipper_units = 50;
int margin = 10;

void VG_FLIPPER_Init(int _flipper_width, int _decimalPlaces, double initialValue) {
  flipper_width = _flipper_width;
  decimalPlaces = _decimalPlaces;
  val = initialValue;
  delta = pow(10,flipper_width-1);
}

void VG_FLIPPER_Destroy() {
  // Does nothing
}

double VG_FLIPPER_GetValue() {
  return val;
}

void VG_FLIPPER_SetValue(double newValue) {
  val = newValue;
}

void VG_FLIPPER_Up() {
  if(val + delta < pow(10,flipper_width)) {
    val += delta;
  }
}
void VG_FLIPPER_Down() {
  val -= delta;
  if(val < 0) {
    val = 0;
  }
}
int VG_FLIPPER_Left() {
  pos -= 1;
  delta = pow(10,flipper_width-pos-1);
  if (pos < 0) {
    pos = -1;
    return 1;
  }
  return 0;
}
int VG_FLIPPER_Right() {
  pos += 1;
  delta = pow(10,flipper_width-pos-1);
  if (pos > flipper_width + decimalPlaces - 1) {
    pos = flipper_width + decimalPlaces;
    return 1;
  }
  return 0;
}

void VG_FLIPPER_Draw(int x, int y, int w, int h) {
  char s[30];
  sprintf(s,"%f",val);
  Fill(255,255,255,0);
  int xPos = 0;
  // Draw the digits 
  for (int i = 0; i < flipper_width + decimalPlaces; i++) {
    double mask = pow(10,(flipper_width - i - 1)); // 10, 1, etc
    int digit = ((int)(val / mask)) % 10; // Get the digit from the val
    sprintf(s,"%d",digit); // store the digit in a string for printing

    if(i == pos) {
      // Change stroke to yellow if you're on the selected position
      Stroke(255,255,0,1);
    }else{
      // White stroke for unselected numbers
      Stroke(255,255,255,1); 
    }
    xPos = x+i*(flipper_units+margin+margin*(i>=flipper_width));
    StrokeWidth(5);
    Fill(255,255,255,0);
    Roundrect(xPos, y, flipper_units, 3*flipper_units/2, margin, margin);
    Fill(255,255,255,1);
    TextMid(xPos + flipper_units/2, y+flipper_units/4, s, SerifTypeface, flipper_units);   
  }
  // Finished drawing all the digits. Draw the decimal point.
  if(decimalPlaces>0) {
    StrokeWidth(0);
    Fill(255,255,255,1);
    Circle(x+flipper_width*(flipper_units+margin)+margin,y+margin,flipper_units/4);
  }
  Fill(255,255,255,0);

  StrokeWidth(0);  
}
