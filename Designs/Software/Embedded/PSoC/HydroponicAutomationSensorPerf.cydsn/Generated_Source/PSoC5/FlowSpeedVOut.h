/*******************************************************************************
* File Name: FlowSpeedVOut.h  
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

#if !defined(CY_PINS_FlowSpeedVOut_H) /* Pins FlowSpeedVOut_H */
#define CY_PINS_FlowSpeedVOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FlowSpeedVOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FlowSpeedVOut__PORT == 15 && ((FlowSpeedVOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FlowSpeedVOut_Write(uint8 value);
void    FlowSpeedVOut_SetDriveMode(uint8 mode);
uint8   FlowSpeedVOut_ReadDataReg(void);
uint8   FlowSpeedVOut_Read(void);
void    FlowSpeedVOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   FlowSpeedVOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FlowSpeedVOut_SetDriveMode() function.
     *  @{
     */
        #define FlowSpeedVOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FlowSpeedVOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FlowSpeedVOut_DM_RES_UP          PIN_DM_RES_UP
        #define FlowSpeedVOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define FlowSpeedVOut_DM_OD_LO           PIN_DM_OD_LO
        #define FlowSpeedVOut_DM_OD_HI           PIN_DM_OD_HI
        #define FlowSpeedVOut_DM_STRONG          PIN_DM_STRONG
        #define FlowSpeedVOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FlowSpeedVOut_MASK               FlowSpeedVOut__MASK
#define FlowSpeedVOut_SHIFT              FlowSpeedVOut__SHIFT
#define FlowSpeedVOut_WIDTH              1u

/* Interrupt constants */
#if defined(FlowSpeedVOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FlowSpeedVOut_SetInterruptMode() function.
     *  @{
     */
        #define FlowSpeedVOut_INTR_NONE      (uint16)(0x0000u)
        #define FlowSpeedVOut_INTR_RISING    (uint16)(0x0001u)
        #define FlowSpeedVOut_INTR_FALLING   (uint16)(0x0002u)
        #define FlowSpeedVOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FlowSpeedVOut_INTR_MASK      (0x01u) 
#endif /* (FlowSpeedVOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FlowSpeedVOut_PS                     (* (reg8 *) FlowSpeedVOut__PS)
/* Data Register */
#define FlowSpeedVOut_DR                     (* (reg8 *) FlowSpeedVOut__DR)
/* Port Number */
#define FlowSpeedVOut_PRT_NUM                (* (reg8 *) FlowSpeedVOut__PRT) 
/* Connect to Analog Globals */                                                  
#define FlowSpeedVOut_AG                     (* (reg8 *) FlowSpeedVOut__AG)                       
/* Analog MUX bux enable */
#define FlowSpeedVOut_AMUX                   (* (reg8 *) FlowSpeedVOut__AMUX) 
/* Bidirectional Enable */                                                        
#define FlowSpeedVOut_BIE                    (* (reg8 *) FlowSpeedVOut__BIE)
/* Bit-mask for Aliased Register Access */
#define FlowSpeedVOut_BIT_MASK               (* (reg8 *) FlowSpeedVOut__BIT_MASK)
/* Bypass Enable */
#define FlowSpeedVOut_BYP                    (* (reg8 *) FlowSpeedVOut__BYP)
/* Port wide control signals */                                                   
#define FlowSpeedVOut_CTL                    (* (reg8 *) FlowSpeedVOut__CTL)
/* Drive Modes */
#define FlowSpeedVOut_DM0                    (* (reg8 *) FlowSpeedVOut__DM0) 
#define FlowSpeedVOut_DM1                    (* (reg8 *) FlowSpeedVOut__DM1)
#define FlowSpeedVOut_DM2                    (* (reg8 *) FlowSpeedVOut__DM2) 
/* Input Buffer Disable Override */
#define FlowSpeedVOut_INP_DIS                (* (reg8 *) FlowSpeedVOut__INP_DIS)
/* LCD Common or Segment Drive */
#define FlowSpeedVOut_LCD_COM_SEG            (* (reg8 *) FlowSpeedVOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define FlowSpeedVOut_LCD_EN                 (* (reg8 *) FlowSpeedVOut__LCD_EN)
/* Slew Rate Control */
#define FlowSpeedVOut_SLW                    (* (reg8 *) FlowSpeedVOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FlowSpeedVOut_PRTDSI__CAPS_SEL       (* (reg8 *) FlowSpeedVOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FlowSpeedVOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FlowSpeedVOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FlowSpeedVOut_PRTDSI__OE_SEL0        (* (reg8 *) FlowSpeedVOut__PRTDSI__OE_SEL0) 
#define FlowSpeedVOut_PRTDSI__OE_SEL1        (* (reg8 *) FlowSpeedVOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FlowSpeedVOut_PRTDSI__OUT_SEL0       (* (reg8 *) FlowSpeedVOut__PRTDSI__OUT_SEL0) 
#define FlowSpeedVOut_PRTDSI__OUT_SEL1       (* (reg8 *) FlowSpeedVOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FlowSpeedVOut_PRTDSI__SYNC_OUT       (* (reg8 *) FlowSpeedVOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FlowSpeedVOut__SIO_CFG)
    #define FlowSpeedVOut_SIO_HYST_EN        (* (reg8 *) FlowSpeedVOut__SIO_HYST_EN)
    #define FlowSpeedVOut_SIO_REG_HIFREQ     (* (reg8 *) FlowSpeedVOut__SIO_REG_HIFREQ)
    #define FlowSpeedVOut_SIO_CFG            (* (reg8 *) FlowSpeedVOut__SIO_CFG)
    #define FlowSpeedVOut_SIO_DIFF           (* (reg8 *) FlowSpeedVOut__SIO_DIFF)
#endif /* (FlowSpeedVOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(FlowSpeedVOut__INTSTAT)
    #define FlowSpeedVOut_INTSTAT            (* (reg8 *) FlowSpeedVOut__INTSTAT)
    #define FlowSpeedVOut_SNAP               (* (reg8 *) FlowSpeedVOut__SNAP)
    
	#define FlowSpeedVOut_0_INTTYPE_REG 		(* (reg8 *) FlowSpeedVOut__0__INTTYPE)
#endif /* (FlowSpeedVOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FlowSpeedVOut_H */


/* [] END OF FILE */
