/*******************************************************************************
* File Name: FlowSensorSig.h  
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

#if !defined(CY_PINS_FlowSensorSig_H) /* Pins FlowSensorSig_H */
#define CY_PINS_FlowSensorSig_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FlowSensorSig_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FlowSensorSig__PORT == 15 && ((FlowSensorSig__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FlowSensorSig_Write(uint8 value);
void    FlowSensorSig_SetDriveMode(uint8 mode);
uint8   FlowSensorSig_ReadDataReg(void);
uint8   FlowSensorSig_Read(void);
void    FlowSensorSig_SetInterruptMode(uint16 position, uint16 mode);
uint8   FlowSensorSig_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FlowSensorSig_SetDriveMode() function.
     *  @{
     */
        #define FlowSensorSig_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FlowSensorSig_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FlowSensorSig_DM_RES_UP          PIN_DM_RES_UP
        #define FlowSensorSig_DM_RES_DWN         PIN_DM_RES_DWN
        #define FlowSensorSig_DM_OD_LO           PIN_DM_OD_LO
        #define FlowSensorSig_DM_OD_HI           PIN_DM_OD_HI
        #define FlowSensorSig_DM_STRONG          PIN_DM_STRONG
        #define FlowSensorSig_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FlowSensorSig_MASK               FlowSensorSig__MASK
#define FlowSensorSig_SHIFT              FlowSensorSig__SHIFT
#define FlowSensorSig_WIDTH              1u

/* Interrupt constants */
#if defined(FlowSensorSig__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FlowSensorSig_SetInterruptMode() function.
     *  @{
     */
        #define FlowSensorSig_INTR_NONE      (uint16)(0x0000u)
        #define FlowSensorSig_INTR_RISING    (uint16)(0x0001u)
        #define FlowSensorSig_INTR_FALLING   (uint16)(0x0002u)
        #define FlowSensorSig_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FlowSensorSig_INTR_MASK      (0x01u) 
#endif /* (FlowSensorSig__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FlowSensorSig_PS                     (* (reg8 *) FlowSensorSig__PS)
/* Data Register */
#define FlowSensorSig_DR                     (* (reg8 *) FlowSensorSig__DR)
/* Port Number */
#define FlowSensorSig_PRT_NUM                (* (reg8 *) FlowSensorSig__PRT) 
/* Connect to Analog Globals */                                                  
#define FlowSensorSig_AG                     (* (reg8 *) FlowSensorSig__AG)                       
/* Analog MUX bux enable */
#define FlowSensorSig_AMUX                   (* (reg8 *) FlowSensorSig__AMUX) 
/* Bidirectional Enable */                                                        
#define FlowSensorSig_BIE                    (* (reg8 *) FlowSensorSig__BIE)
/* Bit-mask for Aliased Register Access */
#define FlowSensorSig_BIT_MASK               (* (reg8 *) FlowSensorSig__BIT_MASK)
/* Bypass Enable */
#define FlowSensorSig_BYP                    (* (reg8 *) FlowSensorSig__BYP)
/* Port wide control signals */                                                   
#define FlowSensorSig_CTL                    (* (reg8 *) FlowSensorSig__CTL)
/* Drive Modes */
#define FlowSensorSig_DM0                    (* (reg8 *) FlowSensorSig__DM0) 
#define FlowSensorSig_DM1                    (* (reg8 *) FlowSensorSig__DM1)
#define FlowSensorSig_DM2                    (* (reg8 *) FlowSensorSig__DM2) 
/* Input Buffer Disable Override */
#define FlowSensorSig_INP_DIS                (* (reg8 *) FlowSensorSig__INP_DIS)
/* LCD Common or Segment Drive */
#define FlowSensorSig_LCD_COM_SEG            (* (reg8 *) FlowSensorSig__LCD_COM_SEG)
/* Enable Segment LCD */
#define FlowSensorSig_LCD_EN                 (* (reg8 *) FlowSensorSig__LCD_EN)
/* Slew Rate Control */
#define FlowSensorSig_SLW                    (* (reg8 *) FlowSensorSig__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FlowSensorSig_PRTDSI__CAPS_SEL       (* (reg8 *) FlowSensorSig__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FlowSensorSig_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FlowSensorSig__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FlowSensorSig_PRTDSI__OE_SEL0        (* (reg8 *) FlowSensorSig__PRTDSI__OE_SEL0) 
#define FlowSensorSig_PRTDSI__OE_SEL1        (* (reg8 *) FlowSensorSig__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FlowSensorSig_PRTDSI__OUT_SEL0       (* (reg8 *) FlowSensorSig__PRTDSI__OUT_SEL0) 
#define FlowSensorSig_PRTDSI__OUT_SEL1       (* (reg8 *) FlowSensorSig__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FlowSensorSig_PRTDSI__SYNC_OUT       (* (reg8 *) FlowSensorSig__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FlowSensorSig__SIO_CFG)
    #define FlowSensorSig_SIO_HYST_EN        (* (reg8 *) FlowSensorSig__SIO_HYST_EN)
    #define FlowSensorSig_SIO_REG_HIFREQ     (* (reg8 *) FlowSensorSig__SIO_REG_HIFREQ)
    #define FlowSensorSig_SIO_CFG            (* (reg8 *) FlowSensorSig__SIO_CFG)
    #define FlowSensorSig_SIO_DIFF           (* (reg8 *) FlowSensorSig__SIO_DIFF)
#endif /* (FlowSensorSig__SIO_CFG) */

/* Interrupt Registers */
#if defined(FlowSensorSig__INTSTAT)
    #define FlowSensorSig_INTSTAT            (* (reg8 *) FlowSensorSig__INTSTAT)
    #define FlowSensorSig_SNAP               (* (reg8 *) FlowSensorSig__SNAP)
    
	#define FlowSensorSig_0_INTTYPE_REG 		(* (reg8 *) FlowSensorSig__0__INTTYPE)
#endif /* (FlowSensorSig__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FlowSensorSig_H */


/* [] END OF FILE */
