/*******************************************************************************
* File Name: ECSenseRxInv.h  
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

#if !defined(CY_PINS_ECSenseRxInv_H) /* Pins ECSenseRxInv_H */
#define CY_PINS_ECSenseRxInv_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ECSenseRxInv_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ECSenseRxInv__PORT == 15 && ((ECSenseRxInv__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ECSenseRxInv_Write(uint8 value);
void    ECSenseRxInv_SetDriveMode(uint8 mode);
uint8   ECSenseRxInv_ReadDataReg(void);
uint8   ECSenseRxInv_Read(void);
void    ECSenseRxInv_SetInterruptMode(uint16 position, uint16 mode);
uint8   ECSenseRxInv_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ECSenseRxInv_SetDriveMode() function.
     *  @{
     */
        #define ECSenseRxInv_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ECSenseRxInv_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ECSenseRxInv_DM_RES_UP          PIN_DM_RES_UP
        #define ECSenseRxInv_DM_RES_DWN         PIN_DM_RES_DWN
        #define ECSenseRxInv_DM_OD_LO           PIN_DM_OD_LO
        #define ECSenseRxInv_DM_OD_HI           PIN_DM_OD_HI
        #define ECSenseRxInv_DM_STRONG          PIN_DM_STRONG
        #define ECSenseRxInv_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ECSenseRxInv_MASK               ECSenseRxInv__MASK
#define ECSenseRxInv_SHIFT              ECSenseRxInv__SHIFT
#define ECSenseRxInv_WIDTH              1u

/* Interrupt constants */
#if defined(ECSenseRxInv__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ECSenseRxInv_SetInterruptMode() function.
     *  @{
     */
        #define ECSenseRxInv_INTR_NONE      (uint16)(0x0000u)
        #define ECSenseRxInv_INTR_RISING    (uint16)(0x0001u)
        #define ECSenseRxInv_INTR_FALLING   (uint16)(0x0002u)
        #define ECSenseRxInv_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ECSenseRxInv_INTR_MASK      (0x01u) 
#endif /* (ECSenseRxInv__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ECSenseRxInv_PS                     (* (reg8 *) ECSenseRxInv__PS)
/* Data Register */
#define ECSenseRxInv_DR                     (* (reg8 *) ECSenseRxInv__DR)
/* Port Number */
#define ECSenseRxInv_PRT_NUM                (* (reg8 *) ECSenseRxInv__PRT) 
/* Connect to Analog Globals */                                                  
#define ECSenseRxInv_AG                     (* (reg8 *) ECSenseRxInv__AG)                       
/* Analog MUX bux enable */
#define ECSenseRxInv_AMUX                   (* (reg8 *) ECSenseRxInv__AMUX) 
/* Bidirectional Enable */                                                        
#define ECSenseRxInv_BIE                    (* (reg8 *) ECSenseRxInv__BIE)
/* Bit-mask for Aliased Register Access */
#define ECSenseRxInv_BIT_MASK               (* (reg8 *) ECSenseRxInv__BIT_MASK)
/* Bypass Enable */
#define ECSenseRxInv_BYP                    (* (reg8 *) ECSenseRxInv__BYP)
/* Port wide control signals */                                                   
#define ECSenseRxInv_CTL                    (* (reg8 *) ECSenseRxInv__CTL)
/* Drive Modes */
#define ECSenseRxInv_DM0                    (* (reg8 *) ECSenseRxInv__DM0) 
#define ECSenseRxInv_DM1                    (* (reg8 *) ECSenseRxInv__DM1)
#define ECSenseRxInv_DM2                    (* (reg8 *) ECSenseRxInv__DM2) 
/* Input Buffer Disable Override */
#define ECSenseRxInv_INP_DIS                (* (reg8 *) ECSenseRxInv__INP_DIS)
/* LCD Common or Segment Drive */
#define ECSenseRxInv_LCD_COM_SEG            (* (reg8 *) ECSenseRxInv__LCD_COM_SEG)
/* Enable Segment LCD */
#define ECSenseRxInv_LCD_EN                 (* (reg8 *) ECSenseRxInv__LCD_EN)
/* Slew Rate Control */
#define ECSenseRxInv_SLW                    (* (reg8 *) ECSenseRxInv__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ECSenseRxInv_PRTDSI__CAPS_SEL       (* (reg8 *) ECSenseRxInv__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ECSenseRxInv_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ECSenseRxInv__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ECSenseRxInv_PRTDSI__OE_SEL0        (* (reg8 *) ECSenseRxInv__PRTDSI__OE_SEL0) 
#define ECSenseRxInv_PRTDSI__OE_SEL1        (* (reg8 *) ECSenseRxInv__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ECSenseRxInv_PRTDSI__OUT_SEL0       (* (reg8 *) ECSenseRxInv__PRTDSI__OUT_SEL0) 
#define ECSenseRxInv_PRTDSI__OUT_SEL1       (* (reg8 *) ECSenseRxInv__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ECSenseRxInv_PRTDSI__SYNC_OUT       (* (reg8 *) ECSenseRxInv__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ECSenseRxInv__SIO_CFG)
    #define ECSenseRxInv_SIO_HYST_EN        (* (reg8 *) ECSenseRxInv__SIO_HYST_EN)
    #define ECSenseRxInv_SIO_REG_HIFREQ     (* (reg8 *) ECSenseRxInv__SIO_REG_HIFREQ)
    #define ECSenseRxInv_SIO_CFG            (* (reg8 *) ECSenseRxInv__SIO_CFG)
    #define ECSenseRxInv_SIO_DIFF           (* (reg8 *) ECSenseRxInv__SIO_DIFF)
#endif /* (ECSenseRxInv__SIO_CFG) */

/* Interrupt Registers */
#if defined(ECSenseRxInv__INTSTAT)
    #define ECSenseRxInv_INTSTAT            (* (reg8 *) ECSenseRxInv__INTSTAT)
    #define ECSenseRxInv_SNAP               (* (reg8 *) ECSenseRxInv__SNAP)
    
	#define ECSenseRxInv_0_INTTYPE_REG 		(* (reg8 *) ECSenseRxInv__0__INTTYPE)
#endif /* (ECSenseRxInv__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ECSenseRxInv_H */


/* [] END OF FILE */
