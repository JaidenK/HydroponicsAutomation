/*
 * File:   pHSense.h
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
#include "pHSense.h"
#include "sensor_data.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define ERROR -1
#define FALSE 0
#define TRUE 1
#define BUFF_SIZE 255

static double ph = 0;
static uint8_t ready = 0;
static char RxBuffer[BUFF_SIZE];



uint16_t CalcCheckSum(const char *s);

/**
 * @function pHSenseDataRxISRHandler(void)
 * @param None
 * @return None
 * @brief Handler for when a byte is recieved
 * @author Barron Wong 05/15/19
 */
CY_ISR(pHSenseDataRxISRHandler){
    static uint8_t count = 0;
    static uint8_t remainder = 0; 
    
    pHSenseDataRxISR_ClearPending();
    //Set ready to false 
    //If ready is TRUE and we are in this ISR, 
    //then a new transmission is incoming
    if(ready == TRUE)
        ready = FALSE;
    
    while(pHSenseUART_ReadRxStatus() == pHSenseUART_RX_STS_FIFO_NOTEMPTY){
        RxBuffer[count++] = pHSenseUART_GetChar();
    }
    RxBuffer[count] = '\0';
    
    
    //Check for end of message
    if(RxBuffer[count - 1] == '\r'){
        //printf("%s",RxBuffer);
        ph = atof(RxBuffer);
        count = 0;
    }
}


/**
 * @function pHSense_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 05/15/19
*/
void pHSense_Init(){
    pHSenseUART_Start();
    pHSenseDataRxISR_StartEx(pHSenseDataRxISRHandler);
    pHSense_TurnOn();
}

/**
 * @function pHSense_GetEC(void)
 * @param None
 * @return EC value
 * @brief Returns current EC value
 * @author Barron Wong 05/15/19
*/
float pHSense_GetpH(){
    //printf("EC %d\r\n", ec);
    return ph;
}

/**
 * @function pHSense_TurnOff(void)
 * @param None
 * @return EC value
 * @brief Turns off the pHSenses
 * @author Barron Wong 05/21/19
*/
void pHSense_TurnOff(){
    pHSenseControlReg_Write(0);
}

/**
 * @function pHSense_TurnOn(void)
 * @param None
 * @return EC value
 * @brief Turns on pHSense and enables updates
 * @author Barron Wong 05/21/19
*/
void pHSense_TurnOn(){
    pHSenseControlReg_Write(1);
}
/**
 * @function pHSense_StartSampling(void)
 * @param None
 * @return None
 * @brief Enables EC Sampling
 * @author Barron Wong 05/21/19
*/
void pHSense_StartSampling(){
    pHSenseUART_Start();
    pHSenseDataRxISR_StartEx(pHSenseDataRxISRHandler);
}
/**
 * @function pHSense_StartSampling(void)
 * @param None
 * @return None
 * @brief Disables EC Sampling
 * @author Barron Wong 05/21/19
*/
void pHSense_StopSampling(){
    pHSenseDataRxISR_Disable();
    pHSenseUART_ClearRxBuffer();
    pHSenseDataRxISR_ClearPending();
    pHSenseUART_Stop();
}

#ifdef PHSENSE_TEST
#define MODULE_TEST
    
#include "SerialCom.h"
 
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    SerialCom_Init();
    pHSense_Init();
    int result = 0;
    
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        printf("%f\r\n",pHSense_GetpH());
    }
    
}

#endif

/* [] END OF FILE */
