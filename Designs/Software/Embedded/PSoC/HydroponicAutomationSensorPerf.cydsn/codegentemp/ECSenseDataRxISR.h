/*******************************************************************************
* File Name: ECSenseDataRxISR.h
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
#if !defined(CY_ISR_ECSenseDataRxISR_H)
#define CY_ISR_ECSenseDataRxISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ECSenseDataRxISR_Start(void);
void ECSenseDataRxISR_StartEx(cyisraddress address);
void ECSenseDataRxISR_Stop(void);

CY_ISR_PROTO(ECSenseDataRxISR_Interrupt);

void ECSenseDataRxISR_SetVector(cyisraddress address);
cyisraddress ECSenseDataRxISR_GetVector(void);

void ECSenseDataRxISR_SetPriority(uint8 priority);
uint8 ECSenseDataRxISR_GetPriority(void);

void ECSenseDataRxISR_Enable(void);
uint8 ECSenseDataRxISR_GetState(void);
void ECSenseDataRxISR_Disable(void);

void ECSenseDataRxISR_SetPending(void);
void ECSenseDataRxISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ECSenseDataRxISR ISR. */
#define ECSenseDataRxISR_INTC_VECTOR            ((reg32 *) ECSenseDataRxISR__INTC_VECT)

/* Address of the ECSenseDataRxISR ISR priority. */
#define ECSenseDataRxISR_INTC_PRIOR             ((reg8 *) ECSenseDataRxISR__INTC_PRIOR_REG)

/* Priority of the ECSenseDataRxISR interrupt. */
#define ECSenseDataRxISR_INTC_PRIOR_NUMBER      ECSenseDataRxISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ECSenseDataRxISR interrupt. */
#define ECSenseDataRxISR_INTC_SET_EN            ((reg32 *) ECSenseDataRxISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ECSenseDataRxISR interrupt. */
#define ECSenseDataRxISR_INTC_CLR_EN            ((reg32 *) ECSenseDataRxISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ECSenseDataRxISR interrupt state to pending. */
#define ECSenseDataRxISR_INTC_SET_PD            ((reg32 *) ECSenseDataRxISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ECSenseDataRxISR interrupt. */
#define ECSenseDataRxISR_INTC_CLR_PD            ((reg32 *) ECSenseDataRxISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_ECSenseDataRxISR_H */


/* [] END OF FILE */
