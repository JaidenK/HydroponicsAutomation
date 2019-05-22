/*******************************************************************************
* File Name: SenseSwitchTimer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "SenseSwitchTimer.h"

static SenseSwitchTimer_backupStruct SenseSwitchTimer_backup;


/*******************************************************************************
* Function Name: SenseSwitchTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SenseSwitchTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void SenseSwitchTimer_SaveConfig(void) 
{
    #if (!SenseSwitchTimer_UsingFixedFunction)
        SenseSwitchTimer_backup.TimerUdb = SenseSwitchTimer_ReadCounter();
        SenseSwitchTimer_backup.InterruptMaskValue = SenseSwitchTimer_STATUS_MASK;
        #if (SenseSwitchTimer_UsingHWCaptureCounter)
            SenseSwitchTimer_backup.TimerCaptureCounter = SenseSwitchTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!SenseSwitchTimer_UDB_CONTROL_REG_REMOVED)
            SenseSwitchTimer_backup.TimerControlRegister = SenseSwitchTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: SenseSwitchTimer_RestoreConfig
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
* Global variables:
*  SenseSwitchTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void SenseSwitchTimer_RestoreConfig(void) 
{   
    #if (!SenseSwitchTimer_UsingFixedFunction)

        SenseSwitchTimer_WriteCounter(SenseSwitchTimer_backup.TimerUdb);
        SenseSwitchTimer_STATUS_MASK =SenseSwitchTimer_backup.InterruptMaskValue;
        #if (SenseSwitchTimer_UsingHWCaptureCounter)
            SenseSwitchTimer_SetCaptureCount(SenseSwitchTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!SenseSwitchTimer_UDB_CONTROL_REG_REMOVED)
            SenseSwitchTimer_WriteControlRegister(SenseSwitchTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: SenseSwitchTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SenseSwitchTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void SenseSwitchTimer_Sleep(void) 
{
    #if(!SenseSwitchTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(SenseSwitchTimer_CTRL_ENABLE == (SenseSwitchTimer_CONTROL & SenseSwitchTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            SenseSwitchTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            SenseSwitchTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    SenseSwitchTimer_Stop();
    SenseSwitchTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: SenseSwitchTimer_Wakeup
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
*  SenseSwitchTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void SenseSwitchTimer_Wakeup(void) 
{
    SenseSwitchTimer_RestoreConfig();
    #if(!SenseSwitchTimer_UDB_CONTROL_REG_REMOVED)
        if(SenseSwitchTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                SenseSwitchTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
