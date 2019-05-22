/*******************************************************************************
* File Name: HalfBridgeSW2.h  
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

#if !defined(CY_PINS_HalfBridgeSW2_H) /* Pins HalfBridgeSW2_H */
#define CY_PINS_HalfBridgeSW2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HalfBridgeSW2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HalfBridgeSW2__PORT == 15 && ((HalfBridgeSW2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    HalfBridgeSW2_Write(uint8 value);
void    HalfBridgeSW2_SetDriveMode(uint8 mode);
uint8   HalfBridgeSW2_ReadDataReg(void);
uint8   HalfBridgeSW2_Read(void);
void    HalfBridgeSW2_SetInterruptMode(uint16 position, uint16 mode);
uint8   HalfBridgeSW2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the HalfBridgeSW2_SetDriveMode() function.
     *  @{
     */
        #define HalfBridgeSW2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define HalfBridgeSW2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define HalfBridgeSW2_DM_RES_UP          PIN_DM_RES_UP
        #define HalfBridgeSW2_DM_RES_DWN         PIN_DM_RES_DWN
        #define HalfBridgeSW2_DM_OD_LO           PIN_DM_OD_LO
        #define HalfBridgeSW2_DM_OD_HI           PIN_DM_OD_HI
        #define HalfBridgeSW2_DM_STRONG          PIN_DM_STRONG
        #define HalfBridgeSW2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define HalfBridgeSW2_MASK               HalfBridgeSW2__MASK
#define HalfBridgeSW2_SHIFT              HalfBridgeSW2__SHIFT
#define HalfBridgeSW2_WIDTH              1u

/* Interrupt constants */
#if defined(HalfBridgeSW2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HalfBridgeSW2_SetInterruptMode() function.
     *  @{
     */
        #define HalfBridgeSW2_INTR_NONE      (uint16)(0x0000u)
        #define HalfBridgeSW2_INTR_RISING    (uint16)(0x0001u)
        #define HalfBridgeSW2_INTR_FALLING   (uint16)(0x0002u)
        #define HalfBridgeSW2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define HalfBridgeSW2_INTR_MASK      (0x01u) 
#endif /* (HalfBridgeSW2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HalfBridgeSW2_PS                     (* (reg8 *) HalfBridgeSW2__PS)
/* Data Register */
#define HalfBridgeSW2_DR                     (* (reg8 *) HalfBridgeSW2__DR)
/* Port Number */
#define HalfBridgeSW2_PRT_NUM                (* (reg8 *) HalfBridgeSW2__PRT) 
/* Connect to Analog Globals */                                                  
#define HalfBridgeSW2_AG                     (* (reg8 *) HalfBridgeSW2__AG)                       
/* Analog MUX bux enable */
#define HalfBridgeSW2_AMUX                   (* (reg8 *) HalfBridgeSW2__AMUX) 
/* Bidirectional Enable */                                                        
#define HalfBridgeSW2_BIE                    (* (reg8 *) HalfBridgeSW2__BIE)
/* Bit-mask for Aliased Register Access */
#define HalfBridgeSW2_BIT_MASK               (* (reg8 *) HalfBridgeSW2__BIT_MASK)
/* Bypass Enable */
#define HalfBridgeSW2_BYP                    (* (reg8 *) HalfBridgeSW2__BYP)
/* Port wide control signals */                                                   
#define HalfBridgeSW2_CTL                    (* (reg8 *) HalfBridgeSW2__CTL)
/* Drive Modes */
#define HalfBridgeSW2_DM0                    (* (reg8 *) HalfBridgeSW2__DM0) 
#define HalfBridgeSW2_DM1                    (* (reg8 *) HalfBridgeSW2__DM1)
#define HalfBridgeSW2_DM2                    (* (reg8 *) HalfBridgeSW2__DM2) 
/* Input Buffer Disable Override */
#define HalfBridgeSW2_INP_DIS                (* (reg8 *) HalfBridgeSW2__INP_DIS)
/* LCD Common or Segment Drive */
#define HalfBridgeSW2_LCD_COM_SEG            (* (reg8 *) HalfBridgeSW2__LCD_COM_SEG)
/* Enable Segment LCD */
#define HalfBridgeSW2_LCD_EN                 (* (reg8 *) HalfBridgeSW2__LCD_EN)
/* Slew Rate Control */
#define HalfBridgeSW2_SLW                    (* (reg8 *) HalfBridgeSW2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HalfBridgeSW2_PRTDSI__CAPS_SEL       (* (reg8 *) HalfBridgeSW2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HalfBridgeSW2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HalfBridgeSW2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HalfBridgeSW2_PRTDSI__OE_SEL0        (* (reg8 *) HalfBridgeSW2__PRTDSI__OE_SEL0) 
#define HalfBridgeSW2_PRTDSI__OE_SEL1        (* (reg8 *) HalfBridgeSW2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HalfBridgeSW2_PRTDSI__OUT_SEL0       (* (reg8 *) HalfBridgeSW2__PRTDSI__OUT_SEL0) 
#define HalfBridgeSW2_PRTDSI__OUT_SEL1       (* (reg8 *) HalfBridgeSW2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HalfBridgeSW2_PRTDSI__SYNC_OUT       (* (reg8 *) HalfBridgeSW2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(HalfBridgeSW2__SIO_CFG)
    #define HalfBridgeSW2_SIO_HYST_EN        (* (reg8 *) HalfBridgeSW2__SIO_HYST_EN)
    #define HalfBridgeSW2_SIO_REG_HIFREQ     (* (reg8 *) HalfBridgeSW2__SIO_REG_HIFREQ)
    #define HalfBridgeSW2_SIO_CFG            (* (reg8 *) HalfBridgeSW2__SIO_CFG)
    #define HalfBridgeSW2_SIO_DIFF           (* (reg8 *) HalfBridgeSW2__SIO_DIFF)
#endif /* (HalfBridgeSW2__SIO_CFG) */

/* Interrupt Registers */
#if defined(HalfBridgeSW2__INTSTAT)
    #define HalfBridgeSW2_INTSTAT            (* (reg8 *) HalfBridgeSW2__INTSTAT)
    #define HalfBridgeSW2_SNAP               (* (reg8 *) HalfBridgeSW2__SNAP)
    
	#define HalfBridgeSW2_0_INTTYPE_REG 		(* (reg8 *) HalfBridgeSW2__0__INTTYPE)
#endif /* (HalfBridgeSW2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HalfBridgeSW2_H */


/* [] END OF FILE */
