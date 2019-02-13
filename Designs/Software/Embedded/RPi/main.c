#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <wiringPi.h>
#include <errno.h>
#include <libusb.h>
#include "USBCom.h"
#include "sensor_data.h"
#include "http.h"

#define PRODUCT_ID "ABCD1234EFGH5678"
struct SensorData sd;

int main(int argc, char * argv[]) {

	libusb_device_handle* dev; // Pointer to data structure representing USB device
	char tx_data[64]; // Transmit data block
	char rx_data[64]; // Receive data block
	int sent_bytes; // Bytes transmitted
	int rcvd_bytes; // Bytes received
	int return_val;

	sensor_data_init(&sd);
	

	while (dev == NULL) {
		dev = USBCom_Init();
		if (dev == NULL) {
			printf("Unable to claim USB device\n");
		}
	}


	//Initialize HTTP library
	HTTP_Init("sdp.ballistaline.com");
	char request[1024];
	char response[1024];

	getGETstr(request, &sd);
	

	HTTP_Get("dataReceiver.php", request, response, 1024);
	printf("Response:\n%s\n", response);


	// Set up data block 
	strcpy(tx_data, "1:432.12\r\n");
	while (1) {


		USBCom_SendData(tx_data);

		if (return_val != 0) {
			printf("Did Not Recieve Data");
		}

		for (int i = 0; i < 64; i++)
			rx_data[i] = 0;

		if (USBCom_CheckReceivedData(rx_data)) {
			printf("%s\n", rx_data);
		}
	}
}