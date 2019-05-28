/*******************************************************************************
* File Name: PingSensorSampleTimer_PM.c
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

#include "PingSensorSampleTimer.h"

static PingSensorSampleTimer_backupStruct PingSensorSampleTimer_backup;


/*******************************************************************************
* Function Name: PingSensorSampleTimer_SaveConfig
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
*  PingSensorSampleTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PingSensorSampleTimer_SaveConfig(void) 
{
    #if (!PingSensorSampleTimer_UsingFixedFunction)
        PingSensorSampleTimer_backup.TimerUdb = PingSensorSampleTimer_ReadCounter();
        PingSensorSampleTimer_backup.InterruptMaskValue = PingSensorSampleTimer_STATUS_MASK;
        #if (PingSensorSampleTimer_UsingHWCaptureCounter)
            PingSensorSampleTimer_backup.TimerCaptureCounter = PingSensorSampleTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!PingSensorSampleTimer_UDB_CONTROL_REG_REMOVED)
            PingSensorSampleTimer_backup.TimerControlRegister = PingSensorSampleTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: PingSensorSampleTimer_RestoreConfig
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
*  PingSensorSampleTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PingSensorSampleTimer_RestoreConfig(void) 
{   
    #if (!PingSensorSampleTimer_UsingFixedFunction)

        PingSensorSampleTimer_WriteCounter(PingSensorSampleTimer_backup.TimerUdb);
        PingSensorSampleTimer_STATUS_MASK =PingSensorSampleTimer_backup.InterruptMaskValue;
        #if (PingSensorSampleTimer_UsingHWCaptureCounter)
            PingSensorSampleTimer_SetCaptureCount(PingSensorSampleTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!PingSensorSampleTimer_UDB_CONTROL_REG_REMOVED)
            PingSensorSampleTimer_WriteControlRegister(PingSensorSampleTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: PingSensorSampleTimer_Sleep
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
*  PingSensorSampleTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void PingSensorSampleTimer_Sleep(void) 
{
    #if(!PingSensorSampleTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(PingSensorSampleTimer_CTRL_ENABLE == (PingSensorSampleTimer_CONTROL & PingSensorSampleTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            PingSensorSampleTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            PingSensorSampleTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    PingSensorSampleTimer_Stop();
    PingSensorSampleTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: PingSensorSampleTimer_Wakeup
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
*  PingSensorSampleTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PingSensorSampleTimer_Wakeup(void) 
{
    PingSensorSampleTimer_RestoreConfig();
    #if(!PingSensorSampleTimer_UDB_CONTROL_REG_REMOVED)
        if(PingSensorSampleTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                PingSensorSampleTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
