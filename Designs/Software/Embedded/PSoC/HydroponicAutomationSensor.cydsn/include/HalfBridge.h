/*
 * File:   HalfBridge.h
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


//#define HALFBRIDGE_TEST

#ifndef HalfBridge_H
#define HalfBridge_H

#ifdef HALFBRIDGE_TEST
    #define MODULE_TEST
#endif

#include "project.h"

#define SUCCESS 1
#define ERROR -1

/**
 * @function HalfBridgeISR(void)
 * @param None
 * @return None
 * @brief Computes time elapsed since last capture
 * @author Barron Wong 04/25/19
 */
CY_ISR_PROTO(HalfBridgeISR);

/**
 * @function HalfBridge_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 04/25/19
*/
void HalfBridge_Init();


#endif

/* [] END OF FILE */
