/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef pHSense_H
#define pHSense_H
    
//#define PH_SENSE_TEST
    
#ifdef PH_SENSE_TEST
#define MODULE_TEST
#endif

#include "project.h"

/**
 * @function pHSampleTimerISRHandler(void)
 * @param None
 * @return None
 * @brief pHSampling ISR. Takes reading of pH meter every second
 * @author Barron Wong 01/25/19
 */
CY_ISR_PROTO(pHSampleTimerISRHandler);
/**
 * @function pHSense_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for pH Control
 * @author Barron Wong 01/25/19
*/
void pHSense_Init(void);

/**
 * @function pHSense_ReadSensor(void)
 * @param None
 * @return pH Sensor Reading in pH
 * @brief Returns pH sensor reading
 * @author Barron Wong 01/25/19
*/
float pHSense_ReadSensor(void);


/**
 * @function pHSense_GetpH(void)
 * @param  Nonw
 * @return pH level
 * @brief Returns the current pH level
 * @author Barron Wong 02/19/19
*/
float pHSense_GetpH(void);

/**
 * @function pHSense_TurnOff(void)
 * @param None
 * @return None
 * @brief Disables updating for pH
 * @author Barron Wong 05/21/19
*/
void pHSense_TurnOff(void);

/**
 * @function pHSense_TurnOn(void)
 * @param None
 * @return None
 * @brief Enables updating for pH
 * @author Barron Wong 05/21/19
*/
void pHSense_TurnOn(void);
    
#endif
/* [] END OF FILE */
