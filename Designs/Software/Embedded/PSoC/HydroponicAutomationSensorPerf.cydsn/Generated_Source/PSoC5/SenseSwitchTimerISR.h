/*******************************************************************************
* File Name: SenseSwitchTimerISR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_SenseSwitchTimerISR_H)
#define CY_ISR_SenseSwitchTimerISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void SenseSwitchTimerISR_Start(void);
void SenseSwitchTimerISR_StartEx(cyisraddress address);
void SenseSwitchTimerISR_Stop(void);

CY_ISR_PROTO(SenseSwitchTimerISR_Interrupt);

void SenseSwitchTimerISR_SetVector(cyisraddress address);
cyisraddress SenseSwitchTimerISR_GetVector(void);

void SenseSwitchTimerISR_SetPriority(uint8 priority);
uint8 SenseSwitchTimerISR_GetPriority(void);

void SenseSwitchTimerISR_Enable(void);
uint8 SenseSwitchTimerISR_GetState(void);
void SenseSwitchTimerISR_Disable(void);

void SenseSwitchTimerISR_SetPending(void);
void SenseSwitchTimerISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the SenseSwitchTimerISR ISR. */
#define SenseSwitchTimerISR_INTC_VECTOR            ((reg32 *) SenseSwitchTimerISR__INTC_VECT)

/* Address of the SenseSwitchTimerISR ISR priority. */
#define SenseSwitchTimerISR_INTC_PRIOR             ((reg8 *) SenseSwitchTimerISR__INTC_PRIOR_REG)

/* Priority of the SenseSwitchTimerISR interrupt. */
#define SenseSwitchTimerISR_INTC_PRIOR_NUMBER      SenseSwitchTimerISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable SenseSwitchTimerISR interrupt. */
#define SenseSwitchTimerISR_INTC_SET_EN            ((reg32 *) SenseSwitchTimerISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the SenseSwitchTimerISR interrupt. */
#define SenseSwitchTimerISR_INTC_CLR_EN            ((reg32 *) SenseSwitchTimerISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the SenseSwitchTimerISR interrupt state to pending. */
#define SenseSwitchTimerISR_INTC_SET_PD            ((reg32 *) SenseSwitchTimerISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the SenseSwitchTimerISR interrupt. */
#define SenseSwitchTimerISR_INTC_CLR_PD            ((reg32 *) SenseSwitchTimerISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_SenseSwitchTimerISR_H */


/* [] END OF FILE */
