/*******************************************************************************
* File Name: PingSensorEchoISR.h
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
#if !defined(CY_ISR_PingSensorEchoISR_H)
#define CY_ISR_PingSensorEchoISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void PingSensorEchoISR_Start(void);
void PingSensorEchoISR_StartEx(cyisraddress address);
void PingSensorEchoISR_Stop(void);

CY_ISR_PROTO(PingSensorEchoISR_Interrupt);

void PingSensorEchoISR_SetVector(cyisraddress address);
cyisraddress PingSensorEchoISR_GetVector(void);

void PingSensorEchoISR_SetPriority(uint8 priority);
uint8 PingSensorEchoISR_GetPriority(void);

void PingSensorEchoISR_Enable(void);
uint8 PingSensorEchoISR_GetState(void);
void PingSensorEchoISR_Disable(void);

void PingSensorEchoISR_SetPending(void);
void PingSensorEchoISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the PingSensorEchoISR ISR. */
#define PingSensorEchoISR_INTC_VECTOR            ((reg32 *) PingSensorEchoISR__INTC_VECT)

/* Address of the PingSensorEchoISR ISR priority. */
#define PingSensorEchoISR_INTC_PRIOR             ((reg8 *) PingSensorEchoISR__INTC_PRIOR_REG)

/* Priority of the PingSensorEchoISR interrupt. */
#define PingSensorEchoISR_INTC_PRIOR_NUMBER      PingSensorEchoISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable PingSensorEchoISR interrupt. */
#define PingSensorEchoISR_INTC_SET_EN            ((reg32 *) PingSensorEchoISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the PingSensorEchoISR interrupt. */
#define PingSensorEchoISR_INTC_CLR_EN            ((reg32 *) PingSensorEchoISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the PingSensorEchoISR interrupt state to pending. */
#define PingSensorEchoISR_INTC_SET_PD            ((reg32 *) PingSensorEchoISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the PingSensorEchoISR interrupt. */
#define PingSensorEchoISR_INTC_CLR_PD            ((reg32 *) PingSensorEchoISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_PingSensorEchoISR_H */


/* [] END OF FILE */
