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
#include "HalfBridge.h"
#include "AD.h"

#define FLOW_REF 1.5
#define PH_REF 7

#ifndef MODULE_TEST 
    
struct SensorData sd;
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    char buffer[BUFF_SIZE];
    uint16_t adc_val;
    message_t target;
    
    USBCom_Init();
    FlowController_Init();
    SerialCom_Init();
    //AD_Init();
    HalfBridge_Init();
    pHController_Init();
    Mixing_Init();
    SensorComRx_Init();
    
    
    
    
    FlowController_SetFlowReference(FLOW_REF);
    pHController_SetpHReference(PH_REF);
    
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        if(SensorComRx_CheckStatus()){
            
            //Encode and send data
            Protocol_EncodeOutput(ph_measured, sd.ph_level, buffer);
            USBCom_SendData(buffer);

            //Encode and send data
            Protocol_EncodeOutput(ec_measured, sd.ec_level, buffer);
            USBCom_SendData(buffer);
            
            //Encode and send data
            Protocol_EncodeOutput(temp_measured, sd.temp_measured, buffer);
            USBCom_SendData(buffer);
            
            //Encode and send data
            Protocol_EncodeOutput(h20_level, sd.h2o_level, buffer);
            USBCom_SendData(buffer);
            
            //Encode and send data
            Protocol_EncodeOutput(h20_stored, sd.h2o_stored, buffer);
            USBCom_SendData(buffer);

            //Encode and send data
            Protocol_EncodeOutput(ph_up_stored, sd.ph_up_stored, buffer);
            USBCom_SendData(buffer);

            //Encode and send data
            Protocol_EncodeOutput(ph_down_stored, sd.ph_down_stored, buffer);
            USBCom_SendData(buffer);

            //Encode and send data
            Protocol_EncodeOutput(ec_stored, sd.ec_stored, buffer);
            USBCom_SendData(buffer);
            
//            //Check if USB has received data
//            USBCom_CheckReceivedData(buffer);
//            target = Protocol_DecodeInput(buffer);
//        
//            if(target.key != invalid_key)
//                Protocol_PrintMessage(target);
            
        
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
