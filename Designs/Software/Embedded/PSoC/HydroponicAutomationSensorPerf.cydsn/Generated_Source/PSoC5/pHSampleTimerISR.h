/*******************************************************************************
* File Name: pHSampleTimerISR.h
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
#if !defined(CY_ISR_pHSampleTimerISR_H)
#define CY_ISR_pHSampleTimerISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void pHSampleTimerISR_Start(void);
void pHSampleTimerISR_StartEx(cyisraddress address);
void pHSampleTimerISR_Stop(void);

CY_ISR_PROTO(pHSampleTimerISR_Interrupt);

void pHSampleTimerISR_SetVector(cyisraddress address);
cyisraddress pHSampleTimerISR_GetVector(void);

void pHSampleTimerISR_SetPriority(uint8 priority);
uint8 pHSampleTimerISR_GetPriority(void);

void pHSampleTimerISR_Enable(void);
uint8 pHSampleTimerISR_GetState(void);
void pHSampleTimerISR_Disable(void);

void pHSampleTimerISR_SetPending(void);
void pHSampleTimerISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the pHSampleTimerISR ISR. */
#define pHSampleTimerISR_INTC_VECTOR            ((reg32 *) pHSampleTimerISR__INTC_VECT)

/* Address of the pHSampleTimerISR ISR priority. */
#define pHSampleTimerISR_INTC_PRIOR             ((reg8 *) pHSampleTimerISR__INTC_PRIOR_REG)

/* Priority of the pHSampleTimerISR interrupt. */
#define pHSampleTimerISR_INTC_PRIOR_NUMBER      pHSampleTimerISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable pHSampleTimerISR interrupt. */
#define pHSampleTimerISR_INTC_SET_EN            ((reg32 *) pHSampleTimerISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the pHSampleTimerISR interrupt. */
#define pHSampleTimerISR_INTC_CLR_EN            ((reg32 *) pHSampleTimerISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the pHSampleTimerISR interrupt state to pending. */
#define pHSampleTimerISR_INTC_SET_PD            ((reg32 *) pHSampleTimerISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the pHSampleTimerISR interrupt. */
#define pHSampleTimerISR_INTC_CLR_PD            ((reg32 *) pHSampleTimerISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_pHSampleTimerISR_H */


/* [] END OF FILE */
