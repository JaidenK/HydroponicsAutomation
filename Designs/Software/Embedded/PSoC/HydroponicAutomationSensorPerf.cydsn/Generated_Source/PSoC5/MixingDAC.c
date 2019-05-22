/*******************************************************************************
* File Name: MixingDAC.c  
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
#include "MixingDAC.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 MixingDAC_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 MixingDAC_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static MixingDAC_backupStruct MixingDAC_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: MixingDAC_Init
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
void MixingDAC_Init(void) 
{
    MixingDAC_CR0 = (MixingDAC_MODE_V );

    /* Set default data source */
    #if(MixingDAC_DEFAULT_DATA_SRC != 0 )
        MixingDAC_CR1 = (MixingDAC_DEFAULT_CNTL | MixingDAC_DACBUS_ENABLE) ;
    #else
        MixingDAC_CR1 = (MixingDAC_DEFAULT_CNTL | MixingDAC_DACBUS_DISABLE) ;
    #endif /* (MixingDAC_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(MixingDAC_DEFAULT_STRB != 0)
        MixingDAC_Strobe |= MixingDAC_STRB_EN ;
    #endif/* (MixingDAC_DEFAULT_STRB != 0) */

    /* Set default range */
    MixingDAC_SetRange(MixingDAC_DEFAULT_RANGE); 

    /* Set default speed */
    MixingDAC_SetSpeed(MixingDAC_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: MixingDAC_Enable
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
void MixingDAC_Enable(void) 
{
    MixingDAC_PWRMGR |= MixingDAC_ACT_PWR_EN;
    MixingDAC_STBY_PWRMGR |= MixingDAC_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(MixingDAC_restoreVal == 1u) 
        {
             MixingDAC_CR0 = MixingDAC_backup.data_value;
             MixingDAC_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: MixingDAC_Start
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
*  MixingDAC_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void MixingDAC_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(MixingDAC_initVar == 0u)
    { 
        MixingDAC_Init();
        MixingDAC_initVar = 1u;
    }

    /* Enable power to DAC */
    MixingDAC_Enable();

    /* Set default value */
    MixingDAC_SetValue(MixingDAC_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: MixingDAC_Stop
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
void MixingDAC_Stop(void) 
{
    /* Disble power to DAC */
    MixingDAC_PWRMGR &= (uint8)(~MixingDAC_ACT_PWR_EN);
    MixingDAC_STBY_PWRMGR &= (uint8)(~MixingDAC_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        MixingDAC_backup.data_value = MixingDAC_CR0;
        MixingDAC_CR0 = MixingDAC_CUR_MODE_OUT_OFF;
        MixingDAC_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: MixingDAC_SetSpeed
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
void MixingDAC_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    MixingDAC_CR0 &= (uint8)(~MixingDAC_HS_MASK);
    MixingDAC_CR0 |=  (speed & MixingDAC_HS_MASK);
}


/*******************************************************************************
* Function Name: MixingDAC_SetRange
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
void MixingDAC_SetRange(uint8 range) 
{
    MixingDAC_CR0 &= (uint8)(~MixingDAC_RANGE_MASK);      /* Clear existing mode */
    MixingDAC_CR0 |= (range & MixingDAC_RANGE_MASK);      /*  Set Range  */
    MixingDAC_DacTrim();
}


/*******************************************************************************
* Function Name: MixingDAC_SetValue
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
void MixingDAC_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 MixingDAC_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    MixingDAC_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        MixingDAC_Data = value;
        CyExitCriticalSection(MixingDAC_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: MixingDAC_DacTrim
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
void MixingDAC_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((MixingDAC_CR0 & MixingDAC_RANGE_MASK) >> 2) + MixingDAC_TRIM_M7_1V_RNG_OFFSET;
    MixingDAC_TR = CY_GET_XTND_REG8((uint8 *)(MixingDAC_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
