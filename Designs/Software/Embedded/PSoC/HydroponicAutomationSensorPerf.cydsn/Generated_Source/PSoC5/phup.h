/*******************************************************************************
* File Name: phup.h  
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

#if !defined(CY_PINS_phup_H) /* Pins phup_H */
#define CY_PINS_phup_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "phup_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 phup__PORT == 15 && ((phup__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    phup_Write(uint8 value);
void    phup_SetDriveMode(uint8 mode);
uint8   phup_ReadDataReg(void);
uint8   phup_Read(void);
void    phup_SetInterruptMode(uint16 position, uint16 mode);
uint8   phup_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the phup_SetDriveMode() function.
     *  @{
     */
        #define phup_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define phup_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define phup_DM_RES_UP          PIN_DM_RES_UP
        #define phup_DM_RES_DWN         PIN_DM_RES_DWN
        #define phup_DM_OD_LO           PIN_DM_OD_LO
        #define phup_DM_OD_HI           PIN_DM_OD_HI
        #define phup_DM_STRONG          PIN_DM_STRONG
        #define phup_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define phup_MASK               phup__MASK
#define phup_SHIFT              phup__SHIFT
#define phup_WIDTH              1u

/* Interrupt constants */
#if defined(phup__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in phup_SetInterruptMode() function.
     *  @{
     */
        #define phup_INTR_NONE      (uint16)(0x0000u)
        #define phup_INTR_RISING    (uint16)(0x0001u)
        #define phup_INTR_FALLING   (uint16)(0x0002u)
        #define phup_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define phup_INTR_MASK      (0x01u) 
#endif /* (phup__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define phup_PS                     (* (reg8 *) phup__PS)
/* Data Register */
#define phup_DR                     (* (reg8 *) phup__DR)
/* Port Number */
#define phup_PRT_NUM                (* (reg8 *) phup__PRT) 
/* Connect to Analog Globals */                                                  
#define phup_AG                     (* (reg8 *) phup__AG)                       
/* Analog MUX bux enable */
#define phup_AMUX                   (* (reg8 *) phup__AMUX) 
/* Bidirectional Enable */                                                        
#define phup_BIE                    (* (reg8 *) phup__BIE)
/* Bit-mask for Aliased Register Access */
#define phup_BIT_MASK               (* (reg8 *) phup__BIT_MASK)
/* Bypass Enable */
#define phup_BYP                    (* (reg8 *) phup__BYP)
/* Port wide control signals */                                                   
#define phup_CTL                    (* (reg8 *) phup__CTL)
/* Drive Modes */
#define phup_DM0                    (* (reg8 *) phup__DM0) 
#define phup_DM1                    (* (reg8 *) phup__DM1)
#define phup_DM2                    (* (reg8 *) phup__DM2) 
/* Input Buffer Disable Override */
#define phup_INP_DIS                (* (reg8 *) phup__INP_DIS)
/* LCD Common or Segment Drive */
#define phup_LCD_COM_SEG            (* (reg8 *) phup__LCD_COM_SEG)
/* Enable Segment LCD */
#define phup_LCD_EN                 (* (reg8 *) phup__LCD_EN)
/* Slew Rate Control */
#define phup_SLW                    (* (reg8 *) phup__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define phup_PRTDSI__CAPS_SEL       (* (reg8 *) phup__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define phup_PRTDSI__DBL_SYNC_IN    (* (reg8 *) phup__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define phup_PRTDSI__OE_SEL0        (* (reg8 *) phup__PRTDSI__OE_SEL0) 
#define phup_PRTDSI__OE_SEL1        (* (reg8 *) phup__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define phup_PRTDSI__OUT_SEL0       (* (reg8 *) phup__PRTDSI__OUT_SEL0) 
#define phup_PRTDSI__OUT_SEL1       (* (reg8 *) phup__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define phup_PRTDSI__SYNC_OUT       (* (reg8 *) phup__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(phup__SIO_CFG)
    #define phup_SIO_HYST_EN        (* (reg8 *) phup__SIO_HYST_EN)
    #define phup_SIO_REG_HIFREQ     (* (reg8 *) phup__SIO_REG_HIFREQ)
    #define phup_SIO_CFG            (* (reg8 *) phup__SIO_CFG)
    #define phup_SIO_DIFF           (* (reg8 *) phup__SIO_DIFF)
#endif /* (phup__SIO_CFG) */

/* Interrupt Registers */
#if defined(phup__INTSTAT)
    #define phup_INTSTAT            (* (reg8 *) phup__INTSTAT)
    #define phup_SNAP               (* (reg8 *) phup__SNAP)
    
	#define phup_0_INTTYPE_REG 		(* (reg8 *) phup__0__INTTYPE)
#endif /* (phup__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_phup_H */


/* [] END OF FILE */
