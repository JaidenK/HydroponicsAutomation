/*******************************************************************************
* File Name: SampleTimerISR.h
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
#if !defined(CY_ISR_SampleTimerISR_H)
#define CY_ISR_SampleTimerISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void SampleTimerISR_Start(void);
void SampleTimerISR_StartEx(cyisraddress address);
void SampleTimerISR_Stop(void);

CY_ISR_PROTO(SampleTimerISR_Interrupt);

void SampleTimerISR_SetVector(cyisraddress address);
cyisraddress SampleTimerISR_GetVector(void);

void SampleTimerISR_SetPriority(uint8 priority);
uint8 SampleTimerISR_GetPriority(void);

void SampleTimerISR_Enable(void);
uint8 SampleTimerISR_GetState(void);
void SampleTimerISR_Disable(void);

void SampleTimerISR_SetPending(void);
void SampleTimerISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the SampleTimerISR ISR. */
#define SampleTimerISR_INTC_VECTOR            ((reg32 *) SampleTimerISR__INTC_VECT)

/* Address of the SampleTimerISR ISR priority. */
#define SampleTimerISR_INTC_PRIOR             ((reg8 *) SampleTimerISR__INTC_PRIOR_REG)

/* Priority of the SampleTimerISR interrupt. */
#define SampleTimerISR_INTC_PRIOR_NUMBER      SampleTimerISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable SampleTimerISR interrupt. */
#define SampleTimerISR_INTC_SET_EN            ((reg32 *) SampleTimerISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the SampleTimerISR interrupt. */
#define SampleTimerISR_INTC_CLR_EN            ((reg32 *) SampleTimerISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the SampleTimerISR interrupt state to pending. */
#define SampleTimerISR_INTC_SET_PD            ((reg32 *) SampleTimerISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the SampleTimerISR interrupt. */
#define SampleTimerISR_INTC_CLR_PD            ((reg32 *) SampleTimerISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_SampleTimerISR_H */


/* [] END OF FILE */
