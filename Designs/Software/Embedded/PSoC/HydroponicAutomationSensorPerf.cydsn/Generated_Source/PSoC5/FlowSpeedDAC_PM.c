/*******************************************************************************
* File Name: FlowSpeedDAC_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "FlowSpeedDAC.h"

static FlowSpeedDAC_backupStruct FlowSpeedDAC_backup;


/*******************************************************************************
* Function Name: FlowSpeedDAC_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void FlowSpeedDAC_SaveConfig(void) 
{
    if (!((FlowSpeedDAC_CR1 & FlowSpeedDAC_SRC_MASK) == FlowSpeedDAC_SRC_UDB))
    {
        FlowSpeedDAC_backup.data_value = FlowSpeedDAC_Data;
    }
}


/*******************************************************************************
* Function Name: FlowSpeedDAC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void FlowSpeedDAC_RestoreConfig(void) 
{
    if (!((FlowSpeedDAC_CR1 & FlowSpeedDAC_SRC_MASK) == FlowSpeedDAC_SRC_UDB))
    {
        if((FlowSpeedDAC_Strobe & FlowSpeedDAC_STRB_MASK) == FlowSpeedDAC_STRB_EN)
        {
            FlowSpeedDAC_Strobe &= (uint8)(~FlowSpeedDAC_STRB_MASK);
            FlowSpeedDAC_Data = FlowSpeedDAC_backup.data_value;
            FlowSpeedDAC_Strobe |= FlowSpeedDAC_STRB_EN;
        }
        else
        {
            FlowSpeedDAC_Data = FlowSpeedDAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: FlowSpeedDAC_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  FlowSpeedDAC_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void FlowSpeedDAC_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(FlowSpeedDAC_ACT_PWR_EN == (FlowSpeedDAC_PWRMGR & FlowSpeedDAC_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        FlowSpeedDAC_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        FlowSpeedDAC_backup.enableState = 0u;
    }
    
    FlowSpeedDAC_Stop();
    FlowSpeedDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: FlowSpeedDAC_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  FlowSpeedDAC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void FlowSpeedDAC_Wakeup(void) 
{
    FlowSpeedDAC_RestoreConfig();
    
    if(FlowSpeedDAC_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        FlowSpeedDAC_Enable();

        /* Restore the data register */
        FlowSpeedDAC_SetValue(FlowSpeedDAC_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
