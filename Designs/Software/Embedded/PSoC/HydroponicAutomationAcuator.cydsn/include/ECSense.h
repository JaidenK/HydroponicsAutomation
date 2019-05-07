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
 * @function HalfBridgeISR(void)
 * @param None
 * @return None
 * @brief ISR for halfbridge control
 * @author Barron Wong 04/25/19
 */
CY_ISR_PROTO(HalfBridgeISRHandler);

/**
 * @function ECSampleTimerISR(void)
 * @param None
 * @return None
 * @brief ISR for sampling
 * @author Barron Wong 04/25/19
 */
CY_ISR_PROTO(ECSampleTimerISRHandler);

/**
 * @function ECSense_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 04/25/19
*/
void ECSense_Init();

/**
 * @function ECSense_GetEC(void)
 * @param None
 * @return EC value
 * @brief Returns current EC value
 * @author Barron Wong 04/25/19
*/
uint16_t ECSense_GetEC();


#endif

/* [] END OF FILE */
