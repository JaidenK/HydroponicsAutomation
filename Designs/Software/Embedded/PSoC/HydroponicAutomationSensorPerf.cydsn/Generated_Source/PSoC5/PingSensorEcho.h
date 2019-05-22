/*******************************************************************************
* File Name: PingSensorEcho.h  
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

#if !defined(CY_PINS_PingSensorEcho_H) /* Pins PingSensorEcho_H */
#define CY_PINS_PingSensorEcho_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PingSensorEcho_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PingSensorEcho__PORT == 15 && ((PingSensorEcho__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PingSensorEcho_Write(uint8 value);
void    PingSensorEcho_SetDriveMode(uint8 mode);
uint8   PingSensorEcho_ReadDataReg(void);
uint8   PingSensorEcho_Read(void);
void    PingSensorEcho_SetInterruptMode(uint16 position, uint16 mode);
uint8   PingSensorEcho_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PingSensorEcho_SetDriveMode() function.
     *  @{
     */
        #define PingSensorEcho_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PingSensorEcho_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PingSensorEcho_DM_RES_UP          PIN_DM_RES_UP
        #define PingSensorEcho_DM_RES_DWN         PIN_DM_RES_DWN
        #define PingSensorEcho_DM_OD_LO           PIN_DM_OD_LO
        #define PingSensorEcho_DM_OD_HI           PIN_DM_OD_HI
        #define PingSensorEcho_DM_STRONG          PIN_DM_STRONG
        #define PingSensorEcho_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PingSensorEcho_MASK               PingSensorEcho__MASK
#define PingSensorEcho_SHIFT              PingSensorEcho__SHIFT
#define PingSensorEcho_WIDTH              1u

/* Interrupt constants */
#if defined(PingSensorEcho__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PingSensorEcho_SetInterruptMode() function.
     *  @{
     */
        #define PingSensorEcho_INTR_NONE      (uint16)(0x0000u)
        #define PingSensorEcho_INTR_RISING    (uint16)(0x0001u)
        #define PingSensorEcho_INTR_FALLING   (uint16)(0x0002u)
        #define PingSensorEcho_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PingSensorEcho_INTR_MASK      (0x01u) 
#endif /* (PingSensorEcho__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PingSensorEcho_PS                     (* (reg8 *) PingSensorEcho__PS)
/* Data Register */
#define PingSensorEcho_DR                     (* (reg8 *) PingSensorEcho__DR)
/* Port Number */
#define PingSensorEcho_PRT_NUM                (* (reg8 *) PingSensorEcho__PRT) 
/* Connect to Analog Globals */                                                  
#define PingSensorEcho_AG                     (* (reg8 *) PingSensorEcho__AG)                       
/* Analog MUX bux enable */
#define PingSensorEcho_AMUX                   (* (reg8 *) PingSensorEcho__AMUX) 
/* Bidirectional Enable */                                                        
#define PingSensorEcho_BIE                    (* (reg8 *) PingSensorEcho__BIE)
/* Bit-mask for Aliased Register Access */
#define PingSensorEcho_BIT_MASK               (* (reg8 *) PingSensorEcho__BIT_MASK)
/* Bypass Enable */
#define PingSensorEcho_BYP                    (* (reg8 *) PingSensorEcho__BYP)
/* Port wide control signals */                                                   
#define PingSensorEcho_CTL                    (* (reg8 *) PingSensorEcho__CTL)
/* Drive Modes */
#define PingSensorEcho_DM0                    (* (reg8 *) PingSensorEcho__DM0) 
#define PingSensorEcho_DM1                    (* (reg8 *) PingSensorEcho__DM1)
#define PingSensorEcho_DM2                    (* (reg8 *) PingSensorEcho__DM2) 
/* Input Buffer Disable Override */
#define PingSensorEcho_INP_DIS                (* (reg8 *) PingSensorEcho__INP_DIS)
/* LCD Common or Segment Drive */
#define PingSensorEcho_LCD_COM_SEG            (* (reg8 *) PingSensorEcho__LCD_COM_SEG)
/* Enable Segment LCD */
#define PingSensorEcho_LCD_EN                 (* (reg8 *) PingSensorEcho__LCD_EN)
/* Slew Rate Control */
#define PingSensorEcho_SLW                    (* (reg8 *) PingSensorEcho__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PingSensorEcho_PRTDSI__CAPS_SEL       (* (reg8 *) PingSensorEcho__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PingSensorEcho_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PingSensorEcho__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PingSensorEcho_PRTDSI__OE_SEL0        (* (reg8 *) PingSensorEcho__PRTDSI__OE_SEL0) 
#define PingSensorEcho_PRTDSI__OE_SEL1        (* (reg8 *) PingSensorEcho__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PingSensorEcho_PRTDSI__OUT_SEL0       (* (reg8 *) PingSensorEcho__PRTDSI__OUT_SEL0) 
#define PingSensorEcho_PRTDSI__OUT_SEL1       (* (reg8 *) PingSensorEcho__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PingSensorEcho_PRTDSI__SYNC_OUT       (* (reg8 *) PingSensorEcho__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PingSensorEcho__SIO_CFG)
    #define PingSensorEcho_SIO_HYST_EN        (* (reg8 *) PingSensorEcho__SIO_HYST_EN)
    #define PingSensorEcho_SIO_REG_HIFREQ     (* (reg8 *) PingSensorEcho__SIO_REG_HIFREQ)
    #define PingSensorEcho_SIO_CFG            (* (reg8 *) PingSensorEcho__SIO_CFG)
    #define PingSensorEcho_SIO_DIFF           (* (reg8 *) PingSensorEcho__SIO_DIFF)
#endif /* (PingSensorEcho__SIO_CFG) */

/* Interrupt Registers */
#if defined(PingSensorEcho__INTSTAT)
    #define PingSensorEcho_INTSTAT            (* (reg8 *) PingSensorEcho__INTSTAT)
    #define PingSensorEcho_SNAP               (* (reg8 *) PingSensorEcho__SNAP)
    
	#define PingSensorEcho_0_INTTYPE_REG 		(* (reg8 *) PingSensorEcho__0__INTTYPE)
#endif /* (PingSensorEcho__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PingSensorEcho_H */


/* [] END OF FILE */
