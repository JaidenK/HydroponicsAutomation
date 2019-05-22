/*******************************************************************************
* File Name: PingSensorTrigISR.h
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
#if !defined(CY_ISR_PingSensorTrigISR_H)
#define CY_ISR_PingSensorTrigISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void PingSensorTrigISR_Start(void);
void PingSensorTrigISR_StartEx(cyisraddress address);
void PingSensorTrigISR_Stop(void);

CY_ISR_PROTO(PingSensorTrigISR_Interrupt);

void PingSensorTrigISR_SetVector(cyisraddress address);
cyisraddress PingSensorTrigISR_GetVector(void);

void PingSensorTrigISR_SetPriority(uint8 priority);
uint8 PingSensorTrigISR_GetPriority(void);

void PingSensorTrigISR_Enable(void);
uint8 PingSensorTrigISR_GetState(void);
void PingSensorTrigISR_Disable(void);

void PingSensorTrigISR_SetPending(void);
void PingSensorTrigISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the PingSensorTrigISR ISR. */
#define PingSensorTrigISR_INTC_VECTOR            ((reg32 *) PingSensorTrigISR__INTC_VECT)

/* Address of the PingSensorTrigISR ISR priority. */
#define PingSensorTrigISR_INTC_PRIOR             ((reg8 *) PingSensorTrigISR__INTC_PRIOR_REG)

/* Priority of the PingSensorTrigISR interrupt. */
#define PingSensorTrigISR_INTC_PRIOR_NUMBER      PingSensorTrigISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable PingSensorTrigISR interrupt. */
#define PingSensorTrigISR_INTC_SET_EN            ((reg32 *) PingSensorTrigISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the PingSensorTrigISR interrupt. */
#define PingSensorTrigISR_INTC_CLR_EN            ((reg32 *) PingSensorTrigISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the PingSensorTrigISR interrupt state to pending. */
#define PingSensorTrigISR_INTC_SET_PD            ((reg32 *) PingSensorTrigISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the PingSensorTrigISR interrupt. */
#define PingSensorTrigISR_INTC_CLR_PD            ((reg32 *) PingSensorTrigISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_PingSensorTrigISR_H */


/* [] END OF FILE */
