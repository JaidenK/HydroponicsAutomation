/*******************************************************************************
* File Name: PWMSpeedSetting.h  
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

#if !defined(CY_PINS_PWMSpeedSetting_H) /* Pins PWMSpeedSetting_H */
#define CY_PINS_PWMSpeedSetting_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PWMSpeedSetting_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PWMSpeedSetting__PORT == 15 && ((PWMSpeedSetting__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PWMSpeedSetting_Write(uint8 value);
void    PWMSpeedSetting_SetDriveMode(uint8 mode);
uint8   PWMSpeedSetting_ReadDataReg(void);
uint8   PWMSpeedSetting_Read(void);
void    PWMSpeedSetting_SetInterruptMode(uint16 position, uint16 mode);
uint8   PWMSpeedSetting_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PWMSpeedSetting_SetDriveMode() function.
     *  @{
     */
        #define PWMSpeedSetting_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PWMSpeedSetting_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PWMSpeedSetting_DM_RES_UP          PIN_DM_RES_UP
        #define PWMSpeedSetting_DM_RES_DWN         PIN_DM_RES_DWN
        #define PWMSpeedSetting_DM_OD_LO           PIN_DM_OD_LO
        #define PWMSpeedSetting_DM_OD_HI           PIN_DM_OD_HI
        #define PWMSpeedSetting_DM_STRONG          PIN_DM_STRONG
        #define PWMSpeedSetting_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PWMSpeedSetting_MASK               PWMSpeedSetting__MASK
#define PWMSpeedSetting_SHIFT              PWMSpeedSetting__SHIFT
#define PWMSpeedSetting_WIDTH              1u

/* Interrupt constants */
#if defined(PWMSpeedSetting__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PWMSpeedSetting_SetInterruptMode() function.
     *  @{
     */
        #define PWMSpeedSetting_INTR_NONE      (uint16)(0x0000u)
        #define PWMSpeedSetting_INTR_RISING    (uint16)(0x0001u)
        #define PWMSpeedSetting_INTR_FALLING   (uint16)(0x0002u)
        #define PWMSpeedSetting_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PWMSpeedSetting_INTR_MASK      (0x01u) 
#endif /* (PWMSpeedSetting__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWMSpeedSetting_PS                     (* (reg8 *) PWMSpeedSetting__PS)
/* Data Register */
#define PWMSpeedSetting_DR                     (* (reg8 *) PWMSpeedSetting__DR)
/* Port Number */
#define PWMSpeedSetting_PRT_NUM                (* (reg8 *) PWMSpeedSetting__PRT) 
/* Connect to Analog Globals */                                                  
#define PWMSpeedSetting_AG                     (* (reg8 *) PWMSpeedSetting__AG)                       
/* Analog MUX bux enable */
#define PWMSpeedSetting_AMUX                   (* (reg8 *) PWMSpeedSetting__AMUX) 
/* Bidirectional Enable */                                                        
#define PWMSpeedSetting_BIE                    (* (reg8 *) PWMSpeedSetting__BIE)
/* Bit-mask for Aliased Register Access */
#define PWMSpeedSetting_BIT_MASK               (* (reg8 *) PWMSpeedSetting__BIT_MASK)
/* Bypass Enable */
#define PWMSpeedSetting_BYP                    (* (reg8 *) PWMSpeedSetting__BYP)
/* Port wide control signals */                                                   
#define PWMSpeedSetting_CTL                    (* (reg8 *) PWMSpeedSetting__CTL)
/* Drive Modes */
#define PWMSpeedSetting_DM0                    (* (reg8 *) PWMSpeedSetting__DM0) 
#define PWMSpeedSetting_DM1                    (* (reg8 *) PWMSpeedSetting__DM1)
#define PWMSpeedSetting_DM2                    (* (reg8 *) PWMSpeedSetting__DM2) 
/* Input Buffer Disable Override */
#define PWMSpeedSetting_INP_DIS                (* (reg8 *) PWMSpeedSetting__INP_DIS)
/* LCD Common or Segment Drive */
#define PWMSpeedSetting_LCD_COM_SEG            (* (reg8 *) PWMSpeedSetting__LCD_COM_SEG)
/* Enable Segment LCD */
#define PWMSpeedSetting_LCD_EN                 (* (reg8 *) PWMSpeedSetting__LCD_EN)
/* Slew Rate Control */
#define PWMSpeedSetting_SLW                    (* (reg8 *) PWMSpeedSetting__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PWMSpeedSetting_PRTDSI__CAPS_SEL       (* (reg8 *) PWMSpeedSetting__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PWMSpeedSetting_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PWMSpeedSetting__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PWMSpeedSetting_PRTDSI__OE_SEL0        (* (reg8 *) PWMSpeedSetting__PRTDSI__OE_SEL0) 
#define PWMSpeedSetting_PRTDSI__OE_SEL1        (* (reg8 *) PWMSpeedSetting__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PWMSpeedSetting_PRTDSI__OUT_SEL0       (* (reg8 *) PWMSpeedSetting__PRTDSI__OUT_SEL0) 
#define PWMSpeedSetting_PRTDSI__OUT_SEL1       (* (reg8 *) PWMSpeedSetting__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PWMSpeedSetting_PRTDSI__SYNC_OUT       (* (reg8 *) PWMSpeedSetting__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PWMSpeedSetting__SIO_CFG)
    #define PWMSpeedSetting_SIO_HYST_EN        (* (reg8 *) PWMSpeedSetting__SIO_HYST_EN)
    #define PWMSpeedSetting_SIO_REG_HIFREQ     (* (reg8 *) PWMSpeedSetting__SIO_REG_HIFREQ)
    #define PWMSpeedSetting_SIO_CFG            (* (reg8 *) PWMSpeedSetting__SIO_CFG)
    #define PWMSpeedSetting_SIO_DIFF           (* (reg8 *) PWMSpeedSetting__SIO_DIFF)
#endif /* (PWMSpeedSetting__SIO_CFG) */

/* Interrupt Registers */
#if defined(PWMSpeedSetting__INTSTAT)
    #define PWMSpeedSetting_INTSTAT            (* (reg8 *) PWMSpeedSetting__INTSTAT)
    #define PWMSpeedSetting_SNAP               (* (reg8 *) PWMSpeedSetting__SNAP)
    
	#define PWMSpeedSetting_0_INTTYPE_REG 		(* (reg8 *) PWMSpeedSetting__0__INTTYPE)
#endif /* (PWMSpeedSetting__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PWMSpeedSetting_H */


/* [] END OF FILE */
