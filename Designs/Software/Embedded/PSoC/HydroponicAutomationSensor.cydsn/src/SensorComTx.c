/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF AdvancedByte.
 *
 * ========================================
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "project.h"
#include "SensorComTx.h"
#include "sensor_data.h"

#define BUFF_SIZE 255

extern struct SensorData sd;
static char buffer[BUFF_SIZE];

int CalcChecksum(const char *s);

/**
 * @function SensorComTx_Init()
 * @param None
 * @return None
 * @brief Initialize serial communication for sensor data
 * @author Barron Wong 04/04/19
 */
void SensorComTx_Init(){
    SensorDataComISR_StartEx(SensorDataComISRHandler);
    SensorComTxUART_Start();
    SensorDataComTimer_Start();
}

/**
 * @function SensorComTx_EncodeMessage()
 * @param SensorData structure, buffer
 * @return None
 * @brief Takes in a SensorData structure and returns
 *        a string in nmea0183 format
 * @author Barron Wong 04/04/19
 */
char * SensorComTx_EncodeMessage(struct SensorData sd, char * buffer){
    int len;
    int checksum;
    char data_buffer[BUFF_SIZE];
    
    //Clear buffer
    len = strlen(buffer);
    for(int i = 0; i < len; i++){
        buffer[i] = 0;
    }
    
    buffer[0] = '$';
    
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
    strcat(buffer,Protocol_EncodeOutput(ec_stored, sd.ec_level, data_buffer));
    buffer[strlen(buffer)]= ',';
    
    //temp_measured
    strcat(buffer,Protocol_EncodeOutput(temp_measured, sd.temp_measured, data_buffer));
    buffer[strlen(buffer)]= ',';
    
    //flow_measured
    strcat(buffer,Protocol_EncodeOutput(flow_measured, sd.flow_measured, data_buffer));
    
    //Calc checksum ignoring starting character
    checksum = CalcChecksum(buffer+1);
    
    buffer[strlen(buffer)]= '*';
    sprintf(data_buffer,"%02X",checksum);
    strcat(buffer, data_buffer);
    printf("%s\r\n", buffer);
    
    return buffer;
}
/**
 * @function checksum()
 * @param pointer to string that needs checksum generated
 * @return checksum
 * @brief computes and returns checksum of a string
 * @author NMEA0183 Wikipedia Page
 */
int CalcChecksum(const char *s) {
    int c = 0;

    while(*s){
        c ^= *s++;
    }
    return c;
}
/**
 * @function SensorDataComISRHandler(void)
 * @param None
 * @return None
 * @brief ISR handler for sensor data transmission. Sends updated
 *        SensorData every 200ms
 * @author Barron Wong 04/05/19
 */
CY_ISR(SensorDataComISRHandler){
    SensorDataComISR_ClearPending();
    SensorComTx_EncodeMessage(sd,buffer);
    SensorComTx_SendMessage(buffer);
}

/**
 * @function SensorComTx_SendMessage()
 * @param A string with data that needs to be sent
 * @return None
 * @brief Takes a string and send it over UART
 * @author Barron Wong 04/04/19
 */
void SensorComTx_SendMessage(char* msg){
    SensorComTxUART_PutString(msg);
}
#ifdef SENSOR_COM_TX_TEST
#include "SerialCom.h"
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    SerialCom_Init();
    SensorComTx_Init();
    sensor_data_init(&sd);

    
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
    }
}
#endif