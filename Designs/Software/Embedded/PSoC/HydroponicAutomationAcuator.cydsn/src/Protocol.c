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
#include "sensor_data.h"

#define BUFF_SIZE 255

extern struct SensorData sd;

/**
 * @function Protocol_DecodeInput(char * input)
 * @param None
 * @return Takes an incoming data transmission and decodes it
 * @brief Converts the current frequency and returns flow rate
 * @author Barron Wong 02/08/19
*/
message_t Protocol_DecodeInput(char * input){
    char * ptr;
    message_t message;
    uint8_t count = 0;
    
    message.key = invalid_key;
    message.key = 0;
    
    ptr = strtok(input,":");
    
    while(ptr != NULL){
        switch(count){
            case 0:{
                message.key = atoi(ptr);
            break;
            }
            case 1:{
                message.value = atof(ptr);
            break;
            }
            default:{
                message.key = invalid_key;
                message.value = -1;
            }
        }
        count++;
        ptr = strtok(NULL,":");
    }
    
    return message;
    
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
    char floatBuff[BUFF_SIZE];
 
    //clear buffer
    for(int i = 0; i < size; i++){
        buffer[0] = 0;
    }
    
    SensorData_FloatToString(floatBuff,value);
    
    if(key > invalid_key && key <= flow_measured){
        sprintf(buffer,"%d:%f",(int)key, value);
        //sprintf(buffer,"%d:%s",(int)key,floatBuff);
    }
    
    return buffer;
}

/**
 * @function SensorComTx_EncodeMessage()
 * @param SensorData structure, buffer
 * @return None
 * @brief Takes in a SensorData structure and returns
 *        a string in nmea0183 format
 * @author Barron Wong 04/04/19
 */
char * Protocol_EncodeMessage(char * buffer){
    int len;
    int checksum;
    char data_buffer[BUFF_SIZE];
    
    //Clear buffer
    len = strlen(buffer);
    for(int i = 0; i < len; i++){
        buffer[i] = 0;
    }
    
    //h20_level
    strcat(buffer,Protocol_EncodeOutput(h20_level, sd.h2o_level, data_buffer));
    buffer[strlen(buffer)]= ',';
    
    //h20_stored
    strcat(buffer,Protocol_EncodeOutput(h20_stored, sd.h2o_stored, data_buffer));
    buffer[strlen(buffer)]= ',';
    
    //ph_measured
    strcat(buffer,Protocol_EncodeOutput(ph_measured, sd.ph_level, data_buffer));
    buffer[strlen(buffer)]= ',';
    
    //ph_up_stored
    strcat(buffer,Protocol_EncodeOutput(ph_up_stored, sd.ph_up_stored, data_buffer));
    buffer[strlen(buffer)]= ',';
    
    //ph_down_stored
    strcat(buffer,Protocol_EncodeOutput(ph_down_stored, sd.ph_down_stored, data_buffer));
    buffer[strlen(buffer)]= ',';
    
    //ec_measured
    strcat(buffer,Protocol_EncodeOutput(ec_measured, sd.ec_level, data_buffer));
    buffer[strlen(buffer)]= ',';
    
    //ec_stored
    strcat(buffer,Protocol_EncodeOutput(ec_stored, sd.ec_stored, data_buffer));
    buffer[strlen(buffer)]= ',';
    
    //temp_measured
    strcat(buffer,Protocol_EncodeOutput(temp_measured, sd.temp_measured, data_buffer));
    buffer[strlen(buffer)]= ',';
    
    //flow_measured
    strcat(buffer,Protocol_EncodeOutput(flow_measured, sd.flow_measured, data_buffer));
    
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