/*******************************************************************************
* File Name: WaterResEcho.h  
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

#if !defined(CY_PINS_WaterResEcho_H) /* Pins WaterResEcho_H */
#define CY_PINS_WaterResEcho_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WaterResEcho_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 WaterResEcho__PORT == 15 && ((WaterResEcho__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    WaterResEcho_Write(uint8 value);
void    WaterResEcho_SetDriveMode(uint8 mode);
uint8   WaterResEcho_ReadDataReg(void);
uint8   WaterResEcho_Read(void);
void    WaterResEcho_SetInterruptMode(uint16 position, uint16 mode);
uint8   WaterResEcho_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the WaterResEcho_SetDriveMode() function.
     *  @{
     */
        #define WaterResEcho_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define WaterResEcho_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define WaterResEcho_DM_RES_UP          PIN_DM_RES_UP
        #define WaterResEcho_DM_RES_DWN         PIN_DM_RES_DWN
        #define WaterResEcho_DM_OD_LO           PIN_DM_OD_LO
        #define WaterResEcho_DM_OD_HI           PIN_DM_OD_HI
        #define WaterResEcho_DM_STRONG          PIN_DM_STRONG
        #define WaterResEcho_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define WaterResEcho_MASK               WaterResEcho__MASK
#define WaterResEcho_SHIFT              WaterResEcho__SHIFT
#define WaterResEcho_WIDTH              1u

/* Interrupt constants */
#if defined(WaterResEcho__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WaterResEcho_SetInterruptMode() function.
     *  @{
     */
        #define WaterResEcho_INTR_NONE      (uint16)(0x0000u)
        #define WaterResEcho_INTR_RISING    (uint16)(0x0001u)
        #define WaterResEcho_INTR_FALLING   (uint16)(0x0002u)
        #define WaterResEcho_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define WaterResEcho_INTR_MASK      (0x01u) 
#endif /* (WaterResEcho__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WaterResEcho_PS                     (* (reg8 *) WaterResEcho__PS)
/* Data Register */
#define WaterResEcho_DR                     (* (reg8 *) WaterResEcho__DR)
/* Port Number */
#define WaterResEcho_PRT_NUM                (* (reg8 *) WaterResEcho__PRT) 
/* Connect to Analog Globals */                                                  
#define WaterResEcho_AG                     (* (reg8 *) WaterResEcho__AG)                       
/* Analog MUX bux enable */
#define WaterResEcho_AMUX                   (* (reg8 *) WaterResEcho__AMUX) 
/* Bidirectional Enable */                                                        
#define WaterResEcho_BIE                    (* (reg8 *) WaterResEcho__BIE)
/* Bit-mask for Aliased Register Access */
#define WaterResEcho_BIT_MASK               (* (reg8 *) WaterResEcho__BIT_MASK)
/* Bypass Enable */
#define WaterResEcho_BYP                    (* (reg8 *) WaterResEcho__BYP)
/* Port wide control signals */                                                   
#define WaterResEcho_CTL                    (* (reg8 *) WaterResEcho__CTL)
/* Drive Modes */
#define WaterResEcho_DM0                    (* (reg8 *) WaterResEcho__DM0) 
#define WaterResEcho_DM1                    (* (reg8 *) WaterResEcho__DM1)
#define WaterResEcho_DM2                    (* (reg8 *) WaterResEcho__DM2) 
/* Input Buffer Disable Override */
#define WaterResEcho_INP_DIS                (* (reg8 *) WaterResEcho__INP_DIS)
/* LCD Common or Segment Drive */
#define WaterResEcho_LCD_COM_SEG            (* (reg8 *) WaterResEcho__LCD_COM_SEG)
/* Enable Segment LCD */
#define WaterResEcho_LCD_EN                 (* (reg8 *) WaterResEcho__LCD_EN)
/* Slew Rate Control */
#define WaterResEcho_SLW                    (* (reg8 *) WaterResEcho__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WaterResEcho_PRTDSI__CAPS_SEL       (* (reg8 *) WaterResEcho__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WaterResEcho_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WaterResEcho__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WaterResEcho_PRTDSI__OE_SEL0        (* (reg8 *) WaterResEcho__PRTDSI__OE_SEL0) 
#define WaterResEcho_PRTDSI__OE_SEL1        (* (reg8 *) WaterResEcho__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WaterResEcho_PRTDSI__OUT_SEL0       (* (reg8 *) WaterResEcho__PRTDSI__OUT_SEL0) 
#define WaterResEcho_PRTDSI__OUT_SEL1       (* (reg8 *) WaterResEcho__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WaterResEcho_PRTDSI__SYNC_OUT       (* (reg8 *) WaterResEcho__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(WaterResEcho__SIO_CFG)
    #define WaterResEcho_SIO_HYST_EN        (* (reg8 *) WaterResEcho__SIO_HYST_EN)
    #define WaterResEcho_SIO_REG_HIFREQ     (* (reg8 *) WaterResEcho__SIO_REG_HIFREQ)
    #define WaterResEcho_SIO_CFG            (* (reg8 *) WaterResEcho__SIO_CFG)
    #define WaterResEcho_SIO_DIFF           (* (reg8 *) WaterResEcho__SIO_DIFF)
#endif /* (WaterResEcho__SIO_CFG) */

/* Interrupt Registers */
#if defined(WaterResEcho__INTSTAT)
    #define WaterResEcho_INTSTAT            (* (reg8 *) WaterResEcho__INTSTAT)
    #define WaterResEcho_SNAP               (* (reg8 *) WaterResEcho__SNAP)
    
	#define WaterResEcho_0_INTTYPE_REG 		(* (reg8 *) WaterResEcho__0__INTTYPE)
#endif /* (WaterResEcho__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_WaterResEcho_H */


/* [] END OF FILE */
