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
#include "SensorRxCom.h"
#include "AD.h"

#define FLOW_REF 1.5
#define PH_REF 7

#ifndef MODULE_TEST 
    
struct SensorData sd;
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    char buffer[64];
    uint16_t adc_val;
    
  
    FlowController_Init();
    SerialCom_Init();
    //USBCom_Init();
    AD_Init();
    pHController_Init();
    Mixing_Init();
    SensorComRx_Init();
    
    
    
    
    FlowController_SetFlowReference(FLOW_REF);
    pHController_SetpHReference(PH_REF);
    
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        
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
            if(SensorComRx_CheckStatus()){
                printf("\r\n\r\n\r\n\r\n\r\n");
                printf("ph_measured: %d\r\n", (int)(sd.ph_level*100));
                printf("ec_measured: %d\r\n", (int) (sd.ec_level*100));
                printf("temp_measured: %d\r\n", (int) (sd.temp_measured*100));
                printf("flow_measured: %d\r\n", (int) (sd.flow_measured*100));
                printf("h20_level: %d\r\n", (int) (sd.h2o_level*100));
                printf("h20_stored: %d\r\n", (int) (sd.h2o_stored*100));
                printf("ph_up_stored: %d\r\n", (int) (sd.ph_up_stored*100));
                printf("ph_down_stored: %d\r\n", (int) (sd.ph_down_stored*100));
                printf("ec_stored: %d\r\n", (int) (sd.ec_stored*100));
                
            }
        
    }
        
    
    
}
#endif

/* [] END OF FILE */
