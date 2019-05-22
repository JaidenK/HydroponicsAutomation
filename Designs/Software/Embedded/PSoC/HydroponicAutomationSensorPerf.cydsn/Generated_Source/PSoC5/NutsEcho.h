/*******************************************************************************
* File Name: NutsEcho.h  
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

#if !defined(CY_PINS_NutsEcho_H) /* Pins NutsEcho_H */
#define CY_PINS_NutsEcho_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "NutsEcho_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 NutsEcho__PORT == 15 && ((NutsEcho__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    NutsEcho_Write(uint8 value);
void    NutsEcho_SetDriveMode(uint8 mode);
uint8   NutsEcho_ReadDataReg(void);
uint8   NutsEcho_Read(void);
void    NutsEcho_SetInterruptMode(uint16 position, uint16 mode);
uint8   NutsEcho_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the NutsEcho_SetDriveMode() function.
     *  @{
     */
        #define NutsEcho_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define NutsEcho_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define NutsEcho_DM_RES_UP          PIN_DM_RES_UP
        #define NutsEcho_DM_RES_DWN         PIN_DM_RES_DWN
        #define NutsEcho_DM_OD_LO           PIN_DM_OD_LO
        #define NutsEcho_DM_OD_HI           PIN_DM_OD_HI
        #define NutsEcho_DM_STRONG          PIN_DM_STRONG
        #define NutsEcho_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define NutsEcho_MASK               NutsEcho__MASK
#define NutsEcho_SHIFT              NutsEcho__SHIFT
#define NutsEcho_WIDTH              1u

/* Interrupt constants */
#if defined(NutsEcho__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in NutsEcho_SetInterruptMode() function.
     *  @{
     */
        #define NutsEcho_INTR_NONE      (uint16)(0x0000u)
        #define NutsEcho_INTR_RISING    (uint16)(0x0001u)
        #define NutsEcho_INTR_FALLING   (uint16)(0x0002u)
        #define NutsEcho_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define NutsEcho_INTR_MASK      (0x01u) 
#endif /* (NutsEcho__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define NutsEcho_PS                     (* (reg8 *) NutsEcho__PS)
/* Data Register */
#define NutsEcho_DR                     (* (reg8 *) NutsEcho__DR)
/* Port Number */
#define NutsEcho_PRT_NUM                (* (reg8 *) NutsEcho__PRT) 
/* Connect to Analog Globals */                                                  
#define NutsEcho_AG                     (* (reg8 *) NutsEcho__AG)                       
/* Analog MUX bux enable */
#define NutsEcho_AMUX                   (* (reg8 *) NutsEcho__AMUX) 
/* Bidirectional Enable */                                                        
#define NutsEcho_BIE                    (* (reg8 *) NutsEcho__BIE)
/* Bit-mask for Aliased Register Access */
#define NutsEcho_BIT_MASK               (* (reg8 *) NutsEcho__BIT_MASK)
/* Bypass Enable */
#define NutsEcho_BYP                    (* (reg8 *) NutsEcho__BYP)
/* Port wide control signals */                                                   
#define NutsEcho_CTL                    (* (reg8 *) NutsEcho__CTL)
/* Drive Modes */
#define NutsEcho_DM0                    (* (reg8 *) NutsEcho__DM0) 
#define NutsEcho_DM1                    (* (reg8 *) NutsEcho__DM1)
#define NutsEcho_DM2                    (* (reg8 *) NutsEcho__DM2) 
/* Input Buffer Disable Override */
#define NutsEcho_INP_DIS                (* (reg8 *) NutsEcho__INP_DIS)
/* LCD Common or Segment Drive */
#define NutsEcho_LCD_COM_SEG            (* (reg8 *) NutsEcho__LCD_COM_SEG)
/* Enable Segment LCD */
#define NutsEcho_LCD_EN                 (* (reg8 *) NutsEcho__LCD_EN)
/* Slew Rate Control */
#define NutsEcho_SLW                    (* (reg8 *) NutsEcho__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define NutsEcho_PRTDSI__CAPS_SEL       (* (reg8 *) NutsEcho__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define NutsEcho_PRTDSI__DBL_SYNC_IN    (* (reg8 *) NutsEcho__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define NutsEcho_PRTDSI__OE_SEL0        (* (reg8 *) NutsEcho__PRTDSI__OE_SEL0) 
#define NutsEcho_PRTDSI__OE_SEL1        (* (reg8 *) NutsEcho__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define NutsEcho_PRTDSI__OUT_SEL0       (* (reg8 *) NutsEcho__PRTDSI__OUT_SEL0) 
#define NutsEcho_PRTDSI__OUT_SEL1       (* (reg8 *) NutsEcho__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define NutsEcho_PRTDSI__SYNC_OUT       (* (reg8 *) NutsEcho__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(NutsEcho__SIO_CFG)
    #define NutsEcho_SIO_HYST_EN        (* (reg8 *) NutsEcho__SIO_HYST_EN)
    #define NutsEcho_SIO_REG_HIFREQ     (* (reg8 *) NutsEcho__SIO_REG_HIFREQ)
    #define NutsEcho_SIO_CFG            (* (reg8 *) NutsEcho__SIO_CFG)
    #define NutsEcho_SIO_DIFF           (* (reg8 *) NutsEcho__SIO_DIFF)
#endif /* (NutsEcho__SIO_CFG) */

/* Interrupt Registers */
#if defined(NutsEcho__INTSTAT)
    #define NutsEcho_INTSTAT            (* (reg8 *) NutsEcho__INTSTAT)
    #define NutsEcho_SNAP               (* (reg8 *) NutsEcho__SNAP)
    
	#define NutsEcho_0_INTTYPE_REG 		(* (reg8 *) NutsEcho__0__INTTYPE)
#endif /* (NutsEcho__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_NutsEcho_H */


/* [] END OF FILE */
