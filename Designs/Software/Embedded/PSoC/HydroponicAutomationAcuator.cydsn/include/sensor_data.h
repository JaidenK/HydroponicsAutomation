#ifndef _SENSOR_DATA_H
#define _SENSOR_DATA_H

#include "Protocol.h"
#include <stdio.h>
    
#define OFF 0
#define ON 1
    
struct SensorData {
   double h2o_level;
   double h2o_stored;
   double ph_level;
   double ph_up_stored;
   double ph_down_stored;
   double ec_level;
   double ec_stored;
   double temp_measured;
   double flow_measured;
   double flow_target;
   double ph_target;
   double ec_target;
   double h2o_target;
   double temp_target;
   char ProductID[256];
};

struct SensorData sd;


void sensor_data_init(struct SensorData *sd);


int SensorData_UpdateSensors(message_t * msg, struct SensorData * sd);
int SensorData_UpdateTarget(message_t target, struct SensorData * sd);


/**
 * @function SensorData_FloatToString(char * buffer, float data)
 * @param pointer to buffer and float to be converted
 * @return Pointer to converted string
 * @brief Converts a float to a string rounding to nearest hundreth.
 * @author Barron Wong 02/08/19
*/
char * SensorData_FloatToString(char * buffer, float data);



#endif


// TODO Rad bio pics
