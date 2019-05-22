/*
 * File:   WaterLevelController.h
 * Author: bwong20
 *
 * Software to control the flow 
 *
 *
 *
 * PWM_TEST (in the .c file) conditionally compiles the test harness for the code. 
 * 
 *
 * Created on Janruary 25, 2019
 */

#include "WaterLevelController.h"
#include "sensor_data.h"

#include "project.h"

#define SUCCESS 1
#define ERROR -1
#define MAX_HEIGHT 16.2
#define MARGIN 0.05
#define LOWER_THRESH sd.h2o_target - MARGIN*sd.h2o_target

extern struct SensorData sd;

/**
 * @function WaterLevelControllerISRHandler(void)
 * @param None
 * @return None
 * @brief Control ISR set on 100ms timer. Turns on pump if
 *        water level is below the target
 * @author Barron Wong 05/06/19
 */
CY_ISR(WaterLevelControllerISRHandler){
    float waterLevel = WaterLevelController_GetWaterLevel();
    
    WaterLevelControllerISR_ClearPending();
    
    
    if (waterLevel < LOWER_THRESH)
        WaterLevelControlReg_Write(1);
    else if (waterLevel > sd.h2o_target)
        WaterLevelControlReg_Write(0);
}

/**
 * @function WaterLevelController_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for water level control
 * @author Barron Wong 05/06/19
*/
void WaterLevelController_Init(){
    WaterLevelControlTimer_Start();
    WaterLevelControllerISR_StartEx(WaterLevelControllerISRHandler);
}

/**
 * @function WaterLevelController_GetWaterLevel(void)
 * @param None
 * @return Height of water level in centimeters
 * @brief Get the water level and returns the height in centimeters
 * @author Barron Wong 05/013/19
*/
float WaterLevelController_GetWaterLevel(){
    float waterLevel = (MAX_HEIGHT - sd.h2o_level);
    
    if (waterLevel < 0.001)
        waterLevel = 0;
    
    return waterLevel;
}


/* [] END OF FILE */
