/*******************************************************************************
* File Name: ECControl.h  
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

#if !defined(CY_PINS_ECControl_H) /* Pins ECControl_H */
#define CY_PINS_ECControl_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ECControl_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ECControl__PORT == 15 && ((ECControl__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ECControl_Write(uint8 value);
void    ECControl_SetDriveMode(uint8 mode);
uint8   ECControl_ReadDataReg(void);
uint8   ECControl_Read(void);
void    ECControl_SetInterruptMode(uint16 position, uint16 mode);
uint8   ECControl_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ECControl_SetDriveMode() function.
     *  @{
     */
        #define ECControl_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ECControl_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ECControl_DM_RES_UP          PIN_DM_RES_UP
        #define ECControl_DM_RES_DWN         PIN_DM_RES_DWN
        #define ECControl_DM_OD_LO           PIN_DM_OD_LO
        #define ECControl_DM_OD_HI           PIN_DM_OD_HI
        #define ECControl_DM_STRONG          PIN_DM_STRONG
        #define ECControl_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ECControl_MASK               ECControl__MASK
#define ECControl_SHIFT              ECControl__SHIFT
#define ECControl_WIDTH              1u

/* Interrupt constants */
#if defined(ECControl__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ECControl_SetInterruptMode() function.
     *  @{
     */
        #define ECControl_INTR_NONE      (uint16)(0x0000u)
        #define ECControl_INTR_RISING    (uint16)(0x0001u)
        #define ECControl_INTR_FALLING   (uint16)(0x0002u)
        #define ECControl_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ECControl_INTR_MASK      (0x01u) 
#endif /* (ECControl__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ECControl_PS                     (* (reg8 *) ECControl__PS)
/* Data Register */
#define ECControl_DR                     (* (reg8 *) ECControl__DR)
/* Port Number */
#define ECControl_PRT_NUM                (* (reg8 *) ECControl__PRT) 
/* Connect to Analog Globals */                                                  
#define ECControl_AG                     (* (reg8 *) ECControl__AG)                       
/* Analog MUX bux enable */
#define ECControl_AMUX                   (* (reg8 *) ECControl__AMUX) 
/* Bidirectional Enable */                                                        
#define ECControl_BIE                    (* (reg8 *) ECControl__BIE)
/* Bit-mask for Aliased Register Access */
#define ECControl_BIT_MASK               (* (reg8 *) ECControl__BIT_MASK)
/* Bypass Enable */
#define ECControl_BYP                    (* (reg8 *) ECControl__BYP)
/* Port wide control signals */                                                   
#define ECControl_CTL                    (* (reg8 *) ECControl__CTL)
/* Drive Modes */
#define ECControl_DM0                    (* (reg8 *) ECControl__DM0) 
#define ECControl_DM1                    (* (reg8 *) ECControl__DM1)
#define ECControl_DM2                    (* (reg8 *) ECControl__DM2) 
/* Input Buffer Disable Override */
#define ECControl_INP_DIS                (* (reg8 *) ECControl__INP_DIS)
/* LCD Common or Segment Drive */
#define ECControl_LCD_COM_SEG            (* (reg8 *) ECControl__LCD_COM_SEG)
/* Enable Segment LCD */
#define ECControl_LCD_EN                 (* (reg8 *) ECControl__LCD_EN)
/* Slew Rate Control */
#define ECControl_SLW                    (* (reg8 *) ECControl__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ECControl_PRTDSI__CAPS_SEL       (* (reg8 *) ECControl__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ECControl_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ECControl__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ECControl_PRTDSI__OE_SEL0        (* (reg8 *) ECControl__PRTDSI__OE_SEL0) 
#define ECControl_PRTDSI__OE_SEL1        (* (reg8 *) ECControl__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ECControl_PRTDSI__OUT_SEL0       (* (reg8 *) ECControl__PRTDSI__OUT_SEL0) 
#define ECControl_PRTDSI__OUT_SEL1       (* (reg8 *) ECControl__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ECControl_PRTDSI__SYNC_OUT       (* (reg8 *) ECControl__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ECControl__SIO_CFG)
    #define ECControl_SIO_HYST_EN        (* (reg8 *) ECControl__SIO_HYST_EN)
    #define ECControl_SIO_REG_HIFREQ     (* (reg8 *) ECControl__SIO_REG_HIFREQ)
    #define ECControl_SIO_CFG            (* (reg8 *) ECControl__SIO_CFG)
    #define ECControl_SIO_DIFF           (* (reg8 *) ECControl__SIO_DIFF)
#endif /* (ECControl__SIO_CFG) */

/* Interrupt Registers */
#if defined(ECControl__INTSTAT)
    #define ECControl_INTSTAT            (* (reg8 *) ECControl__INTSTAT)
    #define ECControl_SNAP               (* (reg8 *) ECControl__SNAP)
    
	#define ECControl_0_INTTYPE_REG 		(* (reg8 *) ECControl__0__INTTYPE)
#endif /* (ECControl__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ECControl_H */


/* [] END OF FILE */
