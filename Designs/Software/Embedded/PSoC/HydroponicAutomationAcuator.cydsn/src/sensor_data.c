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
#define PH_MAX 8
#define PH_MIN 3
#define EC_MIN 200
#define EC_MAX 3000
//struct SensorData {
//	double h2o_level;
//	double h2o_stored;
//	double ph_level;
//	double ph_up_stored;
//	double ph_down_stored;
//	double ec_level;
//	double ec_stored;
//	double temp_measured;
//	double flow_measured;
//	double flow_target;
//	double ph_target;
//	double ec_target;
//	double h2o_target;
//	double temp_target;
//	char ProductID[256];
//};
/**
 * @function sensor_data_Init(char * input)
 * @param pointer to a SensorData Structure
 * @return None
 * @brief Initializes sensor data structure.
 * @author Barron Wong 02/08/19
*/
int updateSensors(message_t * msg, struct SensorData * sd) {
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
        if (target.key < MIN_FLOW)
            target.key = MIN_FLOW;
        else if (target.key > MAX_FLOW)
            target.key = MAX_FLOW;
        else 
            sd->flow_target = target.value;
        break;
        }
        
        case ph_target:{
        if (target.key < PH_MIN || target.key > PH_MAX)
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


void setRandomData(struct SensorData *sd) {
	time_t t;
	srand((unsigned)time(&t));
	sd->h2o_level = rand() % 256;
	sd->h2o_stored = rand() % 256;
	sd->ph_level = rand() % 256;
	sd->ph_up_stored = rand() % 256;
	sd->ph_down_stored = rand() % 256;
	sd->ec_level = rand() % 256;
	sd->ec_stored = rand() % 256;
	sd->temp_measured = rand() % 256;
	sd->flow_measured = rand() % 256;
	sd->flow_target = rand() % 256;
	sd->ph_target = 0;//rand() % 256;
	sd->ec_target = 0;//rand() % 256;
	sd->h2o_target = 0;//rand() % 256;
	sd->temp_target = 0;//rand() % 256;
	strcpy(sd->ProductID, "ABCD1234EFGH5678");
}

//Produces a random number
double randomExponentially(double current, double max, double min) {
	double strength = 20.0;
	double randDouble = ((double)rand()) / RAND_MAX;
	double shift = (current - min) / (max - min); // 0.5 = no bias
	//double coeff = randDouble - shift;
	return (randDouble - shift) * strength;
}

//Adds random walk data to a sensor data structure.
void randomWalk(struct SensorData *sd) {
	sd->h2o_level += randomExponentially(sd->h2o_level, 300, 10);
	sd->h2o_stored += randomExponentially(sd->h2o_stored, 245, 10);
	sd->ph_level += randomExponentially(sd->ph_level, 14, 1);
	sd->ph_up_stored += randomExponentially(sd->ph_up_stored, 245, 10);
	sd->ph_down_stored += randomExponentially(sd->ph_down_stored, 245, 10);
	sd->ec_level += randomExponentially(sd->ec_level, 500, 10);
	sd->ec_stored += randomExponentially(sd->ec_stored, 245, 10);
	sd->temp_measured += randomExponentially(sd->temp_measured, 80, 10);
	sd->flow_measured += randomExponentially(sd->flow_measured, 245, 10);
	// sd->flow_target +=     randomExponentially(sd->flow_target,245,10);
	// sd->ph_target +=       randomExponentially(sd->ph_target,245,10);
	// sd->ec_target +=       randomExponentially(sd->ec_target,245,10);
	// sd->h2o_target +=      randomExponentially(sd->h2o_target,245,10);
}

//Reads sensor data from a file
int loadData(struct SensorData *sd, char *filename) {
	FILE *save_file = fopen("save_data.dat", "r");
	if (!save_file) {
		printf("Error opening saved data.\n");
		setRandomData(sd);
	}
	else {
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
	return 0;
}

int saveData(struct SensorData *sd, char *filename) {
	FILE *save_file = fopen("save_data.dat", "w");
	if (!save_file) {
		printf("Error opening saved data.\n");
		setRandomData(sd);
	}
	else {
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
	return 0;
}

//Gets a string of data.
void getGETstr(char *buf, struct SensorData *sd) {
	sprintf(
		buf,
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
