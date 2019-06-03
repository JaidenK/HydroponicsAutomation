// System libraries
#include <stdio.h>
#include <stdlib.h> // rawterm, restore term
#include <signal.h> // For catching ctrl+c
#include <stdint.h> // Integer data types
#include <math.h> // for sin cos
#include <string.h>
#include <unistd.h> // getopt usleep
#include <errno.h> // Error number
#include <time.h>
#include <libusb.h> //libusb

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

#include "USBCom.h"
#include "sensor_data.h"
#include "Protocol.h"

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

static struct SensorData sd;
static struct SensorData prevSD;
static char rx_data[64]; // Receive data block
static 	message_t msg;   // message data


// General printing
#define BUF_SIZE 1024
static char buf[BUF_SIZE];
// Password string for wifi
// static char passBuf[256];

unsigned int loopCount = 0;

void parseCmd(char *cmd, double val) {
  if(strcmp(cmd,"flow")==0) {
    printf("Flow target changed from %f to %f.\n", sd.flow_target, val);
    sd.flow_target = val;
  }else if(strcmp(cmd,"ph")==0) {
    printf("pH target changed from %f to %f.\n", sd.ph_target, val);
    sd.ph_target = val;
  }else if(strcmp(cmd,"ec")==0) {
    printf("EC target changed from %f to %f.\n", sd.ec_target, val);
    sd.ec_target = val;
  }else if(strcmp(cmd,"water")==0) {
    printf("Water level target changed from %f to %f.\n", sd.h2o_target, val);
    sd.h2o_target = val;
  }else if(strcmp(cmd,"q")==0) {
    INThandler(15);
  }else{
    printf("Invalid command: %s\n", cmd);
  }
}

static libusb_device_handle* dev; // Pointer to data structure representing USB device

void *sdThread(void * vargp){
	while(1){
		
		while (dev == NULL) {
			dev = USBCom_Init();
			if (dev == NULL) {
				printf("Unable to claim USB device\n");
			}
		}
		
		for (int i = 0; i < 64; i++)
			rx_data[i] = 0;

		if (USBCom_CheckReceivedData(rx_data)) {
			msg = Protocol_DecodeInput(rx_data);
			if(updateSensors(&msg, &sd) != -1){
				//Protocol_PrintMessage(&msg);
			}
		}
		
	}
}

void * httpThread(void *vargp){
	
	time_t timestamp;
	
	//Initialize HTTP library
	HTTP_Init("sdp.ballistaline.com");
	char request[1024];
	char response[1024];
	char buffer[1024];
	
	timestamp = time(NULL);
	
	while(1){
		if (difftime(time(NULL), timestamp) > 60) {
			timestamp = time(NULL);
			getGETstr(request, &sd);
			if(HTTP_Get("dataReceiver.php", request, response, 1024) != -1){
				//update targets
				prevSD = sd;
				if(HTTP_ParseResponse(response, &sd)){
					if(prevSD.h2o_target != sd.h2o_target){
						Protocol_EncodeOutput(h20_level_target, sd.h2o_target,buffer);
						USBCom_SendData(buffer);
					}
					if(prevSD.flow_target != sd.flow_target){
						Protocol_EncodeOutput(flow_target, sd.flow_target,buffer);
						USBCom_SendData(buffer);
					}
					if(prevSD.ph_target != sd.ph_target){
						Protocol_EncodeOutput(ph_target, sd.ph_target,buffer);
						USBCom_SendData(buffer);
					}
					if(prevSD.ec_target != sd.ec_target){
						Protocol_EncodeOutput(ec_target, sd.ec_target,buffer);
						USBCom_SendData(buffer);
					}	
				}
			}
			else{
				printf("Error GET\n");
			}
		}
	}
}
void checkTargetChange(){
	char buffer[BUF_SIZE];
	if(prevSD.h2o_target != sd.h2o_target){
		Protocol_EncodeOutput(h20_level_target, sd.h2o_target,buffer);
		USBCom_SendData(buffer);
		prevSD.h2o_target = sd.h2o_target;
	}
	if(prevSD.flow_target != sd.flow_target){
		Protocol_EncodeOutput(flow_target, sd.flow_target,buffer);
		USBCom_SendData(buffer);
		prevSD.flow_target = sd.flow_target;
	}
	if(prevSD.ph_target != sd.ph_target){
		Protocol_EncodeOutput(ph_target, sd.ph_target,buffer);
		USBCom_SendData(buffer);
		prevSD.ph_target = sd.ph_target;
	}
	if(prevSD.ec_target != sd.ec_target){
		Protocol_EncodeOutput(ec_target, sd.ec_target,buffer);
		USBCom_SendData(buffer);
		prevSD.ec_target = sd.ec_target;
	}
}
int main(int argc, char *argv[]) {
  hydro_state = HYDRO_IDLE;


  // Specify the interrupt handler for ctrl+c
  signal(SIGINT, INThandler);
  
  // Setup GPIO
  wiringPiSetup();

  HYDRO_GUI_Init(1,&sd);
  ThreadedInput_Init();
  
  //Sensor data thread
  sensor_data_init(&sd);
  pthread_t thread_sd;
  pthread_create(&thread_sd, NULL, sdThread, NULL);
  
  //HTTP ThreadedInput_Init
  pthread_t thread_http;
  pthread_create(&thread_http, NULL, httpThread, NULL);
  
  
  
  printf("Waiting (to allow network to connect).\n");
  usleep(2000000);
  
  // memset(passBuf,0,strlen(passBuf));
  // Main loop
  while(isRunning) {

    //logData(sd,"logfile.dat");

    // Test for user input
    if(getstr_nonblocking(buf)) {
      char cmd[16];
      // char val[16];
      double val_d = 0;
      sscanf(buf,"%s %lf",cmd,&val_d);
      parseCmd(cmd,val_d);
    }
	checkTargetChange();
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
