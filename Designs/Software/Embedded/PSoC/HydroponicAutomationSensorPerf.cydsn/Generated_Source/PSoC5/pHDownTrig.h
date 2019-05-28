/*******************************************************************************
* File Name: pHDownTrig.h  
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

#if !defined(CY_PINS_pHDownTrig_H) /* Pins pHDownTrig_H */
#define CY_PINS_pHDownTrig_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pHDownTrig_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pHDownTrig__PORT == 15 && ((pHDownTrig__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pHDownTrig_Write(uint8 value);
void    pHDownTrig_SetDriveMode(uint8 mode);
uint8   pHDownTrig_ReadDataReg(void);
uint8   pHDownTrig_Read(void);
void    pHDownTrig_SetInterruptMode(uint16 position, uint16 mode);
uint8   pHDownTrig_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pHDownTrig_SetDriveMode() function.
     *  @{
     */
        #define pHDownTrig_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pHDownTrig_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pHDownTrig_DM_RES_UP          PIN_DM_RES_UP
        #define pHDownTrig_DM_RES_DWN         PIN_DM_RES_DWN
        #define pHDownTrig_DM_OD_LO           PIN_DM_OD_LO
        #define pHDownTrig_DM_OD_HI           PIN_DM_OD_HI
        #define pHDownTrig_DM_STRONG          PIN_DM_STRONG
        #define pHDownTrig_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pHDownTrig_MASK               pHDownTrig__MASK
#define pHDownTrig_SHIFT              pHDownTrig__SHIFT
#define pHDownTrig_WIDTH              1u

/* Interrupt constants */
#if defined(pHDownTrig__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pHDownTrig_SetInterruptMode() function.
     *  @{
     */
        #define pHDownTrig_INTR_NONE      (uint16)(0x0000u)
        #define pHDownTrig_INTR_RISING    (uint16)(0x0001u)
        #define pHDownTrig_INTR_FALLING   (uint16)(0x0002u)
        #define pHDownTrig_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pHDownTrig_INTR_MASK      (0x01u) 
#endif /* (pHDownTrig__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pHDownTrig_PS                     (* (reg8 *) pHDownTrig__PS)
/* Data Register */
#define pHDownTrig_DR                     (* (reg8 *) pHDownTrig__DR)
/* Port Number */
#define pHDownTrig_PRT_NUM                (* (reg8 *) pHDownTrig__PRT) 
/* Connect to Analog Globals */                                                  
#define pHDownTrig_AG                     (* (reg8 *) pHDownTrig__AG)                       
/* Analog MUX bux enable */
#define pHDownTrig_AMUX                   (* (reg8 *) pHDownTrig__AMUX) 
/* Bidirectional Enable */                                                        
#define pHDownTrig_BIE                    (* (reg8 *) pHDownTrig__BIE)
/* Bit-mask for Aliased Register Access */
#define pHDownTrig_BIT_MASK               (* (reg8 *) pHDownTrig__BIT_MASK)
/* Bypass Enable */
#define pHDownTrig_BYP                    (* (reg8 *) pHDownTrig__BYP)
/* Port wide control signals */                                                   
#define pHDownTrig_CTL                    (* (reg8 *) pHDownTrig__CTL)
/* Drive Modes */
#define pHDownTrig_DM0                    (* (reg8 *) pHDownTrig__DM0) 
#define pHDownTrig_DM1                    (* (reg8 *) pHDownTrig__DM1)
#define pHDownTrig_DM2                    (* (reg8 *) pHDownTrig__DM2) 
/* Input Buffer Disable Override */
#define pHDownTrig_INP_DIS                (* (reg8 *) pHDownTrig__INP_DIS)
/* LCD Common or Segment Drive */
#define pHDownTrig_LCD_COM_SEG            (* (reg8 *) pHDownTrig__LCD_COM_SEG)
/* Enable Segment LCD */
#define pHDownTrig_LCD_EN                 (* (reg8 *) pHDownTrig__LCD_EN)
/* Slew Rate Control */
#define pHDownTrig_SLW                    (* (reg8 *) pHDownTrig__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pHDownTrig_PRTDSI__CAPS_SEL       (* (reg8 *) pHDownTrig__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pHDownTrig_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pHDownTrig__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pHDownTrig_PRTDSI__OE_SEL0        (* (reg8 *) pHDownTrig__PRTDSI__OE_SEL0) 
#define pHDownTrig_PRTDSI__OE_SEL1        (* (reg8 *) pHDownTrig__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pHDownTrig_PRTDSI__OUT_SEL0       (* (reg8 *) pHDownTrig__PRTDSI__OUT_SEL0) 
#define pHDownTrig_PRTDSI__OUT_SEL1       (* (reg8 *) pHDownTrig__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pHDownTrig_PRTDSI__SYNC_OUT       (* (reg8 *) pHDownTrig__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pHDownTrig__SIO_CFG)
    #define pHDownTrig_SIO_HYST_EN        (* (reg8 *) pHDownTrig__SIO_HYST_EN)
    #define pHDownTrig_SIO_REG_HIFREQ     (* (reg8 *) pHDownTrig__SIO_REG_HIFREQ)
    #define pHDownTrig_SIO_CFG            (* (reg8 *) pHDownTrig__SIO_CFG)
    #define pHDownTrig_SIO_DIFF           (* (reg8 *) pHDownTrig__SIO_DIFF)
#endif /* (pHDownTrig__SIO_CFG) */

/* Interrupt Registers */
#if defined(pHDownTrig__INTSTAT)
    #define pHDownTrig_INTSTAT            (* (reg8 *) pHDownTrig__INTSTAT)
    #define pHDownTrig_SNAP               (* (reg8 *) pHDownTrig__SNAP)
    
	#define pHDownTrig_0_INTTYPE_REG 		(* (reg8 *) pHDownTrig__0__INTTYPE)
#endif /* (pHDownTrig__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pHDownTrig_H */


/* [] END OF FILE */
