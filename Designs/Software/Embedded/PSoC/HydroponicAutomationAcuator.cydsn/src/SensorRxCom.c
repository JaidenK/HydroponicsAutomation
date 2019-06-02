#include "SensorRxCom.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TURN_OFF 1
#define TURN_ON 0

static char RxBuffer[BUFF_SIZE];
static uint8_t ready = FALSE;

#ifdef SENSOR_COM_RX_TEST
    static struct SensorData sd;
#endif

uint16_t CalcChecksum(const char *s);
void SensorComUpdateData(pkey_t key, float value);

/**
 * @function SensorComRx_CheckStatus()
 * @param None
 * @return TRUE or FALSE
 * @brief Returns TRUE if new data is avaiable, FALSE if not
 * @author Barron Wong 04/05/19
 */   
uint8_t SensorComRx_CheckStatus(){
    if(ready){
        ready = FALSE;
        return TRUE;
    }
        
    return ready;
}

/**
 * @function SensorComRx_Init()
 * @param None
 * @return None
 * @brief Initialize serial communication for sensor data
 * @author Barron Wong 04/05/19
 */
void SensorComRx_Init(){
    SensorSW_Write(TURN_OFF);
    DataComRxISR_StartEx(DataComRxISR);
    SensorRxComUART_Start();
    SensorSW_Write(TURN_ON);
}

/**
 * @function SensorComUpdateData(pkey_t key, float value)
 * @param parameter key with its corresponting value
 * @return None
 * @brief Updates the SensorData outlined by key with value
 * @author Barron Wong 04/05/19
 */
void SensorComUpdateData(pkey_t key, float value){
    switch(key){
        case h20_level:
        sd.h2o_level = value;
        break;
        case h20_stored:
        sd.h2o_stored = value;
        break;
        case ph_measured:
        sd.ph_level = value;
        break;
        case ph_up_stored:
        sd.ph_up_stored = value;
        break;
        case ph_down_stored:
        sd.ph_down_stored = value;
        break;
        case ec_measured:
        sd.ec_level = value;
        break;
        case ec_stored:
        sd.ec_stored = value;
        break;
        case temp_measured:
        sd.temp_measured = value;
        break;
        case flow_measured:
        sd.flow_measured = value;
        break;
        default:
        printf("Invald pkey: %d",key);
    }
}

/**
 * @function SensorComRx_EncodeMessage()
 * @param SensorData structure
 * @return Pointer to SensoData structure
 * @brief Takes in a string checks the checksum and decodes the message
 *        and updates the SensorData structure
 * @author Barron Wong 04/05/19
 */
struct SensorData * SensorComRx_DecodeMessage(struct SensorData * sd, char * buffer){
    uint16_t len;
    unsigned int checksum;
    unsigned int rchecksum;
    char * token;
    const char * delim = ",:";
    char value_str[BUFF_SIZE];
    pkey_t key;
    float value;
    
    len = strlen(buffer);
    
    sscanf(buffer+len-2,"%X",&rchecksum);
    
    buffer[len - 3] = 0;
    buffer = buffer + 1;
    checksum = CalcChecksum(buffer);
    if(rchecksum != checksum){
        printf("Checksum Mismatch: Recvd %2X Actual %2X\r\n",rchecksum, checksum);
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
            SensorComUpdateData(key,value);
            token = strtok(NULL,delim);
        }
    }
    return sd;
}
 
/**
 * @function checksum()
 * @param pointer to string that needs checksum generated
 * @return checksum
 * @brief computes and returns checksum of a string
 * @author NMEA0183 Wikipedia Page
 */
uint16_t CalcChecksum(const char *s) {
    uint16_t c = 0;

    while(*s){
        c ^= *s++;
    }
    return c;
}

/**
 * @function DataComRxISR(void)
 * @param None
 * @return None
 * @brief ISR for recieving data
 * @author Barron Wong 04/05/19
 */
CY_ISR(DataComRxISR){
    static uint8_t count = 0;
    static uint8_t remainder = 0; 
    
    DataComRxISR_ClearPending();
    
    //Set ready to false 
    //If ready is TRUE and we are in this ISR, 
    //then a new transmission is incoming
    if(ready == TRUE)
        ready = FALSE;
    
    while(SensorRxComUART_ReadRxStatus() == SensorRxComUART_RX_STS_FIFO_NOTEMPTY){
        RxBuffer[count++] = SensorRxComUART_GetChar();
    }
    RxBuffer[count] = '\0';
    
    
    if(remainder){
        if(remainder == 1){
            count = 0;
            SensorComRx_DecodeMessage(&sd,RxBuffer);
            ready = TRUE;
        }
        remainder--;
    }
    
        //Check for end of message
    if(RxBuffer[count - 1] == '*'){
        remainder = 2;
    }
}

#ifdef SENSOR_COM_RX_TEST
#include "SerialCom.h"
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    SerialCom_Init();
    SensorComRx_Init();

    
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        if(ready == TRUE){
            ready = FALSE;
//            printf("h20_level: %0.2f\r\n", sd.flow_target);
//            printf("h20_stored: %0.2f\r\n", sd.h2o_stored);
//            printf("ph_measured: %0.2f\r\n", sd.ph_level);
//            printf("ph_up_stored: %0.2f\r\n", sd.ph_up_stored);
//            printf("ph_down_stored: %0.2f\r\n", sd.ph_down_stored);
//            printf("ec_measured: %0.2f\r\n", sd.ec_level);
//            printf("ec_stored: %0.2f\r\n", sd.ec_stored);
//            printf("temp_measured: %0.2f\r\n", sd.temp_measured);
//            printf("flow_measured: %0.2f\r\n", sd.flow_measured);
        }
    }
}
#endif