/*
 * File:   ECSense.h
 * Author: bwong20
 *
 * Software to control the flow 
 *
 *
 *
 * PWM_TEST (in the .c file) conditionally compiles the test harness for the code. 
 * 
 *
 * Created on Janruary 25, 2019
 */

#ifndef ECSense_C
#define ECSense_C

#ifdef ECSENSE_TEST
    #define MODULE_TEST
#endif

#include "project.h"
#include "ECSense.h"
#include <stdio.h>

#define SUCCESS 1
#define ERROR -1

#define POS_TIME 3600  //150us
#define NEG_TIME 3600  //150us
#define DEAD_TIME  2    //83.33ns
#define PERIOD 24000000 //1s
#define COOLDOWN_TIME PERIOD - POS_TIME - NEG_TIME - DEAD_TIME

#define SMP_SIZE 4
#define SMP_SHFT 2
#define HIST_CNT 16
#define SHFT_CNT 4

typedef enum{
    POS,
    DEAD,
    NEG,
    COOLDOWN,
}HalfBridgeStates;

static HalfBridgeStates state =  POS;
static uint16_t ECRaw = 0;
static uint8_t sampleCount = 0;
static uint16_t ECRawHistory[HIST_CNT];
static uint32_t ECRawTotal = 0;

/**
 * @function ECSense_GetEC(void)
 * @param None
 * @return EC value
 * @brief Returns current EC value
 * @author Barron Wong 04/25/19
*/
uint16_t ECSense_GetEC(){
    return ECRaw;
}

/**
 * @function ECSampleTimerISR(void)
 * @param None
 * @return None
 * @brief ISR for sampling
 * @author Barron Wong 05/04/19
 */
CY_ISR_PROTO(ECSampleTimerISRHandler){
    
    static uint32_t ECRawSampleTotal = 0;  //Current sample total
    static uint16_t index = 0;
    
    ECSampleTimerISR_ClearPending();
    
    if (sampleCount < SMP_SIZE){
        ECRawSampleTotal += ECADC_Read16();
        sampleCount++;
    }
    else{
        ECRawTotal -= ECRawHistory[index];
        ECRawHistory[index] = ECRawSampleTotal >> SMP_SHFT;
        ECRawTotal += ECRawHistory[index];
        ECRaw = ECRawTotal>>SHFT_CNT;
        index = (index + 1) % (HIST_CNT);
        ECRawSampleTotal = 0;
        sampleCount = 0;
        ECSampleTimerISR_Disable();
    }
    
//    //Removed Average stability issues
//    //Subtract oldest value
//    sum -= flowSensorPeriodHistory[index]; 
//    flowSensorPeriodHistory[index] = time_elapsed;
//    //Add newest value
//    sum += time_elapsed;
//    //Increment Index
//    index = (index + 1) % (NEW_HIST_CNT);
}

/**
 * @function HalfBridgeISR(void)
 * @param None
 * @return None
 * @brief State machine used to generate EC pulses
 * @author Barron Wong 04/25/19
 */
CY_ISR(HalfBridgeISRHandler){
    HalfBridgeISR_ClearPending();
    switch(state){
        case POS:
        ECADC_Stop();
        HalfBridgeControl_Write(0b00);
        HalfBridgeTimer_WritePeriod(DEAD_TIME);
        HalfBridgeTimerReset_Write(1);
        state = DEAD;
        break;
        
        case DEAD:
        HalfBridgeControl_Write(0b10);
        HalfBridgeTimer_WritePeriod(NEG_TIME);
        HalfBridgeTimerReset_Write(1);
        state = NEG;
        break;
        
        case NEG:
        HalfBridgeControl_Write(0b00);
        HalfBridgeTimer_WritePeriod(COOLDOWN_TIME);
        HalfBridgeTimerReset_Write(1);
        state = COOLDOWN;
        break;
        
        case COOLDOWN:
        HalfBridgeControl_Write(0b01);
        HalfBridgeTimer_WritePeriod(POS_TIME);
        HalfBridgeTimerReset_Write(1);
        state = POS;
        ECSampleTimerISR_Enable();
        ECADC_Start();
        break;
    }
}

/**
 * @function ECSense_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 04/25/19
*/
void ECSense_Init(){
    HalfBridgeISR_StartEx(HalfBridgeISRHandler);
    ECSampleTimerISR_StartEx(ECSampleTimerISRHandler);
    ECSampleTimerISR_Disable();
    ECADC_Start();
    ECSenseSampleTimer_Start();
    HalfBridgeTimer_Start();
    
}

#ifdef ECSENSE_TEST
#define MODULE_TEST
    
#include "SerialCom.h"
 
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    SerialCom_Init();
    ECSense_Init();
    
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        printf("%d\r\n",ECRaw);
    }
    
}
#endif


#endif

/* [] END OF FILE */
