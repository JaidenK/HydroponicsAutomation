#include "ECController.h"
#include "sensor_data.h"
#include "Mixing.h"
#include <math.h>

#define TRUE 1
#define FALSE 0


#define EC_DROP_DURATION 100
#define MARGIN 100
#define EC_LOWERBOUND sd.ec_target*MARGIN
#define EC_TARGET_MIN 100

extern uint8_t pH_Enable;

/**
 * @function ECControllerISRHandler(void)
 * @param None
 * @return None
 * @brief Handler for pH ISR. Makes pH adjustments every two minutes.
 * @author Barron Wong 01/25/19
 */
CY_ISR(ECControllerISRHandler){
    static float kp = 1;
    static int drops = 0;
    static uint8 adjust = FALSE;
    float error; 
    
    float ec_level = ECController_GetEC();
    
    ECControllerTimerISR_ClearPending();
    if(sd.ec_target >= EC_TARGET_MIN){
        error = sd.ec_target - ec_level;
        if(sd.ec_target <= ec_level){
            adjust = FALSE;
            Mixing_TurnOff();
            pH_Enable = ON;
        }

        //Hystersis bound for error
        if(!adjust){
            if(error > MARGIN){
                adjust = TRUE;
                pH_Enable = OFF;
                Mixing_TurnOn();
            }
        }

        if(adjust){
            Mixing_TurnOn();
            printf("EC Adjust\r\n");
            drops = kp*error;
            ECController_AdjustEC(drops);
        }
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
    ECControllerTimer_Start();
    ECControllerTimerISR_StartEx(ECControllerISRHandler);
    //sd.ec_target = 1300;
}

/**
 * @function ECController_AdjustEC(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary for flow control and monitoring
 * @author Barron Wong 05/09/19
*/
void ECController_AdjustEC(uint16_t drops){
    
    uint32_t duration = drops*EC_DROP_DURATION + 1;
    printf("Duration: %d\r\n", duration);
    ECControllerPWMCounter_WritePeriod(duration);
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
 * @function ECController_TurnOff()
 * @param None
 * @return 
 * @brief Turn off EC controller
 * @author Barron Wong 06/01/19
*/
void ECController_TurnOff(){
    ECControllerTimerISR_ClearPending();
    ECControllerTimerISR_Disable();
}

/**
 * @function ECController_TurnOn()
 * @param None
 * @return 
 * @brief Turn on EC controller
 * @author Barron Wong 06/01/19
*/
void ECController_TurnOn(){
    ECControllerTimerISR_Enable();
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
        ECController_AdjustEC(1);
        CyDelay(1000);

    }
        
    
    
}
#endif