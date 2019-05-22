/*******************************************************************************
* File Name: EventCheckerISR.h
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
#if !defined(CY_ISR_EventCheckerISR_H)
#define CY_ISR_EventCheckerISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void EventCheckerISR_Start(void);
void EventCheckerISR_StartEx(cyisraddress address);
void EventCheckerISR_Stop(void);

CY_ISR_PROTO(EventCheckerISR_Interrupt);

void EventCheckerISR_SetVector(cyisraddress address);
cyisraddress EventCheckerISR_GetVector(void);

void EventCheckerISR_SetPriority(uint8 priority);
uint8 EventCheckerISR_GetPriority(void);

void EventCheckerISR_Enable(void);
uint8 EventCheckerISR_GetState(void);
void EventCheckerISR_Disable(void);

void EventCheckerISR_SetPending(void);
void EventCheckerISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the EventCheckerISR ISR. */
#define EventCheckerISR_INTC_VECTOR            ((reg32 *) EventCheckerISR__INTC_VECT)

/* Address of the EventCheckerISR ISR priority. */
#define EventCheckerISR_INTC_PRIOR             ((reg8 *) EventCheckerISR__INTC_PRIOR_REG)

/* Priority of the EventCheckerISR interrupt. */
#define EventCheckerISR_INTC_PRIOR_NUMBER      EventCheckerISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable EventCheckerISR interrupt. */
#define EventCheckerISR_INTC_SET_EN            ((reg32 *) EventCheckerISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the EventCheckerISR interrupt. */
#define EventCheckerISR_INTC_CLR_EN            ((reg32 *) EventCheckerISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the EventCheckerISR interrupt state to pending. */
#define EventCheckerISR_INTC_SET_PD            ((reg32 *) EventCheckerISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the EventCheckerISR interrupt. */
#define EventCheckerISR_INTC_CLR_PD            ((reg32 *) EventCheckerISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_EventCheckerISR_H */


/* [] END OF FILE */
