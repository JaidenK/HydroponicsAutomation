/*******************************************************************************
* File Name: PingSensorEchoTimer_PM.c
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

#include "PingSensorEchoTimer.h"

static PingSensorEchoTimer_backupStruct PingSensorEchoTimer_backup;


/*******************************************************************************
* Function Name: PingSensorEchoTimer_SaveConfig
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
*  PingSensorEchoTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PingSensorEchoTimer_SaveConfig(void) 
{
    #if (!PingSensorEchoTimer_UsingFixedFunction)
        PingSensorEchoTimer_backup.TimerUdb = PingSensorEchoTimer_ReadCounter();
        PingSensorEchoTimer_backup.InterruptMaskValue = PingSensorEchoTimer_STATUS_MASK;
        #if (PingSensorEchoTimer_UsingHWCaptureCounter)
            PingSensorEchoTimer_backup.TimerCaptureCounter = PingSensorEchoTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!PingSensorEchoTimer_UDB_CONTROL_REG_REMOVED)
            PingSensorEchoTimer_backup.TimerControlRegister = PingSensorEchoTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: PingSensorEchoTimer_RestoreConfig
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
*  PingSensorEchoTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PingSensorEchoTimer_RestoreConfig(void) 
{   
    #if (!PingSensorEchoTimer_UsingFixedFunction)

        PingSensorEchoTimer_WriteCounter(PingSensorEchoTimer_backup.TimerUdb);
        PingSensorEchoTimer_STATUS_MASK =PingSensorEchoTimer_backup.InterruptMaskValue;
        #if (PingSensorEchoTimer_UsingHWCaptureCounter)
            PingSensorEchoTimer_SetCaptureCount(PingSensorEchoTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!PingSensorEchoTimer_UDB_CONTROL_REG_REMOVED)
            PingSensorEchoTimer_WriteControlRegister(PingSensorEchoTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: PingSensorEchoTimer_Sleep
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
*  PingSensorEchoTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void PingSensorEchoTimer_Sleep(void) 
{
    #if(!PingSensorEchoTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(PingSensorEchoTimer_CTRL_ENABLE == (PingSensorEchoTimer_CONTROL & PingSensorEchoTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            PingSensorEchoTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            PingSensorEchoTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    PingSensorEchoTimer_Stop();
    PingSensorEchoTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: PingSensorEchoTimer_Wakeup
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
*  PingSensorEchoTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PingSensorEchoTimer_Wakeup(void) 
{
    PingSensorEchoTimer_RestoreConfig();
    #if(!PingSensorEchoTimer_UDB_CONTROL_REG_REMOVED)
        if(PingSensorEchoTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                PingSensorEchoTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
