/*******************************************************************************
* File Name: pHDownEcho.h  
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

#if !defined(CY_PINS_pHDownEcho_H) /* Pins pHDownEcho_H */
#define CY_PINS_pHDownEcho_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pHDownEcho_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pHDownEcho__PORT == 15 && ((pHDownEcho__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pHDownEcho_Write(uint8 value);
void    pHDownEcho_SetDriveMode(uint8 mode);
uint8   pHDownEcho_ReadDataReg(void);
uint8   pHDownEcho_Read(void);
void    pHDownEcho_SetInterruptMode(uint16 position, uint16 mode);
uint8   pHDownEcho_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pHDownEcho_SetDriveMode() function.
     *  @{
     */
        #define pHDownEcho_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pHDownEcho_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pHDownEcho_DM_RES_UP          PIN_DM_RES_UP
        #define pHDownEcho_DM_RES_DWN         PIN_DM_RES_DWN
        #define pHDownEcho_DM_OD_LO           PIN_DM_OD_LO
        #define pHDownEcho_DM_OD_HI           PIN_DM_OD_HI
        #define pHDownEcho_DM_STRONG          PIN_DM_STRONG
        #define pHDownEcho_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pHDownEcho_MASK               pHDownEcho__MASK
#define pHDownEcho_SHIFT              pHDownEcho__SHIFT
#define pHDownEcho_WIDTH              1u

/* Interrupt constants */
#if defined(pHDownEcho__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pHDownEcho_SetInterruptMode() function.
     *  @{
     */
        #define pHDownEcho_INTR_NONE      (uint16)(0x0000u)
        #define pHDownEcho_INTR_RISING    (uint16)(0x0001u)
        #define pHDownEcho_INTR_FALLING   (uint16)(0x0002u)
        #define pHDownEcho_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pHDownEcho_INTR_MASK      (0x01u) 
#endif /* (pHDownEcho__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pHDownEcho_PS                     (* (reg8 *) pHDownEcho__PS)
/* Data Register */
#define pHDownEcho_DR                     (* (reg8 *) pHDownEcho__DR)
/* Port Number */
#define pHDownEcho_PRT_NUM                (* (reg8 *) pHDownEcho__PRT) 
/* Connect to Analog Globals */                                                  
#define pHDownEcho_AG                     (* (reg8 *) pHDownEcho__AG)                       
/* Analog MUX bux enable */
#define pHDownEcho_AMUX                   (* (reg8 *) pHDownEcho__AMUX) 
/* Bidirectional Enable */                                                        
#define pHDownEcho_BIE                    (* (reg8 *) pHDownEcho__BIE)
/* Bit-mask for Aliased Register Access */
#define pHDownEcho_BIT_MASK               (* (reg8 *) pHDownEcho__BIT_MASK)
/* Bypass Enable */
#define pHDownEcho_BYP                    (* (reg8 *) pHDownEcho__BYP)
/* Port wide control signals */                                                   
#define pHDownEcho_CTL                    (* (reg8 *) pHDownEcho__CTL)
/* Drive Modes */
#define pHDownEcho_DM0                    (* (reg8 *) pHDownEcho__DM0) 
#define pHDownEcho_DM1                    (* (reg8 *) pHDownEcho__DM1)
#define pHDownEcho_DM2                    (* (reg8 *) pHDownEcho__DM2) 
/* Input Buffer Disable Override */
#define pHDownEcho_INP_DIS                (* (reg8 *) pHDownEcho__INP_DIS)
/* LCD Common or Segment Drive */
#define pHDownEcho_LCD_COM_SEG            (* (reg8 *) pHDownEcho__LCD_COM_SEG)
/* Enable Segment LCD */
#define pHDownEcho_LCD_EN                 (* (reg8 *) pHDownEcho__LCD_EN)
/* Slew Rate Control */
#define pHDownEcho_SLW                    (* (reg8 *) pHDownEcho__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pHDownEcho_PRTDSI__CAPS_SEL       (* (reg8 *) pHDownEcho__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pHDownEcho_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pHDownEcho__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pHDownEcho_PRTDSI__OE_SEL0        (* (reg8 *) pHDownEcho__PRTDSI__OE_SEL0) 
#define pHDownEcho_PRTDSI__OE_SEL1        (* (reg8 *) pHDownEcho__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pHDownEcho_PRTDSI__OUT_SEL0       (* (reg8 *) pHDownEcho__PRTDSI__OUT_SEL0) 
#define pHDownEcho_PRTDSI__OUT_SEL1       (* (reg8 *) pHDownEcho__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pHDownEcho_PRTDSI__SYNC_OUT       (* (reg8 *) pHDownEcho__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pHDownEcho__SIO_CFG)
    #define pHDownEcho_SIO_HYST_EN        (* (reg8 *) pHDownEcho__SIO_HYST_EN)
    #define pHDownEcho_SIO_REG_HIFREQ     (* (reg8 *) pHDownEcho__SIO_REG_HIFREQ)
    #define pHDownEcho_SIO_CFG            (* (reg8 *) pHDownEcho__SIO_CFG)
    #define pHDownEcho_SIO_DIFF           (* (reg8 *) pHDownEcho__SIO_DIFF)
#endif /* (pHDownEcho__SIO_CFG) */

/* Interrupt Registers */
#if defined(pHDownEcho__INTSTAT)
    #define pHDownEcho_INTSTAT            (* (reg8 *) pHDownEcho__INTSTAT)
    #define pHDownEcho_SNAP               (* (reg8 *) pHDownEcho__SNAP)
    
	#define pHDownEcho_0_INTTYPE_REG 		(* (reg8 *) pHDownEcho__0__INTTYPE)
#endif /* (pHDownEcho__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pHDownEcho_H */


/* [] END OF FILE */
