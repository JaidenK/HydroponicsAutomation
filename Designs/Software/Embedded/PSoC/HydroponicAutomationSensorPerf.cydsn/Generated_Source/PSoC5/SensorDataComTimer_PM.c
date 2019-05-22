/*******************************************************************************
* File Name: SensorDataComTimer_PM.c
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

#include "SensorDataComTimer.h"

static SensorDataComTimer_backupStruct SensorDataComTimer_backup;


/*******************************************************************************
* Function Name: SensorDataComTimer_SaveConfig
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
*  SensorDataComTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void SensorDataComTimer_SaveConfig(void) 
{
    #if (!SensorDataComTimer_UsingFixedFunction)
        SensorDataComTimer_backup.TimerUdb = SensorDataComTimer_ReadCounter();
        SensorDataComTimer_backup.InterruptMaskValue = SensorDataComTimer_STATUS_MASK;
        #if (SensorDataComTimer_UsingHWCaptureCounter)
            SensorDataComTimer_backup.TimerCaptureCounter = SensorDataComTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!SensorDataComTimer_UDB_CONTROL_REG_REMOVED)
            SensorDataComTimer_backup.TimerControlRegister = SensorDataComTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: SensorDataComTimer_RestoreConfig
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
*  SensorDataComTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void SensorDataComTimer_RestoreConfig(void) 
{   
    #if (!SensorDataComTimer_UsingFixedFunction)

        SensorDataComTimer_WriteCounter(SensorDataComTimer_backup.TimerUdb);
        SensorDataComTimer_STATUS_MASK =SensorDataComTimer_backup.InterruptMaskValue;
        #if (SensorDataComTimer_UsingHWCaptureCounter)
            SensorDataComTimer_SetCaptureCount(SensorDataComTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!SensorDataComTimer_UDB_CONTROL_REG_REMOVED)
            SensorDataComTimer_WriteControlRegister(SensorDataComTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: SensorDataComTimer_Sleep
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
*  SensorDataComTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void SensorDataComTimer_Sleep(void) 
{
    #if(!SensorDataComTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(SensorDataComTimer_CTRL_ENABLE == (SensorDataComTimer_CONTROL & SensorDataComTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            SensorDataComTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            SensorDataComTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    SensorDataComTimer_Stop();
    SensorDataComTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: SensorDataComTimer_Wakeup
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
*  SensorDataComTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void SensorDataComTimer_Wakeup(void) 
{
    SensorDataComTimer_RestoreConfig();
    #if(!SensorDataComTimer_UDB_CONTROL_REG_REMOVED)
        if(SensorDataComTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                SensorDataComTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
