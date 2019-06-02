/*
 * File:   TempSense.h
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
#include "TempSense.h"
#include "sensor_data.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define ERROR -1
#define FALSE 0
#define TRUE 1
#define BUFF_SIZE 255

static float temp = 0;
static uint8_t ready = 0;
static char RxBuffer[BUFF_SIZE];


/**
 * @function TempSenseDataRxISRHandler(void)
 * @param None
 * @return None
 * @brief Handler for when a byte is recieved
 * @author Barron Wong 05/15/19
 */
CY_ISR(TempSenseDataRxISRHandler){
    static uint8_t count = 0;
    static uint8_t remainder = 0; 
    
    TempSenseDataRxISR_ClearPending();
    //Set ready to false 
    //If ready is TRUE and we are in this ISR, 
    //then a new transmission is incoming
    if(ready == TRUE)
        ready = FALSE;
    
    while(TempSenseUART_ReadRxStatus() == TempSenseUART_RX_STS_FIFO_NOTEMPTY){
        RxBuffer[count++] = TempSenseUART_GetChar();
    }
    RxBuffer[count] = '\0';
    
    
    //Check for end of message
    if(RxBuffer[count - 1] == '\r'){
        //printf("%s",RxBuffer);
        temp = atof(RxBuffer);
        count = 0;
    }
}

/**
 * @function TempSense_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 05/15/19
*/
void TempSense_Init(){
    TempSenseUART_Start();
    TempSenseDataRxISR_StartEx(TempSenseDataRxISRHandler);
}

/**
 * @function TempSense_GetEC(void)
 * @param None
 * @return EC value
 * @brief Returns current EC value
 * @author Barron Wong 05/15/19
*/
float TempSense_GetTemp(){
    //printf("EC %d\r\n", ec);
    return temp;
}

/**
 * @function TempSense_StartSampling(void)
 * @param None
 * @return None
 * @brief Enables EC Sampling
 * @author Barron Wong 05/21/19
*/
void TempSense_StartSampling(){
    TempSenseUART_Start();
    TempSenseDataRxISR_StartEx(TempSenseDataRxISRHandler);
}

/**
 * @function TempSense_StartSampling(void)
 * @param None
 * @return None
 * @brief Disables EC Sampling
 * @author Barron Wong 05/21/19
*/
void TempSense_StopSampling(){
    TempSenseDataRxISR_Disable();
    TempSenseUART_ClearRxBuffer();
    TempSenseDataRxISR_ClearPending();
    TempSenseUART_Stop();
}

#ifdef TEMPSENSE_TEST
#define MODULE_TEST
    
#include "SerialCom.h"
 
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    SerialCom_Init();
    TempSense_Init();
    int result = 0;
    
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        printf("%f\r\n",TempSense_GetTemp());
    }
    
}

#endif

/* [] END OF FILE */
