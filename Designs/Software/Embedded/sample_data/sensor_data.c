#include "sensor_data.h"

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
};


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
      "ec_target=%f",
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
      sd->ec_target
   );
}
