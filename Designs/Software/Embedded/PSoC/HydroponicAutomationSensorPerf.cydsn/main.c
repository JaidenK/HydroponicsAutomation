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
#include "FlowSense.h"
#include "SerialCom.h"
#include "Protocol.h"
#include "pHSense.h"
#include "PingSensor.h"
#include "SensorComTx.h"
#include "sensor_data.h"
#include "ECSense.h"
#include "SenseSwitch.h"

#define FLOW_REF 2.0
#define PH_REF 4.5

#ifndef MODULE_TEST   

struct SensorData sd;
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    char buffer[64];
    
  
    FlowSense_Init();
    SerialCom_Init();
    PingSensor_Init();
    ECSense_Init();

    
    //Sensor Transmit
    SensorComTx_Init();
    pHSense_Init();
    sensor_data_init(&sd);
    SenseSwitch_Init();
    
    
    
    printf("Hydroponic Automation\r\n");
    message_t target;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        //Update Sensor Readings
        sd.h2o_level = PingSensor_GetWaterLevel();
        sd.h2o_stored = PingSensor_GetWaterResLevel();
        sd.ph_level = pHSense_GetpH();
        sd.ph_up_stored = PingSensor_GetpHUpLevel();
        sd.ph_down_stored = PingSensor_GetpHDownLevel();
        sd.ec_level = ECSense_GetEC();
        sd.ec_stored = PingSensor_GetNutLevel();
        sd.temp_measured = 0;
        sd.flow_measured = FlowSense_GetFlowRate();
        
        //Set Targets
        sd.flow_target = 0;
        sd.ph_target = 0;
        sd.ec_target = 0;
        sd.h2o_target = 0;
        sd.temp_target = 0;   
            
//        if(SensorComTx_isReady()){
//            //Update Sensor Readings
//            sd.h2o_level = PingSensor_GetWaterLevel();
//            sd.h2o_stored = PingSensor_GetWaterResLevel();
//            sd.ph_level = pHSense_GetpH();
//            sd.ph_up_stored = PingSensor_GetpHUpLevel();
//            sd.ph_down_stored = PingSensor_GetpHDownLevel();
//            sd.ec_level = ECSense_GetEC();
//            sd.ec_stored = PingSensor_GetNutLevel();
//            sd.temp_measured = 0;
//            sd.flow_measured = FlowSense_GetFlowRate();
//            
//            //Set Targets
//            sd.flow_target = 0;
//            sd.ph_target = 0;
//            sd.ec_target = 0;
//            sd.h2o_target = 0;
//            sd.temp_target = 0;   
//            
//            SensorComTx_EncodeMessage(sd,buffer);
//            SensorComTx_SendMessage(buffer);
//        }
    }
        
    
    
}
#endif

/* [] END OF FILE */
