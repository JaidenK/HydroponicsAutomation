/*******************************************************************************
* File Name: pHTSampleTimerISR.h
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
#if !defined(CY_ISR_pHTSampleTimerISR_H)
#define CY_ISR_pHTSampleTimerISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void pHTSampleTimerISR_Start(void);
void pHTSampleTimerISR_StartEx(cyisraddress address);
void pHTSampleTimerISR_Stop(void);

CY_ISR_PROTO(pHTSampleTimerISR_Interrupt);

void pHTSampleTimerISR_SetVector(cyisraddress address);
cyisraddress pHTSampleTimerISR_GetVector(void);

void pHTSampleTimerISR_SetPriority(uint8 priority);
uint8 pHTSampleTimerISR_GetPriority(void);

void pHTSampleTimerISR_Enable(void);
uint8 pHTSampleTimerISR_GetState(void);
void pHTSampleTimerISR_Disable(void);

void pHTSampleTimerISR_SetPending(void);
void pHTSampleTimerISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the pHTSampleTimerISR ISR. */
#define pHTSampleTimerISR_INTC_VECTOR            ((reg32 *) pHTSampleTimerISR__INTC_VECT)

/* Address of the pHTSampleTimerISR ISR priority. */
#define pHTSampleTimerISR_INTC_PRIOR             ((reg8 *) pHTSampleTimerISR__INTC_PRIOR_REG)

/* Priority of the pHTSampleTimerISR interrupt. */
#define pHTSampleTimerISR_INTC_PRIOR_NUMBER      pHTSampleTimerISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable pHTSampleTimerISR interrupt. */
#define pHTSampleTimerISR_INTC_SET_EN            ((reg32 *) pHTSampleTimerISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the pHTSampleTimerISR interrupt. */
#define pHTSampleTimerISR_INTC_CLR_EN            ((reg32 *) pHTSampleTimerISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the pHTSampleTimerISR interrupt state to pending. */
#define pHTSampleTimerISR_INTC_SET_PD            ((reg32 *) pHTSampleTimerISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the pHTSampleTimerISR interrupt. */
#define pHTSampleTimerISR_INTC_CLR_PD            ((reg32 *) pHTSampleTimerISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_pHTSampleTimerISR_H */


/* [] END OF FILE */
