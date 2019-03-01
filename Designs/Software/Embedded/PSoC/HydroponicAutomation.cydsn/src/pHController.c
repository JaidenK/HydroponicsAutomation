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
#define MARGIN 0.10

static float pHRef = 4.5;
static float pH = 0;
static uint16_t phRaw = 0;

/**
 * @function pHControlISRHandler(void)
 * @param None
 * @return None
 * @brief Handler for pH ISR. Makes pH adjustments every two minutes.
 * @author Barron Wong 01/25/19
 */
CY_ISR_PROTO(pHControlISRHandler){
    static float kp = 30;
    static int drops = 0;
    float error; 
    
    pHControlISR_ClearPending();
    
    error = pHRef - pH;

    if(fabs(error) > MARGIN){
        drops = kp*error;
        Mixing_TurnOn();
    
        if(drops < 0){
            pHController_AdjustpH(UP,drops*-1);
            //printf("pH up %d pH %0.2f\r\n", drops*-1,pH);
        }else{
            pHController_AdjustpH(DOWN,drops);
            //printf("pH down %d pH %0.2f\r\n", drops, pH);
        }
    }else{
        Mixing_TurnOff();
    }
    
}

/**
 * @function pHSampleTimerISRHandler(void)
 * @param None
 * @return void
 * @brief pH Controller ISR. Takes reading of flow meter every milisecond.
 *        Readings are averaged accrossed 1024 data points.
 * @author Barron Wong 01/25/19
 */
CY_ISR(pHSampleTimerISRHandler){
    
    uint16_t pHADCSample;
    
    static uint16_t index;
    
    static uint16_t phHistory[HIST_CNT] = {0};
    static uint32_t sum = 0;
    
    pHSampleTimerISR_ClearPending();
    pHADCSample = pHController_ReadSensor();
    pHSampleTimer_Start();
    

    //Subtract oldest value
    sum -= phHistory[index]; 
    phHistory[index] = pHADCSample;
    //Add newest value
    sum += pHADCSample;
    //Increment Index
    index = (index + 1) % (HIST_CNT + 1);
    
    
    phRaw = sum>>10;

    
    pH = A0*phRaw + A1;
   
    
}
/**
 * @function pHController_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for pH Control
 * @author Barron Wong 01/25/19
*/
void pHController_Init(void){
    pHADC_Start();
    PeristalticPWM_Start();
    PeristalticCounter_Start();
    PeristalticCounter_WriteCounter(0);
    pHSampleTimer_Start();
    pHControlTimer_Start();
    
    //ISR Setup
    pHSampleTimerISR_StartEx(pHSampleTimerISRHandler);
    pHControlISR_StartEx(pHControlISRHandler);
}


/**
 * @function pHController_ReadSensor(void)
 * @param None
 * @return pH Sensor Reading in pH
 * @brief Returns pH sensor reading
 * @author Barron Wong 01/25/19
*/
float pHController_ReadSensor(void){
    uint16_t result;
    
    pHADC_StartConvert();
    pHADC_IsEndConversion(pHADC_WAIT_FOR_RESULT);
    result = pHADC_GetResult16();

    return result;
}
/**
 * @function pHController_SetFlowDutyCycle(void)
 * @param Duty cycle range 0-1
 * @return None
 * @brief Sets the duty cycle of dosing pump
 * @author Barron Wong 02/15/19
*/
void pHController_SetFlowDutyCycle(float duty){
    PeristalticPWM_WriteCompare((int)(duty*PWM_MAX));
}

/**
 * @function pHController_AdjustpH(float duty)
 * @param Direction up or down and number of drops
 * @return None
 * @brief Adds pH up or down based on dir and duration
 * @author Barron Wong 02/19/19
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
    
    //FlowController_SetFlowReference(FLOW_REF);
    
    printf("Hydroponic Automation\r\n");
    uint16_t PWMSpeed = 0;
    int phadj;
    int duty;
    uint8_t trig;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        
        //Encode and send data
        //Protocol_EncodeOutput(flow_measured, flowRate, buffer);
        //USBCom_SendData(buffer);
        
        //Check if USB has received data
        //USBCom_CheckReceivedData(buffer);
        //target = Protocol_DecodeInput(buffer);
            
        printf("pH %.02f \r\n", pH);
         
    }
        
    
    
}
#endif
/* [] END OF FILE */
