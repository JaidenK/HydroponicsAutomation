// System libraries
#include <stdio.h>
#include <stdlib.h> // rawterm, restore term
#include <signal.h> // For catching ctrl+c
#include <stdint.h> // Integer data types
#include <math.h> // for sin cos
#include <string.h>
#include <time.h> // for debounce clock
#include <unistd.h> // getopt
#include <errno.h> // Error number

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

#define MIN(a,b) (((a)<(b))?(a):(b))

// Flag for the main loop
volatile uint8_t isRunning = 1;

// Signal interrupt handler
void INThandler(int);

// Displays the ip and waits for the joystick to be pressed.
// return 1 to shut down return 2 to continue
int displayIP(void);

// Joystick interrupts
void joy_up(void);
void joy_down(void);
void joy_left(void);
void joy_right(void);
void joy_click(void);

// Debouncing
clock_t t_joyDebounceEvent = 0;
clock_t t_joyDebounceDuration = CLOCKS_PER_SEC / 2; // 1 second debounce
// For some reason CLOCKS_PER_SEC seems to be twice the real value?
int debounce(clock_t *t_lastEvent, clock_t debounceDuration, void (*func)());

enum hydro_states{
  HYDRO_IDLE, // Not doing anything in particular
  WIFI_SELECTING_NETWORK, // Start up, selecting network
  STARTUP_DISP_IP // On bootup, display IP so I can SSH into it
} hydro_state;

// Wifi
// Used during the GUI screen where they select which network to connect to
int selectedNetwork = -1;

int xJoy = 0;
int yJoy = 0;
    
int clicked = 0;

// Screen width and height
int width, height;

// General printing
char buf[1024];
// Password string for wifi
char passBuf[256];

int main(int argc, char *argv[]) {
  hydro_state = HYDRO_IDLE;

  // Analyze options
  int c = 0;
  while ((c = getopt (argc, argv, "i")) != -1) {
    switch(c) {
      case 'i':
        // Start up in IP display mode. Don't actually run the full program.
        hydro_state = STARTUP_DISP_IP;
        break;
    }
  }


  // Specify the interrupt handler for ctrl+c
  signal(SIGINT, INThandler);
  
  // Setup GPIO
  wiringPiSetup();
  
  // Pins for the Y axis of the joystick (op-amp output). 
  // BCM 23, 22, 27, 17, 4, 3
  JOY_Init(3,2,7,0,9,joy_up,joy_down,joy_left,joy_right,joy_click);
  JOY_PreventNegativePositions();
  
  VG_KB_Init();
  
  // Setup Graphics
  // Graphics
  saveterm(); // Save current screen
  init(&width, &height); // Initialize display and get width and height
  Start(width, height);
  //rawterm(); // Needed to receive control characters from keyboard, such as ESC
  
  Background(0, 0, 0);					// Black background
  Fill(255, 255, 255, 1);					// White text
  TextMid((width/2), (height/2), "Testing network connection...", SerifTypeface, height/20);	// Greetings 
  End();
  
  if(hydro_state == STARTUP_DISP_IP) {
    // Blocking function will wait until the user presses the joystick
    // button to exit.
    while(1) {
      int returnCode = displayIP();
      if(returnCode == 1) {
        // Close program
        exit(0);
      }else if(returnCode == 2) {
        // continue program
        break;
      }
    }
  }

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
  // HTTP_Init("sdp.ballistaline.com");
  // char response[1024];
  //HTTP_Get("dataReceiver.php", "ProductID=25258&foo=bar", response, 1024);
  //printf("Response:\n%s\n",response);
  // HTTP_Get("dataReceiver.php", "ProductID=264&foo=bar", response, 1024);
  // printf("Response:\n%s\n",response);
  
  
  
  memset(passBuf,0,strlen(passBuf));
  // Main loop
  while(isRunning) {
    Background(0, 0, 0);					// Black background
    
    /*
    // Keyboard stuff
    VG_KB_Draw(0,0,width,height);
    Fill(255, 255, 255, 1);
    Text(50,height-60,"Enter WiFi password:",SerifTypeface, 40);
    // X pos offset by the string length if it gets too long, 50 otherwise.
    Text(50+MIN(0,width-35*(int)strlen(passBuf)),height-120,passBuf,SerifTypeface, 40);
    */

    
    
    // Draw screen
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

void addKeyToPassword() {
  int len = strlen(passBuf);
  char c = VG_KB_KeyPress();
  printf("VG_KB: %c\n",c);
  if(c == '\0') {
    // Do nothing
  } else if(c == '\b') {
    // backspace
    passBuf[len-1] = '\0';
  } else if(c == '\n') {
    // enter
    printf("Password: %s\n", passBuf);
  } else {
    passBuf[len] = c;
    passBuf[len+1] = '\0';
  }
}

void joy_click(void) {
  clicked = !clicked;
  switch(hydro_state) {
    case HYDRO_IDLE:
      break;
    case WIFI_SELECTING_NETWORK:
      selectedNetwork = yJoy;
      break;
    case STARTUP_DISP_IP:
      isRunning = 0;
      break;
  }
  debounce(&t_joyDebounceEvent,t_joyDebounceDuration,addKeyToPassword);
}

int debounce(clock_t *t_lastEvent, clock_t debounceDuration, void (*func)()) {
  clock_t now = clock();
  if(now - *t_lastEvent > debounceDuration) {
    *t_lastEvent = now;
    func();
    return 0;
  }else{
    printf("Debounced.\n");
  }
  return 1;
}

int displayIP() {
  char ipStr[256]; // Surely we wont need 256 chars for the ip string?
  char line[512]; // line for reading output
  FILE *console = popen("ifconfig | grep wlan0 -A1","r");
  if(console==NULL) {
    printf("Could not make ifconfig system call.\n%s\n",strerror(errno));
  }
  // Loop through each line of file
  while(fgets(line,512,console)!=NULL){
    char *word = strstr(line,"inet");
    if(word != NULL) {
      word += 5; // Move pointer past inet
      sscanf(word,"%s",ipStr);
      break;
    }
  }
  pclose(console);
  printf("%s\n",ipStr);

  Background(0, 0, 0);          // Black background
  Fill(255, 255, 255, 1);         // White text
  sprintf(line, "IP: %s",ipStr);
  TextMid((width/2), (height/2), line, SerifTypeface, height/20);   
  TextMid((width/2), (height/2)-(2*height/20), "Press Joystick to close.", SerifTypeface, height/20);   
  End();
  
  clock_t now = clock();
  while(clock() - now < CLOCKS_PER_SEC) {
    if(isRunning == 0) {
      return 1;
    }
  }
  return 0;
}
