/*******************************************************************************
* File Name: TestEcho.h  
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

#if !defined(CY_PINS_TestEcho_H) /* Pins TestEcho_H */
#define CY_PINS_TestEcho_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TestEcho_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TestEcho__PORT == 15 && ((TestEcho__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TestEcho_Write(uint8 value);
void    TestEcho_SetDriveMode(uint8 mode);
uint8   TestEcho_ReadDataReg(void);
uint8   TestEcho_Read(void);
void    TestEcho_SetInterruptMode(uint16 position, uint16 mode);
uint8   TestEcho_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TestEcho_SetDriveMode() function.
     *  @{
     */
        #define TestEcho_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define TestEcho_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define TestEcho_DM_RES_UP          PIN_DM_RES_UP
        #define TestEcho_DM_RES_DWN         PIN_DM_RES_DWN
        #define TestEcho_DM_OD_LO           PIN_DM_OD_LO
        #define TestEcho_DM_OD_HI           PIN_DM_OD_HI
        #define TestEcho_DM_STRONG          PIN_DM_STRONG
        #define TestEcho_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TestEcho_MASK               TestEcho__MASK
#define TestEcho_SHIFT              TestEcho__SHIFT
#define TestEcho_WIDTH              1u

/* Interrupt constants */
#if defined(TestEcho__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TestEcho_SetInterruptMode() function.
     *  @{
     */
        #define TestEcho_INTR_NONE      (uint16)(0x0000u)
        #define TestEcho_INTR_RISING    (uint16)(0x0001u)
        #define TestEcho_INTR_FALLING   (uint16)(0x0002u)
        #define TestEcho_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define TestEcho_INTR_MASK      (0x01u) 
#endif /* (TestEcho__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TestEcho_PS                     (* (reg8 *) TestEcho__PS)
/* Data Register */
#define TestEcho_DR                     (* (reg8 *) TestEcho__DR)
/* Port Number */
#define TestEcho_PRT_NUM                (* (reg8 *) TestEcho__PRT) 
/* Connect to Analog Globals */                                                  
#define TestEcho_AG                     (* (reg8 *) TestEcho__AG)                       
/* Analog MUX bux enable */
#define TestEcho_AMUX                   (* (reg8 *) TestEcho__AMUX) 
/* Bidirectional Enable */                                                        
#define TestEcho_BIE                    (* (reg8 *) TestEcho__BIE)
/* Bit-mask for Aliased Register Access */
#define TestEcho_BIT_MASK               (* (reg8 *) TestEcho__BIT_MASK)
/* Bypass Enable */
#define TestEcho_BYP                    (* (reg8 *) TestEcho__BYP)
/* Port wide control signals */                                                   
#define TestEcho_CTL                    (* (reg8 *) TestEcho__CTL)
/* Drive Modes */
#define TestEcho_DM0                    (* (reg8 *) TestEcho__DM0) 
#define TestEcho_DM1                    (* (reg8 *) TestEcho__DM1)
#define TestEcho_DM2                    (* (reg8 *) TestEcho__DM2) 
/* Input Buffer Disable Override */
#define TestEcho_INP_DIS                (* (reg8 *) TestEcho__INP_DIS)
/* LCD Common or Segment Drive */
#define TestEcho_LCD_COM_SEG            (* (reg8 *) TestEcho__LCD_COM_SEG)
/* Enable Segment LCD */
#define TestEcho_LCD_EN                 (* (reg8 *) TestEcho__LCD_EN)
/* Slew Rate Control */
#define TestEcho_SLW                    (* (reg8 *) TestEcho__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TestEcho_PRTDSI__CAPS_SEL       (* (reg8 *) TestEcho__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TestEcho_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TestEcho__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TestEcho_PRTDSI__OE_SEL0        (* (reg8 *) TestEcho__PRTDSI__OE_SEL0) 
#define TestEcho_PRTDSI__OE_SEL1        (* (reg8 *) TestEcho__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TestEcho_PRTDSI__OUT_SEL0       (* (reg8 *) TestEcho__PRTDSI__OUT_SEL0) 
#define TestEcho_PRTDSI__OUT_SEL1       (* (reg8 *) TestEcho__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TestEcho_PRTDSI__SYNC_OUT       (* (reg8 *) TestEcho__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TestEcho__SIO_CFG)
    #define TestEcho_SIO_HYST_EN        (* (reg8 *) TestEcho__SIO_HYST_EN)
    #define TestEcho_SIO_REG_HIFREQ     (* (reg8 *) TestEcho__SIO_REG_HIFREQ)
    #define TestEcho_SIO_CFG            (* (reg8 *) TestEcho__SIO_CFG)
    #define TestEcho_SIO_DIFF           (* (reg8 *) TestEcho__SIO_DIFF)
#endif /* (TestEcho__SIO_CFG) */

/* Interrupt Registers */
#if defined(TestEcho__INTSTAT)
    #define TestEcho_INTSTAT            (* (reg8 *) TestEcho__INTSTAT)
    #define TestEcho_SNAP               (* (reg8 *) TestEcho__SNAP)
    
	#define TestEcho_0_INTTYPE_REG 		(* (reg8 *) TestEcho__0__INTTYPE)
#endif /* (TestEcho__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TestEcho_H */


/* [] END OF FILE */
