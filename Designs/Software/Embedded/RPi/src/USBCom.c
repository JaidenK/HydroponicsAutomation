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

libusb_device_handle* dev; // Pointer to data structure representing USB device
/**
* @function USBCom_Init(void)
* @param None
* @return None
* @brief Initializes USBFS device
* @author Barron Wong 01/31/19
*/
libusb_device_handle* USBCom_Init(void) {

	libusb_init(NULL); // Initialize the LIBUSB library

	if (!USBCom_CheckConfiguration())
		return NULL;

	return dev;
}

/**
 * @function USBCom_CheckConfiguration(void)
 * @param None
 * @return None
 * @brief Checks to see if configuration has changed. If it has it
 *        will reenable the output endpoint
 * @author Barron Wong 01/31/19
 */
uint8_t USBCom_CheckConfiguration(void) {

	// Open the USB device (the Cypress device has
	// Vendor ID = 0x04B4 and Product ID = 0x8051)

	dev = libusb_open_device_with_vid_pid(NULL, 0x04B4, 0x8051);

	if (dev == NULL) {
		perror("device not found\n");
		return FALSE;
	}

	// Reset the USB device.
	// This step is not always needed, but clears any residual state from
	// previous invocations of the program.
	if (libusb_reset_device(dev) != 0) {
		perror("Device reset failed\n");
		return FALSE;
	}

	// Set configuration of USB device
	if (libusb_set_configuration(dev, 1) != 0) {
		perror("Set configuration failed\n");
		return FALSE;
	}


	// Claim the interface.  This step is needed before any I/Os can be
	// issued to the USB device.
	if (libusb_claim_interface(dev, 0) != 0) {
		perror("Cannot claim interface");
		return FALSE;
	}
	return TRUE;
}

/**
* @function USBCom_CheckRecievedData(void)
* @param buffer for data recieved
* @return Length of data in bytes
* @brief Fill a buffer is there is data waiting to be received
* @author Barron Wong 01/31/19
*/
int USBCom_CheckReceivedData(char * buffer) {

	int rcvd_bytes = 0;
	int return_val = 0;

	// Perform the IN transfer (from device to host).
	// This will read the data back from the device.
	return_val = libusb_bulk_transfer(dev, // Handle for the USB device
		(0x01 | 0x80), // Address of the Endpoint in USB device
		// MS bit nust be 1 for IN transfers
		buffer, // address of receive data buffer
		64, // Size of data buffer
		&rcvd_bytes, // Number of bytes actually received
		0 // Timeout in milliseconds (0 to disable timeout)
	);
	if (return_val != 0)
		return 0;
	else
		return rcvd_bytes;
}

/**
* @function USBCom_SendData(uint8 * buffer)
* @param None
* @return None
* @brief Checks to see if configuration has changed. If it has it
*        will reenable the output endpoint
* @author Barron Wong 01/31/19
*/
void USBCom_SendData(char * msg) {
	int sent_bytes = 0;
	int return_val = 0;
	int length = strlen(msg);

	// Perform the OUT transfer (from host to device).
	return_val = libusb_bulk_transfer(dev, // Handle for the USB device
		0x02, // Address of the Endpoint in USB device
		msg, // address of data block to transmit
		64, // Size of data block
		&sent_bytes, // Number of bytes actually sent
		0 // Timeout in milliseconds (0 to disable timeout)
	);

	if (return_val != 0) {
		printf("Incomplete Data Send");
		dev = NULL;
		while (dev == NULL) {
			dev = USBCom_Init();
		}
	}

}

#define USBCOM_TEST
#ifdef USBCOM_TEST

int main(int argc, char * argv[]) {

	libusb_device_handle* dev; // Pointer to data structure representing USB device
	char tx_data[64]; // Transmit data block
	char rx_data[64]; // Receive data block
	int sent_bytes; // Bytes transmitted
	int rcvd_bytes; // Bytes received
	int return_val;

	while (dev == NULL) {
		dev = USBCom_Init();
		if (dev == NULL) {
			printf("Unable to claim USB device\n");
		}
	}

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


	libusb_close(dev);

}
#endif
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

