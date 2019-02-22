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
#include <stdio.h>
#include <stdlib.h>
#include "FlowController.h"
#include "SerialCom.h"
#include "USBCom.h"
#include "Protocol.h"
#define PWM_MAX 255
#define HIST_CNT 1024
#define DROP_TIME 200
#define UP 0
#define DOWN 1
#define A0 1.59E-6
#define A1 -0.0101
#define A2 18.2
static float pH = 0;
static uint16_t phRaw = 0;



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

    
    pH = A0*phRaw*phRaw + A1*phRaw + A2;
   
    
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
    pHSampleTimerISR_StartEx(pHSampleTimerISRHandler);
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
    
    //printf("pH: %d\r\n", result);
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
    
    int duration = drops * 200;
    
    PeristalticCounter_WritePeriod(duration);
    
    if(dir == UP)
        pHControllerDirPin_Write(UP);
    else
        pHControllerDirPin_Write(DOWN);
    PeristalticControl_Write(1);
}


#ifdef PH_CONTROLLER_TEST    
#define FLOW_REF 1
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    ADC_DelSig_1_Start();
    FlowController_Init();
    SerialCom_Init();
    //USBCom_Init();
    pHController_Init();
    
    FlowController_SetFlowReference(FLOW_REF);
    
    printf("Hydroponic Automation\r\n");
    uint16_t PWMSpeed = 0;
    message_t target;
    float x;
    int phadj;
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
   
        
        PWMSpeed = ADC_DelSig_1_Read16();
        if(PWMSpeed > 500)
            PWMSpeed = 0;
        if(PWMSpeed > PWM_MAX)
            PWMSpeed = PWM_MAX;
        trig = Trigger_Read();
        if(trig)
            pHController_AdjustpH(UP, 4);
            
            phadj = (int)(pH*100);
        
            
            printf("%d, %d\r\n", phRaw, phadj);
         
    }
        
    
    
}
#endif
/* [] END OF FILE */
