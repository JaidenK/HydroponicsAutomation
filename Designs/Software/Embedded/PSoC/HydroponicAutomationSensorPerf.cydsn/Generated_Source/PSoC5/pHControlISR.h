/*******************************************************************************
* File Name: pHControlISR.h
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
#if !defined(CY_ISR_pHControlISR_H)
#define CY_ISR_pHControlISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void pHControlISR_Start(void);
void pHControlISR_StartEx(cyisraddress address);
void pHControlISR_Stop(void);

CY_ISR_PROTO(pHControlISR_Interrupt);

void pHControlISR_SetVector(cyisraddress address);
cyisraddress pHControlISR_GetVector(void);

void pHControlISR_SetPriority(uint8 priority);
uint8 pHControlISR_GetPriority(void);

void pHControlISR_Enable(void);
uint8 pHControlISR_GetState(void);
void pHControlISR_Disable(void);

void pHControlISR_SetPending(void);
void pHControlISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the pHControlISR ISR. */
#define pHControlISR_INTC_VECTOR            ((reg32 *) pHControlISR__INTC_VECT)

/* Address of the pHControlISR ISR priority. */
#define pHControlISR_INTC_PRIOR             ((reg8 *) pHControlISR__INTC_PRIOR_REG)

/* Priority of the pHControlISR interrupt. */
#define pHControlISR_INTC_PRIOR_NUMBER      pHControlISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable pHControlISR interrupt. */
#define pHControlISR_INTC_SET_EN            ((reg32 *) pHControlISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the pHControlISR interrupt. */
#define pHControlISR_INTC_CLR_EN            ((reg32 *) pHControlISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the pHControlISR interrupt state to pending. */
#define pHControlISR_INTC_SET_PD            ((reg32 *) pHControlISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the pHControlISR interrupt. */
#define pHControlISR_INTC_CLR_PD            ((reg32 *) pHControlISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_pHControlISR_H */


/* [] END OF FILE */
