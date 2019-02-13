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

#define FLOW_REF 1

#ifndef MODULE_TEST    
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    char buffer[64];
    ADC_DelSig_1_Start();
    FlowController_Init();
    SerialCom_Init();
    USBCom_Init();
    
    
    FlowController_SetFlowReference(FLOW_REF);
    
    printf("Hydroponic Automation\r\n");
    float flowRate = 0;
    message_t target;
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        //Get Flow Rate
        flowRate = FlowController_GetFlowRate();
        
        //Encode and send data
        Protocol_EncodeOutput(flow_measured, flowRate, buffer);
        USBCom_SendData(buffer);
        
        //Check if USB has received data
        USBCom_CheckRecievedData(buffer);
        target = Protocol_DecodeInput(buffer);
        
        if(target.key != invalid_key)
            Protocol_PrintMessage(target);
        

    }
    
}
#endif

/* [] END OF FILE */
