#include "Mixing.h"
#include "WaterLevelController.h"
#define ADC_MAX 255
static int dutyCycle = 200;
/**
 * @function Mixing_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary mixing
 * @author Barron Wong 02/28/19
*/
void Mixing_Init(){
    MixingDAC_Start();
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
    MixingDAC_SetValue(dutyCycle);
}

/**
 * @function Mixing_TurnOff(void)
 * @param Nonw
 * @return None
 * @brief Turns the mixing motor off
 * @author Barron Wong 02/28/19
*/
void Mixing_TurnOff(){
    MixingDAC_SetValue(0);
    WaterLevelController_TurnOn();
}

/**
 * @function Mixing_TurnOn(void)
 * @param Nonw
 * @return None
 * @brief Turns the mixing motor on
 * @author Barron Wong 02/28/19
*/
void Mixing_TurnOn(){
    MixingDAC_SetValue(dutyCycle);
    WaterLevelController_TurnOff();
}
#ifdef MIXING_TEST   
    
#include "FlowController.h"
#include "SerialCom.h"
#include "USBCom.h"
#include "Protocol.h"

#define FLOW_REF 1
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    ADC_DelSig_1_Start();
    FlowController_Init();
    SerialCom_Init();
    //USBCom_Init();
    Mixing_Init();
    
    FlowController_SetFlowReference(FLOW_REF);
    
    printf("Hydroponic Automation\r\n");
    uint16_t adcReading;
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        //Check voltage reading from pin 0.1
        adcReading = ADC_DelSig_1_Read16();
        if(adcReading > 600)
            adcReading = 0;
        if(adcReading > ADC_MAX)
            adcReading = ADC_MAX;
        
        MixingDAC_SetValue(adcReading);
        printf("DAC %d\r\n", adcReading);
    }
        
    
    
}
#endif