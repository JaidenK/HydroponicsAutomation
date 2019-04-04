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
//#define USBCOM_TEST
//#define MODULE_TEST

#ifndef USBCom_H
#define USBCom_H

#include "project.h"
    
/**
 * @function USBCom_Init(void)
 * @param None
 * @return None
 * @brief Initializes USBFS device
 * @author Barron Wong 01/31/19
 */
void USBCom_Init(void);

/**
 * @function USBCom_CheckConfiguration(void)
 * @param None
 * @return None
 * @brief Checks to see if configuration has changed. If it has it 
 *        will reenable the output endpoint
 * @author Barron Wong 01/31/19
 */
void USBCom_CheckConfiguration(void);

/**
 * @function USBCom_CheckRecievedData(void)
 * @param buffer for data recieved
 * @return Lgenth of data recieved
 * @brief Checks to see if configuration has changed. If it has it 
 *        will reenable the output endpoint
 * @author Barron Wong 01/31/19
 */
int USBCom_CheckReceivedData(char * buffer);

/**
 * @function USBCom_SendData(uint8 * buffer)
 * @param None
 * @return None
 * @brief Checks to see if configuration has changed. If it has it 
 *        will reenable the output endpoint
 * @author Barron Wong 01/31/19
 */
void USBCom_SendData(char * msg);

#endif
/* [] END OF FILE */
