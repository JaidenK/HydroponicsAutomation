/*******************************************************************************
* File Name: pHUpPump.h  
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

#if !defined(CY_PINS_pHUpPump_H) /* Pins pHUpPump_H */
#define CY_PINS_pHUpPump_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pHUpPump_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pHUpPump__PORT == 15 && ((pHUpPump__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pHUpPump_Write(uint8 value);
void    pHUpPump_SetDriveMode(uint8 mode);
uint8   pHUpPump_ReadDataReg(void);
uint8   pHUpPump_Read(void);
void    pHUpPump_SetInterruptMode(uint16 position, uint16 mode);
uint8   pHUpPump_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pHUpPump_SetDriveMode() function.
     *  @{
     */
        #define pHUpPump_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pHUpPump_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pHUpPump_DM_RES_UP          PIN_DM_RES_UP
        #define pHUpPump_DM_RES_DWN         PIN_DM_RES_DWN
        #define pHUpPump_DM_OD_LO           PIN_DM_OD_LO
        #define pHUpPump_DM_OD_HI           PIN_DM_OD_HI
        #define pHUpPump_DM_STRONG          PIN_DM_STRONG
        #define pHUpPump_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pHUpPump_MASK               pHUpPump__MASK
#define pHUpPump_SHIFT              pHUpPump__SHIFT
#define pHUpPump_WIDTH              1u

/* Interrupt constants */
#if defined(pHUpPump__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pHUpPump_SetInterruptMode() function.
     *  @{
     */
        #define pHUpPump_INTR_NONE      (uint16)(0x0000u)
        #define pHUpPump_INTR_RISING    (uint16)(0x0001u)
        #define pHUpPump_INTR_FALLING   (uint16)(0x0002u)
        #define pHUpPump_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pHUpPump_INTR_MASK      (0x01u) 
#endif /* (pHUpPump__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pHUpPump_PS                     (* (reg8 *) pHUpPump__PS)
/* Data Register */
#define pHUpPump_DR                     (* (reg8 *) pHUpPump__DR)
/* Port Number */
#define pHUpPump_PRT_NUM                (* (reg8 *) pHUpPump__PRT) 
/* Connect to Analog Globals */                                                  
#define pHUpPump_AG                     (* (reg8 *) pHUpPump__AG)                       
/* Analog MUX bux enable */
#define pHUpPump_AMUX                   (* (reg8 *) pHUpPump__AMUX) 
/* Bidirectional Enable */                                                        
#define pHUpPump_BIE                    (* (reg8 *) pHUpPump__BIE)
/* Bit-mask for Aliased Register Access */
#define pHUpPump_BIT_MASK               (* (reg8 *) pHUpPump__BIT_MASK)
/* Bypass Enable */
#define pHUpPump_BYP                    (* (reg8 *) pHUpPump__BYP)
/* Port wide control signals */                                                   
#define pHUpPump_CTL                    (* (reg8 *) pHUpPump__CTL)
/* Drive Modes */
#define pHUpPump_DM0                    (* (reg8 *) pHUpPump__DM0) 
#define pHUpPump_DM1                    (* (reg8 *) pHUpPump__DM1)
#define pHUpPump_DM2                    (* (reg8 *) pHUpPump__DM2) 
/* Input Buffer Disable Override */
#define pHUpPump_INP_DIS                (* (reg8 *) pHUpPump__INP_DIS)
/* LCD Common or Segment Drive */
#define pHUpPump_LCD_COM_SEG            (* (reg8 *) pHUpPump__LCD_COM_SEG)
/* Enable Segment LCD */
#define pHUpPump_LCD_EN                 (* (reg8 *) pHUpPump__LCD_EN)
/* Slew Rate Control */
#define pHUpPump_SLW                    (* (reg8 *) pHUpPump__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pHUpPump_PRTDSI__CAPS_SEL       (* (reg8 *) pHUpPump__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pHUpPump_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pHUpPump__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pHUpPump_PRTDSI__OE_SEL0        (* (reg8 *) pHUpPump__PRTDSI__OE_SEL0) 
#define pHUpPump_PRTDSI__OE_SEL1        (* (reg8 *) pHUpPump__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pHUpPump_PRTDSI__OUT_SEL0       (* (reg8 *) pHUpPump__PRTDSI__OUT_SEL0) 
#define pHUpPump_PRTDSI__OUT_SEL1       (* (reg8 *) pHUpPump__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pHUpPump_PRTDSI__SYNC_OUT       (* (reg8 *) pHUpPump__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pHUpPump__SIO_CFG)
    #define pHUpPump_SIO_HYST_EN        (* (reg8 *) pHUpPump__SIO_HYST_EN)
    #define pHUpPump_SIO_REG_HIFREQ     (* (reg8 *) pHUpPump__SIO_REG_HIFREQ)
    #define pHUpPump_SIO_CFG            (* (reg8 *) pHUpPump__SIO_CFG)
    #define pHUpPump_SIO_DIFF           (* (reg8 *) pHUpPump__SIO_DIFF)
#endif /* (pHUpPump__SIO_CFG) */

/* Interrupt Registers */
#if defined(pHUpPump__INTSTAT)
    #define pHUpPump_INTSTAT            (* (reg8 *) pHUpPump__INTSTAT)
    #define pHUpPump_SNAP               (* (reg8 *) pHUpPump__SNAP)
    
	#define pHUpPump_0_INTTYPE_REG 		(* (reg8 *) pHUpPump__0__INTTYPE)
#endif /* (pHUpPump__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pHUpPump_H */


/* [] END OF FILE */
