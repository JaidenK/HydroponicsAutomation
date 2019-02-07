#include "sensor_data.h"

#include <time.h> // for random
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <ctype.h> // isspace()


#include "http.h"

void parseResponse(char *response, struct SensorData *sd);


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
   sd->ph_target =       0;//rand() % 256;
   sd->ec_target =       0;//rand() % 256;
   sd->h2o_target =      0;//rand() % 256;
   sd->temp_target =     0;//rand() % 256;
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
   sd->h2o_level +=       randomExponentially(sd->h2o_level,300,10);
   sd->h2o_stored +=      randomExponentially(sd->h2o_stored,245,10);
   sd->ph_level +=        randomExponentially(sd->ph_level,14,1);
   sd->ph_up_stored +=    randomExponentially(sd->ph_up_stored,245,10);
   sd->ph_down_stored +=  randomExponentially(sd->ph_down_stored,245,10);
   sd->ec_level +=        randomExponentially(sd->ec_level,500,10);
   sd->ec_stored +=       randomExponentially(sd->ec_stored,245,10);
   sd->temp_measured +=   randomExponentially(sd->temp_measured,80,10);
   sd->flow_measured +=   randomExponentially(sd->flow_measured,245,10);
   // sd->flow_target +=     randomExponentially(sd->flow_target,245,10);
   // sd->ph_target +=       randomExponentially(sd->ph_target,245,10);
   // sd->ec_target +=       randomExponentially(sd->ec_target,245,10);
   // sd->h2o_target +=      randomExponentially(sd->h2o_target,245,10);
}

int loadData(struct SensorData *sd, char *filename) {
   FILE *save_file = fopen("save_data.dat", "r");
   if(!save_file) {
      printf("Error opening saved data.\n");
      setRandomData(sd);
   }else{
      fscanf(
         save_file,
         "h2o_level=%lf\n"
         "h2o_stored=%lf\n"
         "ph_level=%lf\n"
         "ph_up_stored=%lf\n"
         "ph_down_stored=%lf\n"
         "ec_level=%lf\n"
         "ec_stored=%lf\n"
         "temp_measured=%lf\n"
         "flow_measured=%lf\n"
         "flow_target=%lf\n"
         "ph_target=%lf\n"
         "ec_target=%lf\n"
         "h2o_target=%lf\n"
         "temp_target=%lf\n"
         "ProductID=%s\n",
         &(sd->h2o_level),
         &(sd->h2o_stored),
         &(sd->ph_level),
         &(sd->ph_up_stored),
         &(sd->ph_down_stored),
         &(sd->ec_level),
         &(sd->ec_stored),
         &(sd->temp_measured),
         &(sd->flow_measured),
         &(sd->flow_target),
         &(sd->ph_target),
         &(sd->ec_target),
         &(sd->h2o_target),
         &(sd->temp_target),
         (sd->ProductID)
      );
   }
   fclose(save_file);
   return 0;
}


int saveData(struct SensorData *sd, char *filename) {
   FILE *save_file = fopen("save_data.dat", "w");
   if(!save_file) {
      printf("Error opening saved data.\n");
      setRandomData(sd);
   }else{
      fprintf(
         save_file,
         "h2o_level=%lf\n"
         "h2o_stored=%lf\n"
         "ph_level=%lf\n"
         "ph_up_stored=%lf\n"
         "ph_down_stored=%lf\n"
         "ec_level=%lf\n"
         "ec_stored=%lf\n"
         "temp_measured=%lf\n"
         "flow_measured=%lf\n"
         "flow_target=%lf\n"
         "ph_target=%lf\n"
         "ec_target=%lf\n"
         "h2o_target=%lf\n"
         "temp_target=%lf\n"
         "ProductID=%s\n",
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
         sd->h2o_target,
         sd->temp_target,
         sd->ProductID
      );
   }
   fclose(save_file);
   return 0;
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
      "h2o_target=%f&"
      "temp_target=%f&"
      "ProductID=%s&"
      "",
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
      sd->h2o_target,
      sd->temp_target,
      sd->ProductID
   );
}

int logData(struct SensorData *sd) {
   char response[4096];
   char getStr[4096];
   getGETstr(getStr,sd);
   HTTP_Get("dataReceiver.php",getStr,response,4096);
   parseResponse(response,sd);
   return 0;
}

// TODO something more useful than a print satement
void parseResponse(char *response, struct SensorData *sd) {
   //printf("Parsing response:\n");
   // printf("%s\n",response);
   char *tok; 
   tok = strtok(response,"\n");
   while(tok != NULL) {
      char *val;
      val = strchr(tok,'=');
      if(val != NULL) {
         // If val was null then no '=' was found and this isn't a line
         // with a key=value pair
         val++;
         char arg[256];
         memset(arg,'\0',256);
         strncpy(arg,tok,val-tok-1);
         // printf("arg: %s\nval: %s\n", arg, val);


         if(strcmp(arg,"new_record") == 0) {
            if(strcmp(val,"success")==0) {
               printf("Record created successfully.\n");
            }else{
               if(strncmp(val,"Invalid product id",18)==0) {
                  printf("Your data will not be saved to the web until you've registered your product to your account.\n");
               }
               printf("Error logging data: %s\n", val);
            }
         }

         if(strcmp(arg,"water_target") == 0) {
            char *err;
            double d = strtod(val, &err);
            if (*err == 0) { 
               sd->h2o_target = d;
            }else if (!isspace((unsigned char)*err)) {
               printf("Error parsing water_target %s\n",val);
            }
         }
         if(strcmp(arg,"ph_target") == 0) {
            char *err;
            double d = strtod(val, &err);
            if (*err == 0) { 
               sd->ph_target = d;
            }else if (!isspace((unsigned char)*err)) {
               printf("Error parsing ph_target %s\n",val);
            }
         }
         if(strcmp(arg,"ec_target") == 0) {
            char *err;
            double d = strtod(val, &err);
            if (*err == 0) { 
               sd->ec_target = d;
            }else if (!isspace((unsigned char)*err)) {
               printf("Error parsing ec_target %s\n",val);
            }
         }
         if(strcmp(arg,"flow_target") == 0) {
            char *err;
            double d = strtod(val, &err);
            if (*err == 0) { 
               sd->flow_target = d;
            }else if (!isspace((unsigned char)*err)) {
               printf("Error parsing flow_target %s\n",val);
            }
         }
         if(strcmp(arg,"temp_target") == 0) {
            char *err;
            double d = strtod(val, &err);
            if (*err == 0) { 
               sd->temp_target = d;
            }else if (!isspace((unsigned char)*err)) {
               printf("Error parsing temp_target %s\n",val);
            }
         }
      }

      // Move to the next line of the response
      tok = strtok(NULL,"\n");
   }
}

void funcPointerTest(void (*func)()) {
   func();
}

