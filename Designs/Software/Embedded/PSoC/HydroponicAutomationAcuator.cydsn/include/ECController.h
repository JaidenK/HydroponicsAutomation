/*
 * File:   ECController.h
 * Author: bwong20
 *
 * Software to control the flow 
 *
 *
 *
 * PWM_TEST (in the .c file) conditionally compiles the test harness for the code. 
 * 
 *
 * Created on May 09, 2019
 */


//#define ECCONTROLLER_TEST

#ifndef ECController_H
#define ECController_H

#ifdef ECCONTROLLER_TEST
    #define MODULE_TEST
#endif

#include "project.h"

#define SUCCESS 1
#define ERROR -1


/**
 * @function ECController_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for EC control
 * @author Barron Wong 05/09/19
*/
void ECController_Init();

/**
 * @function ECController_AdjustEC(void)
 * @param number of drops to by added
 * @return None
 * @brief Adjusts solution mixture by adding drops 
 * @author Barron Wong 05/09/19
*/
void ECController_AdjustEC(uint16_t drops);

#endif

/* [] END OF FILE */
