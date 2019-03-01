#include "Mixing.h"

static int dutyCycle = 22873;
/**
 * @function Mixing_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary mixing
 * @author Barron Wong 02/28/19
*/
void Mixing_Init(){
    MixingPWM_Start();
    Mixing_TurnOff();
}

/**
 * @function Mixing_SetDutyCycle(void)
 * @param duty cycle 0-1000
 * @return None
 * @brief Sets the duty cycle between 0-1000 with 1000 being 100%
 * @author Barron Wong 02/28/19
*/
void Mixing_SetDutyCycle(int newDutyCycle){
    if(newDutyCycle > MIXING_DUTY_MAX)
        newDutyCycle = MIXING_DUTY_MAX;
    if(newDutyCycle < 0)
        newDutyCycle = 0;
    
    dutyCycle = newDutyCycle;
    
    MixingPWM_WriteCompare(dutyCycle);
}

/**
 * @function Mixing_TurnOff(void)
 * @param Nonw
 * @return None
 * @brief Turns the mixing motor off
 * @author Barron Wong 02/28/19
*/
void Mixing_TurnOff(){
    MixingPWM_WriteCompare(0);
}

/**
 * @function Mixing_TurnOn(void)
 * @param Nonw
 * @return None
 * @brief Turns the mixing motor on
 * @author Barron Wong 02/28/19
*/
void Mixing_TurnOn(){
    MixingPWM_WriteCompare(dutyCycle);
}