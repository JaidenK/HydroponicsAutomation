/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "AD.h"
/* [] END OF FILE */
/**
 * @function AD_Init(void)
 * @param None
 * @return None
 * @brief Initliazes AD pin for general use.
 * @author Barron Wong 01/25/19
 */
void AD_Init(void){
    PotADC_Start();
}

/**
 * @function GetADCValue(void)
 * @param None
 * @return None
 * @brief Returns the ADC reading on the analog pin from 0-4096.
 * @author Barron Wong 01/25/19
 */
uint16_t AD_GetADCValue(){
    uint16_t adc_val;
    
    adc_val = PotADC_Read32();
    
    if(adc_val > AD_MAX + 200)
        return 0;
    
    if(adc_val > AD_MAX)
        return AD_MAX;
    
    return adc_val;
}

#ifdef AD_TEST
#define MODULE_TEST
/*
    Test Harness for checking FlowController Library.
    The test should enable an analog value on pin 0.1.
    This value will be used to set the pwm speed on
    the water pump. The flow rate should also default to 
    4.347.
    
*/
#include "AD.h"
#include "SerialCom.h"
#include <stdio.h>
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    SerialCom_Init();
    AD_Init();
    
    printf("Hydroponic Automation\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        
        printf("%d\r\n", AD_GetADCValue());

    }
    
}
#endif