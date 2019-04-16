/*
 * File:   FlowController.h
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


//#define AD_TEST

#ifndef AD_H
#define AD_H

#ifdef AD_TEST
#define MODULE_TEST
#endif

#include "project.h"

#define SUCCESS 1
#define ERROR -1
#define AD_MAX 255
    
/**
 * @function AD_Init(void)
 * @param None
 * @return None
 * @brief Initliazes AD pin for general use.
 * @author Barron Wong 01/25/19
 */
void AD_Init(void);

/**
 * @function GetADCValue(void)
 * @param None
 * @return None
 * @brief Returns the ADC reading on the analog pin.
 * @author Barron Wong 01/25/19
 */
uint16_t AD_GetADCValue();

#endif

/* [] END OF FILE */
