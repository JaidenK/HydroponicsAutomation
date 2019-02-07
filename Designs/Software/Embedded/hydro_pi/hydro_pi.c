// System libraries
#include <stdio.h>
#include <stdlib.h> // rawterm, restore term
#include <signal.h> // For catching ctrl+c
#include <stdint.h> // Integer data types

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
    sprintf(buf, "Pos: %d", QEI_GetPosition());
    TextMid(width / 2, height / 2, buf, SerifTypeface, width / 10);	// Greetings 
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
