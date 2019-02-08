#include "Joy.h"

#include <stdint.h>
#include <stdio.h>

// Peripheral libraries
#include <wiringPi.h>

// Pin assignments
int chXpos = 0;
int chXneg = 0;
int chYpos = 0;
int chYneg = 0;
int chSw = 0;

// Accumulated position
int xPosition = 0;
int yPosition = 0;
int isNegativeAllowed = 1;

void JOY_UP_ISR(void);
void JOY_DOWN_ISR(void);
void JOY_LEFT_ISR(void);
void JOY_RIGHT_ISR(void);

void (*callback_up)(void);
void (*callback_down)(void);
void (*callback_left)(void);
void (*callback_right)(void);
void (*callback_click)(void);

void JOY_Init(int chXpos_, int chXneg_, int chYpos_, int chYneg_, int sw, void (*func_up)(), void (*func_down)(), void (*func_left)(), void (*func_right)(), void (*func_click)()) {
  
  chXpos = chXpos_;
  chXneg = chXneg_;
  chYpos = chYpos_;
  chYneg = chYneg_;
  chSw = sw;
  callback_up = func_up;
  callback_down = func_down;
  callback_right = func_right;
  callback_left = func_left;
  callback_click = func_click;
  // Configure the pins for input
  pinMode(chXpos,INPUT);
  pinMode(chXneg,INPUT);
  pinMode(chYpos,INPUT);
  pinMode(chYneg,INPUT);
  pinMode(chSw,INPUT);
  // Specify the pull down resistors.
  // (Not sure if necessary)
  pullUpDnControl(chXpos, PUD_DOWN); 
  pullUpDnControl(chXneg, PUD_DOWN); 
  pullUpDnControl(chYpos, PUD_DOWN); 
  pullUpDnControl(chYneg, PUD_DOWN);
  // The switch is active low, so this probably _is_ and imporant pull up 
  pullUpDnControl(chSw, PUD_UP); 
  // Assign the ISRs
  wiringPiISR(chXpos,INT_EDGE_RISING,JOY_RIGHT_ISR);
  wiringPiISR(chXneg,INT_EDGE_RISING,JOY_LEFT_ISR);
  wiringPiISR(chYpos,INT_EDGE_RISING,JOY_UP_ISR);
  wiringPiISR(chYneg,INT_EDGE_RISING,JOY_DOWN_ISR);
  wiringPiISR(chSw,INT_EDGE_FALLING,func_click);
  
  
}

int JOY_GetXPosition() {
  return xPosition;
}

int JOY_GetYPosition() {
  return yPosition;
}

void JOY_UP_ISR(void) {
  yPosition++;
  callback_up();
}
void JOY_DOWN_ISR(void) {
  yPosition--;
  if(!isNegativeAllowed&&yPosition<0){
    yPosition = 0;
  }
  callback_down();
}
void JOY_LEFT_ISR(void) {
  xPosition--;
  if(!isNegativeAllowed&&xPosition<0){
    xPosition = 0;
  }
  callback_left();
}
void JOY_RIGHT_ISR(void) {
  xPosition++;
  callback_right();
}
void JOY_PreventNegativePositions() {
  isNegativeAllowed = 0;
}
