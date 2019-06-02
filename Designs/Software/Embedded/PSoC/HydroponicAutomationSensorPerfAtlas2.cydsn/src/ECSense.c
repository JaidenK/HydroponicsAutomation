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


#include "project.h"
#include "ECSense.h"
#include "sensor_data.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define ERROR -1
#define FALSE 0
#define TRUE 1
#define BUFF_SIZE 255

static uint16_t ec = 0;
static uint8_t ready = 0;
static char RxBuffer[BUFF_SIZE];



uint16_t CalcCheckSum(const char *s);

/**
 * @function ECSenseDataRxISRHandler(void)
 * @param None
 * @return None
 * @brief Handler for when a byte is recieved
 * @author Barron Wong 05/15/19
 */
CY_ISR(ECSenseDataRxISRHandler){
    static uint8_t count = 0;
    static uint8_t remainder = 0; 
    
    ECSenseDataRxISR_ClearPending();
    //Set ready to false 
    //If ready is TRUE and we are in this ISR, 
    //then a new transmission is incoming
    if(ready == TRUE)
        ready = FALSE;
    
    while(ECSenseUART_ReadRxStatus() == ECSenseUART_RX_STS_FIFO_NOTEMPTY){
        RxBuffer[count++] = ECSenseUART_GetChar();
    }
    RxBuffer[count] = '\0';
    
    
    //Check for end of message
    if(RxBuffer[count - 1] == '\r'){
        ec = atoi(RxBuffer);
        count = 0;
    }
}

/**
 * @function checksum()
 * @param pointer to string that needs checksum generated
 * @return checksum
 * @brief computes and returns checksum of a string
 * @author NMEA0183 Wikipedia Page
 */
uint16_t CalcCheckSum(const char *s){
    uint16_t c = 0;

    while(*s){
        c ^= *s++;
    }
    return c;
}

 uint16_t ECSense_DecodeMessage(char * buffer){
    uint16_t len;
    unsigned int checksum;
    unsigned int rchecksum;
    char * token;
    const char * delim = ",:";
    char value_str[BUFF_SIZE];
    uint8_t key;
    uint16_t value;
    uint8_t return_val = ERROR;
    len = strlen(buffer);
    
    sscanf(buffer+len-2,"%X",&rchecksum);
    
    buffer[len - 3] = 0;
    buffer = buffer + 1;
    checksum = CalcCheckSum(buffer);
    if(rchecksum != checksum){
        printf("Checksum Mismatch: Recvd %2X Actual %2X\r\n",rchecksum, checksum);
        return_val = ERROR;
    }
    else{
        //Update sd
        //printf("%s\r\n", buffer);
        token = strtok(buffer,delim);
        while(token != NULL){;
            sscanf(token,"%d", &key);
            token = strtok(NULL,delim);
            sscanf(token,"%s", value_str);
            value = atof(value_str);
            if(key == ec_measured){
                ec = value;
                return_val = SUCCESS;
            }
            token = strtok(NULL,delim);
        }
    }
    return return_val;
}

/**
 * @function ECSense_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 05/15/19
*/
void ECSense_Init(){
    ECSenseUART_Start();
    ECSenseDataRxISR_StartEx(ECSenseDataRxISRHandler);
    ECSense_TurnOff();
}

/**
 * @function ECSense_GetEC(void)
 * @param None
 * @return EC value
 * @brief Returns current EC value
 * @author Barron Wong 05/15/19
*/
uint16_t ECSense_GetEC(){
    //printf("EC %d\r\n", ec);
    return ec;
}

/**
 * @function ECSense_TurnOff(void)
 * @param None
 * @return EC value
 * @brief Turns off the ECSenses
 * @author Barron Wong 05/21/19
*/
void ECSense_TurnOff(){
    ECSenseControlReg_Write(0);
}

/**
 * @function ECSense_TurnOn(void)
 * @param None
 * @return EC value
 * @brief Turns on ECSense and enables updates
 * @author Barron Wong 05/21/19
*/
void ECSense_TurnOn(){
    ECSenseControlReg_Write(1);
}
/**
 * @function ECSense_StartSampling(void)
 * @param None
 * @return None
 * @brief Enables EC Sampling
 * @author Barron Wong 05/21/19
*/
void ECSense_StartSampling(){
    ECSenseUART_Start();
    ECSenseDataRxISR_StartEx(ECSenseDataRxISRHandler);
}
/**
 * @function ECSense_StartSampling(void)
 * @param None
 * @return None
 * @brief Disables EC Sampling
 * @author Barron Wong 05/21/19
*/
void ECSense_StopSampling(){
    ECSenseDataRxISR_Disable();
    ECSenseUART_ClearRxBuffer();
    ECSenseDataRxISR_ClearPending();
    ECSenseUART_Stop();
}

#ifdef ECSENSE_TEST
#define MODULE_TEST
    
#include "SerialCom.h"
 
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    SerialCom_Init();
    ECSense_Init();
    int result = 0;
    
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        printf("%d\r\n",ECSense_GetEC());
    }
    
}

#endif

/* [] END OF FILE */
