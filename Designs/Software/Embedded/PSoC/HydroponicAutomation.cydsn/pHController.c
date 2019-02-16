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
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        
        //Encode and send data
        //Protocol_EncodeOutput(flow_measured, flowRate, buffer);
        //USBCom_SendData(buffer);
        
        //Check if USB has received data
        //USBCom_CheckReceivedData(buffer);
        //target = Protocol_DecodeInput(buffer);
        
        if(target.key != invalid_key)
            //Protocol_PrintMessage(target);
        
        
        pHController_ReadSensor();
        PWMSpeed = ADC_DelSig_1_Read16();
        if(PWMSpeed > 500)
            PWMSpeed = 0;
        if(PWMSpeed > PWM_MAX)
            PWMSpeed = PWM_MAX;
        if(Trigger_Read())
            PeristalticControl_Write(0b11111111);
            
        printf("Trigger: %d Timer: %d TC: %d\r\n", Trigger_Read(), PeristalticCounter_ReadCounter(), TimerOut_Read());
    
         
    }
        
    
    
}
#endif
/* [] END OF FILE */
