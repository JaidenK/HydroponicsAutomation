/*
 * File:   WaterLevelController.h
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


//#define SENSESWITCH_TEST

#ifndef SenseSwitch_H
#define SenseSwitch_H

#ifdef SENSESWITCH_TEST
#define MODULE_TEST
#endif

#include "project.h"

#define SUCCESS 1
#define ERROR -1

/**
 * @function SenseSwitchTimerISRHandler(void)
 * @param None
 * @return None
 * @brief ISR used to switch between EC and pH sensor updates
 * @author Barron Wong 05/21/19
 */
CY_ISR_PROTO(SenseSwitchTimerISRHandler);

/**
 * @function SenseSwitch_Init(void)
 * @param None
 * @return None
 * @brief Initializes components for senor reading switches
 * @author Barron Wong 05/21/19
*/
void SenseSwitch_Init();

#endif

/* [] END OF FILE */
