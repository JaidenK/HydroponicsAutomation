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
#include "pHSense.h"
#include "project.h"
#include "Mixing.h" 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PH_MAX_REF 10
#define PH_MIN_REF 2
#define PH_DEFAULT_REF 5
#define PWM_MAX 255.0
#define DROP_TIME 200
#define UP 0
#define DOWN 1
#define A0 -4.40E-3
#define A1 13.22
#define UP_PUMP_DROP_PERIOD 200
#define DOWN_PUMP_DROP_PERIOD 200
#define UP_PUMP_DROP_CMP 127
#define DOWN_PUMP_DROP_CMP 100
#define MARGIN 0.05

#define FALSE 0
#define TRUE 1

#define PH_UPPERBOUND pHRef*MARGIN
#define PH_LOWERBOUND -pHRef*MARGIN

#define HIST_CNT 1
#define SHIFT_CNT 0

static float pHRef = 4.5;
static float pH = 0;
static uint16_t phRaw = 0;
static uint16_t phHistory[HIST_CNT] = {0};
static uint32_t sum = 0;


/**
 * @function pHSampleTimerISRHandler(void)
 * @param None
 * @return void
 * @brief pH Controller ISR. Takes reading of flow meter every milisecond.
 *        Readings are averaged accrossed 1024 data points.
 * @author Barron Wong 01/25/19
 */
CY_ISR(pHSampleTimerISRHandler){
    
    uint16_t pHADCSample;
    
    static uint16_t index;
    
    pHADCSample = pHSense_ReadSensor();
    pHSampleTimer_Start();
    
    //Removed Average stability issues
    //Subtract oldest value
    sum -= phHistory[index]; 
    phHistory[index] = pHADCSample;
    //Add newest value
    sum += pHADCSample;
    //Increment Index
    index = (index + 1) % (HIST_CNT);
    
    phRaw = sum>>SHIFT_CNT;
    pH = A0*phRaw + A1;
    
    pHSampleTimerISR_ClearPending();
    
}
/**
 * @function pHSense_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for pH Control.
 *        Sets default reference to 5
 * @author Barron Wong 01/25/19
*/
void pHSense_Init(void){
    
    pHADC_Start();
    pHSampleTimer_Start();
    
    //ISR Setup
    pHSampleTimerISR_StartEx(pHSampleTimerISRHandler);
}


/**
 * @function pHSense_ReadSensor(void)
 * @param  None
 * @return pH Sensor reading
 * @brief  Readings are in ADC values; 
 * @author Barron Wong 01/25/19
*/
float pHSense_ReadSensor(void){
    uint16_t result;
    
    pHADC_StartConvert();
    pHADC_IsEndConversion(pHADC_WAIT_FOR_RESULT);
    result = pHADC_GetResult16();

    return result;
}

/**
 * @function pHSense_GetpH(void)
 * @param  Nonw
 * @return pH level
 * @brief Returns the current pH level
 * @author Barron Wong 02/19/19
*/
float pHSense_GetpH(void){
    return pH;
}


#ifdef PH_SENSE_TEST   
#include "SerialCom.h"
#include "USBCom.h"
#include "Protocol.h"

#define FLOW_REF 1
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    ADC_DelSig_1_Start();
    SerialCom_Init();
    //USBCom_Init();
    pHSense_Init();
    
    
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        printf("pHRaw: %d pH %.02f\r\n",phRaw, pHSense_GetpH());    
    }
        
    
    
}
#endif
/* [] END OF FILE */
