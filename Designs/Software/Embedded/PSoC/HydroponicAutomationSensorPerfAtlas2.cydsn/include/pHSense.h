/*
 * File:   pHSense.h
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


//#define PHSENSE_TEST

#ifndef pHSense_H
#define pHSense_H

#ifdef PHSENSE_TEST
    #define MODULE_TEST
#endif

#include "project.h"

#define SUCCESS 1
#define ERROR -1

/**
 * @function pHSenseDataRxISRHandler(void)
 * @param None
 * @return None
 * @brief Handler for when a byte is recieved
 * @author Barron Wong 05/15/19
 */
CY_ISR_PROTO(pHSenseDataRxISRHandler);

/**
 * @function pHSense_DecodeMessage(uint16_t * ec, char * buffer)
 * @param message from EC Sensor
 * @return SUCCESS if EC was updated, ERROR if not
 * @brief Decode message recieved from EC Sensor
 * @author Barron Wong 05/15/19
 */
uint16_t pHSense_DecodeMessage(char * buffer);

/**
 * @function pHSense_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 05/15/19
*/
void pHSense_Init();

/**
 * @function pHSense_GetEC(void)
 * @param None
 * @return EC value
 * @brief Returns current EC value
 * @author Barron Wong 05/15/19
*/
float pHSense_GetpH();

/**
 * @function pHSense_TurnOff(void)
 * @param None
 * @return EC value
 * @brief Turns off the pHSense and disable updates
 * @author Barron Wong 05/21/19
*/
void pHSense_TurnOff();

/**
 * @function pHSense_TurnOn(void)
 * @param None
 * @return EC value
 * @brief Turns on pHSense and enables updates
 * @author Barron Wong 05/21/19
*/
void pHSense_TurnOn();
/**
 * @function pHSense_StartSampling(void)
 * @param None
 * @return None
 * @brief Enables EC Sampling
 * @author Barron Wong 05/21/19
*/
void pHSense_StartSampling();

/**
 * @function pHSense_StopSampling(void)
 * @param None
 * @return None
 * @brief Disables EC Sampling
 * @author Barron Wong 05/21/19
*/
void pHSense_StopSampling();


#endif

/* [] END OF FILE */
