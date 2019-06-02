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
#include "pHController.h"
#include "project.h"
#include "Mixing.h" 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sensor_data.h"

#define PH_MAX_REF 10
#define PH_MIN_REF 3
#define PH_DEFAULT_REF 5
#define PWM_MAX 255.0
#define HIST_CNT 1024
#define DROP_TIME 200
#define UP 0
#define DOWN 1
#define A0 -4.40E-3
#define A1 13.22
#define UP_PUMP_DROP_PERIOD 200
#define DOWN_PUMP_DROP_PERIOD 200
#define UP_PUMP_DROP_CMP 127
#define DOWN_PUMP_DROP_CMP 100
#define MARGIN 0.05


#define FALSE 0
#define TRUE 1

#define PH_UPPERBOUND sd.ph_target*MARGIN
#define PH_LOWERBOUND -sd.ph_target*MARGIN

#ifdef PHCONTROLLER_TEST
    static float pHRef = 4.5;
    static float pH = 0;
#endif


/**
 * @function pHControlISRHandler(void)
 * @param None
 * @return None
 * @brief Handler for pH ISR. Makes pH adjustments every two minutes.
 * @author Barron Wong 01/25/19
 */
CY_ISR(pHControlISRHandler){
    static float kp = 80;
    static int drops = 0;
    static uint8 adjust = FALSE;
    float error; 
    
    pHControlISR_ClearPending();
    
    if(sd.ph_target >= PH_MIN_REF){
        error = sd.ph_target - sd.ph_level;
        
        if(fabs(error) < sd.ph_target*MARGIN){
            adjust = FALSE;
            Mixing_TurnOff();
        }
        
        //Hystersis bound for error
        if(!adjust){
            if(error > PH_UPPERBOUND){
                adjust = TRUE;;
            }
            if(error < PH_LOWERBOUND){
                adjust = TRUE;
            }
        }
        
        if(adjust){
            Mixing_TurnOn();
            printf("pH Target: %f Meas: %f Error: %f\r\n",sd.ph_target, sd.ph_level, error);
            drops = kp*error;
            //printf("ph_ref: %f ph_level: %f error: %f\r\n",pHRef, sd.ph_level, error);
            if(drops > 0){
                printf("pH up: %d\r\n", drops);
                pHController_AdjustpH(UP,drops);
            }else{
                printf("pH down: %d\r\n", drops*-1);
                pHController_AdjustpH(DOWN,drops*-1);
            }
        }
    }  
}


/**
 * @function pHController_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for pH Control.
 *        Sets default reference to 5
 * @author Barron Wong 01/25/19
*/
void pHController_Init(void){
    PeristalticPWM_Start();
    PeristalticCounter_Start();
    PeristalticCounter_WriteCounter(0);
    pHControlTimer_Start();
    
    //ISR Setup
    pHControlISR_StartEx(pHControlISRHandler);
}

/**
 * @function pHController_SetFlowDutyCycle(void)
 * @param    Duty cycle range 0-1
 * @return   None
 * @brief    Sets the duty cycle of dosing pump
 * @author   Barron Wong 02/15/19
*/
void pHController_SetFlowDutyCycle(float duty){
    PeristalticPWM_WriteCompare((int)(duty*PWM_MAX));
}

/**
 * @function pHController_AdjustpH(float duty)
 * @param    Direction up or down and number of drops
 * @return   None
 * @brief    Adds pH up or down based on dir and duration
 * @author   Barron Wong 02/19/19
*/
void pHController_AdjustpH(uint8_t dir, uint8_t drops){
    
    int duration;
    
    
    if(dir == UP){
        pHControllerpHDir_Write(UP);
        duration = drops * UP_PUMP_DROP_PERIOD;
        PeristalticPWM_WriteCompare(UP_PUMP_DROP_CMP);
    }
    else{
        pHControllerpHDir_Write(DOWN);
        duration = drops * DOWN_PUMP_DROP_PERIOD;
        PeristalticPWM_WriteCompare(DOWN_PUMP_DROP_CMP);
    }
    PeristalticCounter_WritePeriod(duration);
    PeristalticControl_Write(1);
}
/**
 * @function pHController_SetReference(float reference)
 * @param Sets reference ph
 * @return None
 * @brief Reference must be between 2-10 pH
 * @author Barron Wong 02/19/19
*/
void pHController_SetpHReference(float reference){
    if(reference > PH_MAX_REF)
        reference = PH_MAX_REF;
    
    if(reference < PH_MIN_REF)
        reference = PH_MIN_REF;
 
    sd.ph_target = reference;
}
/**
 * @function pHController_GetpH(void)
 * @param  Nonw
 * @return pH level
 * @brief Returns the current pH level
 * @author Barron Wong 02/19/19
*/
float pHController_GetpH(void){
    return sd.ph_level;
}
/**
 * @function pHController_GetpH(void)
 * @param  Nonw
 * @return pH level
 * @brief Turns off pH controller
 * @author Barron Wong 06/01/19
*/
void pHController_TurnOff(void){
    pHControlISR_ClearPending();
    pHControlISR_Disable();
}
/**
 * @function pHController_TurnOn(void)
 * @param  Nonw
 * @return pH level
 * @brief Turns on the pH Controller
 * @author Barron Wong 06/01/19
*/
void pHController_TurnOn(void){
    pHControlISR_Enable();
}


#ifdef PH_CONTROLLER_TEST   
    
#include "FlowController.h"
#include "SerialCom.h"
#include "USBCom.h"
#include "Protocol.h"

#define FLOW_REF 1
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    ADC_DelSig_1_Start();
    FlowController_Init();
    SerialCom_Init();
    //USBCom_Init();
    pHController_Init();
    Mixing_Init();
    
    FlowController_SetFlowReference(FLOW_REF);
    
    printf("Hydroponic Automation\r\n");
    uint16_t PWMSpeed = 0;
    int phadj;
    int duty;
    uint8_t trig;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        printf("pHRaw: %d pH %.02f Flow %.02f \r\n",phRaw, pH, FlowController_GetFlowRate());    
    }
        
    
    
}
#endif
/* [] END OF FILE */
