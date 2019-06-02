/*
 * File:   WaterLevelController.h
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


#include "project.h"
#include "ECSense.h"
#include "pHSense.h"
#include <stdio.h>


typedef enum {
    ECStart,
    ECSampling,
    pHSampling,
    pHStart,
}SenseSwitchStates;

#define PH_COOLDOWN 45000
#define EC_COOLDOWN 60000
#define PH_SAMPLE_TIME 60000
#define EC_SAMPLE_TIME 60000
#define FIFTEEN_SECONDS 7500

/**
 * @function SenseSwitchTimerISRHandler(void)
 * @param None
 * @return None
 * @brief ISR used to switch between EC and pH sensor updates
 * @author Barron Wong 05/21/19
 */
CY_ISR(SenseSwitchTimerISRHandler){
    
    static SenseSwitchStates nextState = pHStart;
    static SenseSwitchStates prevState = ECSampling;
    static uint8_t pHCoolDownCount = 0;
    
    SenseSwitchTimer_Stop();
    SenseSwitchTimerISR_ClearPending();
    
    switch(nextState){
        case pHStart:
            printf("pHStart\r\n");
            SenseSwitchTimer_WritePeriod(PH_COOLDOWN);
            ECSense_StopSampling();
            ECSense_TurnOff();
            if(pHCoolDownCount > 0){
                nextState = pHSampling;
                pHCoolDownCount = 0;
            }else{
                pHCoolDownCount++;
            }
            break;
        case pHSampling:
            printf("pHSampling\r\n");
            SenseSwitchTimer_WritePeriod(PH_SAMPLE_TIME);
            pHSense_TurnOn();
            nextState = ECStart;
            break;
        case ECStart:
            printf("ECStart\r\n");
            SenseSwitchTimer_WritePeriod(EC_COOLDOWN);
            pHSense_TurnOff();
            ECSense_TurnOn(); 
            nextState = ECSampling;
            break;
        case ECSampling:
            printf("ECSampling\r\n");
            SenseSwitchTimer_WritePeriod(EC_SAMPLE_TIME);
            ECSense_StartSampling();
            nextState = pHStart;
            break;
        break;
    }
    
    SenseSwitchTimer_Start();
    
}

/**
 * @function SenseSwitch_Init(void)
 * @param None
 * @return None
 * @brief Initializes components for senor reading switches
 * @author Barron Wong 05/21/19
*/
void SenseSwitch_Init(){
    SenseSwitchTimer_Start();
    SenseSwitchTimerISR_StartEx(SenseSwitchTimerISRHandler);
}



/* [] END OF FILE */
