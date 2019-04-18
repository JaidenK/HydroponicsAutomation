// System libraries
#include <stdio.h>
#include <stdlib.h> // rawterm, restore term
#include <signal.h> // For catching ctrl+c
#include <stdint.h> // Integer data types
#include <math.h> // for sin cos
#include <string.h>
#include <unistd.h> // getopt usleep
#include <errno.h> // Error number

// Peripheral libraries
#include <wiringPi.h>

// Graphics
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>

// My libraries
#include "http.h"
#include "hydro_gui.h"
#include "sensor_data.h"
#include "threaded_input.h"

#define MIN(a,b) (((a)<(b))?(a):(b))

#define MAIN_DELAY 200000

// Flag for the main loop
volatile uint8_t isRunning = 1;

// Signal interrupt handler
void INThandler(int);

enum hydro_states{
  HYDRO_IDLE, // Not doing anything in particular
  WIFI_SELECTING_NETWORK, // Start up, selecting network
  STARTUP_DISP_IP // On bootup, display IP so I can SSH into it
} hydro_state;

// Wifi
// Used during the GUI screen where they select which network to connect to
// static int selectedNetwork = -1;

// static int clicked = 0;

struct SensorData *sd;

// General printing
#define BUF_SIZE 1024
static char buf[BUF_SIZE];
// Password string for wifi
// static char passBuf[256];

unsigned int loopCount = 0;

void parseCmd(char *cmd, double val) {
  if(strcmp(cmd,"flow")==0) {
    printf("Flow target changed from %f to %f.\n", sd->flow_target, val);
    sd->flow_target = val;
  }else if(strcmp(cmd,"ph")==0) {
    printf("pH target changed from %f to %f.\n", sd->ph_target, val);
    sd->ph_target = val;
  }else if(strcmp(cmd,"ec")==0) {
    printf("EC target changed from %f to %f.\n", sd->ec_target, val);
    sd->ec_target = val;
  }else if(strcmp(cmd,"water")==0) {
    printf("Water level target changed from %f to %f.\n", sd->h2o_target, val);
    sd->h2o_target = val;
  }else if(strcmp(cmd,"q")==0) {
    INThandler(15);
  }else{
    printf("Invalid command: %s\n", cmd);
  }
}

int main(int argc, char *argv[]) {
  hydro_state = HYDRO_IDLE;

  // Analyze options
  // int c = 0;
  // while ((c = getopt (argc, argv, "i")) != -1) {
  //   switch(c) {
  //     case 'i':
  //       // Start up in IP display mode. Don't actually run the full program.
  //       hydro_state = STARTUP_DISP_IP;
  //       break;
  //   }
  // }

  // Specify the interrupt handler for ctrl+c
  signal(SIGINT, INThandler);
  
  // Setup GPIO
  wiringPiSetup();

  sd = malloc(sizeof(struct SensorData));
  setRandomData(sd);

  HYDRO_GUI_Init(1,sd);
  ThreadedInput_Init();


  
/*
  // if(hydro_state == STARTUP_DISP_IP) {
  //   // Blocking function will wait until the user presses the joystick
  //   // button to exit.
  //   while(1) {
  //     int returnCode = displayIP();
  //     if(returnCode == 1) {
  //       // Close program
  //       exit(0);
  //     }else if(returnCode == 2) {
  //       // continue program
  //       break;
  //     }
  //   }
  // }
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
*/
  printf("Waiting (to allow network to connect).\n");
  usleep(2000000);
    
  // Initialize HTTP library
  HTTP_Init("sdp.ballistaline.com");
  char response[1024];  
  
  // memset(passBuf,0,strlen(passBuf));
  // Main loop
  while(isRunning) {
    
    /*
    // Keyboard stuff
    VG_KB_Draw(0,0,width,height);
    Fill(255, 255, 255, 1);
    Text(50,height-60,"Enter WiFi password:",SerifTypeface, 40);
    // X pos offset by the string length if it gets too long, 50 otherwise.
    Text(50+MIN(0,width-35*(int)strlen(passBuf)),height-120,passBuf,SerifTypeface, 40);
    */

    randomWalk(sd);
    logData(sd,"logfile.dat");

    // Upload the data ocassionally 
    if(loopCount % (10*1000000/MAIN_DELAY) == 0) {
      if(HTTP_getStatus() != HTTP_IDLE) {
        printf("Warning: HTTP busy. %s\n", HTTP_getStatusString());
      }else{
        // Load the sensor data as a formatted string into a char buffer
        memset(buf,0,BUF_SIZE);
        getGETstr(buf,sd);
        // Upload the data to the website
        HTTP_Get("dataReceiver.php",buf);
      }
    }

    // Once the http response is ready, print it out.
    if(HTTP_GetResponse(response)) {
      printf("Response received.\n");
      // printf("%s\n", response);
    }

    // Test for user input
    if(getstr_nonblocking(buf)) {
      char cmd[16];
      // char val[16];
      double val_d = 0;
      sscanf(buf,"%s %lf",cmd,&val_d);
      parseCmd(cmd,val_d);
    }
    loopCount++;
    usleep(MAIN_DELAY);
  }
  printf("\n");
  
  // Close the OpenVG stuff
  finish(); // Graphics cleanup
  restoreterm(); 
  return 0;
}

void INThandler(int sig) {
  isRunning = 0;
  // finish(); // Graphics cleanup
  // restoreterm(); 
  // exit(0);
}
