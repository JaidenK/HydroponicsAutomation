/*******************************************************************************
* File Name: pHUpEcho.h  
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

#if !defined(CY_PINS_pHUpEcho_H) /* Pins pHUpEcho_H */
#define CY_PINS_pHUpEcho_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pHUpEcho_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pHUpEcho__PORT == 15 && ((pHUpEcho__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pHUpEcho_Write(uint8 value);
void    pHUpEcho_SetDriveMode(uint8 mode);
uint8   pHUpEcho_ReadDataReg(void);
uint8   pHUpEcho_Read(void);
void    pHUpEcho_SetInterruptMode(uint16 position, uint16 mode);
uint8   pHUpEcho_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pHUpEcho_SetDriveMode() function.
     *  @{
     */
        #define pHUpEcho_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pHUpEcho_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pHUpEcho_DM_RES_UP          PIN_DM_RES_UP
        #define pHUpEcho_DM_RES_DWN         PIN_DM_RES_DWN
        #define pHUpEcho_DM_OD_LO           PIN_DM_OD_LO
        #define pHUpEcho_DM_OD_HI           PIN_DM_OD_HI
        #define pHUpEcho_DM_STRONG          PIN_DM_STRONG
        #define pHUpEcho_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pHUpEcho_MASK               pHUpEcho__MASK
#define pHUpEcho_SHIFT              pHUpEcho__SHIFT
#define pHUpEcho_WIDTH              1u

/* Interrupt constants */
#if defined(pHUpEcho__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pHUpEcho_SetInterruptMode() function.
     *  @{
     */
        #define pHUpEcho_INTR_NONE      (uint16)(0x0000u)
        #define pHUpEcho_INTR_RISING    (uint16)(0x0001u)
        #define pHUpEcho_INTR_FALLING   (uint16)(0x0002u)
        #define pHUpEcho_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pHUpEcho_INTR_MASK      (0x01u) 
#endif /* (pHUpEcho__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pHUpEcho_PS                     (* (reg8 *) pHUpEcho__PS)
/* Data Register */
#define pHUpEcho_DR                     (* (reg8 *) pHUpEcho__DR)
/* Port Number */
#define pHUpEcho_PRT_NUM                (* (reg8 *) pHUpEcho__PRT) 
/* Connect to Analog Globals */                                                  
#define pHUpEcho_AG                     (* (reg8 *) pHUpEcho__AG)                       
/* Analog MUX bux enable */
#define pHUpEcho_AMUX                   (* (reg8 *) pHUpEcho__AMUX) 
/* Bidirectional Enable */                                                        
#define pHUpEcho_BIE                    (* (reg8 *) pHUpEcho__BIE)
/* Bit-mask for Aliased Register Access */
#define pHUpEcho_BIT_MASK               (* (reg8 *) pHUpEcho__BIT_MASK)
/* Bypass Enable */
#define pHUpEcho_BYP                    (* (reg8 *) pHUpEcho__BYP)
/* Port wide control signals */                                                   
#define pHUpEcho_CTL                    (* (reg8 *) pHUpEcho__CTL)
/* Drive Modes */
#define pHUpEcho_DM0                    (* (reg8 *) pHUpEcho__DM0) 
#define pHUpEcho_DM1                    (* (reg8 *) pHUpEcho__DM1)
#define pHUpEcho_DM2                    (* (reg8 *) pHUpEcho__DM2) 
/* Input Buffer Disable Override */
#define pHUpEcho_INP_DIS                (* (reg8 *) pHUpEcho__INP_DIS)
/* LCD Common or Segment Drive */
#define pHUpEcho_LCD_COM_SEG            (* (reg8 *) pHUpEcho__LCD_COM_SEG)
/* Enable Segment LCD */
#define pHUpEcho_LCD_EN                 (* (reg8 *) pHUpEcho__LCD_EN)
/* Slew Rate Control */
#define pHUpEcho_SLW                    (* (reg8 *) pHUpEcho__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pHUpEcho_PRTDSI__CAPS_SEL       (* (reg8 *) pHUpEcho__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pHUpEcho_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pHUpEcho__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pHUpEcho_PRTDSI__OE_SEL0        (* (reg8 *) pHUpEcho__PRTDSI__OE_SEL0) 
#define pHUpEcho_PRTDSI__OE_SEL1        (* (reg8 *) pHUpEcho__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pHUpEcho_PRTDSI__OUT_SEL0       (* (reg8 *) pHUpEcho__PRTDSI__OUT_SEL0) 
#define pHUpEcho_PRTDSI__OUT_SEL1       (* (reg8 *) pHUpEcho__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pHUpEcho_PRTDSI__SYNC_OUT       (* (reg8 *) pHUpEcho__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pHUpEcho__SIO_CFG)
    #define pHUpEcho_SIO_HYST_EN        (* (reg8 *) pHUpEcho__SIO_HYST_EN)
    #define pHUpEcho_SIO_REG_HIFREQ     (* (reg8 *) pHUpEcho__SIO_REG_HIFREQ)
    #define pHUpEcho_SIO_CFG            (* (reg8 *) pHUpEcho__SIO_CFG)
    #define pHUpEcho_SIO_DIFF           (* (reg8 *) pHUpEcho__SIO_DIFF)
#endif /* (pHUpEcho__SIO_CFG) */

/* Interrupt Registers */
#if defined(pHUpEcho__INTSTAT)
    #define pHUpEcho_INTSTAT            (* (reg8 *) pHUpEcho__INTSTAT)
    #define pHUpEcho_SNAP               (* (reg8 *) pHUpEcho__SNAP)
    
	#define pHUpEcho_0_INTTYPE_REG 		(* (reg8 *) pHUpEcho__0__INTTYPE)
#endif /* (pHUpEcho__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pHUpEcho_H */


/* [] END OF FILE */
