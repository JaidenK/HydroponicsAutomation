#include <project.h>
#include <stdio.h>
#include "PingSensor.h"

#define TIMEOUT 100000//65536 //About 65.536 ms
#define ECHO_TIMER_MAX 65536 //About 65.536 ms
#define LEVEL_SENSE_CNT 4
#define MEGA 1000000.0
static double SupplyLevel[LEVEL_SENSE_CNT];
static Level  PingSelector = 0;

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
    PingSensorTrigCounter_Start();
    PingSensorEchoTimer_Start();
    FreeRunningTimer_Start();
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
    
    uint32_t currentTime = FreeRunningTimer_ReadCounter();
    uint32_t timestamp = currentTime;
    uint32_t elapsedTime = 0;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        currentTime = FreeRunningTimer_ReadCounter();
        elapsedTime = timestamp - currentTime;

        
        if(elapsedTime > TIMEOUT){
            PingSensor_InitiateReading(PingSelector);
            timestamp = currentTime;
            printf("Initiated %d\r\n", PingSelector);
            PingSelector = (PingSelector + 1) % LEVEL_SENSE_CNT;
            printf("Water Level: %f\r\n", SupplyLevel[LEVEL_WATER]);
            printf("pH Up Level: %f\r\n", SupplyLevel[LEVEL_pH_UP]);
            printf("pH Down Level: %f\r\n", SupplyLevel[LEVEL_pH_DOWN]);
            printf("Nut Level: %f\r\n", SupplyLevel[LEVEL_NUTS]);
        }
        

    }
}
#endif