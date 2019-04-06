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

#define SENSOR_COM_RX_TEST
#ifdef SENSOR_COM_RX_TEST
    #define MODULE_TEST
#endif

#ifndef SensorComRx_h
#define SensorComRx_h

#include "sensor_data.h"
#include "project.h"

/**
 * @function SensorComRx_Init()
 * @param None
 * @return None
 * @brief Initialize serial communication for sensor data
 * @author Barron Wong 04/05/19
 */
void SensorComRx_Init();

/**
 * @function SensorComRx_EncodeMessage()
 * @param SensorData structure
 * @return Pointer to SensoData structure
 * @brief Takes in a string checks the checksum and decodes the message
 *        and updates the SensorData structure
 * @author Barron Wong 04/05/19
 */
struct SensorData * SensorComRx_DecodeMessage(struct SensorData * sd, char * buffer);

/**
 * @function DataComRxISR(void)
 * @param None
 * @return None
 * @brief ISR for recieving data
 * @author Barron Wong 04/05/19
 */
CY_ISR_PROTO(DataComRxISR);

#endif
/* [] END OF FILE */
