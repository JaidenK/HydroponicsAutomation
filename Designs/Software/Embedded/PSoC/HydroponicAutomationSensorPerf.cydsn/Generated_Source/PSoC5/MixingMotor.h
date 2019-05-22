/*******************************************************************************
* File Name: MixingMotor.h  
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

#if !defined(CY_PINS_MixingMotor_H) /* Pins MixingMotor_H */
#define CY_PINS_MixingMotor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MixingMotor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MixingMotor__PORT == 15 && ((MixingMotor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MixingMotor_Write(uint8 value);
void    MixingMotor_SetDriveMode(uint8 mode);
uint8   MixingMotor_ReadDataReg(void);
uint8   MixingMotor_Read(void);
void    MixingMotor_SetInterruptMode(uint16 position, uint16 mode);
uint8   MixingMotor_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MixingMotor_SetDriveMode() function.
     *  @{
     */
        #define MixingMotor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MixingMotor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MixingMotor_DM_RES_UP          PIN_DM_RES_UP
        #define MixingMotor_DM_RES_DWN         PIN_DM_RES_DWN
        #define MixingMotor_DM_OD_LO           PIN_DM_OD_LO
        #define MixingMotor_DM_OD_HI           PIN_DM_OD_HI
        #define MixingMotor_DM_STRONG          PIN_DM_STRONG
        #define MixingMotor_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MixingMotor_MASK               MixingMotor__MASK
#define MixingMotor_SHIFT              MixingMotor__SHIFT
#define MixingMotor_WIDTH              1u

/* Interrupt constants */
#if defined(MixingMotor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MixingMotor_SetInterruptMode() function.
     *  @{
     */
        #define MixingMotor_INTR_NONE      (uint16)(0x0000u)
        #define MixingMotor_INTR_RISING    (uint16)(0x0001u)
        #define MixingMotor_INTR_FALLING   (uint16)(0x0002u)
        #define MixingMotor_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MixingMotor_INTR_MASK      (0x01u) 
#endif /* (MixingMotor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MixingMotor_PS                     (* (reg8 *) MixingMotor__PS)
/* Data Register */
#define MixingMotor_DR                     (* (reg8 *) MixingMotor__DR)
/* Port Number */
#define MixingMotor_PRT_NUM                (* (reg8 *) MixingMotor__PRT) 
/* Connect to Analog Globals */                                                  
#define MixingMotor_AG                     (* (reg8 *) MixingMotor__AG)                       
/* Analog MUX bux enable */
#define MixingMotor_AMUX                   (* (reg8 *) MixingMotor__AMUX) 
/* Bidirectional Enable */                                                        
#define MixingMotor_BIE                    (* (reg8 *) MixingMotor__BIE)
/* Bit-mask for Aliased Register Access */
#define MixingMotor_BIT_MASK               (* (reg8 *) MixingMotor__BIT_MASK)
/* Bypass Enable */
#define MixingMotor_BYP                    (* (reg8 *) MixingMotor__BYP)
/* Port wide control signals */                                                   
#define MixingMotor_CTL                    (* (reg8 *) MixingMotor__CTL)
/* Drive Modes */
#define MixingMotor_DM0                    (* (reg8 *) MixingMotor__DM0) 
#define MixingMotor_DM1                    (* (reg8 *) MixingMotor__DM1)
#define MixingMotor_DM2                    (* (reg8 *) MixingMotor__DM2) 
/* Input Buffer Disable Override */
#define MixingMotor_INP_DIS                (* (reg8 *) MixingMotor__INP_DIS)
/* LCD Common or Segment Drive */
#define MixingMotor_LCD_COM_SEG            (* (reg8 *) MixingMotor__LCD_COM_SEG)
/* Enable Segment LCD */
#define MixingMotor_LCD_EN                 (* (reg8 *) MixingMotor__LCD_EN)
/* Slew Rate Control */
#define MixingMotor_SLW                    (* (reg8 *) MixingMotor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MixingMotor_PRTDSI__CAPS_SEL       (* (reg8 *) MixingMotor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MixingMotor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MixingMotor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MixingMotor_PRTDSI__OE_SEL0        (* (reg8 *) MixingMotor__PRTDSI__OE_SEL0) 
#define MixingMotor_PRTDSI__OE_SEL1        (* (reg8 *) MixingMotor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MixingMotor_PRTDSI__OUT_SEL0       (* (reg8 *) MixingMotor__PRTDSI__OUT_SEL0) 
#define MixingMotor_PRTDSI__OUT_SEL1       (* (reg8 *) MixingMotor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MixingMotor_PRTDSI__SYNC_OUT       (* (reg8 *) MixingMotor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MixingMotor__SIO_CFG)
    #define MixingMotor_SIO_HYST_EN        (* (reg8 *) MixingMotor__SIO_HYST_EN)
    #define MixingMotor_SIO_REG_HIFREQ     (* (reg8 *) MixingMotor__SIO_REG_HIFREQ)
    #define MixingMotor_SIO_CFG            (* (reg8 *) MixingMotor__SIO_CFG)
    #define MixingMotor_SIO_DIFF           (* (reg8 *) MixingMotor__SIO_DIFF)
#endif /* (MixingMotor__SIO_CFG) */

/* Interrupt Registers */
#if defined(MixingMotor__INTSTAT)
    #define MixingMotor_INTSTAT            (* (reg8 *) MixingMotor__INTSTAT)
    #define MixingMotor_SNAP               (* (reg8 *) MixingMotor__SNAP)
    
	#define MixingMotor_0_INTTYPE_REG 		(* (reg8 *) MixingMotor__0__INTTYPE)
#endif /* (MixingMotor__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MixingMotor_H */


/* [] END OF FILE */
