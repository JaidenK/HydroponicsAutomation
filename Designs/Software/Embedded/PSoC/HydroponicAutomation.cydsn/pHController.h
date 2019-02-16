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
#ifndef pHController_H
#define pHController_H
    
#define PH_CONTROLLER_TEST
    
#ifdef PH_CONTROLLER_TEST
#define MODULE_TEST

    
#endif

#include "project.h"

/**
 * @function pHController_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for pH Control
 * @author Barron Wong 01/25/19
*/
void pHController_Init(void);

/**
 * @function pHController_ReadSensor(void)
 * @param None
 * @return pH Sensor Reading in pH
 * @brief Returns pH sensor reading
 * @author Barron Wong 01/25/19
*/
float pHController_ReadSensor(void);

/**
 * @function pHController_SetFlowDutyCycle(void)
 * @param Duty cycle range 0-1
 * @return None
 * @brief Sets the duty cycle of dosing pump
 * @author Barron Wong 02/15/19
*/
void pHController_SetFlowDutyCycle(float duty);
    
#endif
/* [] END OF FILE */
