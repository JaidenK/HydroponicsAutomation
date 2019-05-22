/*******************************************************************************
* File Name: FlowSenseTimeOutISR.h
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
#if !defined(CY_ISR_FlowSenseTimeOutISR_H)
#define CY_ISR_FlowSenseTimeOutISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void FlowSenseTimeOutISR_Start(void);
void FlowSenseTimeOutISR_StartEx(cyisraddress address);
void FlowSenseTimeOutISR_Stop(void);

CY_ISR_PROTO(FlowSenseTimeOutISR_Interrupt);

void FlowSenseTimeOutISR_SetVector(cyisraddress address);
cyisraddress FlowSenseTimeOutISR_GetVector(void);

void FlowSenseTimeOutISR_SetPriority(uint8 priority);
uint8 FlowSenseTimeOutISR_GetPriority(void);

void FlowSenseTimeOutISR_Enable(void);
uint8 FlowSenseTimeOutISR_GetState(void);
void FlowSenseTimeOutISR_Disable(void);

void FlowSenseTimeOutISR_SetPending(void);
void FlowSenseTimeOutISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the FlowSenseTimeOutISR ISR. */
#define FlowSenseTimeOutISR_INTC_VECTOR            ((reg32 *) FlowSenseTimeOutISR__INTC_VECT)

/* Address of the FlowSenseTimeOutISR ISR priority. */
#define FlowSenseTimeOutISR_INTC_PRIOR             ((reg8 *) FlowSenseTimeOutISR__INTC_PRIOR_REG)

/* Priority of the FlowSenseTimeOutISR interrupt. */
#define FlowSenseTimeOutISR_INTC_PRIOR_NUMBER      FlowSenseTimeOutISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable FlowSenseTimeOutISR interrupt. */
#define FlowSenseTimeOutISR_INTC_SET_EN            ((reg32 *) FlowSenseTimeOutISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the FlowSenseTimeOutISR interrupt. */
#define FlowSenseTimeOutISR_INTC_CLR_EN            ((reg32 *) FlowSenseTimeOutISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the FlowSenseTimeOutISR interrupt state to pending. */
#define FlowSenseTimeOutISR_INTC_SET_PD            ((reg32 *) FlowSenseTimeOutISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the FlowSenseTimeOutISR interrupt. */
#define FlowSenseTimeOutISR_INTC_CLR_PD            ((reg32 *) FlowSenseTimeOutISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_FlowSenseTimeOutISR_H */


/* [] END OF FILE */
