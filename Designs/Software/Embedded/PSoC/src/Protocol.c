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
target_t Protocol_DecodeInput(char * input){
    char * ptr;
    target_t target;
    uint8_t count = 0;
    
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

#ifdef PROTOCOL_TEST
#include "SerialCom.h"
#include "USBCom.h"
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    SerialCom_Init();
    
    char buffer[20] = {"1:543.24"};
    target_t target;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    target = Protocol_DecodeInput(buffer);
    
    printf("Key: %d Value: %f\r\n", (int)target.key, target.value);
    
    
}
#endif
/* [] END OF FILE */