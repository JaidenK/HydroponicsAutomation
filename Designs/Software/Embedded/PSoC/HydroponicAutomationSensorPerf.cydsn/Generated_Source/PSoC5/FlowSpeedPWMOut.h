/*******************************************************************************
* File Name: FlowSpeedPWMOut.h  
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

#if !defined(CY_PINS_FlowSpeedPWMOut_H) /* Pins FlowSpeedPWMOut_H */
#define CY_PINS_FlowSpeedPWMOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FlowSpeedPWMOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FlowSpeedPWMOut__PORT == 15 && ((FlowSpeedPWMOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FlowSpeedPWMOut_Write(uint8 value);
void    FlowSpeedPWMOut_SetDriveMode(uint8 mode);
uint8   FlowSpeedPWMOut_ReadDataReg(void);
uint8   FlowSpeedPWMOut_Read(void);
void    FlowSpeedPWMOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   FlowSpeedPWMOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FlowSpeedPWMOut_SetDriveMode() function.
     *  @{
     */
        #define FlowSpeedPWMOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FlowSpeedPWMOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FlowSpeedPWMOut_DM_RES_UP          PIN_DM_RES_UP
        #define FlowSpeedPWMOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define FlowSpeedPWMOut_DM_OD_LO           PIN_DM_OD_LO
        #define FlowSpeedPWMOut_DM_OD_HI           PIN_DM_OD_HI
        #define FlowSpeedPWMOut_DM_STRONG          PIN_DM_STRONG
        #define FlowSpeedPWMOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FlowSpeedPWMOut_MASK               FlowSpeedPWMOut__MASK
#define FlowSpeedPWMOut_SHIFT              FlowSpeedPWMOut__SHIFT
#define FlowSpeedPWMOut_WIDTH              1u

/* Interrupt constants */
#if defined(FlowSpeedPWMOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FlowSpeedPWMOut_SetInterruptMode() function.
     *  @{
     */
        #define FlowSpeedPWMOut_INTR_NONE      (uint16)(0x0000u)
        #define FlowSpeedPWMOut_INTR_RISING    (uint16)(0x0001u)
        #define FlowSpeedPWMOut_INTR_FALLING   (uint16)(0x0002u)
        #define FlowSpeedPWMOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FlowSpeedPWMOut_INTR_MASK      (0x01u) 
#endif /* (FlowSpeedPWMOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FlowSpeedPWMOut_PS                     (* (reg8 *) FlowSpeedPWMOut__PS)
/* Data Register */
#define FlowSpeedPWMOut_DR                     (* (reg8 *) FlowSpeedPWMOut__DR)
/* Port Number */
#define FlowSpeedPWMOut_PRT_NUM                (* (reg8 *) FlowSpeedPWMOut__PRT) 
/* Connect to Analog Globals */                                                  
#define FlowSpeedPWMOut_AG                     (* (reg8 *) FlowSpeedPWMOut__AG)                       
/* Analog MUX bux enable */
#define FlowSpeedPWMOut_AMUX                   (* (reg8 *) FlowSpeedPWMOut__AMUX) 
/* Bidirectional Enable */                                                        
#define FlowSpeedPWMOut_BIE                    (* (reg8 *) FlowSpeedPWMOut__BIE)
/* Bit-mask for Aliased Register Access */
#define FlowSpeedPWMOut_BIT_MASK               (* (reg8 *) FlowSpeedPWMOut__BIT_MASK)
/* Bypass Enable */
#define FlowSpeedPWMOut_BYP                    (* (reg8 *) FlowSpeedPWMOut__BYP)
/* Port wide control signals */                                                   
#define FlowSpeedPWMOut_CTL                    (* (reg8 *) FlowSpeedPWMOut__CTL)
/* Drive Modes */
#define FlowSpeedPWMOut_DM0                    (* (reg8 *) FlowSpeedPWMOut__DM0) 
#define FlowSpeedPWMOut_DM1                    (* (reg8 *) FlowSpeedPWMOut__DM1)
#define FlowSpeedPWMOut_DM2                    (* (reg8 *) FlowSpeedPWMOut__DM2) 
/* Input Buffer Disable Override */
#define FlowSpeedPWMOut_INP_DIS                (* (reg8 *) FlowSpeedPWMOut__INP_DIS)
/* LCD Common or Segment Drive */
#define FlowSpeedPWMOut_LCD_COM_SEG            (* (reg8 *) FlowSpeedPWMOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define FlowSpeedPWMOut_LCD_EN                 (* (reg8 *) FlowSpeedPWMOut__LCD_EN)
/* Slew Rate Control */
#define FlowSpeedPWMOut_SLW                    (* (reg8 *) FlowSpeedPWMOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FlowSpeedPWMOut_PRTDSI__CAPS_SEL       (* (reg8 *) FlowSpeedPWMOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FlowSpeedPWMOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FlowSpeedPWMOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FlowSpeedPWMOut_PRTDSI__OE_SEL0        (* (reg8 *) FlowSpeedPWMOut__PRTDSI__OE_SEL0) 
#define FlowSpeedPWMOut_PRTDSI__OE_SEL1        (* (reg8 *) FlowSpeedPWMOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FlowSpeedPWMOut_PRTDSI__OUT_SEL0       (* (reg8 *) FlowSpeedPWMOut__PRTDSI__OUT_SEL0) 
#define FlowSpeedPWMOut_PRTDSI__OUT_SEL1       (* (reg8 *) FlowSpeedPWMOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FlowSpeedPWMOut_PRTDSI__SYNC_OUT       (* (reg8 *) FlowSpeedPWMOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FlowSpeedPWMOut__SIO_CFG)
    #define FlowSpeedPWMOut_SIO_HYST_EN        (* (reg8 *) FlowSpeedPWMOut__SIO_HYST_EN)
    #define FlowSpeedPWMOut_SIO_REG_HIFREQ     (* (reg8 *) FlowSpeedPWMOut__SIO_REG_HIFREQ)
    #define FlowSpeedPWMOut_SIO_CFG            (* (reg8 *) FlowSpeedPWMOut__SIO_CFG)
    #define FlowSpeedPWMOut_SIO_DIFF           (* (reg8 *) FlowSpeedPWMOut__SIO_DIFF)
#endif /* (FlowSpeedPWMOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(FlowSpeedPWMOut__INTSTAT)
    #define FlowSpeedPWMOut_INTSTAT            (* (reg8 *) FlowSpeedPWMOut__INTSTAT)
    #define FlowSpeedPWMOut_SNAP               (* (reg8 *) FlowSpeedPWMOut__SNAP)
    
	#define FlowSpeedPWMOut_0_INTTYPE_REG 		(* (reg8 *) FlowSpeedPWMOut__0__INTTYPE)
#endif /* (FlowSpeedPWMOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FlowSpeedPWMOut_H */


/* [] END OF FILE */
