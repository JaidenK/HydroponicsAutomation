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
//#define MODULE_TEST
    
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include "FlowController.h"
#include "SerialCom.h"
#include "USBCom.h"
#include "Protocol.h"
#include "pHController.h"
#include "Mixing.h"
#include "PingSensor.h"

#define FLOW_REF 1
#define PH_REF 4.5

#ifndef MODULE_TEST    
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    char buffer[64];
  
    ADC_DelSig_1_Start();
    FlowController_Init();
    SerialCom_Init();
    //USBCom_Init();
    pHController_Init();
    Mixing_Init();
    
    
    FlowController_SetFlowReference(FLOW_REF);
    pHController_SetpHReference(PH_REF);
    
    printf("Hydroponic Automation\r\n");
    float pH = 0;
    float flowRate = 0;
    message_t target;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        //Get Flow Rate
        flowRate = FlowController_GetFlowRate();
        
//        //Encode and send data
//        Protocol_EncodeOutput(flow_measured, flowRate, buffer);
//        USBCom_SendData(buffer);
//        
//        //Check if USB has received data
//        USBCom_CheckReceivedData(buffer);
//        target = Protocol_DecodeInput(buffer);
//        
//        if(target.key != invalid_key)
//            Protocol_PrintMessage(target);
        
        
        //Get pH
        pH = pHController_GetpH();
        
//        //Encode and send data
//        Protocol_EncodeOutput(ph_measured, pH, buffer);
//        USBCom_SendData(buffer);
//        
//        //Check if USB has received data
//        USBCom_CheckReceivedData(buffer);
//        target = Protocol_DecodeInput(buffer);
//        
//        if(target.key != invalid_key)
//            Protocol_PrintMessage(target);
            
        printf("pH: %f Flow: %f\r\n", pH,flowRate);
        
    }
        
    
    
}
#endif

/* [] END OF FILE */
