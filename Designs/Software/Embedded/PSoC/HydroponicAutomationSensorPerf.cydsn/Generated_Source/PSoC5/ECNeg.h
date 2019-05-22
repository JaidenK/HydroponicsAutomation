/*******************************************************************************
* File Name: ECNeg.h  
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

#if !defined(CY_PINS_ECNeg_H) /* Pins ECNeg_H */
#define CY_PINS_ECNeg_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ECNeg_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ECNeg__PORT == 15 && ((ECNeg__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ECNeg_Write(uint8 value);
void    ECNeg_SetDriveMode(uint8 mode);
uint8   ECNeg_ReadDataReg(void);
uint8   ECNeg_Read(void);
void    ECNeg_SetInterruptMode(uint16 position, uint16 mode);
uint8   ECNeg_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ECNeg_SetDriveMode() function.
     *  @{
     */
        #define ECNeg_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ECNeg_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ECNeg_DM_RES_UP          PIN_DM_RES_UP
        #define ECNeg_DM_RES_DWN         PIN_DM_RES_DWN
        #define ECNeg_DM_OD_LO           PIN_DM_OD_LO
        #define ECNeg_DM_OD_HI           PIN_DM_OD_HI
        #define ECNeg_DM_STRONG          PIN_DM_STRONG
        #define ECNeg_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ECNeg_MASK               ECNeg__MASK
#define ECNeg_SHIFT              ECNeg__SHIFT
#define ECNeg_WIDTH              1u

/* Interrupt constants */
#if defined(ECNeg__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ECNeg_SetInterruptMode() function.
     *  @{
     */
        #define ECNeg_INTR_NONE      (uint16)(0x0000u)
        #define ECNeg_INTR_RISING    (uint16)(0x0001u)
        #define ECNeg_INTR_FALLING   (uint16)(0x0002u)
        #define ECNeg_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ECNeg_INTR_MASK      (0x01u) 
#endif /* (ECNeg__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ECNeg_PS                     (* (reg8 *) ECNeg__PS)
/* Data Register */
#define ECNeg_DR                     (* (reg8 *) ECNeg__DR)
/* Port Number */
#define ECNeg_PRT_NUM                (* (reg8 *) ECNeg__PRT) 
/* Connect to Analog Globals */                                                  
#define ECNeg_AG                     (* (reg8 *) ECNeg__AG)                       
/* Analog MUX bux enable */
#define ECNeg_AMUX                   (* (reg8 *) ECNeg__AMUX) 
/* Bidirectional Enable */                                                        
#define ECNeg_BIE                    (* (reg8 *) ECNeg__BIE)
/* Bit-mask for Aliased Register Access */
#define ECNeg_BIT_MASK               (* (reg8 *) ECNeg__BIT_MASK)
/* Bypass Enable */
#define ECNeg_BYP                    (* (reg8 *) ECNeg__BYP)
/* Port wide control signals */                                                   
#define ECNeg_CTL                    (* (reg8 *) ECNeg__CTL)
/* Drive Modes */
#define ECNeg_DM0                    (* (reg8 *) ECNeg__DM0) 
#define ECNeg_DM1                    (* (reg8 *) ECNeg__DM1)
#define ECNeg_DM2                    (* (reg8 *) ECNeg__DM2) 
/* Input Buffer Disable Override */
#define ECNeg_INP_DIS                (* (reg8 *) ECNeg__INP_DIS)
/* LCD Common or Segment Drive */
#define ECNeg_LCD_COM_SEG            (* (reg8 *) ECNeg__LCD_COM_SEG)
/* Enable Segment LCD */
#define ECNeg_LCD_EN                 (* (reg8 *) ECNeg__LCD_EN)
/* Slew Rate Control */
#define ECNeg_SLW                    (* (reg8 *) ECNeg__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ECNeg_PRTDSI__CAPS_SEL       (* (reg8 *) ECNeg__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ECNeg_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ECNeg__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ECNeg_PRTDSI__OE_SEL0        (* (reg8 *) ECNeg__PRTDSI__OE_SEL0) 
#define ECNeg_PRTDSI__OE_SEL1        (* (reg8 *) ECNeg__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ECNeg_PRTDSI__OUT_SEL0       (* (reg8 *) ECNeg__PRTDSI__OUT_SEL0) 
#define ECNeg_PRTDSI__OUT_SEL1       (* (reg8 *) ECNeg__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ECNeg_PRTDSI__SYNC_OUT       (* (reg8 *) ECNeg__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ECNeg__SIO_CFG)
    #define ECNeg_SIO_HYST_EN        (* (reg8 *) ECNeg__SIO_HYST_EN)
    #define ECNeg_SIO_REG_HIFREQ     (* (reg8 *) ECNeg__SIO_REG_HIFREQ)
    #define ECNeg_SIO_CFG            (* (reg8 *) ECNeg__SIO_CFG)
    #define ECNeg_SIO_DIFF           (* (reg8 *) ECNeg__SIO_DIFF)
#endif /* (ECNeg__SIO_CFG) */

/* Interrupt Registers */
#if defined(ECNeg__INTSTAT)
    #define ECNeg_INTSTAT            (* (reg8 *) ECNeg__INTSTAT)
    #define ECNeg_SNAP               (* (reg8 *) ECNeg__SNAP)
    
	#define ECNeg_0_INTTYPE_REG 		(* (reg8 *) ECNeg__0__INTTYPE)
#endif /* (ECNeg__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ECNeg_H */


/* [] END OF FILE */
