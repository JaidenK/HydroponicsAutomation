/*******************************************************************************
* File Name: DataComTxInv.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DataComTxInv_H) /* Pins DataComTxInv_H */
#define CY_PINS_DataComTxInv_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DataComTxInv_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DataComTxInv__PORT == 15 && ((DataComTxInv__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DataComTxInv_Write(uint8 value);
void    DataComTxInv_SetDriveMode(uint8 mode);
uint8   DataComTxInv_ReadDataReg(void);
uint8   DataComTxInv_Read(void);
void    DataComTxInv_SetInterruptMode(uint16 position, uint16 mode);
uint8   DataComTxInv_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DataComTxInv_SetDriveMode() function.
     *  @{
     */
        #define DataComTxInv_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DataComTxInv_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DataComTxInv_DM_RES_UP          PIN_DM_RES_UP
        #define DataComTxInv_DM_RES_DWN         PIN_DM_RES_DWN
        #define DataComTxInv_DM_OD_LO           PIN_DM_OD_LO
        #define DataComTxInv_DM_OD_HI           PIN_DM_OD_HI
        #define DataComTxInv_DM_STRONG          PIN_DM_STRONG
        #define DataComTxInv_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DataComTxInv_MASK               DataComTxInv__MASK
#define DataComTxInv_SHIFT              DataComTxInv__SHIFT
#define DataComTxInv_WIDTH              1u

/* Interrupt constants */
#if defined(DataComTxInv__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DataComTxInv_SetInterruptMode() function.
     *  @{
     */
        #define DataComTxInv_INTR_NONE      (uint16)(0x0000u)
        #define DataComTxInv_INTR_RISING    (uint16)(0x0001u)
        #define DataComTxInv_INTR_FALLING   (uint16)(0x0002u)
        #define DataComTxInv_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DataComTxInv_INTR_MASK      (0x01u) 
#endif /* (DataComTxInv__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DataComTxInv_PS                     (* (reg8 *) DataComTxInv__PS)
/* Data Register */
#define DataComTxInv_DR                     (* (reg8 *) DataComTxInv__DR)
/* Port Number */
#define DataComTxInv_PRT_NUM                (* (reg8 *) DataComTxInv__PRT) 
/* Connect to Analog Globals */                                                  
#define DataComTxInv_AG                     (* (reg8 *) DataComTxInv__AG)                       
/* Analog MUX bux enable */
#define DataComTxInv_AMUX                   (* (reg8 *) DataComTxInv__AMUX) 
/* Bidirectional Enable */                                                        
#define DataComTxInv_BIE                    (* (reg8 *) DataComTxInv__BIE)
/* Bit-mask for Aliased Register Access */
#define DataComTxInv_BIT_MASK               (* (reg8 *) DataComTxInv__BIT_MASK)
/* Bypass Enable */
#define DataComTxInv_BYP                    (* (reg8 *) DataComTxInv__BYP)
/* Port wide control signals */                                                   
#define DataComTxInv_CTL                    (* (reg8 *) DataComTxInv__CTL)
/* Drive Modes */
#define DataComTxInv_DM0                    (* (reg8 *) DataComTxInv__DM0) 
#define DataComTxInv_DM1                    (* (reg8 *) DataComTxInv__DM1)
#define DataComTxInv_DM2                    (* (reg8 *) DataComTxInv__DM2) 
/* Input Buffer Disable Override */
#define DataComTxInv_INP_DIS                (* (reg8 *) DataComTxInv__INP_DIS)
/* LCD Common or Segment Drive */
#define DataComTxInv_LCD_COM_SEG            (* (reg8 *) DataComTxInv__LCD_COM_SEG)
/* Enable Segment LCD */
#define DataComTxInv_LCD_EN                 (* (reg8 *) DataComTxInv__LCD_EN)
/* Slew Rate Control */
#define DataComTxInv_SLW                    (* (reg8 *) DataComTxInv__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DataComTxInv_PRTDSI__CAPS_SEL       (* (reg8 *) DataComTxInv__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DataComTxInv_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DataComTxInv__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DataComTxInv_PRTDSI__OE_SEL0        (* (reg8 *) DataComTxInv__PRTDSI__OE_SEL0) 
#define DataComTxInv_PRTDSI__OE_SEL1        (* (reg8 *) DataComTxInv__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DataComTxInv_PRTDSI__OUT_SEL0       (* (reg8 *) DataComTxInv__PRTDSI__OUT_SEL0) 
#define DataComTxInv_PRTDSI__OUT_SEL1       (* (reg8 *) DataComTxInv__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DataComTxInv_PRTDSI__SYNC_OUT       (* (reg8 *) DataComTxInv__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DataComTxInv__SIO_CFG)
    #define DataComTxInv_SIO_HYST_EN        (* (reg8 *) DataComTxInv__SIO_HYST_EN)
    #define DataComTxInv_SIO_REG_HIFREQ     (* (reg8 *) DataComTxInv__SIO_REG_HIFREQ)
    #define DataComTxInv_SIO_CFG            (* (reg8 *) DataComTxInv__SIO_CFG)
    #define DataComTxInv_SIO_DIFF           (* (reg8 *) DataComTxInv__SIO_DIFF)
#endif /* (DataComTxInv__SIO_CFG) */

/* Interrupt Registers */
#if defined(DataComTxInv__INTSTAT)
    #define DataComTxInv_INTSTAT            (* (reg8 *) DataComTxInv__INTSTAT)
    #define DataComTxInv_SNAP               (* (reg8 *) DataComTxInv__SNAP)
    
	#define DataComTxInv_0_INTTYPE_REG 		(* (reg8 *) DataComTxInv__0__INTTYPE)
#endif /* (DataComTxInv__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DataComTxInv_H */


/* [] END OF FILE */
