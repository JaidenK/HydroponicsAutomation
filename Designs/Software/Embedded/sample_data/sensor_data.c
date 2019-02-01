#include "sensor_data.h"

#include <time.h> // for random
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



void setRandomData(struct SensorData *sd) {
   time_t t;
   srand((unsigned)time(&t));
   sd->h2o_level =       rand() % 256;
   sd->h2o_stored =      rand() % 256;
   sd->ph_level =        rand() % 256;
   sd->ph_up_stored =    rand() % 256;
   sd->ph_down_stored =  rand() % 256;
   sd->ec_level =        rand() % 256;
   sd->ec_stored =       rand() % 256;
   sd->temp_measured =   rand() % 256;
   sd->flow_measured =   rand() % 256;
   sd->flow_target =     rand() % 256;
   sd->ph_target =       rand() % 256;
   sd->ec_target =       rand() % 256;
   strcpy(sd->ProductID,"ABCD1234EFGH5678");
}

double randomExponentially(double current, double max, double min) {
   double strength = 20.0;
   double randDouble = ((double)rand())/RAND_MAX;
   double shift = (current - min) / (max - min); // 0.5 = no bias
   //double coeff = randDouble - shift;
   return (randDouble - shift) * strength;
}

void randomWalk(struct SensorData *sd) {
   sd->h2o_level +=       randomExponentially(sd->h2o_level,245,10);
   sd->h2o_stored +=      randomExponentially(sd->h2o_stored,245,10);
   sd->ph_level +=        randomExponentially(sd->ph_level,245,10);
   sd->ph_up_stored +=    randomExponentially(sd->ph_up_stored,245,10);
   sd->ph_down_stored +=  randomExponentially(sd->ph_down_stored,245,10);
   sd->ec_level +=        randomExponentially(sd->ec_level,245,10);
   sd->ec_stored +=       randomExponentially(sd->ec_stored,245,10);
   sd->temp_measured +=   randomExponentially(sd->temp_measured,245,10);
   sd->flow_measured +=   randomExponentially(sd->flow_measured,245,10);
   sd->flow_target +=     randomExponentially(sd->flow_target,245,10);
   sd->ph_target +=       randomExponentially(sd->ph_target,245,10);
   sd->ec_target +=       randomExponentially(sd->ec_target,245,10);
}

void getGETstr(char *buf, struct SensorData *sd) {
   sprintf(
      buf,
      "ProductID=password&"
      "h2o_level=%f&"
      "h2o_stored=%f&"
      "ph_level=%f&"
      "ph_up_stored=%f&"
      "ph_down_stored=%f&"
      "ec_level=%f&"
      "ec_stored=%f&"
      "temp_measured=%f&"
      "flow_measured=%f&"
      "flow_target=%f&"
      "ph_target=%f&"
      "ec_target=%f&"
      "ProductID=%s",
      sd->h2o_level,
      sd->h2o_stored,
      sd->ph_level,
      sd->ph_up_stored,
      sd->ph_down_stored,
      sd->ec_level,
      sd->ec_stored,
      sd->temp_measured,
      sd->flow_measured,
      sd->flow_target,
      sd->ph_target,
      sd->ec_target,
      sd->ProductID
   );
}
