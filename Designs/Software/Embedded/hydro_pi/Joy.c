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

// Accumulated position
int xPosition = 0;
int yPosition = 0;

void JOY_UP_ISR(void);
void JOY_DOWN_ISR(void);
void JOY_LEFT_ISR(void);
void JOY_RIGHT_ISR(void);

void (*callback_up)(void);
void (*callback_down)(void);
void (*callback_left)(void);
void (*callback_right)(void);

void JOY_Init(int chXpos_, int chXneg_, int chYpos_, int chYneg_, void (*func_up)(), void (*func_down)(), void (*func_left)(), void (*func_right)()) {
  
  chXpos = chXpos_;
  chXneg = chXneg_;
  chYpos = chYpos_;
  chYneg = chYneg_;
  callback_up = func_up;
  callback_down = func_down;
  callback_right = func_right;
  callback_left = func_left;
  // Configure the pins for input
  pinMode(chXpos,INPUT);
  pinMode(chXneg,INPUT);
  pinMode(chYpos,INPUT);
  pinMode(chYneg,INPUT);
  // Specify the pull down resistors.
  // (Not sure if necessary)
  pullUpDnControl(chXpos, PUD_DOWN); 
  pullUpDnControl(chXneg, PUD_DOWN); 
  pullUpDnControl(chYpos, PUD_DOWN); 
  pullUpDnControl(chYneg, PUD_DOWN); 
  // Assign the ISRs
  wiringPiISR(chXpos,INT_EDGE_RISING,JOY_RIGHT_ISR);
  wiringPiISR(chXneg,INT_EDGE_RISING,JOY_LEFT_ISR);
  wiringPiISR(chYpos,INT_EDGE_RISING,JOY_UP_ISR);
  wiringPiISR(chYneg,INT_EDGE_RISING,JOY_DOWN_ISR);
  
  
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
  callback_down();
}
void JOY_LEFT_ISR(void) {
  xPosition--;
  callback_left();
}
void JOY_RIGHT_ISR(void) {
  xPosition++;
  callback_right();
}
