/*
 * File:   TempSense.h
 * Author: bwong20
 *
 * Software to control the flow 
 *
 *
 *
 * PWM_TEST (in the .c file) conditionally compiles the test harness for the code. 
 * 
 *
 * Created on Janruary 25, 2019
 */


//#define TEMPSENSE_TEST

#ifndef TempSense_H
#define TempSense_H

#ifdef TEMPSENSE_TEST
    #define MODULE_TEST
#endif

#include "project.h"

#define SUCCESS 1
#define ERROR -1

/**
 * @function TempSenseDataRxISRHandler(void)
 * @param None
 * @return None
 * @brief Handler for when a byte is recieved
 * @author Barron Wong 05/15/19
 */
CY_ISR_PROTO(TempSenseDataRxISRHandler);

/**
 * @function TempSense_DecodeMessage(uint16_t * ec, char * buffer)
 * @param message from EC Sensor
 * @return SUCCESS if EC was updated, ERROR if not
 * @brief Decode message recieved from EC Sensor
 * @author Barron Wong 05/15/19
 */
uint16_t TempSense_DecodeMessage(char * buffer);

/**
 * @function TempSense_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 05/15/19
*/
void TempSense_Init();

/**
 * @function TempSense_GetEC(void)
 * @param None
 * @return EC value
 * @brief Returns current EC value
 * @author Barron Wong 05/15/19
*/
float TempSense_GetTemp();

/**
 * @function TempSense_TurnOff(void)
 * @param None
 * @return EC value
 * @brief Turns off the TempSense and disable updates
 * @author Barron Wong 05/21/19
*/
void TempSense_TurnOff();

/**
 * @function TempSense_TurnOn(void)
 * @param None
 * @return EC value
 * @brief Turns on TempSense and enables updates
 * @author Barron Wong 05/21/19
*/
void TempSense_TurnOn();
/**
 * @function TempSense_StartSampling(void)
 * @param None
 * @return None
 * @brief Enables EC Sampling
 * @author Barron Wong 05/21/19
*/
void TempSense_StartSampling();

/**
 * @function TempSense_StopSampling(void)
 * @param None
 * @return None
 * @brief Disables EC Sampling
 * @author Barron Wong 05/21/19
*/
void TempSense_StopSampling();


#endif

/* [] END OF FILE */