libusb_device_handle* dev; // Pointer to data structure representing USB device
/**
* @function USBCom_Init(void)
* @param None
* @return None
* @brief Initializes USBFS device
* @author Barron Wong 01/31/19
*/
libusb_device_handle* USBCom_Init(void) {

	libusb_init(NULL); // Initialize the LIBUSB library

	if (!USBCom_CheckConfiguration())
		return NULL;

	return dev;
}

/**
 * @function USBCom_CheckConfiguration(void)
 * @param None
 * @return None
 * @brief Checks to see if configuration has changed. If it has it
 *        will reenable the output endpoint
 * @author Barron Wong 01/31/19
 */
uint8_t USBCom_CheckConfiguration(void) {

	// Open the USB device (the Cypress device has
	// Vendor ID = 0x04B4 and Product ID = 0x8051)

	dev = libusb_open_device_with_vid_pid(NULL, 0x04B4, 0x8051);

	if (dev == NULL) {
		perror("device not found\n");
		return FALSE;
	}

	// Reset the USB device.
	// This step is not always needed, but clears any residual state from
	// previous invocations of the program.
	if (libusb_reset_device(dev) != 0) {
		perror("Device reset failed\n");
		return FALSE;
	}

	// Set configuration of USB device
	if (libusb_set_configuration(dev, 1) != 0) {
		perror("Set configuration failed\n");
		return FALSE;
	}


	// Claim the interface.  This step is needed before any I/Os can be
	// issued to the USB device.
	if (libusb_claim_interface(dev, 0) != 0) {
		perror("Cannot claim interface");
		return FALSE;
	}
	return TRUE;
}

/**
* @function USBCom_CheckRecievedData(void)
* @param buffer for data recieved
* @return Length of data in bytes
* @brief Fill a buffer is there is data waiting to be received
* @author Barron Wong 01/31/19
*/
int USBCom_CheckReceivedData(char * buffer) {

	int rcvd_bytes = 0;
	int return_val = 0;

	// Perform the IN transfer (from device to host).
	// This will read the data back from the device.
	return_val = libusb_bulk_transfer(dev, // Handle for the USB device
		(0x01 | 0x80), // Address of the Endpoint in USB device
		// MS bit nust be 1 for IN transfers
		buffer, // address of receive data buffer
		64, // Size of data buffer
		&rcvd_bytes, // Number of bytes actually received
		0 // Timeout in milliseconds (0 to disable timeout)
	);
	if (return_val != 0)
		return 0;
	else
		return rcvd_bytes;
}

/**
* @function USBCom_SendData(uint8 * buffer)
* @param None
* @return None
* @brief Checks to see if configuration has changed. If it has it
*        will reenable the output endpoint
* @author Barron Wong 01/31/19
*/
void USBCom_SendData(char * msg) {
	int sent_bytes = 0;
	int return_val = 0;
	int length = strlen(msg);

	// Perform the OUT transfer (from host to device).
	return_val = libusb_bulk_transfer(dev, // Handle for the USB device
		0x02, // Address of the Endpoint in USB device
		msg, // address of data block to transmit
		64, // Size of data block
		&sent_bytes, // Number of bytes actually sent
		0 // Timeout in milliseconds (0 to disable timeout)
	);

	if (return_val != 0) {
		printf("Incomplete Data Send");
		dev = NULL;
		while (dev == NULL) {
			dev = USBCom_Init();
		}
	}

}

//#define USBCOM_TEST
#ifdef USBCOM_TEST

int main(int argc, char * argv[]) {

	libusb_device_handle* dev; // Pointer to data structure representing USB device
	char tx_data[64]; // Transmit data block
	char rx_data[64]; // Receive data block
	int sent_bytes; // Bytes transmitted
	int rcvd_bytes; // Bytes received
	int return_val;

	while (dev == NULL) {
		dev = USBCom_Init();
		if (dev == NULL) {
			printf("Unable to claim USB device\n");
		}
	}

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


	libusb_close(dev);

}
#endif