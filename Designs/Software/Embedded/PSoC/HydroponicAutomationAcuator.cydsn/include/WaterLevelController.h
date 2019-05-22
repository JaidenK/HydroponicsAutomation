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


//#define WATERLEVELCONTROLLER_TEST

#ifndef WaterLevelController_H
#define WaterLevelController_H

#ifdef WATERLEVELCONTROLLER_TEST
#define MODULE_TEST
#endif

#include "project.h"

#define SUCCESS 1
#define ERROR -1

/**
 * @function WaterLevelControllerISRHandler(void)
 * @param None
 * @return None
 * @brief Control ISR set on 100ms timer
 * @author Barron Wong 05/06/19
 */
CY_ISR_PROTO(WaterLevelControllerISRHandler);

/**
 * @function WaterLevelController_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for water level control
 * @author Barron Wong 05/06/19
*/
void WaterLevelController_Init();

/**
 * @function WaterLevelController_GetWaterLevel(void)
 * @param None
 * @return Height of water level in centimeters
 * @brief Get the water level and returns the height in centimeters
 * @author Barron Wong 05/013/19
*/
float WaterLevelController_GetWaterLevel();

#endif

/* [] END OF FILE */
