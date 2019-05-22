/*******************************************************************************
* File Name: pHControllerDirPin.h  
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

#if !defined(CY_PINS_pHControllerDirPin_H) /* Pins pHControllerDirPin_H */
#define CY_PINS_pHControllerDirPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pHControllerDirPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pHControllerDirPin__PORT == 15 && ((pHControllerDirPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pHControllerDirPin_Write(uint8 value);
void    pHControllerDirPin_SetDriveMode(uint8 mode);
uint8   pHControllerDirPin_ReadDataReg(void);
uint8   pHControllerDirPin_Read(void);
void    pHControllerDirPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   pHControllerDirPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pHControllerDirPin_SetDriveMode() function.
     *  @{
     */
        #define pHControllerDirPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pHControllerDirPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pHControllerDirPin_DM_RES_UP          PIN_DM_RES_UP
        #define pHControllerDirPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define pHControllerDirPin_DM_OD_LO           PIN_DM_OD_LO
        #define pHControllerDirPin_DM_OD_HI           PIN_DM_OD_HI
        #define pHControllerDirPin_DM_STRONG          PIN_DM_STRONG
        #define pHControllerDirPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pHControllerDirPin_MASK               pHControllerDirPin__MASK
#define pHControllerDirPin_SHIFT              pHControllerDirPin__SHIFT
#define pHControllerDirPin_WIDTH              1u

/* Interrupt constants */
#if defined(pHControllerDirPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pHControllerDirPin_SetInterruptMode() function.
     *  @{
     */
        #define pHControllerDirPin_INTR_NONE      (uint16)(0x0000u)
        #define pHControllerDirPin_INTR_RISING    (uint16)(0x0001u)
        #define pHControllerDirPin_INTR_FALLING   (uint16)(0x0002u)
        #define pHControllerDirPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pHControllerDirPin_INTR_MASK      (0x01u) 
#endif /* (pHControllerDirPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pHControllerDirPin_PS                     (* (reg8 *) pHControllerDirPin__PS)
/* Data Register */
#define pHControllerDirPin_DR                     (* (reg8 *) pHControllerDirPin__DR)
/* Port Number */
#define pHControllerDirPin_PRT_NUM                (* (reg8 *) pHControllerDirPin__PRT) 
/* Connect to Analog Globals */                                                  
#define pHControllerDirPin_AG                     (* (reg8 *) pHControllerDirPin__AG)                       
/* Analog MUX bux enable */
#define pHControllerDirPin_AMUX                   (* (reg8 *) pHControllerDirPin__AMUX) 
/* Bidirectional Enable */                                                        
#define pHControllerDirPin_BIE                    (* (reg8 *) pHControllerDirPin__BIE)
/* Bit-mask for Aliased Register Access */
#define pHControllerDirPin_BIT_MASK               (* (reg8 *) pHControllerDirPin__BIT_MASK)
/* Bypass Enable */
#define pHControllerDirPin_BYP                    (* (reg8 *) pHControllerDirPin__BYP)
/* Port wide control signals */                                                   
#define pHControllerDirPin_CTL                    (* (reg8 *) pHControllerDirPin__CTL)
/* Drive Modes */
#define pHControllerDirPin_DM0                    (* (reg8 *) pHControllerDirPin__DM0) 
#define pHControllerDirPin_DM1                    (* (reg8 *) pHControllerDirPin__DM1)
#define pHControllerDirPin_DM2                    (* (reg8 *) pHControllerDirPin__DM2) 
/* Input Buffer Disable Override */
#define pHControllerDirPin_INP_DIS                (* (reg8 *) pHControllerDirPin__INP_DIS)
/* LCD Common or Segment Drive */
#define pHControllerDirPin_LCD_COM_SEG            (* (reg8 *) pHControllerDirPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define pHControllerDirPin_LCD_EN                 (* (reg8 *) pHControllerDirPin__LCD_EN)
/* Slew Rate Control */
#define pHControllerDirPin_SLW                    (* (reg8 *) pHControllerDirPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pHControllerDirPin_PRTDSI__CAPS_SEL       (* (reg8 *) pHControllerDirPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pHControllerDirPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pHControllerDirPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pHControllerDirPin_PRTDSI__OE_SEL0        (* (reg8 *) pHControllerDirPin__PRTDSI__OE_SEL0) 
#define pHControllerDirPin_PRTDSI__OE_SEL1        (* (reg8 *) pHControllerDirPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pHControllerDirPin_PRTDSI__OUT_SEL0       (* (reg8 *) pHControllerDirPin__PRTDSI__OUT_SEL0) 
#define pHControllerDirPin_PRTDSI__OUT_SEL1       (* (reg8 *) pHControllerDirPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pHControllerDirPin_PRTDSI__SYNC_OUT       (* (reg8 *) pHControllerDirPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pHControllerDirPin__SIO_CFG)
    #define pHControllerDirPin_SIO_HYST_EN        (* (reg8 *) pHControllerDirPin__SIO_HYST_EN)
    #define pHControllerDirPin_SIO_REG_HIFREQ     (* (reg8 *) pHControllerDirPin__SIO_REG_HIFREQ)
    #define pHControllerDirPin_SIO_CFG            (* (reg8 *) pHControllerDirPin__SIO_CFG)
    #define pHControllerDirPin_SIO_DIFF           (* (reg8 *) pHControllerDirPin__SIO_DIFF)
#endif /* (pHControllerDirPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(pHControllerDirPin__INTSTAT)
    #define pHControllerDirPin_INTSTAT            (* (reg8 *) pHControllerDirPin__INTSTAT)
    #define pHControllerDirPin_SNAP               (* (reg8 *) pHControllerDirPin__SNAP)
    
	#define pHControllerDirPin_0_INTTYPE_REG 		(* (reg8 *) pHControllerDirPin__0__INTTYPE)
#endif /* (pHControllerDirPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pHControllerDirPin_H */


/* [] END OF FILE */
