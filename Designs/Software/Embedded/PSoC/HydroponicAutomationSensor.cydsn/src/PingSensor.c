#include <project.h>
#include <stdio.h>
#include "PingSensor.h"

#define TIMEOUT 100000//65536 //About 65.536 ms
#define ECHO_TIMER_MAX 65536 //About 65.536 ms
#define LEVEL_SENSE_CNT 4
#define MEGA 1000000.0

static double SupplyLevel[LEVEL_SENSE_CNT];
static Level  PingSelector = 0;

double PingSensor_GetWaterLevel(){return SupplyLevel[LEVEL_WATER];}
double PingSensor_GetpHUpLevel(){return SupplyLevel[LEVEL_pH_UP];}
double PingSensor_GetpHDownLevel(){return SupplyLevel[LEVEL_pH_DOWN];}
double PingSensor_GetNutLevel(){return SupplyLevel[LEVEL_NUTS];}

/**
 * @function PingSensor_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary level sensing
 * @author Barron Wong 03/30/19
*/
void PingSensor_Init(){
    PingSensorEchoISR_StartEx(PingSensorEchoISRHandler);
    PingSensorTrigISR_StartEx(PingSensorTrigISRHandler);
    PingSensorSampleTimerISR_StartEx(PingSensorSampleTimerISRHandler);
    PingSensorTrigCounter_Start();
    PingSensorEchoTimer_Start();
    PingSensorSampleTimer_Start();
    PingSelector = LEVEL_WATER;
}

/**
 * @function PingSensor_InitiateReading(Level sensor)
 * @param The sensor the user wants to initiate
 * @return None
 * @brief Intiates a reading for a level sensor
 * @author Barron Wong 03/30/19
*/
void PingSensor_InitiateReading(Level sensor){
    LevelSelect_Write(sensor);
    PingSensorControl_Write(1);
    PingSensorTrigControl_Write(1);
}
/**
 * @function PingSensorSampleTimerISRHandler(void)
 * @param None
 * @return None
 * @brief Timeout for level sense. Takes level readings every 100ms
 * @author Barron Wong 04/07/19
 */
CY_ISR(PingSensorSampleTimerISRHandler){
    PingSensor_InitiateReading(PingSelector);
    PingSelector = (PingSelector + 1) % LEVEL_SENSE_CNT;
    PingSensorSampleTimerISR_ClearPending();
}
/**
 * @function PingSensorEchoISRHandler(void)
 * @param None
 * @return None
 * @brief Reads time of flight in microseconds 
 * @author Barron Wong 03/30/19
*/
CY_ISR(PingSensorEchoISRHandler){
    uint32_t time;
    uint8_t echo_select = (PingSelector - 1) % LEVEL_SENSE_CNT;
    PingSensorEchoISR_ClearPending();
    time = ECHO_TIMER_MAX - PingSensorEchoTimer_ReadCapture();
    SupplyLevel[echo_select] = (time/MEGA * 340)/2;;
    PingSensorEchoTimer_ClearFIFO();
}
/**
 * @function PingSensorTrigISRHandler(void)
 * @param None
 * @return None
 * @brief ISR Handler for Trig Pin
 * @author Barron Wong 01/25/19
 */
CY_ISR(PingSensorTrigISRHandler){
    PingSensorTrigISR_ClearPending();
    PingSensorTrigControl_Write(0);
}

#ifdef PING_TEST   

#include "SerialCom.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    SerialCom_Init();
    PingSensor_Init();
    
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        printf("Water Level: %f\r\n", SupplyLevel[LEVEL_WATER]);
        printf("pH Up Level: %f\r\n", SupplyLevel[LEVEL_pH_UP]);
        printf("pH Down Level: %f\r\n", SupplyLevel[LEVEL_pH_DOWN]);
        printf("Nut Level: %f\r\n", SupplyLevel[LEVEL_NUTS]);

    }
}
#endif