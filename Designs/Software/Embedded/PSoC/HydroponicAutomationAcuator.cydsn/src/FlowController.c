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
#include "FlowController.h"
#include "SerialCom.h"
#include "sensor_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FLOWRATE_CONVERSION_FACTOR 23.0
#define FALSE 0 
#define TRUE 1
#define ADC_MAX 255
#define MARGIN 0.05
static uint16_t flowSensorFreq = 0;

static float flow_ref = 0;

extern struct SensorData sd;



/**
 * @function FlowCounterTimerISRHandler(void)
 * @param None
 * @return void
 * @brief FlowCounter ISR. Takes reading of flow meter every second
 * @author Barron Wong 01/25/19
 */
CY_ISR(FlowCounterTimerISRHandler){
    float flowRate = 0;
    static float dutyCycle = 0.5;
    float kp = 0.2;
    float error = 0;
     
    
    flowRate = FlowController_GetFlowRate();
    
    error = flow_ref - flowRate;
    if(fabs(error) > flow_ref*MARGIN){
        dutyCycle = dutyCycle+(kp*error)/100.0;
        FlowController_SetFlowDutyCycle(dutyCycle);
        //printf("Duty Cycle %d Error: %f\r\n", (int)(dutyCycle*100), error);
    }
    
    
    //Clear Interrupt
    FlowCounterTimerISR_ClearPending(); 
    //Start Next Conversion
    FlowControlRegister_Write(1);
}

/**
 * @function FlowController_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 01/25/19
*/
void FlowController_Init(void){
    FlowSpeedDAC_Start();
    FlowSpeedPWM_Start();
    FlowCounterTimerISR_StartEx(FlowCounterTimerISRHandler);
    FlowCountTimer_Start();
    flow_ref = 1.5;
}

#define SLOPE 1.1763
#define BIAS 0.131
/**
 * @function FlowController_GetFlowRate(void)
 * @param None
 * @return Flow rate in liters per minute
 * @brief Converts the current frequency and returns flow rate
 * @author Barron Wong 01/25/19
*/
float FlowController_GetFlowRate(){
    
    return sd.flow_measured;
}
/**
 * @function FlowController_SetFlow(void)
 * @param float value 0 - 1
 * @return SUCCESS or ERROR
 * @brief Sets the voltage of the pump in terms of percentages
 * @author Barron Wong 01/25/19
*/
uint8_t FlowController_SetFlowDutyCycle(float dutyCycle){
    uint16_t vout = 0;
    if(dutyCycle < 0 || dutyCycle > 1){
        return ERROR;
    }
    
    vout = (uint16_t) (dutyCycle*ADC_MAX);
    //FlowSpeedDAC_SetValue(vout);
    //FlowSpeedPWM_WriteCompare(dutyCycle*ADC_MAX);
    
    
    return SUCCESS;
}
/**
 * @function FlowController_SetFlowReference(void)
 * @param float value 0 - 1
 * @return SUCCESS or ERROR
 * @brief Sets the reference flow rate in Liters Per Minute
 * @author Barron Wong 01/25/19
*/
uint8_t FlowController_SetFlowReference(float reference){
    if(reference < 0 || reference > 10){
        return ERROR;
    }
    flow_ref = reference;
    return SUCCESS;
}

#ifdef FLOWCONTROLLER_TEST
#define MODULE_TEST
/*
    Test Harness for checking FlowController Library.
    The test should enable an analog value on pin 0.1.
    This value will be used to set the pwm speed on
    the water pump. The flow rate should also default to 
    4.347.
    
*/
#include "pHController.h"
 
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    ADC_DelSig_1_Start();
    FlowController_Init();
    SerialCom_Init();
    //USBFS_Init();
    
    uint16_t adcReading = 0;;
    uint16_t adcPrev = 0;
    float flowRate = 0;
    float dutyCycle = 0;
    float difference = 0;
    float kp = .005;
    float error = 0;
    
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        
        //Check voltage reading from pin 0.1
        adcReading = ADC_DelSig_1_Read16();
        if(adcReading > 600)
            adcReading = 0;
        if(adcReading > ADC_MAX)
            adcReading = ADC_MAX;
        

    }
    
}
#endif
/* [] END OF FILE */
