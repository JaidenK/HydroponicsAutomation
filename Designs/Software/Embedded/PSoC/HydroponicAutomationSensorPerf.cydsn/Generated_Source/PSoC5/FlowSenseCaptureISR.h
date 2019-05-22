/*******************************************************************************
* File Name: FlowSenseCaptureISR.h
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
#if !defined(CY_ISR_FlowSenseCaptureISR_H)
#define CY_ISR_FlowSenseCaptureISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void FlowSenseCaptureISR_Start(void);
void FlowSenseCaptureISR_StartEx(cyisraddress address);
void FlowSenseCaptureISR_Stop(void);

CY_ISR_PROTO(FlowSenseCaptureISR_Interrupt);

void FlowSenseCaptureISR_SetVector(cyisraddress address);
cyisraddress FlowSenseCaptureISR_GetVector(void);

void FlowSenseCaptureISR_SetPriority(uint8 priority);
uint8 FlowSenseCaptureISR_GetPriority(void);

void FlowSenseCaptureISR_Enable(void);
uint8 FlowSenseCaptureISR_GetState(void);
void FlowSenseCaptureISR_Disable(void);

void FlowSenseCaptureISR_SetPending(void);
void FlowSenseCaptureISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the FlowSenseCaptureISR ISR. */
#define FlowSenseCaptureISR_INTC_VECTOR            ((reg32 *) FlowSenseCaptureISR__INTC_VECT)

/* Address of the FlowSenseCaptureISR ISR priority. */
#define FlowSenseCaptureISR_INTC_PRIOR             ((reg8 *) FlowSenseCaptureISR__INTC_PRIOR_REG)

/* Priority of the FlowSenseCaptureISR interrupt. */
#define FlowSenseCaptureISR_INTC_PRIOR_NUMBER      FlowSenseCaptureISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable FlowSenseCaptureISR interrupt. */
#define FlowSenseCaptureISR_INTC_SET_EN            ((reg32 *) FlowSenseCaptureISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the FlowSenseCaptureISR interrupt. */
#define FlowSenseCaptureISR_INTC_CLR_EN            ((reg32 *) FlowSenseCaptureISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the FlowSenseCaptureISR interrupt state to pending. */
#define FlowSenseCaptureISR_INTC_SET_PD            ((reg32 *) FlowSenseCaptureISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the FlowSenseCaptureISR interrupt. */
#define FlowSenseCaptureISR_INTC_CLR_PD            ((reg32 *) FlowSenseCaptureISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_FlowSenseCaptureISR_H */


/* [] END OF FILE */
