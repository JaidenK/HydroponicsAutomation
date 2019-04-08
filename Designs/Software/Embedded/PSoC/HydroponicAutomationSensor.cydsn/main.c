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
#include "USBCom.h"
#include "Protocol.h"
#include "pHSense.h"
#include "Mixing.h"
#include "PingSensor.h"
#include "SensorComTx.h"
#include "sensor_data.h"

#define FLOW_REF 1
#define PH_REF 4.5

#ifndef MODULE_TEST   

struct SensorData sd;
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    char buffer[64];
    
  
    ADC_DelSig_1_Start();
    FlowSense_Init();
    SerialCom_Init();
    //USBCom_Init();
    pHSense_Init();
    PingSensor_Init();

    
    //Sensor Transmit
    SensorComTx_Init();
    sensor_data_init(&sd);
    
    
    printf("Hydroponic Automation\r\n");
    float pH = 0;
    float flowRate = 0;
    message_t target;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        //Update Sensor Readings
        sd.h2o_level = PingSensor_GetWaterLevel();
        sd.h2o_stored = 0;
        sd.ph_level = pHSense_GetpH();
	    sd.ph_up_stored = PingSensor_GetpHUpLevel();
	    sd.ph_down_stored = PingSensor_GetpHDownLevel();
	    sd.ec_level = 0;
	    sd.ec_stored = PingSensor_GetNutLevel();
	    sd.temp_measured = 0;
	    sd.flow_measured = FlowSense_GetFlowRate();
        
        //Set Targets
	    sd.flow_target = 0;
	    sd.ph_target = 0;
	    sd.ec_target = 0;
	    sd.h2o_target = 0;
	    sd.temp_target = 0;
    }
        
    
    
}
#endif

/* [] END OF FILE */
