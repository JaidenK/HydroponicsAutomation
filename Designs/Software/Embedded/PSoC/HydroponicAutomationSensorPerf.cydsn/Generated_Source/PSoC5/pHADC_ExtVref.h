/*******************************************************************************
* File Name: pHADC_ExtVref.h  
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

#if !defined(CY_PINS_pHADC_ExtVref_H) /* Pins pHADC_ExtVref_H */
#define CY_PINS_pHADC_ExtVref_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pHADC_ExtVref_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pHADC_ExtVref__PORT == 15 && ((pHADC_ExtVref__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pHADC_ExtVref_Write(uint8 value);
void    pHADC_ExtVref_SetDriveMode(uint8 mode);
uint8   pHADC_ExtVref_ReadDataReg(void);
uint8   pHADC_ExtVref_Read(void);
void    pHADC_ExtVref_SetInterruptMode(uint16 position, uint16 mode);
uint8   pHADC_ExtVref_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pHADC_ExtVref_SetDriveMode() function.
     *  @{
     */
        #define pHADC_ExtVref_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pHADC_ExtVref_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pHADC_ExtVref_DM_RES_UP          PIN_DM_RES_UP
        #define pHADC_ExtVref_DM_RES_DWN         PIN_DM_RES_DWN
        #define pHADC_ExtVref_DM_OD_LO           PIN_DM_OD_LO
        #define pHADC_ExtVref_DM_OD_HI           PIN_DM_OD_HI
        #define pHADC_ExtVref_DM_STRONG          PIN_DM_STRONG
        #define pHADC_ExtVref_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pHADC_ExtVref_MASK               pHADC_ExtVref__MASK
#define pHADC_ExtVref_SHIFT              pHADC_ExtVref__SHIFT
#define pHADC_ExtVref_WIDTH              1u

/* Interrupt constants */
#if defined(pHADC_ExtVref__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pHADC_ExtVref_SetInterruptMode() function.
     *  @{
     */
        #define pHADC_ExtVref_INTR_NONE      (uint16)(0x0000u)
        #define pHADC_ExtVref_INTR_RISING    (uint16)(0x0001u)
        #define pHADC_ExtVref_INTR_FALLING   (uint16)(0x0002u)
        #define pHADC_ExtVref_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pHADC_ExtVref_INTR_MASK      (0x01u) 
#endif /* (pHADC_ExtVref__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pHADC_ExtVref_PS                     (* (reg8 *) pHADC_ExtVref__PS)
/* Data Register */
#define pHADC_ExtVref_DR                     (* (reg8 *) pHADC_ExtVref__DR)
/* Port Number */
#define pHADC_ExtVref_PRT_NUM                (* (reg8 *) pHADC_ExtVref__PRT) 
/* Connect to Analog Globals */                                                  
#define pHADC_ExtVref_AG                     (* (reg8 *) pHADC_ExtVref__AG)                       
/* Analog MUX bux enable */
#define pHADC_ExtVref_AMUX                   (* (reg8 *) pHADC_ExtVref__AMUX) 
/* Bidirectional Enable */                                                        
#define pHADC_ExtVref_BIE                    (* (reg8 *) pHADC_ExtVref__BIE)
/* Bit-mask for Aliased Register Access */
#define pHADC_ExtVref_BIT_MASK               (* (reg8 *) pHADC_ExtVref__BIT_MASK)
/* Bypass Enable */
#define pHADC_ExtVref_BYP                    (* (reg8 *) pHADC_ExtVref__BYP)
/* Port wide control signals */                                                   
#define pHADC_ExtVref_CTL                    (* (reg8 *) pHADC_ExtVref__CTL)
/* Drive Modes */
#define pHADC_ExtVref_DM0                    (* (reg8 *) pHADC_ExtVref__DM0) 
#define pHADC_ExtVref_DM1                    (* (reg8 *) pHADC_ExtVref__DM1)
#define pHADC_ExtVref_DM2                    (* (reg8 *) pHADC_ExtVref__DM2) 
/* Input Buffer Disable Override */
#define pHADC_ExtVref_INP_DIS                (* (reg8 *) pHADC_ExtVref__INP_DIS)
/* LCD Common or Segment Drive */
#define pHADC_ExtVref_LCD_COM_SEG            (* (reg8 *) pHADC_ExtVref__LCD_COM_SEG)
/* Enable Segment LCD */
#define pHADC_ExtVref_LCD_EN                 (* (reg8 *) pHADC_ExtVref__LCD_EN)
/* Slew Rate Control */
#define pHADC_ExtVref_SLW                    (* (reg8 *) pHADC_ExtVref__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pHADC_ExtVref_PRTDSI__CAPS_SEL       (* (reg8 *) pHADC_ExtVref__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pHADC_ExtVref_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pHADC_ExtVref__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pHADC_ExtVref_PRTDSI__OE_SEL0        (* (reg8 *) pHADC_ExtVref__PRTDSI__OE_SEL0) 
#define pHADC_ExtVref_PRTDSI__OE_SEL1        (* (reg8 *) pHADC_ExtVref__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pHADC_ExtVref_PRTDSI__OUT_SEL0       (* (reg8 *) pHADC_ExtVref__PRTDSI__OUT_SEL0) 
#define pHADC_ExtVref_PRTDSI__OUT_SEL1       (* (reg8 *) pHADC_ExtVref__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pHADC_ExtVref_PRTDSI__SYNC_OUT       (* (reg8 *) pHADC_ExtVref__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pHADC_ExtVref__SIO_CFG)
    #define pHADC_ExtVref_SIO_HYST_EN        (* (reg8 *) pHADC_ExtVref__SIO_HYST_EN)
    #define pHADC_ExtVref_SIO_REG_HIFREQ     (* (reg8 *) pHADC_ExtVref__SIO_REG_HIFREQ)
    #define pHADC_ExtVref_SIO_CFG            (* (reg8 *) pHADC_ExtVref__SIO_CFG)
    #define pHADC_ExtVref_SIO_DIFF           (* (reg8 *) pHADC_ExtVref__SIO_DIFF)
#endif /* (pHADC_ExtVref__SIO_CFG) */

/* Interrupt Registers */
#if defined(pHADC_ExtVref__INTSTAT)
    #define pHADC_ExtVref_INTSTAT            (* (reg8 *) pHADC_ExtVref__INTSTAT)
    #define pHADC_ExtVref_SNAP               (* (reg8 *) pHADC_ExtVref__SNAP)
    
	#define pHADC_ExtVref_0_INTTYPE_REG 		(* (reg8 *) pHADC_ExtVref__0__INTTYPE)
#endif /* (pHADC_ExtVref__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pHADC_ExtVref_H */


/* [] END OF FILE */
