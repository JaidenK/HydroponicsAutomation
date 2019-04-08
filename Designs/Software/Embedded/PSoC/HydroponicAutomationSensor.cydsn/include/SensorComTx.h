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

//#define SENSOR_COM_TX_TEST
#ifdef SENSOR_COM_TX_TEST
    #define MODULE_TEST
#endif

#ifndef SensorComTx_h
#define SensorComTx_h

#include "project.h"
#include "sensor_data.h"

/**
 * @function SensorComTx_Init()
 * @param None
 * @return None
 * @brief Initialize serial communication for sensor data
 * @author Barron Wong 04/04/19
 */
void SensorComTx_Init();

/**
 * @function SensorComTx_EncodeMessage()
 * @param SensorData structure
 * @return Pointer to encoded message
 * @brief Takes in a SensorData structure and returns
 *        a string in nmea0183 format
 * @author Barron Wong 04/04/19
 */
char * SensorComTx_EncodeMessage(struct SensorData sd, char * buffer);

/**
 * @function SensorComTx_SendMessage()
 * @param A string with data that needs to be sent
 * @return None
 * @brief Takes a string and send it over UART
 * @author Barron Wong 04/04/19
 */
void SensorComTx_SendMessage(char* msg);

/**
 * @function SensorDataComISRHandler(void)
 * @param None
 * @return None
 * @brief ISR handler for sensor data transmission. Sends updated
 *        SensorData every 200ms
 * @author Barron Wong 04/05/19
 */
CY_ISR_PROTO(SensorDataComISRHandler);

#endif
/* [] END OF FILE */
