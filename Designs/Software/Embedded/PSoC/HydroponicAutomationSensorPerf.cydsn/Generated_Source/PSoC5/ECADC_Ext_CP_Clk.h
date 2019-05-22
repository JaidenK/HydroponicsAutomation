/*******************************************************************************
* File Name: ECADC_Ext_CP_Clk.h
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

#if !defined(CY_CLOCK_ECADC_Ext_CP_Clk_H)
#define CY_CLOCK_ECADC_Ext_CP_Clk_H

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

void ECADC_Ext_CP_Clk_Start(void) ;
void ECADC_Ext_CP_Clk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void ECADC_Ext_CP_Clk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void ECADC_Ext_CP_Clk_StandbyPower(uint8 state) ;
void ECADC_Ext_CP_Clk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 ECADC_Ext_CP_Clk_GetDividerRegister(void) ;
void ECADC_Ext_CP_Clk_SetModeRegister(uint8 modeBitMask) ;
void ECADC_Ext_CP_Clk_ClearModeRegister(uint8 modeBitMask) ;
uint8 ECADC_Ext_CP_Clk_GetModeRegister(void) ;
void ECADC_Ext_CP_Clk_SetSourceRegister(uint8 clkSource) ;
uint8 ECADC_Ext_CP_Clk_GetSourceRegister(void) ;
#if defined(ECADC_Ext_CP_Clk__CFG3)
void ECADC_Ext_CP_Clk_SetPhaseRegister(uint8 clkPhase) ;
uint8 ECADC_Ext_CP_Clk_GetPhaseRegister(void) ;
#endif /* defined(ECADC_Ext_CP_Clk__CFG3) */

#define ECADC_Ext_CP_Clk_Enable()                       ECADC_Ext_CP_Clk_Start()
#define ECADC_Ext_CP_Clk_Disable()                      ECADC_Ext_CP_Clk_Stop()
#define ECADC_Ext_CP_Clk_SetDivider(clkDivider)         ECADC_Ext_CP_Clk_SetDividerRegister(clkDivider, 1u)
#define ECADC_Ext_CP_Clk_SetDividerValue(clkDivider)    ECADC_Ext_CP_Clk_SetDividerRegister((clkDivider) - 1u, 1u)
#define ECADC_Ext_CP_Clk_SetMode(clkMode)               ECADC_Ext_CP_Clk_SetModeRegister(clkMode)
#define ECADC_Ext_CP_Clk_SetSource(clkSource)           ECADC_Ext_CP_Clk_SetSourceRegister(clkSource)
#if defined(ECADC_Ext_CP_Clk__CFG3)
#define ECADC_Ext_CP_Clk_SetPhase(clkPhase)             ECADC_Ext_CP_Clk_SetPhaseRegister(clkPhase)
#define ECADC_Ext_CP_Clk_SetPhaseValue(clkPhase)        ECADC_Ext_CP_Clk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(ECADC_Ext_CP_Clk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define ECADC_Ext_CP_Clk_CLKEN              (* (reg8 *) ECADC_Ext_CP_Clk__PM_ACT_CFG)
#define ECADC_Ext_CP_Clk_CLKEN_PTR          ((reg8 *) ECADC_Ext_CP_Clk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define ECADC_Ext_CP_Clk_CLKSTBY            (* (reg8 *) ECADC_Ext_CP_Clk__PM_STBY_CFG)
#define ECADC_Ext_CP_Clk_CLKSTBY_PTR        ((reg8 *) ECADC_Ext_CP_Clk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define ECADC_Ext_CP_Clk_DIV_LSB            (* (reg8 *) ECADC_Ext_CP_Clk__CFG0)
#define ECADC_Ext_CP_Clk_DIV_LSB_PTR        ((reg8 *) ECADC_Ext_CP_Clk__CFG0)
#define ECADC_Ext_CP_Clk_DIV_PTR            ((reg16 *) ECADC_Ext_CP_Clk__CFG0)

/* Clock MSB divider configuration register. */
#define ECADC_Ext_CP_Clk_DIV_MSB            (* (reg8 *) ECADC_Ext_CP_Clk__CFG1)
#define ECADC_Ext_CP_Clk_DIV_MSB_PTR        ((reg8 *) ECADC_Ext_CP_Clk__CFG1)

/* Mode and source configuration register */
#define ECADC_Ext_CP_Clk_MOD_SRC            (* (reg8 *) ECADC_Ext_CP_Clk__CFG2)
#define ECADC_Ext_CP_Clk_MOD_SRC_PTR        ((reg8 *) ECADC_Ext_CP_Clk__CFG2)

#if defined(ECADC_Ext_CP_Clk__CFG3)
/* Analog clock phase configuration register */
#define ECADC_Ext_CP_Clk_PHASE              (* (reg8 *) ECADC_Ext_CP_Clk__CFG3)
#define ECADC_Ext_CP_Clk_PHASE_PTR          ((reg8 *) ECADC_Ext_CP_Clk__CFG3)
#endif /* defined(ECADC_Ext_CP_Clk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define ECADC_Ext_CP_Clk_CLKEN_MASK         ECADC_Ext_CP_Clk__PM_ACT_MSK
#define ECADC_Ext_CP_Clk_CLKSTBY_MASK       ECADC_Ext_CP_Clk__PM_STBY_MSK

/* CFG2 field masks */
#define ECADC_Ext_CP_Clk_SRC_SEL_MSK        ECADC_Ext_CP_Clk__CFG2_SRC_SEL_MASK
#define ECADC_Ext_CP_Clk_MODE_MASK          (~(ECADC_Ext_CP_Clk_SRC_SEL_MSK))

#if defined(ECADC_Ext_CP_Clk__CFG3)
/* CFG3 phase mask */
#define ECADC_Ext_CP_Clk_PHASE_MASK         ECADC_Ext_CP_Clk__CFG3_PHASE_DLY_MASK
#endif /* defined(ECADC_Ext_CP_Clk__CFG3) */

#endif /* CY_CLOCK_ECADC_Ext_CP_Clk_H */


/* [] END OF FILE */
