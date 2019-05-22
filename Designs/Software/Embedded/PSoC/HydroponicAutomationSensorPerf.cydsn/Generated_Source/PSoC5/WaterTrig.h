/*******************************************************************************
* File Name: WaterTrig.h  
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

#if !defined(CY_PINS_WaterTrig_H) /* Pins WaterTrig_H */
#define CY_PINS_WaterTrig_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WaterTrig_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 WaterTrig__PORT == 15 && ((WaterTrig__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    WaterTrig_Write(uint8 value);
void    WaterTrig_SetDriveMode(uint8 mode);
uint8   WaterTrig_ReadDataReg(void);
uint8   WaterTrig_Read(void);
void    WaterTrig_SetInterruptMode(uint16 position, uint16 mode);
uint8   WaterTrig_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the WaterTrig_SetDriveMode() function.
     *  @{
     */
        #define WaterTrig_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define WaterTrig_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define WaterTrig_DM_RES_UP          PIN_DM_RES_UP
        #define WaterTrig_DM_RES_DWN         PIN_DM_RES_DWN
        #define WaterTrig_DM_OD_LO           PIN_DM_OD_LO
        #define WaterTrig_DM_OD_HI           PIN_DM_OD_HI
        #define WaterTrig_DM_STRONG          PIN_DM_STRONG
        #define WaterTrig_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define WaterTrig_MASK               WaterTrig__MASK
#define WaterTrig_SHIFT              WaterTrig__SHIFT
#define WaterTrig_WIDTH              1u

/* Interrupt constants */
#if defined(WaterTrig__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WaterTrig_SetInterruptMode() function.
     *  @{
     */
        #define WaterTrig_INTR_NONE      (uint16)(0x0000u)
        #define WaterTrig_INTR_RISING    (uint16)(0x0001u)
        #define WaterTrig_INTR_FALLING   (uint16)(0x0002u)
        #define WaterTrig_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define WaterTrig_INTR_MASK      (0x01u) 
#endif /* (WaterTrig__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WaterTrig_PS                     (* (reg8 *) WaterTrig__PS)
/* Data Register */
#define WaterTrig_DR                     (* (reg8 *) WaterTrig__DR)
/* Port Number */
#define WaterTrig_PRT_NUM                (* (reg8 *) WaterTrig__PRT) 
/* Connect to Analog Globals */                                                  
#define WaterTrig_AG                     (* (reg8 *) WaterTrig__AG)                       
/* Analog MUX bux enable */
#define WaterTrig_AMUX                   (* (reg8 *) WaterTrig__AMUX) 
/* Bidirectional Enable */                                                        
#define WaterTrig_BIE                    (* (reg8 *) WaterTrig__BIE)
/* Bit-mask for Aliased Register Access */
#define WaterTrig_BIT_MASK               (* (reg8 *) WaterTrig__BIT_MASK)
/* Bypass Enable */
#define WaterTrig_BYP                    (* (reg8 *) WaterTrig__BYP)
/* Port wide control signals */                                                   
#define WaterTrig_CTL                    (* (reg8 *) WaterTrig__CTL)
/* Drive Modes */
#define WaterTrig_DM0                    (* (reg8 *) WaterTrig__DM0) 
#define WaterTrig_DM1                    (* (reg8 *) WaterTrig__DM1)
#define WaterTrig_DM2                    (* (reg8 *) WaterTrig__DM2) 
/* Input Buffer Disable Override */
#define WaterTrig_INP_DIS                (* (reg8 *) WaterTrig__INP_DIS)
/* LCD Common or Segment Drive */
#define WaterTrig_LCD_COM_SEG            (* (reg8 *) WaterTrig__LCD_COM_SEG)
/* Enable Segment LCD */
#define WaterTrig_LCD_EN                 (* (reg8 *) WaterTrig__LCD_EN)
/* Slew Rate Control */
#define WaterTrig_SLW                    (* (reg8 *) WaterTrig__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WaterTrig_PRTDSI__CAPS_SEL       (* (reg8 *) WaterTrig__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WaterTrig_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WaterTrig__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WaterTrig_PRTDSI__OE_SEL0        (* (reg8 *) WaterTrig__PRTDSI__OE_SEL0) 
#define WaterTrig_PRTDSI__OE_SEL1        (* (reg8 *) WaterTrig__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WaterTrig_PRTDSI__OUT_SEL0       (* (reg8 *) WaterTrig__PRTDSI__OUT_SEL0) 
#define WaterTrig_PRTDSI__OUT_SEL1       (* (reg8 *) WaterTrig__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WaterTrig_PRTDSI__SYNC_OUT       (* (reg8 *) WaterTrig__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(WaterTrig__SIO_CFG)
    #define WaterTrig_SIO_HYST_EN        (* (reg8 *) WaterTrig__SIO_HYST_EN)
    #define WaterTrig_SIO_REG_HIFREQ     (* (reg8 *) WaterTrig__SIO_REG_HIFREQ)
    #define WaterTrig_SIO_CFG            (* (reg8 *) WaterTrig__SIO_CFG)
    #define WaterTrig_SIO_DIFF           (* (reg8 *) WaterTrig__SIO_DIFF)
#endif /* (WaterTrig__SIO_CFG) */

/* Interrupt Registers */
#if defined(WaterTrig__INTSTAT)
    #define WaterTrig_INTSTAT            (* (reg8 *) WaterTrig__INTSTAT)
    #define WaterTrig_SNAP               (* (reg8 *) WaterTrig__SNAP)
    
	#define WaterTrig_0_INTTYPE_REG 		(* (reg8 *) WaterTrig__0__INTTYPE)
#endif /* (WaterTrig__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_WaterTrig_H */


/* [] END OF FILE */
