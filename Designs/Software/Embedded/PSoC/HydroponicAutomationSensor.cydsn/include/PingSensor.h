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
/* Add an explicit reference to the floating point printf library to allow
the usage of floating point conversion specifier */

//#define PING_TEST
#ifdef PING_TEST
#define MODULE_TEST
#endif

#ifndef PingSensor_H
#define PingSensor_H
    
    
#include <project.h>
#include <stdio.h>
    
typedef enum{
    LEVEL_WATER,
    LEVEL_pH_UP,
    LEVEL_pH_DOWN,
    LEVEL_NUTS,
}Level;

//Getters
double PingSensor_GetWaterLevel();
double PingSensor_GetpHUpLevel();
double PingSensor_GetpHDownLevel();
double PingSensor_GetNutLevel();

/**
 * @function PingSensorSampleTimerISRHandler(void)
 * @param None
 * @return None
 * @brief Timeout for level sense. Takes level readings every 100ms
 * @author Barron Wong 04/07/19
 */
CY_ISR_PROTO(PingSensorSampleTimerISRHandler);

/**
 * @function PingSensorEchoISRHandler(void)
 * @param None
 * @return None
 * @brief ISR Handler for Echo Pin
 * @author Barron Wong 03/30/19
 */
CY_ISR_PROTO(PingSensorEchoISRHandler);

/**
 * @function PingSensorTrigISRHandler(void)
 * @param None
 * @return None
 * @brief ISR Handler for Trig Pin
 * @author Barron Wong 03/30/19
 */
CY_ISR_PROTO(PingSensorTrigISRHandler);

/**
 * @function PingSensor_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary level sensing
 * @author Barron Wong 03/30/19
*/
void PingSensor_Init();

/**
 * @function PingSensor_InitiateReading(Level sensor)
 * @param The sensor the user wants to initiate
 * @return None
 * @brief Intiates a reading for a level sensor
 * @author Barron Wong 03/30/19
*/
void PingSensor_InitiateReading(Level sensor);



#endif

/* [] END OF FILE */
