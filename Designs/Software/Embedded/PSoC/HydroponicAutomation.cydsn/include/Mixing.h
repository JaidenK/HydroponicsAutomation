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
/* Add an explicit reference to the floating point printf library to allow
the usage of floating point conversion specifier */

#ifndef Mixing_H
#define Mixing_H
#define MIXING_DUTY_MAX 65535.0
    
#include <project.h>
#include <stdio.h>


/**
 * @function Mixing_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary mixing
 * @author Barron Wong 02/28/19
*/
void Mixing_Init();

/**
 * @function Mixing_SetDutyCycle(void)
 * @param duty cycle 0-1000
 * @return None
 * @brief Sets the duty cycle between 0-1000 with 1000 being 100%
 * @author Barron Wong 02/28/19
*/
void Mixing_SetDutyCycle(int dutyCycle);

/**
 * @function Mixing_TurnOff(void)
 * @param Nonw
 * @return None
 * @brief Turns the mixing motor off
 * @author Barron Wong 02/28/19
*/
void Mixing_TurnOff();

/**
 * @function Mixing_TurnOn(void)
 * @param Nonw
 * @return None
 * @brief Turns the mixing motor on
 * @author Barron Wong 02/28/19
*/
void Mixing_TurnOn();

#endif

/* [] END OF FILE */
