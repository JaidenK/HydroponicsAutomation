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
#include "WaterLevelController.h"
#include "AD.h"
#include "ECController.h"
#include "Calibration.h"

#define FLOW_REF 1.5
#define PH_REF 7
#define PH_UP_SUPPLY_MAX 8.653
#define PH_DOWN_SUPPLY_MAX 7.259

#define EC_SUPPLY_MAX 9.231
#define EC_SUPPLY_BIAS 2.652
#define EC_SUPPLY_DIVISOR 6.61

#define WATERLEVEL_MIN 3
#define PHLEVEL_MIN 3
#define FLOW_MIN 0.5


uint8_t EC_Enable = OFF;
uint8_t Flow_Enable = OFF;
uint8_t pH_Enable = OFF;

#ifndef MODULE_TEST 
    
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    char buffer[BUFF_SIZE];
    message_t target;
    
    SerialCom_Init();
    FlowController_Init();
    pHController_Init();
    ECController_Init();
    Mixing_Init();
    SensorComRx_Init();
    WaterLevelController_Init();
    
    USBCom_Init();
    double water_level = 0;
    
    
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {   
        water_level = WaterLevelController_GetWaterLevel();
        
        //Flow Controller
        if( water_level < WATERLEVEL_MIN){
            FlowController_TurnOff();
            Flow_Enable = OFF;
        }
        else if(!Flow_Enable){
            FlowController_TurnOn();
            Flow_Enable = ON;
        }
        
        //EC Controller
        if(Flow_Enable){
            ECController_TurnOn();
        }else{
            ECController_TurnOff();
        }
            
        //pH Controller
        if( pH_Enable){
            pHController_TurnOn();
        }
        else{
            pHController_TurnOff();
        }
        
        //printf("Flow: %d EC: %d pH: %d\r\n", Flow_Enable, EC_Enable, pH_Enable);
        
        
        if(SensorComRx_CheckStatus()){
            //Flow
            Protocol_EncodeOutput(flow_measured, FlowController_GetFlowRate(), buffer);
            USBCom_SendData(buffer);
            
            //pH
            Protocol_EncodeOutput(ph_measured, sd.ph_level, buffer);
            USBCom_SendData(buffer);

            //EC
            Protocol_EncodeOutput(ec_measured, ECController_GetEC(), buffer);
            USBCom_SendData(buffer);
            
            //Temp
            Protocol_EncodeOutput(temp_measured, sd.temp_measured, buffer);
            USBCom_SendData(buffer);
            
            //Water Level
            Protocol_EncodeOutput(h20_level, WaterLevelController_GetWaterLevel(), buffer);
            USBCom_SendData(buffer);
            
            //Water Stored
            Protocol_EncodeOutput(h20_stored, sd.h2o_stored, buffer);
            USBCom_SendData(buffer);

            //pH up stored
            Protocol_EncodeOutput(ph_up_stored, sd.ph_up_stored, buffer);
            USBCom_SendData(buffer);

            //pH Down Stored
            Protocol_EncodeOutput(ph_down_stored, sd.ph_down_stored, buffer);
            USBCom_SendData(buffer);

            //EC Stored
            Protocol_EncodeOutput(ec_stored, sd.ec_stored, buffer);
            USBCom_SendData(buffer);
            
            //Check if USB has received data
            USBCom_CheckReceivedData(buffer);
            target = Protocol_DecodeInput(buffer);
        
            if(target.key != invalid_key){
                SensorData_UpdateTarget(target, &sd);
                Protocol_PrintMessage(target);
                printf("h20_target: %f\r\n", (sd.h2o_target));
                printf("flow_target: %f\r\n", (sd.flow_target));
                printf("ph_target: %f\r\n", (sd.ph_target));
                printf("ec_target: %f\r\n", (sd.ec_target));
            }
        }
        
    }
        
    
    
}
#endif

/* [] END OF FILE */
