/*******************************************************************************
* File Name: pHDownPump.h  
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

#if !defined(CY_PINS_pHDownPump_H) /* Pins pHDownPump_H */
#define CY_PINS_pHDownPump_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pHDownPump_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pHDownPump__PORT == 15 && ((pHDownPump__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pHDownPump_Write(uint8 value);
void    pHDownPump_SetDriveMode(uint8 mode);
uint8   pHDownPump_ReadDataReg(void);
uint8   pHDownPump_Read(void);
void    pHDownPump_SetInterruptMode(uint16 position, uint16 mode);
uint8   pHDownPump_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pHDownPump_SetDriveMode() function.
     *  @{
     */
        #define pHDownPump_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pHDownPump_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pHDownPump_DM_RES_UP          PIN_DM_RES_UP
        #define pHDownPump_DM_RES_DWN         PIN_DM_RES_DWN
        #define pHDownPump_DM_OD_LO           PIN_DM_OD_LO
        #define pHDownPump_DM_OD_HI           PIN_DM_OD_HI
        #define pHDownPump_DM_STRONG          PIN_DM_STRONG
        #define pHDownPump_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pHDownPump_MASK               pHDownPump__MASK
#define pHDownPump_SHIFT              pHDownPump__SHIFT
#define pHDownPump_WIDTH              1u

/* Interrupt constants */
#if defined(pHDownPump__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pHDownPump_SetInterruptMode() function.
     *  @{
     */
        #define pHDownPump_INTR_NONE      (uint16)(0x0000u)
        #define pHDownPump_INTR_RISING    (uint16)(0x0001u)
        #define pHDownPump_INTR_FALLING   (uint16)(0x0002u)
        #define pHDownPump_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pHDownPump_INTR_MASK      (0x01u) 
#endif /* (pHDownPump__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pHDownPump_PS                     (* (reg8 *) pHDownPump__PS)
/* Data Register */
#define pHDownPump_DR                     (* (reg8 *) pHDownPump__DR)
/* Port Number */
#define pHDownPump_PRT_NUM                (* (reg8 *) pHDownPump__PRT) 
/* Connect to Analog Globals */                                                  
#define pHDownPump_AG                     (* (reg8 *) pHDownPump__AG)                       
/* Analog MUX bux enable */
#define pHDownPump_AMUX                   (* (reg8 *) pHDownPump__AMUX) 
/* Bidirectional Enable */                                                        
#define pHDownPump_BIE                    (* (reg8 *) pHDownPump__BIE)
/* Bit-mask for Aliased Register Access */
#define pHDownPump_BIT_MASK               (* (reg8 *) pHDownPump__BIT_MASK)
/* Bypass Enable */
#define pHDownPump_BYP                    (* (reg8 *) pHDownPump__BYP)
/* Port wide control signals */                                                   
#define pHDownPump_CTL                    (* (reg8 *) pHDownPump__CTL)
/* Drive Modes */
#define pHDownPump_DM0                    (* (reg8 *) pHDownPump__DM0) 
#define pHDownPump_DM1                    (* (reg8 *) pHDownPump__DM1)
#define pHDownPump_DM2                    (* (reg8 *) pHDownPump__DM2) 
/* Input Buffer Disable Override */
#define pHDownPump_INP_DIS                (* (reg8 *) pHDownPump__INP_DIS)
/* LCD Common or Segment Drive */
#define pHDownPump_LCD_COM_SEG            (* (reg8 *) pHDownPump__LCD_COM_SEG)
/* Enable Segment LCD */
#define pHDownPump_LCD_EN                 (* (reg8 *) pHDownPump__LCD_EN)
/* Slew Rate Control */
#define pHDownPump_SLW                    (* (reg8 *) pHDownPump__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pHDownPump_PRTDSI__CAPS_SEL       (* (reg8 *) pHDownPump__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pHDownPump_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pHDownPump__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pHDownPump_PRTDSI__OE_SEL0        (* (reg8 *) pHDownPump__PRTDSI__OE_SEL0) 
#define pHDownPump_PRTDSI__OE_SEL1        (* (reg8 *) pHDownPump__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pHDownPump_PRTDSI__OUT_SEL0       (* (reg8 *) pHDownPump__PRTDSI__OUT_SEL0) 
#define pHDownPump_PRTDSI__OUT_SEL1       (* (reg8 *) pHDownPump__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pHDownPump_PRTDSI__SYNC_OUT       (* (reg8 *) pHDownPump__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pHDownPump__SIO_CFG)
    #define pHDownPump_SIO_HYST_EN        (* (reg8 *) pHDownPump__SIO_HYST_EN)
    #define pHDownPump_SIO_REG_HIFREQ     (* (reg8 *) pHDownPump__SIO_REG_HIFREQ)
    #define pHDownPump_SIO_CFG            (* (reg8 *) pHDownPump__SIO_CFG)
    #define pHDownPump_SIO_DIFF           (* (reg8 *) pHDownPump__SIO_DIFF)
#endif /* (pHDownPump__SIO_CFG) */

/* Interrupt Registers */
#if defined(pHDownPump__INTSTAT)
    #define pHDownPump_INTSTAT            (* (reg8 *) pHDownPump__INTSTAT)
    #define pHDownPump_SNAP               (* (reg8 *) pHDownPump__SNAP)
    
	#define pHDownPump_0_INTTYPE_REG 		(* (reg8 *) pHDownPump__0__INTTYPE)
#endif /* (pHDownPump__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pHDownPump_H */


/* [] END OF FILE */
