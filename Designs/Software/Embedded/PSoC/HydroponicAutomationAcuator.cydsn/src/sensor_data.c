//This file generates random sensor data and stores it into a sensor data structure.

#include "sensor_data.h"
#include <time.h> // for random
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define SUCCESS 1
#define ERROR   0
#define MAX_HEIGHT 16.2
#define MIN_HEIGHT 0
#define MIN_FLOW 0
#define MAX_FLOW 3.5
#define PH_MAX 10
#define PH_MIN 3
#define EC_MIN 0
#define EC_MAX 3000
/**
 * @function SensorData_UpdateSensors(message_t * msg, struct SensorData * sd)
 * @param pointer to a SensorData Structure
 * @return None
 * @brief Initializes sensor data structure.
 * @author Barron Wong 02/08/19
*/
int SensorData_UpdateSensors(message_t * msg, struct SensorData * sd){
	int return_val = 0;
	switch (msg->key) {
	case h20_level:
		sd->h2o_level = msg->value;
		break;
	case h20_stored:
		sd->h2o_stored = msg->value;
		break;
	case ph_measured:
		sd->ph_level = msg->value;
		break;
	case ph_up_stored:
		sd->ph_up_stored = msg->value;
		break;
	case ph_down_stored:
		sd->ph_down_stored = msg->value;
		break;
	case ec_measured:
		sd->ec_level = msg->value;
		break;
	case ec_stored:
		sd->ec_stored = msg->value;
		break;
	case temp_measured:
		sd->temp_measured = msg->value;
		break;
	case flow_measured:
		sd->flow_measured = msg->value;
		break;
	default:
		return_val = -1;

	}
	return return_val;
}

int SensorData_UpdateTarget(message_t target, struct SensorData * sd){
    
    switch(target.key){
        case h20_level_target:{
        if(target.value < MIN_HEIGHT)
            target.key = 0;
        else if (target.value > MAX_HEIGHT - 2)
            target.key = 0;
        else
            sd->h2o_target = target.value;
        break;
        }
        
        case flow_target:{
        if (target.value < MIN_FLOW)
            target.value = MIN_FLOW;
        else if (target.value > MAX_FLOW)
            target.value = MAX_FLOW;
        else 
            sd->flow_target = target.value;
        break;
        }
        
        case ph_target:{
        if (target.value < PH_MIN || target.value > PH_MAX)
            break;
        sd->ph_target = target.value;
        break;
        
        case ec_target:
        if (target.value < EC_MIN || target.value > EC_MAX)
            break;
        sd->ec_target = target.value;
        break;
        }
        
        default:
        return ERROR;
    }
    
    return SUCCESS;
}

/**
 * @function sensor_data_Init(char * input)
 * @param pointer to a SensorData Structure
 * @return None
 * @brief Initializes sensor data structure.
 * @author Barron Wong 02/08/19
*/
void sensor_data_init(struct SensorData *sd) {
	sd->h2o_level = 0;
	sd->h2o_stored = 0;
	sd->ph_level = 0;
	sd->ph_up_stored = 0;
	sd->ph_down_stored = 0;
	sd->ec_level = 0;
	sd->ec_stored = 0;
	sd->temp_measured = 0;
	sd->flow_measured = 0;
	sd->flow_target = 0;
	sd->ph_target = 0;
	sd->ec_target = 0;
	sd->h2o_target = 0;
	sd->temp_target = 0;
	strcpy(sd->ProductID, "ABCD1234EFGH5678");
}
/**
 * @function SensorData_FloatToString(char * buffer, float data)
 * @param pointer to buffer and float to be converted
 * @return Pointer to converted string
 * @brief Converts a float to a string rounding to nearest hundreth.
 * @author Barron Wong 02/08/19
*/
char * SensorData_FloatToString(char * buffer, float value){
    int len = strlen(buffer); 
    
    for( int i = 0; i < len; i++)
        buffer[i] = '\0';
        
    sprintf(buffer,"%d.%02d",(int)value, ((int)(value * 100.0 + 0.5))%100);
    
    return buffer;
}
