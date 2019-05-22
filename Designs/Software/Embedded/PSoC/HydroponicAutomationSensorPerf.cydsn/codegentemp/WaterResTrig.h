/*******************************************************************************
* File Name: WaterResTrig.h  
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

#if !defined(CY_PINS_WaterResTrig_H) /* Pins WaterResTrig_H */
#define CY_PINS_WaterResTrig_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WaterResTrig_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 WaterResTrig__PORT == 15 && ((WaterResTrig__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    WaterResTrig_Write(uint8 value);
void    WaterResTrig_SetDriveMode(uint8 mode);
uint8   WaterResTrig_ReadDataReg(void);
uint8   WaterResTrig_Read(void);
void    WaterResTrig_SetInterruptMode(uint16 position, uint16 mode);
uint8   WaterResTrig_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the WaterResTrig_SetDriveMode() function.
     *  @{
     */
        #define WaterResTrig_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define WaterResTrig_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define WaterResTrig_DM_RES_UP          PIN_DM_RES_UP
        #define WaterResTrig_DM_RES_DWN         PIN_DM_RES_DWN
        #define WaterResTrig_DM_OD_LO           PIN_DM_OD_LO
        #define WaterResTrig_DM_OD_HI           PIN_DM_OD_HI
        #define WaterResTrig_DM_STRONG          PIN_DM_STRONG
        #define WaterResTrig_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define WaterResTrig_MASK               WaterResTrig__MASK
#define WaterResTrig_SHIFT              WaterResTrig__SHIFT
#define WaterResTrig_WIDTH              1u

/* Interrupt constants */
#if defined(WaterResTrig__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WaterResTrig_SetInterruptMode() function.
     *  @{
     */
        #define WaterResTrig_INTR_NONE      (uint16)(0x0000u)
        #define WaterResTrig_INTR_RISING    (uint16)(0x0001u)
        #define WaterResTrig_INTR_FALLING   (uint16)(0x0002u)
        #define WaterResTrig_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define WaterResTrig_INTR_MASK      (0x01u) 
#endif /* (WaterResTrig__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WaterResTrig_PS                     (* (reg8 *) WaterResTrig__PS)
/* Data Register */
#define WaterResTrig_DR                     (* (reg8 *) WaterResTrig__DR)
/* Port Number */
#define WaterResTrig_PRT_NUM                (* (reg8 *) WaterResTrig__PRT) 
/* Connect to Analog Globals */                                                  
#define WaterResTrig_AG                     (* (reg8 *) WaterResTrig__AG)                       
/* Analog MUX bux enable */
#define WaterResTrig_AMUX                   (* (reg8 *) WaterResTrig__AMUX) 
/* Bidirectional Enable */                                                        
#define WaterResTrig_BIE                    (* (reg8 *) WaterResTrig__BIE)
/* Bit-mask for Aliased Register Access */
#define WaterResTrig_BIT_MASK               (* (reg8 *) WaterResTrig__BIT_MASK)
/* Bypass Enable */
#define WaterResTrig_BYP                    (* (reg8 *) WaterResTrig__BYP)
/* Port wide control signals */                                                   
#define WaterResTrig_CTL                    (* (reg8 *) WaterResTrig__CTL)
/* Drive Modes */
#define WaterResTrig_DM0                    (* (reg8 *) WaterResTrig__DM0) 
#define WaterResTrig_DM1                    (* (reg8 *) WaterResTrig__DM1)
#define WaterResTrig_DM2                    (* (reg8 *) WaterResTrig__DM2) 
/* Input Buffer Disable Override */
#define WaterResTrig_INP_DIS                (* (reg8 *) WaterResTrig__INP_DIS)
/* LCD Common or Segment Drive */
#define WaterResTrig_LCD_COM_SEG            (* (reg8 *) WaterResTrig__LCD_COM_SEG)
/* Enable Segment LCD */
#define WaterResTrig_LCD_EN                 (* (reg8 *) WaterResTrig__LCD_EN)
/* Slew Rate Control */
#define WaterResTrig_SLW                    (* (reg8 *) WaterResTrig__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WaterResTrig_PRTDSI__CAPS_SEL       (* (reg8 *) WaterResTrig__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WaterResTrig_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WaterResTrig__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WaterResTrig_PRTDSI__OE_SEL0        (* (reg8 *) WaterResTrig__PRTDSI__OE_SEL0) 
#define WaterResTrig_PRTDSI__OE_SEL1        (* (reg8 *) WaterResTrig__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WaterResTrig_PRTDSI__OUT_SEL0       (* (reg8 *) WaterResTrig__PRTDSI__OUT_SEL0) 
#define WaterResTrig_PRTDSI__OUT_SEL1       (* (reg8 *) WaterResTrig__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WaterResTrig_PRTDSI__SYNC_OUT       (* (reg8 *) WaterResTrig__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(WaterResTrig__SIO_CFG)
    #define WaterResTrig_SIO_HYST_EN        (* (reg8 *) WaterResTrig__SIO_HYST_EN)
    #define WaterResTrig_SIO_REG_HIFREQ     (* (reg8 *) WaterResTrig__SIO_REG_HIFREQ)
    #define WaterResTrig_SIO_CFG            (* (reg8 *) WaterResTrig__SIO_CFG)
    #define WaterResTrig_SIO_DIFF           (* (reg8 *) WaterResTrig__SIO_DIFF)
#endif /* (WaterResTrig__SIO_CFG) */

/* Interrupt Registers */
#if defined(WaterResTrig__INTSTAT)
    #define WaterResTrig_INTSTAT            (* (reg8 *) WaterResTrig__INTSTAT)
    #define WaterResTrig_SNAP               (* (reg8 *) WaterResTrig__SNAP)
    
	#define WaterResTrig_0_INTTYPE_REG 		(* (reg8 *) WaterResTrig__0__INTTYPE)
#endif /* (WaterResTrig__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_WaterResTrig_H */


/* [] END OF FILE */
