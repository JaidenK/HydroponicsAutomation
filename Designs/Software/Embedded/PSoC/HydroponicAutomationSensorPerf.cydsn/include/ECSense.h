/*
 * File:   ECSense.h
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


//#define ECSENSE_TEST

#ifndef ECSense_H
#define ECSense_H

#ifdef ECSENSE_TEST
    #define MODULE_TEST
#endif

#include "project.h"

#define SUCCESS 1
#define ERROR -1

/**
 * @function ECSenseDataRxISRHandler(void)
 * @param None
 * @return None
 * @brief Handler for when a byte is recieved
 * @author Barron Wong 05/15/19
 */
CY_ISR_PROTO(ECSenseDataRxISRHandler);

/**
 * @function ECSense_DecodeMessage(uint16_t * ec, char * buffer)
 * @param message from EC Sensor
 * @return SUCCESS if EC was updated, ERROR if not
 * @brief Decode message recieved from EC Sensor
 * @author Barron Wong 05/15/19
 */
uint16_t ECSense_DecodeMessage(char * buffer);

/**
 * @function ECSense_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 05/15/19
*/
void ECSense_Init();

/**
 * @function ECSense_GetEC(void)
 * @param None
 * @return EC value
 * @brief Returns current EC value
 * @author Barron Wong 05/15/19
*/
uint16_t ECSense_GetEC();

/**
 * @function ECSense_TurnOff(void)
 * @param None
 * @return EC value
 * @brief Turns off the ECSense and disable updates
 * @author Barron Wong 05/21/19
*/
void ECSense_TurnOff();

/**
 * @function ECSense_TurnOn(void)
 * @param None
 * @return EC value
 * @brief Turns on ECSense and enables updates
 * @author Barron Wong 05/21/19
*/
void ECSense_TurnOn();
/**
 * @function ECSense_StartSampling(void)
 * @param None
 * @return None
 * @brief Enables EC Sampling
 * @author Barron Wong 05/21/19
*/
void ECSense_StartSampling();

/**
 * @function ECSense_StopSampling(void)
 * @param None
 * @return None
 * @brief Disables EC Sampling
 * @author Barron Wong 05/21/19
*/
void ECSense_StopSampling();


#endif

/* [] END OF FILE */
