/*******************************************************************************
* File Name: FlowSpeedDAC.c  
* Version 1.90
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "FlowSpeedDAC.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 FlowSpeedDAC_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 FlowSpeedDAC_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static FlowSpeedDAC_backupStruct FlowSpeedDAC_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: FlowSpeedDAC_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void FlowSpeedDAC_Init(void) 
{
    FlowSpeedDAC_CR0 = (FlowSpeedDAC_MODE_V );

    /* Set default data source */
    #if(FlowSpeedDAC_DEFAULT_DATA_SRC != 0 )
        FlowSpeedDAC_CR1 = (FlowSpeedDAC_DEFAULT_CNTL | FlowSpeedDAC_DACBUS_ENABLE) ;
    #else
        FlowSpeedDAC_CR1 = (FlowSpeedDAC_DEFAULT_CNTL | FlowSpeedDAC_DACBUS_DISABLE) ;
    #endif /* (FlowSpeedDAC_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(FlowSpeedDAC_DEFAULT_STRB != 0)
        FlowSpeedDAC_Strobe |= FlowSpeedDAC_STRB_EN ;
    #endif/* (FlowSpeedDAC_DEFAULT_STRB != 0) */

    /* Set default range */
    FlowSpeedDAC_SetRange(FlowSpeedDAC_DEFAULT_RANGE); 

    /* Set default speed */
    FlowSpeedDAC_SetSpeed(FlowSpeedDAC_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: FlowSpeedDAC_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void FlowSpeedDAC_Enable(void) 
{
    FlowSpeedDAC_PWRMGR |= FlowSpeedDAC_ACT_PWR_EN;
    FlowSpeedDAC_STBY_PWRMGR |= FlowSpeedDAC_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(FlowSpeedDAC_restoreVal == 1u) 
        {
             FlowSpeedDAC_CR0 = FlowSpeedDAC_backup.data_value;
             FlowSpeedDAC_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: FlowSpeedDAC_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  FlowSpeedDAC_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void FlowSpeedDAC_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(FlowSpeedDAC_initVar == 0u)
    { 
        FlowSpeedDAC_Init();
        FlowSpeedDAC_initVar = 1u;
    }

    /* Enable power to DAC */
    FlowSpeedDAC_Enable();

    /* Set default value */
    FlowSpeedDAC_SetValue(FlowSpeedDAC_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: FlowSpeedDAC_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void FlowSpeedDAC_Stop(void) 
{
    /* Disble power to DAC */
    FlowSpeedDAC_PWRMGR &= (uint8)(~FlowSpeedDAC_ACT_PWR_EN);
    FlowSpeedDAC_STBY_PWRMGR &= (uint8)(~FlowSpeedDAC_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        FlowSpeedDAC_backup.data_value = FlowSpeedDAC_CR0;
        FlowSpeedDAC_CR0 = FlowSpeedDAC_CUR_MODE_OUT_OFF;
        FlowSpeedDAC_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: FlowSpeedDAC_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void FlowSpeedDAC_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    FlowSpeedDAC_CR0 &= (uint8)(~FlowSpeedDAC_HS_MASK);
    FlowSpeedDAC_CR0 |=  (speed & FlowSpeedDAC_HS_MASK);
}


/*******************************************************************************
* Function Name: FlowSpeedDAC_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void FlowSpeedDAC_SetRange(uint8 range) 
{
    FlowSpeedDAC_CR0 &= (uint8)(~FlowSpeedDAC_RANGE_MASK);      /* Clear existing mode */
    FlowSpeedDAC_CR0 |= (range & FlowSpeedDAC_RANGE_MASK);      /*  Set Range  */
    FlowSpeedDAC_DacTrim();
}


/*******************************************************************************
* Function Name: FlowSpeedDAC_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void FlowSpeedDAC_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 FlowSpeedDAC_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    FlowSpeedDAC_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        FlowSpeedDAC_Data = value;
        CyExitCriticalSection(FlowSpeedDAC_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: FlowSpeedDAC_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void FlowSpeedDAC_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((FlowSpeedDAC_CR0 & FlowSpeedDAC_RANGE_MASK) >> 2) + FlowSpeedDAC_TRIM_M7_1V_RNG_OFFSET;
    FlowSpeedDAC_TR = CY_GET_XTND_REG8((uint8 *)(FlowSpeedDAC_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
