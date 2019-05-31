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

#define CALIBRATION_TEST

#ifdef CALIBRATION_TEST
    #define MODULE_TEST
#endif

#ifndef Calibration_h
#define Calibration_h

#include "project.h"
    
#define BUFF_SIZE 255
#define FALSE 0
#define TRUE 1
#define CALIBRATION_RUNNING 1
#define CALIBRATION_FINISHED 0
    
/**
 * @function xStepperInit();
 * @param None
 * @return TRUE or FALSE
 * @brief Returns TRUE if the stepper was succesfully initalized, FALSE if not
 * @author Eric Lery 04/15/19
 */   
uint8_t xStepperInit();     

/**
 * @function zStepperInit();
 * @param None
 * @return TRUE or FALSE
 * @brief Returns TRUE if the stepper was succesfully initalized, FALSE if not
 * @author Eric Lery 04/15/19
 */   
uint8_t zStepperInit();     


/**
 * @function xMove(uint8_t xSteps);
 * @param None
 * @return TRUE or FALSE
 * @brief Returns TRUE after steps are compleated, FALSE if not
 * @author Eric Lery 04/15/19
 */   
uint8_t xMove(uint8_t xSteps);

uint8_t zMove(uint8_t zSteps);
    
/**
 * @function Calibration_Init()
 * @param None
 * @return None
 * @brief Initialize calibration
 * @author Barron Wong 05/22/19
 */
void Calibration_Init();

/**
 * @function Calibration_RunCalibration()
 * @param None
 * @return CALIBRATION_FINISHED if calibration is finished
 *         CALIBRATION_RUNNING if calibration is still running
 * @brief Runs Calibration
 * @author Barron Wong 05/22/19
 */
uint8_t Calibration_RunCalibration();


/**
 * @function CY_ISR_PROTO(X_Step_ISR)
 * @param None
 * @return None
 * @brief ISR for commanding stepper to move
 * @author Eric Lery 04/15/19
 */    
CY_ISR_PROTO(X_Step_ISR);

/**
 * @function CY_ISR_PROTO(Z_Step_ISR)
 * @param None
 * @return None
 * @brief ISR for commanding stepper to move
 * @author Eric Lery 04/16/19
 */    
CY_ISR_PROTO(Z_Step_ISR);

/**
 * @function CY_ISR_PROTO(X_Limit);
 * @param None
 * @return None
 * @brief ISR Horizontal Limit Switch
 * @author Eric Lery 04/15/19
 */    
CY_ISR_PROTO(X_Limit_ISR);

/**
 * @function CY_ISR_PROTO(Z_Limit);
 * @param None
 * @return None
 * @brief ISR Vertical Limit Switch
 * @author Eric Lery 04/15/19
 */    
CY_ISR_PROTO(Z_Limit_ISR);
#endif
/* [] END OF FILE */
