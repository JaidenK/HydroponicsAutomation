/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "USBCom.h"
#include "SerialCom.h"

//USBFS Defines
#define USBFS_DEVICE  (0u)

/* Active endpoints of USB device. */
#define IN_EP_NUM     (1u)
#define OUT_EP_NUM    (2u)

/* Size of SRAM buffer to store endpoint data. */
#define BUFFER_SIZE   (64u)

/* There are no specific requirements to the buffer size and alignment for 
* the 8-bit APIs usage.
*/

char buffer[BUFFER_SIZE];


/**
 * @function USBCom_Init(void)
 * @param None
 * @return None
 * @brief Initializes 
 * @author Barron Wong 01/31/19
 */
void USBCom_Init(void){
    /* Start USBFS operation with 5V operation. */
    USBFS_Start(USBFS_DEVICE, USBFS_5V_OPERATION);

    /* Wait until device is enumerated by host. */
    while (0u == USBFS_GetConfiguration())
    {
    }

    /* Enable OUT endpoint to receive data from host. */
    USBFS_EnableOutEP(OUT_EP_NUM);;
}

/**
 * @function USBCom_CheckConfiguration(void)
 * @param None
 * @return None
 * @brief Checks to see if configuration has changed. If it has it 
 *        will reenable the output endpoint. Used by USBCom_Init()
 *        and USBCom_CheckRecievedData()
 * @author Barron Wong 01/31/19
 */
void USBCom_CheckConfiguration(void){
        /* Check if configuration is changed. */
        if (0u != USBFS_IsConfigurationChanged())
        {
            /* Re-enable endpoint when device is configured. */
            if (0u != USBFS_GetConfiguration())
            {
                /* Enable OUT endpoint to receive data from host. */
                USBFS_EnableOutEP(OUT_EP_NUM);
            }
        }
}

/**
 * @function USBCom_CheckConfiguration(void)
 * @param None
 * @return None
 * @brief Must Call USBCom_Init() before using. Checks to see if configuration has changed. If it has it 
 *        will reenable the output endpoint
 * @author Barron Wong 01/31/19
 */
int USBCom_CheckRecievedData(char * buffer){

    uint16 length = 0;
    
    USBCom_CheckConfiguration();
    
    /* Check if data was received. */
    if (USBFS_OUT_BUFFER_FULL == USBFS_GetEPState(OUT_EP_NUM))
    {
        /* Read number of received data bytes. */
        length = USBFS_GetEPCount(OUT_EP_NUM);
        
        /* Trigger DMA to copy data from OUT endpoint buffer. */
        USBFS_ReadOutEP(OUT_EP_NUM,(uint8*) buffer, length);

        /* Wait until DMA completes copying data from OUT endpoint buffer. */
        while (USBFS_OUT_BUFFER_FULL == USBFS_GetEPState(OUT_EP_NUM))
        {
        }
    }
    /* Enable OUT endpoint to receive data from host. */
    USBFS_EnableOutEP(OUT_EP_NUM);
    if(length == 0){
        buffer = NULL;
    }
    return length;
}

/**
 * @function USBCom_SendData(void)
 * @param None
 * @return None
 * @brief Must Call USBCom_Init() before using. Checks to see if configuration has changed. If it has it 
 *        will reenable the output endpoint
 * @author Barron Wong 01/31/19
 */
void USBCom_SendData(char * msg){
    int length = 0;
    /* Wait until IN buffer becomes empty (host has read data). */
    while (USBFS_IN_BUFFER_EMPTY != USBFS_GetEPState(IN_EP_NUM))
    {
    }
    /* Trigger DMA to copy data into IN endpoint buffer.
    * After data has been copied, IN endpoint is ready to be read by the
    * host.
    */

    length = strlen(msg);
    
    USBFS_LoadInEP(IN_EP_NUM,(uint8*) msg, length);
}

#ifdef USBCOM_TEST
/*******************************************************************************
* File Name: main.c
*
* Version: 3.0
*
* Description:
*  This example project demonstrates how to establish communication between 
*  the PC and Vendor-Specific USB device. The device has two endpoints: 
*  BULK IN and BULK OUT. The OUT endpoint allows the host to write data into 
*  the device and the IN endpoint allows the host to read data from the device. 
*  The data received in the OUT endpoint is looped back to the IN endpoint.
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>
#include <SerialCom.h>


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  The main function performs the following actions:
*   1. Starts the USBFS component.
*   2. Waits until the device is enumerated by the host.
*   3. Enables the OUT endpoint to start communication with the host.
*   4. Waits for OUT data coming from the host and sends it back on a
*      subsequent IN request.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
int main()
{
    CyGlobalIntEnable;
    USBCom_Init();
    SerialCom_Init();
    uint16 length = 0;
    

    for(;;)
    {
        USBCom_CheckConfiguration();
        length = USBCom_CheckRecievedData(buffer);
        if(length > 0)
            printf("%s", buffer);
        USBCom_SendData("Hello Bitch ass trick");
    }

}

#endif
/* [] END OF FILE */
