/*******************************************************************************
* File Name: MixingDAC_PM.c  
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

#include "MixingDAC.h"

static MixingDAC_backupStruct MixingDAC_backup;


/*******************************************************************************
* Function Name: MixingDAC_SaveConfig
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
void MixingDAC_SaveConfig(void) 
{
    if (!((MixingDAC_CR1 & MixingDAC_SRC_MASK) == MixingDAC_SRC_UDB))
    {
        MixingDAC_backup.data_value = MixingDAC_Data;
    }
}


/*******************************************************************************
* Function Name: MixingDAC_RestoreConfig
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
void MixingDAC_RestoreConfig(void) 
{
    if (!((MixingDAC_CR1 & MixingDAC_SRC_MASK) == MixingDAC_SRC_UDB))
    {
        if((MixingDAC_Strobe & MixingDAC_STRB_MASK) == MixingDAC_STRB_EN)
        {
            MixingDAC_Strobe &= (uint8)(~MixingDAC_STRB_MASK);
            MixingDAC_Data = MixingDAC_backup.data_value;
            MixingDAC_Strobe |= MixingDAC_STRB_EN;
        }
        else
        {
            MixingDAC_Data = MixingDAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: MixingDAC_Sleep
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
*  MixingDAC_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void MixingDAC_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(MixingDAC_ACT_PWR_EN == (MixingDAC_PWRMGR & MixingDAC_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        MixingDAC_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        MixingDAC_backup.enableState = 0u;
    }
    
    MixingDAC_Stop();
    MixingDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: MixingDAC_Wakeup
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
*  MixingDAC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MixingDAC_Wakeup(void) 
{
    MixingDAC_RestoreConfig();
    
    if(MixingDAC_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        MixingDAC_Enable();

        /* Restore the data register */
        MixingDAC_SetValue(MixingDAC_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
