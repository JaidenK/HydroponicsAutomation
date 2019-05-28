/*******************************************************************************
* File Name: NutsTrig.h  
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

#if !defined(CY_PINS_NutsTrig_H) /* Pins NutsTrig_H */
#define CY_PINS_NutsTrig_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "NutsTrig_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 NutsTrig__PORT == 15 && ((NutsTrig__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    NutsTrig_Write(uint8 value);
void    NutsTrig_SetDriveMode(uint8 mode);
uint8   NutsTrig_ReadDataReg(void);
uint8   NutsTrig_Read(void);
void    NutsTrig_SetInterruptMode(uint16 position, uint16 mode);
uint8   NutsTrig_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the NutsTrig_SetDriveMode() function.
     *  @{
     */
        #define NutsTrig_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define NutsTrig_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define NutsTrig_DM_RES_UP          PIN_DM_RES_UP
        #define NutsTrig_DM_RES_DWN         PIN_DM_RES_DWN
        #define NutsTrig_DM_OD_LO           PIN_DM_OD_LO
        #define NutsTrig_DM_OD_HI           PIN_DM_OD_HI
        #define NutsTrig_DM_STRONG          PIN_DM_STRONG
        #define NutsTrig_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define NutsTrig_MASK               NutsTrig__MASK
#define NutsTrig_SHIFT              NutsTrig__SHIFT
#define NutsTrig_WIDTH              1u

/* Interrupt constants */
#if defined(NutsTrig__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in NutsTrig_SetInterruptMode() function.
     *  @{
     */
        #define NutsTrig_INTR_NONE      (uint16)(0x0000u)
        #define NutsTrig_INTR_RISING    (uint16)(0x0001u)
        #define NutsTrig_INTR_FALLING   (uint16)(0x0002u)
        #define NutsTrig_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define NutsTrig_INTR_MASK      (0x01u) 
#endif /* (NutsTrig__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define NutsTrig_PS                     (* (reg8 *) NutsTrig__PS)
/* Data Register */
#define NutsTrig_DR                     (* (reg8 *) NutsTrig__DR)
/* Port Number */
#define NutsTrig_PRT_NUM                (* (reg8 *) NutsTrig__PRT) 
/* Connect to Analog Globals */                                                  
#define NutsTrig_AG                     (* (reg8 *) NutsTrig__AG)                       
/* Analog MUX bux enable */
#define NutsTrig_AMUX                   (* (reg8 *) NutsTrig__AMUX) 
/* Bidirectional Enable */                                                        
#define NutsTrig_BIE                    (* (reg8 *) NutsTrig__BIE)
/* Bit-mask for Aliased Register Access */
#define NutsTrig_BIT_MASK               (* (reg8 *) NutsTrig__BIT_MASK)
/* Bypass Enable */
#define NutsTrig_BYP                    (* (reg8 *) NutsTrig__BYP)
/* Port wide control signals */                                                   
#define NutsTrig_CTL                    (* (reg8 *) NutsTrig__CTL)
/* Drive Modes */
#define NutsTrig_DM0                    (* (reg8 *) NutsTrig__DM0) 
#define NutsTrig_DM1                    (* (reg8 *) NutsTrig__DM1)
#define NutsTrig_DM2                    (* (reg8 *) NutsTrig__DM2) 
/* Input Buffer Disable Override */
#define NutsTrig_INP_DIS                (* (reg8 *) NutsTrig__INP_DIS)
/* LCD Common or Segment Drive */
#define NutsTrig_LCD_COM_SEG            (* (reg8 *) NutsTrig__LCD_COM_SEG)
/* Enable Segment LCD */
#define NutsTrig_LCD_EN                 (* (reg8 *) NutsTrig__LCD_EN)
/* Slew Rate Control */
#define NutsTrig_SLW                    (* (reg8 *) NutsTrig__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define NutsTrig_PRTDSI__CAPS_SEL       (* (reg8 *) NutsTrig__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define NutsTrig_PRTDSI__DBL_SYNC_IN    (* (reg8 *) NutsTrig__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define NutsTrig_PRTDSI__OE_SEL0        (* (reg8 *) NutsTrig__PRTDSI__OE_SEL0) 
#define NutsTrig_PRTDSI__OE_SEL1        (* (reg8 *) NutsTrig__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define NutsTrig_PRTDSI__OUT_SEL0       (* (reg8 *) NutsTrig__PRTDSI__OUT_SEL0) 
#define NutsTrig_PRTDSI__OUT_SEL1       (* (reg8 *) NutsTrig__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define NutsTrig_PRTDSI__SYNC_OUT       (* (reg8 *) NutsTrig__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(NutsTrig__SIO_CFG)
    #define NutsTrig_SIO_HYST_EN        (* (reg8 *) NutsTrig__SIO_HYST_EN)
    #define NutsTrig_SIO_REG_HIFREQ     (* (reg8 *) NutsTrig__SIO_REG_HIFREQ)
    #define NutsTrig_SIO_CFG            (* (reg8 *) NutsTrig__SIO_CFG)
    #define NutsTrig_SIO_DIFF           (* (reg8 *) NutsTrig__SIO_DIFF)
#endif /* (NutsTrig__SIO_CFG) */

/* Interrupt Registers */
#if defined(NutsTrig__INTSTAT)
    #define NutsTrig_INTSTAT            (* (reg8 *) NutsTrig__INTSTAT)
    #define NutsTrig_SNAP               (* (reg8 *) NutsTrig__SNAP)
    
	#define NutsTrig_0_INTTYPE_REG 		(* (reg8 *) NutsTrig__0__INTTYPE)
#endif /* (NutsTrig__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_NutsTrig_H */


/* [] END OF FILE */
