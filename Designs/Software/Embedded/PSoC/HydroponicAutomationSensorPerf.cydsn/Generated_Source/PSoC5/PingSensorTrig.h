/*******************************************************************************
* File Name: PingSensorTrig.h  
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

#if !defined(CY_PINS_PingSensorTrig_H) /* Pins PingSensorTrig_H */
#define CY_PINS_PingSensorTrig_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PingSensorTrig_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PingSensorTrig__PORT == 15 && ((PingSensorTrig__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PingSensorTrig_Write(uint8 value);
void    PingSensorTrig_SetDriveMode(uint8 mode);
uint8   PingSensorTrig_ReadDataReg(void);
uint8   PingSensorTrig_Read(void);
void    PingSensorTrig_SetInterruptMode(uint16 position, uint16 mode);
uint8   PingSensorTrig_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PingSensorTrig_SetDriveMode() function.
     *  @{
     */
        #define PingSensorTrig_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PingSensorTrig_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PingSensorTrig_DM_RES_UP          PIN_DM_RES_UP
        #define PingSensorTrig_DM_RES_DWN         PIN_DM_RES_DWN
        #define PingSensorTrig_DM_OD_LO           PIN_DM_OD_LO
        #define PingSensorTrig_DM_OD_HI           PIN_DM_OD_HI
        #define PingSensorTrig_DM_STRONG          PIN_DM_STRONG
        #define PingSensorTrig_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PingSensorTrig_MASK               PingSensorTrig__MASK
#define PingSensorTrig_SHIFT              PingSensorTrig__SHIFT
#define PingSensorTrig_WIDTH              1u

/* Interrupt constants */
#if defined(PingSensorTrig__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PingSensorTrig_SetInterruptMode() function.
     *  @{
     */
        #define PingSensorTrig_INTR_NONE      (uint16)(0x0000u)
        #define PingSensorTrig_INTR_RISING    (uint16)(0x0001u)
        #define PingSensorTrig_INTR_FALLING   (uint16)(0x0002u)
        #define PingSensorTrig_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PingSensorTrig_INTR_MASK      (0x01u) 
#endif /* (PingSensorTrig__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PingSensorTrig_PS                     (* (reg8 *) PingSensorTrig__PS)
/* Data Register */
#define PingSensorTrig_DR                     (* (reg8 *) PingSensorTrig__DR)
/* Port Number */
#define PingSensorTrig_PRT_NUM                (* (reg8 *) PingSensorTrig__PRT) 
/* Connect to Analog Globals */                                                  
#define PingSensorTrig_AG                     (* (reg8 *) PingSensorTrig__AG)                       
/* Analog MUX bux enable */
#define PingSensorTrig_AMUX                   (* (reg8 *) PingSensorTrig__AMUX) 
/* Bidirectional Enable */                                                        
#define PingSensorTrig_BIE                    (* (reg8 *) PingSensorTrig__BIE)
/* Bit-mask for Aliased Register Access */
#define PingSensorTrig_BIT_MASK               (* (reg8 *) PingSensorTrig__BIT_MASK)
/* Bypass Enable */
#define PingSensorTrig_BYP                    (* (reg8 *) PingSensorTrig__BYP)
/* Port wide control signals */                                                   
#define PingSensorTrig_CTL                    (* (reg8 *) PingSensorTrig__CTL)
/* Drive Modes */
#define PingSensorTrig_DM0                    (* (reg8 *) PingSensorTrig__DM0) 
#define PingSensorTrig_DM1                    (* (reg8 *) PingSensorTrig__DM1)
#define PingSensorTrig_DM2                    (* (reg8 *) PingSensorTrig__DM2) 
/* Input Buffer Disable Override */
#define PingSensorTrig_INP_DIS                (* (reg8 *) PingSensorTrig__INP_DIS)
/* LCD Common or Segment Drive */
#define PingSensorTrig_LCD_COM_SEG            (* (reg8 *) PingSensorTrig__LCD_COM_SEG)
/* Enable Segment LCD */
#define PingSensorTrig_LCD_EN                 (* (reg8 *) PingSensorTrig__LCD_EN)
/* Slew Rate Control */
#define PingSensorTrig_SLW                    (* (reg8 *) PingSensorTrig__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PingSensorTrig_PRTDSI__CAPS_SEL       (* (reg8 *) PingSensorTrig__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PingSensorTrig_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PingSensorTrig__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PingSensorTrig_PRTDSI__OE_SEL0        (* (reg8 *) PingSensorTrig__PRTDSI__OE_SEL0) 
#define PingSensorTrig_PRTDSI__OE_SEL1        (* (reg8 *) PingSensorTrig__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PingSensorTrig_PRTDSI__OUT_SEL0       (* (reg8 *) PingSensorTrig__PRTDSI__OUT_SEL0) 
#define PingSensorTrig_PRTDSI__OUT_SEL1       (* (reg8 *) PingSensorTrig__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PingSensorTrig_PRTDSI__SYNC_OUT       (* (reg8 *) PingSensorTrig__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PingSensorTrig__SIO_CFG)
    #define PingSensorTrig_SIO_HYST_EN        (* (reg8 *) PingSensorTrig__SIO_HYST_EN)
    #define PingSensorTrig_SIO_REG_HIFREQ     (* (reg8 *) PingSensorTrig__SIO_REG_HIFREQ)
    #define PingSensorTrig_SIO_CFG            (* (reg8 *) PingSensorTrig__SIO_CFG)
    #define PingSensorTrig_SIO_DIFF           (* (reg8 *) PingSensorTrig__SIO_DIFF)
#endif /* (PingSensorTrig__SIO_CFG) */

/* Interrupt Registers */
#if defined(PingSensorTrig__INTSTAT)
    #define PingSensorTrig_INTSTAT            (* (reg8 *) PingSensorTrig__INTSTAT)
    #define PingSensorTrig_SNAP               (* (reg8 *) PingSensorTrig__SNAP)
    
	#define PingSensorTrig_0_INTTYPE_REG 		(* (reg8 *) PingSensorTrig__0__INTTYPE)
#endif /* (PingSensorTrig__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PingSensorTrig_H */


/* [] END OF FILE */
