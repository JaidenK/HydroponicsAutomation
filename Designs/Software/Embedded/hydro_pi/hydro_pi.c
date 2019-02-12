// System libraries
#include <stdio.h>
#include <stdlib.h> // rawterm, restore term
#include <signal.h> // For catching ctrl+c
#include <stdint.h> // Integer data types
#include <math.h> // for sin cos
#include <string.h>

// Peripheral libraries
#include <wiringPi.h>

// Graphics
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>

// My libraries
#include "QEI.h"
#include "Joy.h"
#include "http.h"
#include "vg_keyboard.h"

// Flag for the main loop
volatile uint8_t isRunning = 1;

// Signal interrupt handler
void INThandler(int);

// Joystick interrupts
void joy_up(void);
void joy_down(void);
void joy_left(void);
void joy_right(void);
void joy_click(void);

enum hydro_states{
  HYDRO_IDLE, WIFI_SELECTING_NETWORK
} hydro_state;

// Wifi
// Used during the GUI screen where they select which network to connect to
int selectedNetwork = -1;

int xJoy = 0;
int yJoy = 0;
    
int clicked = 0;

// General printing
char buf[1024];


int main(int argc, char *argv[]) {
  // Specify the interrupt handler for ctrl+c
  signal(SIGINT, INThandler);
  
  // Setup GPIO
  wiringPiSetup();
  
  // pinMode(9,OUTPUT);
  // pinMode(3,OUTPUT);
  // pinMode(2,OUTPUT);
  // pinMode(0,OUTPUT);
  // pinMode(7,OUTPUT);
  
  // while(1) {
  //   printf("High\n");
  //   digitalWrite(9,1);
  //   digitalWrite(3,1);
  //   digitalWrite(2,1);
  //   digitalWrite(0,1);
  //   digitalWrite(7,1);
  //   for(unsigned int i =0;i<50000000;i++){}
  //   printf("Low\n");
  //   digitalWrite(9,0);
  //   digitalWrite(3,0);
  //   digitalWrite(2,0);
  //   digitalWrite(0,0);
  //   digitalWrite(7,0);
  //   for(unsigned int i =0;i<50000000;i++){}
  // }
  
  // Initialize QEI with GPIO Pins 24, 25
  //QEI_Init( , );
  // Pins for the Y axis of the joystick (op-amp output). 
  // BCM 23, 22, 27, 17, 4, 3
  JOY_Init(3,2,7,0,9,joy_up,joy_down,joy_left,joy_right,joy_click);
  JOY_PreventNegativePositions();
  
  VG_KB_Init();
  
  // Setup Graphics
	int width, height;
  // Graphics
  saveterm(); // Save current screen
  init(&width, &height); // Initialize display and get width and height
  Start(width, height);
  //rawterm(); // Needed to receive control characters from keyboard, such as ESC
  
  hydro_state = HYDRO_IDLE;
  
  
  Background(0, 0, 0);					// Black background
  Fill(255, 255, 255, 1);					// White text
  TextMid((width/2), (height/2), "Testing network connection...", SerifTypeface, height/20);	// Greetings 
  End();
  
  
  
  // To-do just ping. Maybe they have an ethernet cable.
  
  // Wifi connect console command
  char line[512]; // line
  if(system("iw wlan0 link > console.log")) {
    printf("Error making iw system call.\n");
    exit(1);
  }
  FILE *f = fopen("console.log","r");
  if(f==NULL){
    printf("Error opening file.\n");
      exit(1);
  }
  printf("File contents first line:\n");
  if(fgets(line,512,f)==NULL){
    printf("File should not be empty!\n");
      exit(1);
  };
  puts(line);
  fclose(f);
  
  // Parse the results of the iw wlan0 link
  int isConnected = 0;
  if(strncmp(line,"Not connected.",14)==0) {
    // They're not connected.
    printf("You're not connected to a WiFi network.\n");
    Background(0,0,0);
    TextMid((width/2), (height/2), "Searching for networks...", SerifTypeface, height/20);	// Greetings 
    End();
  }else if(strncmp(line,"Connected",9)==0) {
    printf("You appear to be connected to a network.\n");
    isConnected = 1;
    Background(0,0,0);
    TextMid((width/2), (height/2), "You appear to be connected to a network.", SerifTypeface, height/20);	// Greetings 
    End();
  }else{
    printf("I can't tell if you're connected to a network or not.\n");
    exit(1);
  }
  
  // They need to connect to a network
  if(!isConnected) {
    if(system("iw wlan0 scan > console.log")) {
      printf("Error making iw system call.\n");
      exit(1);
    }
    f = fopen("console.log","r");
    if(f==NULL){
      printf("Error opening file.\n");
      exit(1);
    }
    char networks[10][256]; // 10 possible networks each 256 chars long
    int numNetworks = 0;
    while(fgets(line,512,f)!=NULL){
      char *word = strstr(line,"SSID:");
      if(word != NULL) {
        word += 6; // Move pointer past SSID
        word[strlen(word)-1] = '\0'; // remove newline character
        int networkAlreadyExists = 0;
        for(int i = 0; i < numNetworks; i++) {
          if(strcmp(networks[i],word)==0){
            networkAlreadyExists = 1;
            break;
          }
        }
        if(!networkAlreadyExists) {
          sprintf(networks[numNetworks],"%s",word);
          puts(networks[numNetworks]);
          numNetworks++;
        }
      }
    }
    fclose(f);
    hydro_state = WIFI_SELECTING_NETWORK;
    while(isRunning && selectedNetwork<0) {
      Background(0,0,0);
      yJoy = JOY_GetYPosition();
      for(int i = 0; i < numNetworks; i++){
        Fill(255, 255, 255, 0.5 + (0.5*(yJoy==i)));
        Text(10, i * (height/15)+30, networks[i], SerifTypeface, height/20);	
      }
      End();
    }
    printf("Selected: %s\n",networks[selectedNetwork]);
  }
  
  
  
  
  
  
  
  // Initialize HTTP library
  //HTTP_Init("sdp.ballistaline.com");
  //char response[1024];
  //HTTP_Get("dataReceiver.php", "ProductID=25258&foo=bar", response, 1024);
  //printf("Response:\n%s\n",response);
  //HTTP_Get("dataReceiver.php", "ProductID=264&foo=bar", response, 1024);
  //printf("Response:\n%s\n",response);
  
  
  
  // Main loop
  while(isRunning) {
    Background(0, 0, 0);					// Black background
    Fill(44, 77, 232, 1);					// Big blue marble
    Circle(width / 2, 0, width);			// The "world"
    Fill(255, 255, 255, 1);					// White text
    //char buf[100];
    //int pos = QEI_GetPosition();
    //sprintf(buf, "Pos: %d", pos);
    //TextMid((width/2)+(width/2)*cos(-pos/100.0+M_PI/2), (width/2)*sin(-pos/100.0+M_PI/2), buf, SerifTypeface, 10);	// Greetings 
    
    VG_KB_Draw(0,0,width,height);
    
    // Color the circles based on the joystick readings.
    Fill(255,255,255,0.3 + digitalRead(1)*0.7);
    Circle(width / 2, height/2 + 30, 40);
    Fill(255,255,255,0.3 + digitalRead(4)*0.7);
    Circle(width / 2, height/2 - 30, 40);
    Fill(255,255,255,0.3 + digitalRead(10)*0.7);
    Circle(width / 2 - 30, height/2, 40);
    Fill(255,255,255,0.3 + digitalRead(11)*0.7);
    Circle(width / 2 + 30, height/2, 40);
    
      
    // Selection based on QEI
    // Square on highlighted one
    //int selected = (abs(pos)/4)%4;
    //if(pos<0) {
    //  selected = 3-selected;
    //}
    //Fill(255,255,255,1);
    //Roundrect(width/2 + 200*selected - 305, height/2+95, 50, 50, 15, 15);
    // Squares
    //Fill(77,255,255,1);
    //Roundrect(width/2 - 100, height/2+100, 40, 40, 10, 10);
    //Roundrect(width/2 - 300, height/2+100, 40, 40, 10, 10);
    //Roundrect(width/2 + 100, height/2+100, 40, 40, 10, 10);
    //Roundrect(width/2 + 300, height/2+100, 40, 40, 10, 10);
    
    
    // Display joystick coords
    xJoy = JOY_GetXPosition(); 
    yJoy = JOY_GetYPosition();
    sprintf(buf, "(%d, %d)", xJoy,yJoy);
    TextMid((width/2), (height/2)-400, buf, SerifTypeface, 30);	
    // Grid for joystick as well as selection based on joystick
    for(int row=0;row<5;row++){
      for(int col=0;col<10;col++){
        if((row-2)==-yJoy && (col-5)==xJoy) {
          Fill(255*clicked,255,255,1);
        }else{
          Fill(255,255,255,0.3);
        }
        Roundrect(width/2 - 9*20 + 40*col, height/2-200 - 40*row, 30, 30, 5, 5);
      }
    }
    
    
    
    
    
    
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
  finish(); // Graphics cleanup
  restoreterm(); 
  exit(0);
}

void joy_up(void) {
  VG_KB_Up();
}
void joy_down(void){
  VG_KB_Down();
}
void joy_left(void){
  VG_KB_Left();
}
void joy_right(void){
  VG_KB_Right();
}

void joy_click(void) {
  clicked = !clicked;
  switch(hydro_state) {
    case HYDRO_IDLE:
      break;
    case WIFI_SELECTING_NETWORK:
      selectedNetwork = yJoy;
      break;
  }
}
