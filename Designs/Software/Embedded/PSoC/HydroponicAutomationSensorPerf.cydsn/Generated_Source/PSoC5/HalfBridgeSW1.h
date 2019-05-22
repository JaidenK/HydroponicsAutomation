/*******************************************************************************
* File Name: HalfBridgeSW1.h  
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

#if !defined(CY_PINS_HalfBridgeSW1_H) /* Pins HalfBridgeSW1_H */
#define CY_PINS_HalfBridgeSW1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HalfBridgeSW1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HalfBridgeSW1__PORT == 15 && ((HalfBridgeSW1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    HalfBridgeSW1_Write(uint8 value);
void    HalfBridgeSW1_SetDriveMode(uint8 mode);
uint8   HalfBridgeSW1_ReadDataReg(void);
uint8   HalfBridgeSW1_Read(void);
void    HalfBridgeSW1_SetInterruptMode(uint16 position, uint16 mode);
uint8   HalfBridgeSW1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the HalfBridgeSW1_SetDriveMode() function.
     *  @{
     */
        #define HalfBridgeSW1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define HalfBridgeSW1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define HalfBridgeSW1_DM_RES_UP          PIN_DM_RES_UP
        #define HalfBridgeSW1_DM_RES_DWN         PIN_DM_RES_DWN
        #define HalfBridgeSW1_DM_OD_LO           PIN_DM_OD_LO
        #define HalfBridgeSW1_DM_OD_HI           PIN_DM_OD_HI
        #define HalfBridgeSW1_DM_STRONG          PIN_DM_STRONG
        #define HalfBridgeSW1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define HalfBridgeSW1_MASK               HalfBridgeSW1__MASK
#define HalfBridgeSW1_SHIFT              HalfBridgeSW1__SHIFT
#define HalfBridgeSW1_WIDTH              1u

/* Interrupt constants */
#if defined(HalfBridgeSW1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HalfBridgeSW1_SetInterruptMode() function.
     *  @{
     */
        #define HalfBridgeSW1_INTR_NONE      (uint16)(0x0000u)
        #define HalfBridgeSW1_INTR_RISING    (uint16)(0x0001u)
        #define HalfBridgeSW1_INTR_FALLING   (uint16)(0x0002u)
        #define HalfBridgeSW1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define HalfBridgeSW1_INTR_MASK      (0x01u) 
#endif /* (HalfBridgeSW1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HalfBridgeSW1_PS                     (* (reg8 *) HalfBridgeSW1__PS)
/* Data Register */
#define HalfBridgeSW1_DR                     (* (reg8 *) HalfBridgeSW1__DR)
/* Port Number */
#define HalfBridgeSW1_PRT_NUM                (* (reg8 *) HalfBridgeSW1__PRT) 
/* Connect to Analog Globals */                                                  
#define HalfBridgeSW1_AG                     (* (reg8 *) HalfBridgeSW1__AG)                       
/* Analog MUX bux enable */
#define HalfBridgeSW1_AMUX                   (* (reg8 *) HalfBridgeSW1__AMUX) 
/* Bidirectional Enable */                                                        
#define HalfBridgeSW1_BIE                    (* (reg8 *) HalfBridgeSW1__BIE)
/* Bit-mask for Aliased Register Access */
#define HalfBridgeSW1_BIT_MASK               (* (reg8 *) HalfBridgeSW1__BIT_MASK)
/* Bypass Enable */
#define HalfBridgeSW1_BYP                    (* (reg8 *) HalfBridgeSW1__BYP)
/* Port wide control signals */                                                   
#define HalfBridgeSW1_CTL                    (* (reg8 *) HalfBridgeSW1__CTL)
/* Drive Modes */
#define HalfBridgeSW1_DM0                    (* (reg8 *) HalfBridgeSW1__DM0) 
#define HalfBridgeSW1_DM1                    (* (reg8 *) HalfBridgeSW1__DM1)
#define HalfBridgeSW1_DM2                    (* (reg8 *) HalfBridgeSW1__DM2) 
/* Input Buffer Disable Override */
#define HalfBridgeSW1_INP_DIS                (* (reg8 *) HalfBridgeSW1__INP_DIS)
/* LCD Common or Segment Drive */
#define HalfBridgeSW1_LCD_COM_SEG            (* (reg8 *) HalfBridgeSW1__LCD_COM_SEG)
/* Enable Segment LCD */
#define HalfBridgeSW1_LCD_EN                 (* (reg8 *) HalfBridgeSW1__LCD_EN)
/* Slew Rate Control */
#define HalfBridgeSW1_SLW                    (* (reg8 *) HalfBridgeSW1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HalfBridgeSW1_PRTDSI__CAPS_SEL       (* (reg8 *) HalfBridgeSW1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HalfBridgeSW1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HalfBridgeSW1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HalfBridgeSW1_PRTDSI__OE_SEL0        (* (reg8 *) HalfBridgeSW1__PRTDSI__OE_SEL0) 
#define HalfBridgeSW1_PRTDSI__OE_SEL1        (* (reg8 *) HalfBridgeSW1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HalfBridgeSW1_PRTDSI__OUT_SEL0       (* (reg8 *) HalfBridgeSW1__PRTDSI__OUT_SEL0) 
#define HalfBridgeSW1_PRTDSI__OUT_SEL1       (* (reg8 *) HalfBridgeSW1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HalfBridgeSW1_PRTDSI__SYNC_OUT       (* (reg8 *) HalfBridgeSW1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(HalfBridgeSW1__SIO_CFG)
    #define HalfBridgeSW1_SIO_HYST_EN        (* (reg8 *) HalfBridgeSW1__SIO_HYST_EN)
    #define HalfBridgeSW1_SIO_REG_HIFREQ     (* (reg8 *) HalfBridgeSW1__SIO_REG_HIFREQ)
    #define HalfBridgeSW1_SIO_CFG            (* (reg8 *) HalfBridgeSW1__SIO_CFG)
    #define HalfBridgeSW1_SIO_DIFF           (* (reg8 *) HalfBridgeSW1__SIO_DIFF)
#endif /* (HalfBridgeSW1__SIO_CFG) */

/* Interrupt Registers */
#if defined(HalfBridgeSW1__INTSTAT)
    #define HalfBridgeSW1_INTSTAT            (* (reg8 *) HalfBridgeSW1__INTSTAT)
    #define HalfBridgeSW1_SNAP               (* (reg8 *) HalfBridgeSW1__SNAP)
    
	#define HalfBridgeSW1_0_INTTYPE_REG 		(* (reg8 *) HalfBridgeSW1__0__INTTYPE)
#endif /* (HalfBridgeSW1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HalfBridgeSW1_H */


/* [] END OF FILE */
