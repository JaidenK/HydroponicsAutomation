/*
 * File:   HalfBridge.h
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

#ifndef HalfBridge_H
#define HalfBridge_H

#ifdef HALFBRIDGE_TEST
    #define MODULE_TEST
#endif

#include "project.h"
#include "HalfBridge.h"
#include <stdio.h>

#define SUCCESS 1
#define ERROR -1

#define POS_TIME 72000  //3ms
#define NEG_TIME 72000  //3ms
#define DEAD_TIME  2    //83.33ns
#define PERIOD 24000000 - POS_TIME - NEG_TIME - DEAD_TIME //1s

typedef enum{
    POS,
    DEAD,
    NEG,
    COOLDOWN,
}HalfBridgeStates;

static HalfBridgeStates state =  POS;

/**
 * @function HalfBridgeISR(void)
 * @param None
 * @return None
 * @brief Computes time elapsed since last capture
 * @author Barron Wong 04/25/19
 */
CY_ISR(HalfBridgeISR){
    HalfBridgeISR_ClearPending();
    switch(state){
        case POS:
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
        HalfBridgeTimer_WritePeriod(PERIOD);
        HalfBridgeTimerReset_Write(1);
        state = COOLDOWN;
        break;
        
        case COOLDOWN:
        HalfBridgeControl_Write(0b01);
        HalfBridgeTimer_WritePeriod(POS_TIME);
        HalfBridgeTimerReset_Write(1);
        state = POS;
        break;
    }
}

/**
 * @function HalfBridge_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 04/25/19
*/
void HalfBridge_Init(){
    HalfBridgeISR_StartEx(HalfBridgeISR);
    HalfBridgeTimer_Start();
    
}

#ifdef HALFBRIDGE_TEST
#define MODULE_TEST
    
#include "SerialCom.h"
 
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    SerialCom_Init();
    HalfBridge_Init();
    ECADC_Start();
    
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        printf("%d\r\n",ECADC_Read16());
    }
    
}
#endif


#endif

/* [] END OF FILE */
