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
#include "notifications.h"

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

SensorData *sd;

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

  // Specify the interrupt handler for ctrl+c
  signal(SIGINT, INThandler);
  
  // Setup GPIO
  wiringPiSetup();

  sd = malloc(sizeof(SensorData));
  setRandomData(sd);

  HYDRO_GUI_Init(1,sd);
  ThreadedInput_Init();
  
  printf("Waiting (to allow network to connect).\n");
  usleep(2000000);
    
  // Initialize HTTP library
  HTTP_Init("sdp.ballistaline.com");
  char response[1024];  
  
  // memset(passBuf,0,strlen(passBuf));
  // Main loop
  while(isRunning) {
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
      // Returns a line
      char* line = strtok(response, "\n"); 
      // loops through each line.
      while (line != NULL) { 
        char key[256];
        double value = 0;
        sscanf(line,"%s %lf",key,&value);
        if(strcmp(key,"flow_target")==0) {
          if(value > 0) {
            sd->flow_target = value;
            printf("%s -> %f\n", key, value);
          }
        }
        if(strcmp(key,"ph_target")==0) {
          if(value > 0) {
            sd->ph_target = value;
            printf("%s -> %f\n", key, value);
          }
        }
        if(strcmp(key,"ec_target")==0) {
          if(value > 0) {
            sd->ec_target = value;
            printf("%s -> %f\n", key, value);
          }
        }
        if(strcmp(key,"water_target")==0) {
          if(value > 0) {
            sd->h2o_target = value;
            printf("%s -> %f\n", key, value);
          }
        }
        // printf("line: %s\n", token); 
        line = strtok(NULL, "\n"); 
      } 
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
