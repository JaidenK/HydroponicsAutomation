/*******************************************************************************
* File Name: pH.h  
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

#if !defined(CY_PINS_pH_H) /* Pins pH_H */
#define CY_PINS_pH_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pH_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pH__PORT == 15 && ((pH__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pH_Write(uint8 value);
void    pH_SetDriveMode(uint8 mode);
uint8   pH_ReadDataReg(void);
uint8   pH_Read(void);
void    pH_SetInterruptMode(uint16 position, uint16 mode);
uint8   pH_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pH_SetDriveMode() function.
     *  @{
     */
        #define pH_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pH_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pH_DM_RES_UP          PIN_DM_RES_UP
        #define pH_DM_RES_DWN         PIN_DM_RES_DWN
        #define pH_DM_OD_LO           PIN_DM_OD_LO
        #define pH_DM_OD_HI           PIN_DM_OD_HI
        #define pH_DM_STRONG          PIN_DM_STRONG
        #define pH_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pH_MASK               pH__MASK
#define pH_SHIFT              pH__SHIFT
#define pH_WIDTH              1u

/* Interrupt constants */
#if defined(pH__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pH_SetInterruptMode() function.
     *  @{
     */
        #define pH_INTR_NONE      (uint16)(0x0000u)
        #define pH_INTR_RISING    (uint16)(0x0001u)
        #define pH_INTR_FALLING   (uint16)(0x0002u)
        #define pH_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pH_INTR_MASK      (0x01u) 
#endif /* (pH__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pH_PS                     (* (reg8 *) pH__PS)
/* Data Register */
#define pH_DR                     (* (reg8 *) pH__DR)
/* Port Number */
#define pH_PRT_NUM                (* (reg8 *) pH__PRT) 
/* Connect to Analog Globals */                                                  
#define pH_AG                     (* (reg8 *) pH__AG)                       
/* Analog MUX bux enable */
#define pH_AMUX                   (* (reg8 *) pH__AMUX) 
/* Bidirectional Enable */                                                        
#define pH_BIE                    (* (reg8 *) pH__BIE)
/* Bit-mask for Aliased Register Access */
#define pH_BIT_MASK               (* (reg8 *) pH__BIT_MASK)
/* Bypass Enable */
#define pH_BYP                    (* (reg8 *) pH__BYP)
/* Port wide control signals */                                                   
#define pH_CTL                    (* (reg8 *) pH__CTL)
/* Drive Modes */
#define pH_DM0                    (* (reg8 *) pH__DM0) 
#define pH_DM1                    (* (reg8 *) pH__DM1)
#define pH_DM2                    (* (reg8 *) pH__DM2) 
/* Input Buffer Disable Override */
#define pH_INP_DIS                (* (reg8 *) pH__INP_DIS)
/* LCD Common or Segment Drive */
#define pH_LCD_COM_SEG            (* (reg8 *) pH__LCD_COM_SEG)
/* Enable Segment LCD */
#define pH_LCD_EN                 (* (reg8 *) pH__LCD_EN)
/* Slew Rate Control */
#define pH_SLW                    (* (reg8 *) pH__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pH_PRTDSI__CAPS_SEL       (* (reg8 *) pH__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pH_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pH__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pH_PRTDSI__OE_SEL0        (* (reg8 *) pH__PRTDSI__OE_SEL0) 
#define pH_PRTDSI__OE_SEL1        (* (reg8 *) pH__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pH_PRTDSI__OUT_SEL0       (* (reg8 *) pH__PRTDSI__OUT_SEL0) 
#define pH_PRTDSI__OUT_SEL1       (* (reg8 *) pH__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pH_PRTDSI__SYNC_OUT       (* (reg8 *) pH__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pH__SIO_CFG)
    #define pH_SIO_HYST_EN        (* (reg8 *) pH__SIO_HYST_EN)
    #define pH_SIO_REG_HIFREQ     (* (reg8 *) pH__SIO_REG_HIFREQ)
    #define pH_SIO_CFG            (* (reg8 *) pH__SIO_CFG)
    #define pH_SIO_DIFF           (* (reg8 *) pH__SIO_DIFF)
#endif /* (pH__SIO_CFG) */

/* Interrupt Registers */
#if defined(pH__INTSTAT)
    #define pH_INTSTAT            (* (reg8 *) pH__INTSTAT)
    #define pH_SNAP               (* (reg8 *) pH__SNAP)
    
	#define pH_0_INTTYPE_REG 		(* (reg8 *) pH__0__INTTYPE)
#endif /* (pH__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pH_H */


/* [] END OF FILE */
