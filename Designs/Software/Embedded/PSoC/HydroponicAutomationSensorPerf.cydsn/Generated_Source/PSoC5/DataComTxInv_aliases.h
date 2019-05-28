/*******************************************************************************
* File Name: DataComTxInv.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DataComTxInv_ALIASES_H) /* Pins DataComTxInv_ALIASES_H */
#define CY_PINS_DataComTxInv_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define DataComTxInv_0			(DataComTxInv__0__PC)
#define DataComTxInv_0_INTR	((uint16)((uint16)0x0001u << DataComTxInv__0__SHIFT))

#define DataComTxInv_INTR_ALL	 ((uint16)(DataComTxInv_0_INTR))

#endif /* End Pins DataComTxInv_ALIASES_H */


/* [] END OF FILE */
