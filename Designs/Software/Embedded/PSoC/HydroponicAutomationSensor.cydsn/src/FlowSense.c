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
#include "FlowSense.h"
#include "SerialCom.h"
#include <stdio.h>
#include <stdlib.h>

#define FLOWRATE_CONVERSION_FACTOR 23.0
#define FALSE 0 
#define TRUE 1
#define ADC_MAX 255

#define HIST_CNT 4
#define SHIFT_CNT 2

static uint16_t flowSensorFreqHistory[HIST_CNT] = {0};

static uint16_t flowSensorFreq = 0;

/**
 * @function FlowCounterTimerISRHandler(void)
 * @param None
 * @return void
 * @brief FlowCounter ISR. Takes reading of flow meter every second
 * @author Barron Wong 01/25/19
 */
CY_ISR(FlowCounterTimerISRHandler){
    
    static uint16_t index = 0;
    static uint32_t sum = 0;
    uint16_t flowSensorSample = 0;
    
    //Take Reading
    flowSensorSample = FlowSensorCounter_ReadCounter();
    //Start Next Conversion
    FlowControlRegister_Write(1);
    //Clear Interrupt
    FlowCounterTimerISR_ClearPending();  
    
    
     //Removed Average stability issues
    //Subtract oldest value
    sum -= flowSensorFreqHistory[index]; 
    flowSensorFreqHistory[index] = flowSensorSample;
    //Add newest value
    sum += flowSensorSample;
    //Increment Index
    index = (index + 1) % (HIST_CNT);
    
    flowSensorFreq = sum>>SHIFT_CNT;

    
}

/**
 * @function FlowSense_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 01/25/19
*/
void FlowSense_Init(void){
    FlowCounterTimerISR_StartEx(FlowCounterTimerISRHandler);
    FlowCountTimer_Start();
    FlowSensorCounter_Start();
}

#define SLOPE 1.1763
#define BIAS 0.131
/**
 * @function FlowSense_GetFlowRate(void)
 * @param None
 * @return Flow rate in liters per minute
 * @brief Converts the current frequency and returns flow rate
 * @author Barron Wong 01/25/19
*/
float FlowSense_GetFlowRate(){
    
    uint16_t reading = 0;
    float flowRate;
    
    reading = flowSensorFreq;
    flowRate = SLOPE*(reading/FLOWRATE_CONVERSION_FACTOR) + BIAS;
    
    return flowRate;
}

#ifdef FLOWSENSE_TEST
#define MODULE_TEST
 
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    FlowSense_Init();
    SerialCom_Init();
    
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        printf("Flow Rate %f \r\n", FlowSense_GetFlowRate());
    }
    
}
#endif
/* [] END OF FILE */
