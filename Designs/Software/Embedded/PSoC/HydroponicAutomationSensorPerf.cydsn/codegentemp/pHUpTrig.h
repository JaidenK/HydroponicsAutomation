/*******************************************************************************
* File Name: pHUpTrig.h  
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

#if !defined(CY_PINS_pHUpTrig_H) /* Pins pHUpTrig_H */
#define CY_PINS_pHUpTrig_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pHUpTrig_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pHUpTrig__PORT == 15 && ((pHUpTrig__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pHUpTrig_Write(uint8 value);
void    pHUpTrig_SetDriveMode(uint8 mode);
uint8   pHUpTrig_ReadDataReg(void);
uint8   pHUpTrig_Read(void);
void    pHUpTrig_SetInterruptMode(uint16 position, uint16 mode);
uint8   pHUpTrig_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pHUpTrig_SetDriveMode() function.
     *  @{
     */
        #define pHUpTrig_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pHUpTrig_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pHUpTrig_DM_RES_UP          PIN_DM_RES_UP
        #define pHUpTrig_DM_RES_DWN         PIN_DM_RES_DWN
        #define pHUpTrig_DM_OD_LO           PIN_DM_OD_LO
        #define pHUpTrig_DM_OD_HI           PIN_DM_OD_HI
        #define pHUpTrig_DM_STRONG          PIN_DM_STRONG
        #define pHUpTrig_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pHUpTrig_MASK               pHUpTrig__MASK
#define pHUpTrig_SHIFT              pHUpTrig__SHIFT
#define pHUpTrig_WIDTH              1u

/* Interrupt constants */
#if defined(pHUpTrig__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pHUpTrig_SetInterruptMode() function.
     *  @{
     */
        #define pHUpTrig_INTR_NONE      (uint16)(0x0000u)
        #define pHUpTrig_INTR_RISING    (uint16)(0x0001u)
        #define pHUpTrig_INTR_FALLING   (uint16)(0x0002u)
        #define pHUpTrig_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pHUpTrig_INTR_MASK      (0x01u) 
#endif /* (pHUpTrig__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pHUpTrig_PS                     (* (reg8 *) pHUpTrig__PS)
/* Data Register */
#define pHUpTrig_DR                     (* (reg8 *) pHUpTrig__DR)
/* Port Number */
#define pHUpTrig_PRT_NUM                (* (reg8 *) pHUpTrig__PRT) 
/* Connect to Analog Globals */                                                  
#define pHUpTrig_AG                     (* (reg8 *) pHUpTrig__AG)                       
/* Analog MUX bux enable */
#define pHUpTrig_AMUX                   (* (reg8 *) pHUpTrig__AMUX) 
/* Bidirectional Enable */                                                        
#define pHUpTrig_BIE                    (* (reg8 *) pHUpTrig__BIE)
/* Bit-mask for Aliased Register Access */
#define pHUpTrig_BIT_MASK               (* (reg8 *) pHUpTrig__BIT_MASK)
/* Bypass Enable */
#define pHUpTrig_BYP                    (* (reg8 *) pHUpTrig__BYP)
/* Port wide control signals */                                                   
#define pHUpTrig_CTL                    (* (reg8 *) pHUpTrig__CTL)
/* Drive Modes */
#define pHUpTrig_DM0                    (* (reg8 *) pHUpTrig__DM0) 
#define pHUpTrig_DM1                    (* (reg8 *) pHUpTrig__DM1)
#define pHUpTrig_DM2                    (* (reg8 *) pHUpTrig__DM2) 
/* Input Buffer Disable Override */
#define pHUpTrig_INP_DIS                (* (reg8 *) pHUpTrig__INP_DIS)
/* LCD Common or Segment Drive */
#define pHUpTrig_LCD_COM_SEG            (* (reg8 *) pHUpTrig__LCD_COM_SEG)
/* Enable Segment LCD */
#define pHUpTrig_LCD_EN                 (* (reg8 *) pHUpTrig__LCD_EN)
/* Slew Rate Control */
#define pHUpTrig_SLW                    (* (reg8 *) pHUpTrig__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pHUpTrig_PRTDSI__CAPS_SEL       (* (reg8 *) pHUpTrig__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pHUpTrig_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pHUpTrig__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pHUpTrig_PRTDSI__OE_SEL0        (* (reg8 *) pHUpTrig__PRTDSI__OE_SEL0) 
#define pHUpTrig_PRTDSI__OE_SEL1        (* (reg8 *) pHUpTrig__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pHUpTrig_PRTDSI__OUT_SEL0       (* (reg8 *) pHUpTrig__PRTDSI__OUT_SEL0) 
#define pHUpTrig_PRTDSI__OUT_SEL1       (* (reg8 *) pHUpTrig__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pHUpTrig_PRTDSI__SYNC_OUT       (* (reg8 *) pHUpTrig__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pHUpTrig__SIO_CFG)
    #define pHUpTrig_SIO_HYST_EN        (* (reg8 *) pHUpTrig__SIO_HYST_EN)
    #define pHUpTrig_SIO_REG_HIFREQ     (* (reg8 *) pHUpTrig__SIO_REG_HIFREQ)
    #define pHUpTrig_SIO_CFG            (* (reg8 *) pHUpTrig__SIO_CFG)
    #define pHUpTrig_SIO_DIFF           (* (reg8 *) pHUpTrig__SIO_DIFF)
#endif /* (pHUpTrig__SIO_CFG) */

/* Interrupt Registers */
#if defined(pHUpTrig__INTSTAT)
    #define pHUpTrig_INTSTAT            (* (reg8 *) pHUpTrig__INTSTAT)
    #define pHUpTrig_SNAP               (* (reg8 *) pHUpTrig__SNAP)
    
	#define pHUpTrig_0_INTTYPE_REG 		(* (reg8 *) pHUpTrig__0__INTTYPE)
#endif /* (pHUpTrig__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pHUpTrig_H */


/* [] END OF FILE */
