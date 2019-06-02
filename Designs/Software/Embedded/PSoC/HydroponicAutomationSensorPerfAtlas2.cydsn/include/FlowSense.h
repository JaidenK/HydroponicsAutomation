/*
 * File:   FlowSense.h
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


//#define FLOWSENSE_TEST

#ifndef FlowSense_H
#define FlowSense_H

#ifdef FLOWSENSE_TEST
    #define MODULE_TEST
#endif

#include "project.h"

#define SUCCESS 1
#define ERROR -1

/**
 * @function FlowCounterTimerISRHandler(void)
 * @param None
 * @return None
 * @brief Computes time elapsed since last capture
 * @author Barron Wong 01/25/19
 */
CY_ISR_PROTO(FlowSenseCaptureISRHandler);

/**
 * @function FlowSenseTimeOutISRHandler(void)
 * @param None
 * @return None
 * @brief Interrupt to detect timeouts when no flow occurs
 * @author Barron Wong 01/25/19
 */
CY_ISR_PROTO(FlowSenseTimeOutISRHandler);

/**
 * @function FlowSense_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 01/25/19
*/
void FlowSense_Init();

/**
 * @function FlowSense_GetFlowRate(void)
 * @param None
 * @return Flow rate in liters per minute
 * @brief Converts the current frequency and returns flow rate
 * @author Barron Wong 01/25/19
*/
float FlowSense_GetFlowRate();
#endif

/* [] END OF FILE */
