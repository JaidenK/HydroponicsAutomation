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

#include <stdio.h>
#include <stdlib.h>
#include "Protocol.h"
#include "project.h"

/**
 * @function Protocol_DecodeInput(char * input)
 * @param None
 * @return Takes an incoming data transmission and decodes it
 * @brief Converts the current frequency and returns flow rate
 * @author Barron Wong 02/08/19
*/
message_t Protocol_DecodeInput(char * input){
    char * ptr;
    message_t target;
    uint8_t count = 0;
    
    target.key = invalid_key;
    target.key = 0;
    
    ptr = strtok(input,":");
    
    while(ptr != NULL){
        switch(count){
            case 0:{
                target.key = atoi(ptr);
            break;
            }
            case 1:{
                target.value = atof(ptr);
            break;
            }
            default:{
                target.key = invalid_key;
                target.value = -1;
            }
        }
        count++;
        ptr = strtok(NULL,":");
    }
    
    return target;
    
}
/**
 * @function Protocol_EncodeOutput(char * input)
 * @param key, value, and buffer
 * @return String pointer ready for output
 * @brief Takes a key and a parameter and get it read for output
 * @author Barron Wong 02/08/19
*/
char * Protocol_EncodeOutput(pkey_t key, float value, char * buffer){
    int size = strlen(buffer);
 
    //clear buffer
    for(int i = 0; i < size; i++){
        buffer[0] = 0;
    }
    if(key > invalid_key && key <= flow_measured){
        sprintf(buffer,"%d:%f",(int)key,value);
    }
    
    return buffer;
}
/**
 * @function Protocol_PrintMessage(char * input)
 * @param target_t
 * @return none
 * @brief Prints a message and its value
 * @author Barron Wong 02/08/19
 */
void Protocol_PrintMessage(message_t message){
    if(message.key <= flow_measured)
        printf("%s:%f\r\n", pkey_const[message.key], message.value);
}

#ifdef PROTOCOL_TEST
#include "SerialCom.h"
#include "USBCom.h"
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    //Output data to UART
    SerialCom_Init();
    
    //Channel for receiving and sending data
    USBCom_Init();
    
    char buffer[20] = {"1:543.24"};
    int length = 0;
    target_t target;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;){
        length = USBCom_CheckRecievedData(buffer);
        if(length > 0){
            target = Protocol_DecodeInput(buffer);
            if(target.key != invalid_key){
                printf("Key: %d Value: %f\r\n", (int)target.key, target.value);
            }
        }
        Protocol_EncodeOutput(ph_measured, 3.456, buffer);
        USBCom_SendData(buffer);
    }
    
    
}
#endif
/* [] END OF FILE */