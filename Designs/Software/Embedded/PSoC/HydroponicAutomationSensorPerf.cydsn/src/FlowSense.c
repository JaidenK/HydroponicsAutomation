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
#define FREE_TIMER_MAX 4294967296
#define MEGA 100000.0

#define NEW_HIST_CNT 16
#define NEW_SHIFT_CNT 4

#define HIST_CNT 4
#define SHIFT_CNT 2

static uint16_t flowSensorPeriodHistory[NEW_HIST_CNT] = {0};

static uint32_t flowSensorPeriod = 0;
static uint8_t timeout_flag = 0;
/**
 * @function FlowSenseTimeOutISRHandler(void)
 * @param None
 * @return None
 * @brief Interrupt to detect timeouts when no flow occurs
 * @author Barron Wong 01/25/19
 */
CY_ISR(FlowSenseTimeOutISRHandler){
    FlowSenseTimeOutISR_ClearPending();
    
    if (!timeout_flag){
        timeout_flag = 1;
    }
    else{
        flowSensorPeriod = MEGA*10;
    }
}
/**
 * @function FlowCounterTimerISRHandler(void)
 * @param None
 * @return None
 * @brief Computes time elapsed since last capture
 * @author Barron Wong 01/25/19
 */
CY_ISR(FlowSenseCaptureISRHandler){
    static uint32_t prev; 
    static uint16_t index = 0;
    static uint32_t sum;
    static uint16_t time_elapsed;
    uint32_t current;
    
    timeout_flag = 0;
    
    current = FREE_TIMER_MAX - FreeRunningTimer_ReadCounter();
    
    time_elapsed = current - prev;
    prev = current;
    
    //Removed Average stability issues
    //Subtract oldest value
    sum -= flowSensorPeriodHistory[index]; 
    flowSensorPeriodHistory[index] = time_elapsed;
    //Add newest value
    sum += time_elapsed;
    //Increment Index
    index = (index + 1) % (NEW_HIST_CNT);
    
    flowSensorPeriod = sum>>NEW_SHIFT_CNT;
    
    
    FlowSenseCaptureISR_ClearPending();
}


/**
 * @function FlowSense_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 01/25/19
*/
void FlowSense_Init(void){
    FlowSenseCaptureISR_StartEx(FlowSenseCaptureISRHandler);
    FlowSenseTimeOutISR_StartEx(FlowSenseTimeOutISRHandler);
    FreeRunningTimer_Start();
    FlowSenseTimeOutTimer_Start();
}

#define SLOPE 1.1763
#define BIAS 0.131

float FlowSense_GetFlowRate(){
    
    double flowRate;
    
    double freq = 1.0/(flowSensorPeriod/MEGA);
    
    flowRate = SLOPE*(freq/FLOWRATE_CONVERSION_FACTOR) + BIAS;
    
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
        printf("Old %f New %f Period %d \r\n",FlowSense_GetFlowRate2(), FlowSense_GetFlowRate(),flowSensorPeriod);
    }
    
}
#endif
/* [] END OF FILE */
