/*******************************************************************************
* File Name: FlowSenseTimerISR.h
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
#if !defined(CY_ISR_FlowSenseTimerISR_H)
#define CY_ISR_FlowSenseTimerISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void FlowSenseTimerISR_Start(void);
void FlowSenseTimerISR_StartEx(cyisraddress address);
void FlowSenseTimerISR_Stop(void);

CY_ISR_PROTO(FlowSenseTimerISR_Interrupt);

void FlowSenseTimerISR_SetVector(cyisraddress address);
cyisraddress FlowSenseTimerISR_GetVector(void);

void FlowSenseTimerISR_SetPriority(uint8 priority);
uint8 FlowSenseTimerISR_GetPriority(void);

void FlowSenseTimerISR_Enable(void);
uint8 FlowSenseTimerISR_GetState(void);
void FlowSenseTimerISR_Disable(void);

void FlowSenseTimerISR_SetPending(void);
void FlowSenseTimerISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the FlowSenseTimerISR ISR. */
#define FlowSenseTimerISR_INTC_VECTOR            ((reg32 *) FlowSenseTimerISR__INTC_VECT)

/* Address of the FlowSenseTimerISR ISR priority. */
#define FlowSenseTimerISR_INTC_PRIOR             ((reg8 *) FlowSenseTimerISR__INTC_PRIOR_REG)

/* Priority of the FlowSenseTimerISR interrupt. */
#define FlowSenseTimerISR_INTC_PRIOR_NUMBER      FlowSenseTimerISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable FlowSenseTimerISR interrupt. */
#define FlowSenseTimerISR_INTC_SET_EN            ((reg32 *) FlowSenseTimerISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the FlowSenseTimerISR interrupt. */
#define FlowSenseTimerISR_INTC_CLR_EN            ((reg32 *) FlowSenseTimerISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the FlowSenseTimerISR interrupt state to pending. */
#define FlowSenseTimerISR_INTC_SET_PD            ((reg32 *) FlowSenseTimerISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the FlowSenseTimerISR interrupt. */
#define FlowSenseTimerISR_INTC_CLR_PD            ((reg32 *) FlowSenseTimerISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_FlowSenseTimerISR_H */


/* [] END OF FILE */
