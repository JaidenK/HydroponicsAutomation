#include "ECController.h"
#include "sensor_data.h"
#include "Mixing.h"
#include <math.h>

#define TRUE 1
#define FALSE 0


extern struct SensorData sd;
#define EC_DROP_DURATION 100
#define MARGIN 0.05
#define EC_LOWERBOUND sd.ec_level*MARGIN

/**
 * @function ECControllerISRHandler(void)
 * @param None
 * @return None
 * @brief Handler for pH ISR. Makes pH adjustments every two minutes.
 * @author Barron Wong 01/25/19
 */
CY_ISR_PROTO(ECControllerISRHandler){
    static float kp = 30;
    static int drops = 0;
    static uint8 adjust = FALSE;
    float error; 
    
    ECControllerISR_ClearPending();
    error = sd.ec_target - sd.ph_level;
    
    
    if(fabs(error) < MARGIN){
        adjust = FALSE;
        Mixing_TurnOff();
    }
    
    //Hystersis bound for error
    if(!adjust){
        if(error < EC_LOWERBOUND){
            adjust = TRUE;
            Mixing_TurnOn();
        }
    }
    
    if(adjust){
        drops = kp*error;
        ECController_AdjustEC(drops);
    }
    
    
}

/**
 * @function ECController_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for EC control
 * @author Barron Wong 05/09/19
*/
void ECController_Init(){
    ECControllerPWMCounter_Start();
    ECControllerPWMCounter_WriteCounter(0);
    ECControllerPWM_Start();
    
}

/**
 * @function ECController_AdjustEC(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 05/09/19
*/
void ECController_AdjustEC(uint16_t drops){
    
    uint32_t duration = drops*EC_DROP_DURATION;
    
    ECControllerPWMCounter_WritePeriod(drops);
    ECControlReg_Write(1);
}
/**
 * @function ECController_GetEC(void)
 * @param None
 * @return EC reading
 * @brief Get the current EC reading 
 * @author Barron Wong 05/25/19
*/
double ECController_GetEC(){
    return sd.ec_level;
}
/**
 * @function ECController_GetEC(void)
 * @param None
 * @return EC reading
 * @brief Get the current EC reading 
 * @author Barron Wong 05/25/19
*/
double ECController_TurnOff(){
    return sd.ec_level;
}

#ifdef ECCONTROLLER_TEST   
    
#include "SerialCom.h"

#define FLOW_REF 1
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */;
    SerialCom_Init();
    ECController_Init();
    int switch1;
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        CyDelay(1000);
        //ECController_AdjustEC();
        CyDelay(1000);

    }
        
    
    
}
#endif