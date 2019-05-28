/*******************************************************************************
* File Name: SensorDataComISR.h
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
#if !defined(CY_ISR_SensorDataComISR_H)
#define CY_ISR_SensorDataComISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void SensorDataComISR_Start(void);
void SensorDataComISR_StartEx(cyisraddress address);
void SensorDataComISR_Stop(void);

CY_ISR_PROTO(SensorDataComISR_Interrupt);

void SensorDataComISR_SetVector(cyisraddress address);
cyisraddress SensorDataComISR_GetVector(void);

void SensorDataComISR_SetPriority(uint8 priority);
uint8 SensorDataComISR_GetPriority(void);

void SensorDataComISR_Enable(void);
uint8 SensorDataComISR_GetState(void);
void SensorDataComISR_Disable(void);

void SensorDataComISR_SetPending(void);
void SensorDataComISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the SensorDataComISR ISR. */
#define SensorDataComISR_INTC_VECTOR            ((reg32 *) SensorDataComISR__INTC_VECT)

/* Address of the SensorDataComISR ISR priority. */
#define SensorDataComISR_INTC_PRIOR             ((reg8 *) SensorDataComISR__INTC_PRIOR_REG)

/* Priority of the SensorDataComISR interrupt. */
#define SensorDataComISR_INTC_PRIOR_NUMBER      SensorDataComISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable SensorDataComISR interrupt. */
#define SensorDataComISR_INTC_SET_EN            ((reg32 *) SensorDataComISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the SensorDataComISR interrupt. */
#define SensorDataComISR_INTC_CLR_EN            ((reg32 *) SensorDataComISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the SensorDataComISR interrupt state to pending. */
#define SensorDataComISR_INTC_SET_PD            ((reg32 *) SensorDataComISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the SensorDataComISR interrupt. */
#define SensorDataComISR_INTC_CLR_PD            ((reg32 *) SensorDataComISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_SensorDataComISR_H */


/* [] END OF FILE */
