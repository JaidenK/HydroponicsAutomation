// System libraries
#include <stdio.h>
#include <stdlib.h> // rawterm, restore term
#include <signal.h> // For catching ctrl+c
#include <stdint.h> // Integer data types
#include <math.h> // for sin cos

// Peripheral libraries
#include <wiringPi.h>

// Graphics
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>

// My libraries
#include "QEI.h"

// Flag for the main loop
volatile uint8_t isRunning = 1;

uint8_t pin1prevState = 0;
int edges = 0;

void INThandler(int);
uint8_t isRisingEdge(int pin);

int main(int argc, char *argv[]) {
  // Specify the interrupt handler for ctrl+c
  signal(SIGINT, INThandler);
  
  // Setup GPIO
  wiringPiSetup();
  // Initialize QEI with GPIO Pins 24, 25
  QEI_Init(5,6);
  // Pins for the Y axis of the joystick (op-amp output)
  pinMode(1,INPUT);
  pinMode(4,INPUT);
  
	int width, height;
  // Graphics
  saveterm(); // Save current screen
  init(&width, &height); // Initialize display and get width and height
  //initWindowSize(10,10,100,200);
  //width = 100; 
  //height = 200;
  Start(width, height);
  //rawterm(); // Needed to receive control characters from keyboard, such as ESC
  
  
  
  // Main loop
  while(isRunning) {
    Background(0, 0, 0);					// Black background
    Fill(44, 77, 232, 1);					// Big blue marble
    Circle(width / 2, 0, width);			// The "world"
    Fill(255, 255, 255, 1);					// White text
    char buf[100];
    int pos = QEI_GetPosition();
    sprintf(buf, "Pos: %d", pos);
    TextMid((width/2)+(width/2)*cos(-pos/100.0+M_PI/2), (width/2)*sin(-pos/100.0+M_PI/2), buf, SerifTypeface, 10);	// Greetings 
    
    // Color the circles based on the joystick readings.
    Fill(255,255,255,0.3 + digitalRead(1)*0.7);
    Circle(width / 2, height/2 + 30, 40);
    Fill(255,255,255,0.3 + digitalRead(4)*0.7);
    Circle(width / 2, height/2 - 30, 40);
    
    // Square on highlighted one
    int selected = (abs(pos)/4)%4;
    if(pos<0) {
      selected = 3-selected;
    }
    Fill(255,255,255,1);
    Roundrect(width/2 + 200*selected - 305, height/2+95, 50, 50, 15, 15);
    
    // Squares
    Fill(77,255,255,1);
    Roundrect(width/2 - 100, height/2+100, 40, 40, 10, 10);
    Roundrect(width/2 - 300, height/2+100, 40, 40, 10, 10);
    Roundrect(width/2 + 100, height/2+100, 40, 40, 10, 10);
    Roundrect(width/2 + 300, height/2+100, 40, 40, 10, 10);
    
    
    
    End();	
  }
  printf("\n");
  
  // Close the OpenVG stuff
  finish(); // Graphics cleanup
  restoreterm(); 
  return 0;
}

void INThandler(int sig) {
  isRunning = 0;
}

uint8_t isRisingEdge(int pin) {
  uint8_t pinState = digitalRead(pin);
  uint8_t hasRisingEdge = (pin1prevState != pinState) && pinState;
  pin1prevState = pinState;
  return hasRisingEdge;
}
