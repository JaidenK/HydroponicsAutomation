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

#ifdef PROTOCOL_TEST
#include "USBCom.h"
    
int main(void)
{

    
    
}
#endif
/* [] END OF FILE */