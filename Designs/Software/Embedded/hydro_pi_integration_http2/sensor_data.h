#ifndef _SENSOR_DATA_H
#define _SENSOR_DATA_H
#include "Protocol.h"

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

typedef struct SensorData SensorData;

void getGETstr(char *buf, SensorData *sd);
void setRandomData(SensorData *sd);
void randomWalk(SensorData *sd);
void sensor_data_init(SensorData *sd);

int logData(SensorData *sd, char *filename);
int loadData(SensorData *sd, char *filename);
int saveData(SensorData *sd, char *filename);
int updateSensors(message_t * msg, SensorData *sd);


#endif


// TODO Rad bio pics
