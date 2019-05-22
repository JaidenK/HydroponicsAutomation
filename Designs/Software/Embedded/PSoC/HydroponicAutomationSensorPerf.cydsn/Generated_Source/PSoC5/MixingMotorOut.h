/*******************************************************************************
* File Name: MixingMotorOut.h  
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

#if !defined(CY_PINS_MixingMotorOut_H) /* Pins MixingMotorOut_H */
#define CY_PINS_MixingMotorOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MixingMotorOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MixingMotorOut__PORT == 15 && ((MixingMotorOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MixingMotorOut_Write(uint8 value);
void    MixingMotorOut_SetDriveMode(uint8 mode);
uint8   MixingMotorOut_ReadDataReg(void);
uint8   MixingMotorOut_Read(void);
void    MixingMotorOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   MixingMotorOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MixingMotorOut_SetDriveMode() function.
     *  @{
     */
        #define MixingMotorOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MixingMotorOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MixingMotorOut_DM_RES_UP          PIN_DM_RES_UP
        #define MixingMotorOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define MixingMotorOut_DM_OD_LO           PIN_DM_OD_LO
        #define MixingMotorOut_DM_OD_HI           PIN_DM_OD_HI
        #define MixingMotorOut_DM_STRONG          PIN_DM_STRONG
        #define MixingMotorOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MixingMotorOut_MASK               MixingMotorOut__MASK
#define MixingMotorOut_SHIFT              MixingMotorOut__SHIFT
#define MixingMotorOut_WIDTH              1u

/* Interrupt constants */
#if defined(MixingMotorOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MixingMotorOut_SetInterruptMode() function.
     *  @{
     */
        #define MixingMotorOut_INTR_NONE      (uint16)(0x0000u)
        #define MixingMotorOut_INTR_RISING    (uint16)(0x0001u)
        #define MixingMotorOut_INTR_FALLING   (uint16)(0x0002u)
        #define MixingMotorOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MixingMotorOut_INTR_MASK      (0x01u) 
#endif /* (MixingMotorOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MixingMotorOut_PS                     (* (reg8 *) MixingMotorOut__PS)
/* Data Register */
#define MixingMotorOut_DR                     (* (reg8 *) MixingMotorOut__DR)
/* Port Number */
#define MixingMotorOut_PRT_NUM                (* (reg8 *) MixingMotorOut__PRT) 
/* Connect to Analog Globals */                                                  
#define MixingMotorOut_AG                     (* (reg8 *) MixingMotorOut__AG)                       
/* Analog MUX bux enable */
#define MixingMotorOut_AMUX                   (* (reg8 *) MixingMotorOut__AMUX) 
/* Bidirectional Enable */                                                        
#define MixingMotorOut_BIE                    (* (reg8 *) MixingMotorOut__BIE)
/* Bit-mask for Aliased Register Access */
#define MixingMotorOut_BIT_MASK               (* (reg8 *) MixingMotorOut__BIT_MASK)
/* Bypass Enable */
#define MixingMotorOut_BYP                    (* (reg8 *) MixingMotorOut__BYP)
/* Port wide control signals */                                                   
#define MixingMotorOut_CTL                    (* (reg8 *) MixingMotorOut__CTL)
/* Drive Modes */
#define MixingMotorOut_DM0                    (* (reg8 *) MixingMotorOut__DM0) 
#define MixingMotorOut_DM1                    (* (reg8 *) MixingMotorOut__DM1)
#define MixingMotorOut_DM2                    (* (reg8 *) MixingMotorOut__DM2) 
/* Input Buffer Disable Override */
#define MixingMotorOut_INP_DIS                (* (reg8 *) MixingMotorOut__INP_DIS)
/* LCD Common or Segment Drive */
#define MixingMotorOut_LCD_COM_SEG            (* (reg8 *) MixingMotorOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define MixingMotorOut_LCD_EN                 (* (reg8 *) MixingMotorOut__LCD_EN)
/* Slew Rate Control */
#define MixingMotorOut_SLW                    (* (reg8 *) MixingMotorOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MixingMotorOut_PRTDSI__CAPS_SEL       (* (reg8 *) MixingMotorOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MixingMotorOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MixingMotorOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MixingMotorOut_PRTDSI__OE_SEL0        (* (reg8 *) MixingMotorOut__PRTDSI__OE_SEL0) 
#define MixingMotorOut_PRTDSI__OE_SEL1        (* (reg8 *) MixingMotorOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MixingMotorOut_PRTDSI__OUT_SEL0       (* (reg8 *) MixingMotorOut__PRTDSI__OUT_SEL0) 
#define MixingMotorOut_PRTDSI__OUT_SEL1       (* (reg8 *) MixingMotorOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MixingMotorOut_PRTDSI__SYNC_OUT       (* (reg8 *) MixingMotorOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MixingMotorOut__SIO_CFG)
    #define MixingMotorOut_SIO_HYST_EN        (* (reg8 *) MixingMotorOut__SIO_HYST_EN)
    #define MixingMotorOut_SIO_REG_HIFREQ     (* (reg8 *) MixingMotorOut__SIO_REG_HIFREQ)
    #define MixingMotorOut_SIO_CFG            (* (reg8 *) MixingMotorOut__SIO_CFG)
    #define MixingMotorOut_SIO_DIFF           (* (reg8 *) MixingMotorOut__SIO_DIFF)
#endif /* (MixingMotorOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(MixingMotorOut__INTSTAT)
    #define MixingMotorOut_INTSTAT            (* (reg8 *) MixingMotorOut__INTSTAT)
    #define MixingMotorOut_SNAP               (* (reg8 *) MixingMotorOut__SNAP)
    
	#define MixingMotorOut_0_INTTYPE_REG 		(* (reg8 *) MixingMotorOut__0__INTTYPE)
#endif /* (MixingMotorOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MixingMotorOut_H */


/* [] END OF FILE */
