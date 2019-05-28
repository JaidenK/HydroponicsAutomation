/*******************************************************************************
* File Name: TestTrig.h  
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

#if !defined(CY_PINS_TestTrig_H) /* Pins TestTrig_H */
#define CY_PINS_TestTrig_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TestTrig_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TestTrig__PORT == 15 && ((TestTrig__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TestTrig_Write(uint8 value);
void    TestTrig_SetDriveMode(uint8 mode);
uint8   TestTrig_ReadDataReg(void);
uint8   TestTrig_Read(void);
void    TestTrig_SetInterruptMode(uint16 position, uint16 mode);
uint8   TestTrig_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TestTrig_SetDriveMode() function.
     *  @{
     */
        #define TestTrig_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define TestTrig_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define TestTrig_DM_RES_UP          PIN_DM_RES_UP
        #define TestTrig_DM_RES_DWN         PIN_DM_RES_DWN
        #define TestTrig_DM_OD_LO           PIN_DM_OD_LO
        #define TestTrig_DM_OD_HI           PIN_DM_OD_HI
        #define TestTrig_DM_STRONG          PIN_DM_STRONG
        #define TestTrig_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TestTrig_MASK               TestTrig__MASK
#define TestTrig_SHIFT              TestTrig__SHIFT
#define TestTrig_WIDTH              1u

/* Interrupt constants */
#if defined(TestTrig__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TestTrig_SetInterruptMode() function.
     *  @{
     */
        #define TestTrig_INTR_NONE      (uint16)(0x0000u)
        #define TestTrig_INTR_RISING    (uint16)(0x0001u)
        #define TestTrig_INTR_FALLING   (uint16)(0x0002u)
        #define TestTrig_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define TestTrig_INTR_MASK      (0x01u) 
#endif /* (TestTrig__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TestTrig_PS                     (* (reg8 *) TestTrig__PS)
/* Data Register */
#define TestTrig_DR                     (* (reg8 *) TestTrig__DR)
/* Port Number */
#define TestTrig_PRT_NUM                (* (reg8 *) TestTrig__PRT) 
/* Connect to Analog Globals */                                                  
#define TestTrig_AG                     (* (reg8 *) TestTrig__AG)                       
/* Analog MUX bux enable */
#define TestTrig_AMUX                   (* (reg8 *) TestTrig__AMUX) 
/* Bidirectional Enable */                                                        
#define TestTrig_BIE                    (* (reg8 *) TestTrig__BIE)
/* Bit-mask for Aliased Register Access */
#define TestTrig_BIT_MASK               (* (reg8 *) TestTrig__BIT_MASK)
/* Bypass Enable */
#define TestTrig_BYP                    (* (reg8 *) TestTrig__BYP)
/* Port wide control signals */                                                   
#define TestTrig_CTL                    (* (reg8 *) TestTrig__CTL)
/* Drive Modes */
#define TestTrig_DM0                    (* (reg8 *) TestTrig__DM0) 
#define TestTrig_DM1                    (* (reg8 *) TestTrig__DM1)
#define TestTrig_DM2                    (* (reg8 *) TestTrig__DM2) 
/* Input Buffer Disable Override */
#define TestTrig_INP_DIS                (* (reg8 *) TestTrig__INP_DIS)
/* LCD Common or Segment Drive */
#define TestTrig_LCD_COM_SEG            (* (reg8 *) TestTrig__LCD_COM_SEG)
/* Enable Segment LCD */
#define TestTrig_LCD_EN                 (* (reg8 *) TestTrig__LCD_EN)
/* Slew Rate Control */
#define TestTrig_SLW                    (* (reg8 *) TestTrig__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TestTrig_PRTDSI__CAPS_SEL       (* (reg8 *) TestTrig__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TestTrig_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TestTrig__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TestTrig_PRTDSI__OE_SEL0        (* (reg8 *) TestTrig__PRTDSI__OE_SEL0) 
#define TestTrig_PRTDSI__OE_SEL1        (* (reg8 *) TestTrig__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TestTrig_PRTDSI__OUT_SEL0       (* (reg8 *) TestTrig__PRTDSI__OUT_SEL0) 
#define TestTrig_PRTDSI__OUT_SEL1       (* (reg8 *) TestTrig__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TestTrig_PRTDSI__SYNC_OUT       (* (reg8 *) TestTrig__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TestTrig__SIO_CFG)
    #define TestTrig_SIO_HYST_EN        (* (reg8 *) TestTrig__SIO_HYST_EN)
    #define TestTrig_SIO_REG_HIFREQ     (* (reg8 *) TestTrig__SIO_REG_HIFREQ)
    #define TestTrig_SIO_CFG            (* (reg8 *) TestTrig__SIO_CFG)
    #define TestTrig_SIO_DIFF           (* (reg8 *) TestTrig__SIO_DIFF)
#endif /* (TestTrig__SIO_CFG) */

/* Interrupt Registers */
#if defined(TestTrig__INTSTAT)
    #define TestTrig_INTSTAT            (* (reg8 *) TestTrig__INTSTAT)
    #define TestTrig_SNAP               (* (reg8 *) TestTrig__SNAP)
    
	#define TestTrig_0_INTTYPE_REG 		(* (reg8 *) TestTrig__0__INTTYPE)
#endif /* (TestTrig__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TestTrig_H */


/* [] END OF FILE */
