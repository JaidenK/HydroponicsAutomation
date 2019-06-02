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


//#define FLOWCONTROLLER_TEST

#ifndef FlowController_H
#define FlowController_H

#ifdef FLOWCONTROLLER_TEST
#define MODULE_TEST
#endif

#include "project.h"

#define SUCCESS 1
#define ERROR -1
#define FLOW_SENSE_MIN 0.14
    
/**
 * @function FlowCounterTimerISRHandler(void)
 * @param None
 * @return None
 * @brief FlowCounter ISR. Takes reading of flow meter every second
 * @author Barron Wong 01/25/19
 */
CY_ISR_PROTO(FlowCounterTimerISRHandler);

/**
 * @function FlowController_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 01/25/19
*/
void FlowController_Init();

/**
 * @function FlowController_GetFlowRate(void)
 * @param None
 * @return Flow rate in liters per minute
 * @brief Converts the current frequency and returns flow rate
 * @author Barron Wong 01/25/19
*/
float FlowController_GetFlowRate();

/**
 * @function FlowController_SetFlow(void)
 * @param float value 0 - 1
 * @return SUCCESS or ERROR
 * @brief Sets the voltage of the pump in terms of percentages
 * @author Barron Wong 01/25/19
*/
uint8_t FlowController_SetFlowDutyCycle(float flowRate);

/**
 * @function FlowController_SetFlowReference(void)
 * @param float value 0 - 1
 * @return SUCCESS or ERROR
 * @brief Sets the reference flow rate in Liters Per Minute
 * @author Barron Wong 01/25/19
*/
uint8_t FlowController_SetFlowReference(float reference);
/**
 * @function FlowController_TurnOff(void)
 * @param float value 0 - 1
 * @return None
 * @brief Turns off FlowController
 * @author Barron Wong 05/30/19
*/
void FlowController_TurnOff();

/**
 * @function FlowController_TurnOff(void)
 * @param float value 0 - 1
 * @return None
 * @brief Turns on FlowController
 * @author Barron Wong 05/30/19
*/
void FlowController_TurnOn();
#endif

/* [] END OF FILE */
