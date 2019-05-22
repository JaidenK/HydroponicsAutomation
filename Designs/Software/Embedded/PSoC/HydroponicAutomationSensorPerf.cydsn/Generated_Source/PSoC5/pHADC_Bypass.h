/*******************************************************************************
* File Name: pHADC_Bypass.h  
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

#if !defined(CY_PINS_pHADC_Bypass_H) /* Pins pHADC_Bypass_H */
#define CY_PINS_pHADC_Bypass_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pHADC_Bypass_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pHADC_Bypass__PORT == 15 && ((pHADC_Bypass__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pHADC_Bypass_Write(uint8 value);
void    pHADC_Bypass_SetDriveMode(uint8 mode);
uint8   pHADC_Bypass_ReadDataReg(void);
uint8   pHADC_Bypass_Read(void);
void    pHADC_Bypass_SetInterruptMode(uint16 position, uint16 mode);
uint8   pHADC_Bypass_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pHADC_Bypass_SetDriveMode() function.
     *  @{
     */
        #define pHADC_Bypass_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pHADC_Bypass_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pHADC_Bypass_DM_RES_UP          PIN_DM_RES_UP
        #define pHADC_Bypass_DM_RES_DWN         PIN_DM_RES_DWN
        #define pHADC_Bypass_DM_OD_LO           PIN_DM_OD_LO
        #define pHADC_Bypass_DM_OD_HI           PIN_DM_OD_HI
        #define pHADC_Bypass_DM_STRONG          PIN_DM_STRONG
        #define pHADC_Bypass_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pHADC_Bypass_MASK               pHADC_Bypass__MASK
#define pHADC_Bypass_SHIFT              pHADC_Bypass__SHIFT
#define pHADC_Bypass_WIDTH              1u

/* Interrupt constants */
#if defined(pHADC_Bypass__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pHADC_Bypass_SetInterruptMode() function.
     *  @{
     */
        #define pHADC_Bypass_INTR_NONE      (uint16)(0x0000u)
        #define pHADC_Bypass_INTR_RISING    (uint16)(0x0001u)
        #define pHADC_Bypass_INTR_FALLING   (uint16)(0x0002u)
        #define pHADC_Bypass_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pHADC_Bypass_INTR_MASK      (0x01u) 
#endif /* (pHADC_Bypass__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pHADC_Bypass_PS                     (* (reg8 *) pHADC_Bypass__PS)
/* Data Register */
#define pHADC_Bypass_DR                     (* (reg8 *) pHADC_Bypass__DR)
/* Port Number */
#define pHADC_Bypass_PRT_NUM                (* (reg8 *) pHADC_Bypass__PRT) 
/* Connect to Analog Globals */                                                  
#define pHADC_Bypass_AG                     (* (reg8 *) pHADC_Bypass__AG)                       
/* Analog MUX bux enable */
#define pHADC_Bypass_AMUX                   (* (reg8 *) pHADC_Bypass__AMUX) 
/* Bidirectional Enable */                                                        
#define pHADC_Bypass_BIE                    (* (reg8 *) pHADC_Bypass__BIE)
/* Bit-mask for Aliased Register Access */
#define pHADC_Bypass_BIT_MASK               (* (reg8 *) pHADC_Bypass__BIT_MASK)
/* Bypass Enable */
#define pHADC_Bypass_BYP                    (* (reg8 *) pHADC_Bypass__BYP)
/* Port wide control signals */                                                   
#define pHADC_Bypass_CTL                    (* (reg8 *) pHADC_Bypass__CTL)
/* Drive Modes */
#define pHADC_Bypass_DM0                    (* (reg8 *) pHADC_Bypass__DM0) 
#define pHADC_Bypass_DM1                    (* (reg8 *) pHADC_Bypass__DM1)
#define pHADC_Bypass_DM2                    (* (reg8 *) pHADC_Bypass__DM2) 
/* Input Buffer Disable Override */
#define pHADC_Bypass_INP_DIS                (* (reg8 *) pHADC_Bypass__INP_DIS)
/* LCD Common or Segment Drive */
#define pHADC_Bypass_LCD_COM_SEG            (* (reg8 *) pHADC_Bypass__LCD_COM_SEG)
/* Enable Segment LCD */
#define pHADC_Bypass_LCD_EN                 (* (reg8 *) pHADC_Bypass__LCD_EN)
/* Slew Rate Control */
#define pHADC_Bypass_SLW                    (* (reg8 *) pHADC_Bypass__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pHADC_Bypass_PRTDSI__CAPS_SEL       (* (reg8 *) pHADC_Bypass__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pHADC_Bypass_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pHADC_Bypass__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pHADC_Bypass_PRTDSI__OE_SEL0        (* (reg8 *) pHADC_Bypass__PRTDSI__OE_SEL0) 
#define pHADC_Bypass_PRTDSI__OE_SEL1        (* (reg8 *) pHADC_Bypass__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pHADC_Bypass_PRTDSI__OUT_SEL0       (* (reg8 *) pHADC_Bypass__PRTDSI__OUT_SEL0) 
#define pHADC_Bypass_PRTDSI__OUT_SEL1       (* (reg8 *) pHADC_Bypass__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pHADC_Bypass_PRTDSI__SYNC_OUT       (* (reg8 *) pHADC_Bypass__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pHADC_Bypass__SIO_CFG)
    #define pHADC_Bypass_SIO_HYST_EN        (* (reg8 *) pHADC_Bypass__SIO_HYST_EN)
    #define pHADC_Bypass_SIO_REG_HIFREQ     (* (reg8 *) pHADC_Bypass__SIO_REG_HIFREQ)
    #define pHADC_Bypass_SIO_CFG            (* (reg8 *) pHADC_Bypass__SIO_CFG)
    #define pHADC_Bypass_SIO_DIFF           (* (reg8 *) pHADC_Bypass__SIO_DIFF)
#endif /* (pHADC_Bypass__SIO_CFG) */

/* Interrupt Registers */
#if defined(pHADC_Bypass__INTSTAT)
    #define pHADC_Bypass_INTSTAT            (* (reg8 *) pHADC_Bypass__INTSTAT)
    #define pHADC_Bypass_SNAP               (* (reg8 *) pHADC_Bypass__SNAP)
    
	#define pHADC_Bypass_0_INTTYPE_REG 		(* (reg8 *) pHADC_Bypass__0__INTTYPE)
#endif /* (pHADC_Bypass__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pHADC_Bypass_H */


/* [] END OF FILE */
