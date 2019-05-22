/*******************************************************************************
* File Name: PWMOut.h  
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

#if !defined(CY_PINS_PWMOut_H) /* Pins PWMOut_H */
#define CY_PINS_PWMOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PWMOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PWMOut__PORT == 15 && ((PWMOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PWMOut_Write(uint8 value);
void    PWMOut_SetDriveMode(uint8 mode);
uint8   PWMOut_ReadDataReg(void);
uint8   PWMOut_Read(void);
void    PWMOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   PWMOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PWMOut_SetDriveMode() function.
     *  @{
     */
        #define PWMOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PWMOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PWMOut_DM_RES_UP          PIN_DM_RES_UP
        #define PWMOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define PWMOut_DM_OD_LO           PIN_DM_OD_LO
        #define PWMOut_DM_OD_HI           PIN_DM_OD_HI
        #define PWMOut_DM_STRONG          PIN_DM_STRONG
        #define PWMOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PWMOut_MASK               PWMOut__MASK
#define PWMOut_SHIFT              PWMOut__SHIFT
#define PWMOut_WIDTH              1u

/* Interrupt constants */
#if defined(PWMOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PWMOut_SetInterruptMode() function.
     *  @{
     */
        #define PWMOut_INTR_NONE      (uint16)(0x0000u)
        #define PWMOut_INTR_RISING    (uint16)(0x0001u)
        #define PWMOut_INTR_FALLING   (uint16)(0x0002u)
        #define PWMOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PWMOut_INTR_MASK      (0x01u) 
#endif /* (PWMOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWMOut_PS                     (* (reg8 *) PWMOut__PS)
/* Data Register */
#define PWMOut_DR                     (* (reg8 *) PWMOut__DR)
/* Port Number */
#define PWMOut_PRT_NUM                (* (reg8 *) PWMOut__PRT) 
/* Connect to Analog Globals */                                                  
#define PWMOut_AG                     (* (reg8 *) PWMOut__AG)                       
/* Analog MUX bux enable */
#define PWMOut_AMUX                   (* (reg8 *) PWMOut__AMUX) 
/* Bidirectional Enable */                                                        
#define PWMOut_BIE                    (* (reg8 *) PWMOut__BIE)
/* Bit-mask for Aliased Register Access */
#define PWMOut_BIT_MASK               (* (reg8 *) PWMOut__BIT_MASK)
/* Bypass Enable */
#define PWMOut_BYP                    (* (reg8 *) PWMOut__BYP)
/* Port wide control signals */                                                   
#define PWMOut_CTL                    (* (reg8 *) PWMOut__CTL)
/* Drive Modes */
#define PWMOut_DM0                    (* (reg8 *) PWMOut__DM0) 
#define PWMOut_DM1                    (* (reg8 *) PWMOut__DM1)
#define PWMOut_DM2                    (* (reg8 *) PWMOut__DM2) 
/* Input Buffer Disable Override */
#define PWMOut_INP_DIS                (* (reg8 *) PWMOut__INP_DIS)
/* LCD Common or Segment Drive */
#define PWMOut_LCD_COM_SEG            (* (reg8 *) PWMOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define PWMOut_LCD_EN                 (* (reg8 *) PWMOut__LCD_EN)
/* Slew Rate Control */
#define PWMOut_SLW                    (* (reg8 *) PWMOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PWMOut_PRTDSI__CAPS_SEL       (* (reg8 *) PWMOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PWMOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PWMOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PWMOut_PRTDSI__OE_SEL0        (* (reg8 *) PWMOut__PRTDSI__OE_SEL0) 
#define PWMOut_PRTDSI__OE_SEL1        (* (reg8 *) PWMOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PWMOut_PRTDSI__OUT_SEL0       (* (reg8 *) PWMOut__PRTDSI__OUT_SEL0) 
#define PWMOut_PRTDSI__OUT_SEL1       (* (reg8 *) PWMOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PWMOut_PRTDSI__SYNC_OUT       (* (reg8 *) PWMOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PWMOut__SIO_CFG)
    #define PWMOut_SIO_HYST_EN        (* (reg8 *) PWMOut__SIO_HYST_EN)
    #define PWMOut_SIO_REG_HIFREQ     (* (reg8 *) PWMOut__SIO_REG_HIFREQ)
    #define PWMOut_SIO_CFG            (* (reg8 *) PWMOut__SIO_CFG)
    #define PWMOut_SIO_DIFF           (* (reg8 *) PWMOut__SIO_DIFF)
#endif /* (PWMOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(PWMOut__INTSTAT)
    #define PWMOut_INTSTAT            (* (reg8 *) PWMOut__INTSTAT)
    #define PWMOut_SNAP               (* (reg8 *) PWMOut__SNAP)
    
	#define PWMOut_0_INTTYPE_REG 		(* (reg8 *) PWMOut__0__INTTYPE)
#endif /* (PWMOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PWMOut_H */


/* [] END OF FILE */
