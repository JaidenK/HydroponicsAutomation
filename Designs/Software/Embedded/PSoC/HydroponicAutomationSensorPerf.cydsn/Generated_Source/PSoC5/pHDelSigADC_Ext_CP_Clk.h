/*******************************************************************************
* File Name: pHDelSigADC_Ext_CP_Clk.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_pHDelSigADC_Ext_CP_Clk_H)
#define CY_CLOCK_pHDelSigADC_Ext_CP_Clk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void pHDelSigADC_Ext_CP_Clk_Start(void) ;
void pHDelSigADC_Ext_CP_Clk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void pHDelSigADC_Ext_CP_Clk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void pHDelSigADC_Ext_CP_Clk_StandbyPower(uint8 state) ;
void pHDelSigADC_Ext_CP_Clk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 pHDelSigADC_Ext_CP_Clk_GetDividerRegister(void) ;
void pHDelSigADC_Ext_CP_Clk_SetModeRegister(uint8 modeBitMask) ;
void pHDelSigADC_Ext_CP_Clk_ClearModeRegister(uint8 modeBitMask) ;
uint8 pHDelSigADC_Ext_CP_Clk_GetModeRegister(void) ;
void pHDelSigADC_Ext_CP_Clk_SetSourceRegister(uint8 clkSource) ;
uint8 pHDelSigADC_Ext_CP_Clk_GetSourceRegister(void) ;
#if defined(pHDelSigADC_Ext_CP_Clk__CFG3)
void pHDelSigADC_Ext_CP_Clk_SetPhaseRegister(uint8 clkPhase) ;
uint8 pHDelSigADC_Ext_CP_Clk_GetPhaseRegister(void) ;
#endif /* defined(pHDelSigADC_Ext_CP_Clk__CFG3) */

#define pHDelSigADC_Ext_CP_Clk_Enable()                       pHDelSigADC_Ext_CP_Clk_Start()
#define pHDelSigADC_Ext_CP_Clk_Disable()                      pHDelSigADC_Ext_CP_Clk_Stop()
#define pHDelSigADC_Ext_CP_Clk_SetDivider(clkDivider)         pHDelSigADC_Ext_CP_Clk_SetDividerRegister(clkDivider, 1u)
#define pHDelSigADC_Ext_CP_Clk_SetDividerValue(clkDivider)    pHDelSigADC_Ext_CP_Clk_SetDividerRegister((clkDivider) - 1u, 1u)
#define pHDelSigADC_Ext_CP_Clk_SetMode(clkMode)               pHDelSigADC_Ext_CP_Clk_SetModeRegister(clkMode)
#define pHDelSigADC_Ext_CP_Clk_SetSource(clkSource)           pHDelSigADC_Ext_CP_Clk_SetSourceRegister(clkSource)
#if defined(pHDelSigADC_Ext_CP_Clk__CFG3)
#define pHDelSigADC_Ext_CP_Clk_SetPhase(clkPhase)             pHDelSigADC_Ext_CP_Clk_SetPhaseRegister(clkPhase)
#define pHDelSigADC_Ext_CP_Clk_SetPhaseValue(clkPhase)        pHDelSigADC_Ext_CP_Clk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(pHDelSigADC_Ext_CP_Clk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define pHDelSigADC_Ext_CP_Clk_CLKEN              (* (reg8 *) pHDelSigADC_Ext_CP_Clk__PM_ACT_CFG)
#define pHDelSigADC_Ext_CP_Clk_CLKEN_PTR          ((reg8 *) pHDelSigADC_Ext_CP_Clk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define pHDelSigADC_Ext_CP_Clk_CLKSTBY            (* (reg8 *) pHDelSigADC_Ext_CP_Clk__PM_STBY_CFG)
#define pHDelSigADC_Ext_CP_Clk_CLKSTBY_PTR        ((reg8 *) pHDelSigADC_Ext_CP_Clk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define pHDelSigADC_Ext_CP_Clk_DIV_LSB            (* (reg8 *) pHDelSigADC_Ext_CP_Clk__CFG0)
#define pHDelSigADC_Ext_CP_Clk_DIV_LSB_PTR        ((reg8 *) pHDelSigADC_Ext_CP_Clk__CFG0)
#define pHDelSigADC_Ext_CP_Clk_DIV_PTR            ((reg16 *) pHDelSigADC_Ext_CP_Clk__CFG0)

/* Clock MSB divider configuration register. */
#define pHDelSigADC_Ext_CP_Clk_DIV_MSB            (* (reg8 *) pHDelSigADC_Ext_CP_Clk__CFG1)
#define pHDelSigADC_Ext_CP_Clk_DIV_MSB_PTR        ((reg8 *) pHDelSigADC_Ext_CP_Clk__CFG1)

/* Mode and source configuration register */
#define pHDelSigADC_Ext_CP_Clk_MOD_SRC            (* (reg8 *) pHDelSigADC_Ext_CP_Clk__CFG2)
#define pHDelSigADC_Ext_CP_Clk_MOD_SRC_PTR        ((reg8 *) pHDelSigADC_Ext_CP_Clk__CFG2)

#if defined(pHDelSigADC_Ext_CP_Clk__CFG3)
/* Analog clock phase configuration register */
#define pHDelSigADC_Ext_CP_Clk_PHASE              (* (reg8 *) pHDelSigADC_Ext_CP_Clk__CFG3)
#define pHDelSigADC_Ext_CP_Clk_PHASE_PTR          ((reg8 *) pHDelSigADC_Ext_CP_Clk__CFG3)
#endif /* defined(pHDelSigADC_Ext_CP_Clk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define pHDelSigADC_Ext_CP_Clk_CLKEN_MASK         pHDelSigADC_Ext_CP_Clk__PM_ACT_MSK
#define pHDelSigADC_Ext_CP_Clk_CLKSTBY_MASK       pHDelSigADC_Ext_CP_Clk__PM_STBY_MSK

/* CFG2 field masks */
#define pHDelSigADC_Ext_CP_Clk_SRC_SEL_MSK        pHDelSigADC_Ext_CP_Clk__CFG2_SRC_SEL_MASK
#define pHDelSigADC_Ext_CP_Clk_MODE_MASK          (~(pHDelSigADC_Ext_CP_Clk_SRC_SEL_MSK))

#if defined(pHDelSigADC_Ext_CP_Clk__CFG3)
/* CFG3 phase mask */
#define pHDelSigADC_Ext_CP_Clk_PHASE_MASK         pHDelSigADC_Ext_CP_Clk__CFG3_PHASE_DLY_MASK
#endif /* defined(pHDelSigADC_Ext_CP_Clk__CFG3) */

#endif /* CY_CLOCK_pHDelSigADC_Ext_CP_Clk_H */


/* [] END OF FILE */
