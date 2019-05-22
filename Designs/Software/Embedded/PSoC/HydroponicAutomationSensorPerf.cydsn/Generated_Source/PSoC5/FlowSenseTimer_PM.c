/*******************************************************************************
* File Name: FlowSenseTimer_PM.c
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

#include "FlowSenseTimer.h"

static FlowSenseTimer_backupStruct FlowSenseTimer_backup;


/*******************************************************************************
* Function Name: FlowSenseTimer_SaveConfig
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
*  FlowSenseTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void FlowSenseTimer_SaveConfig(void) 
{
    #if (!FlowSenseTimer_UsingFixedFunction)
        FlowSenseTimer_backup.TimerUdb = FlowSenseTimer_ReadCounter();
        FlowSenseTimer_backup.InterruptMaskValue = FlowSenseTimer_STATUS_MASK;
        #if (FlowSenseTimer_UsingHWCaptureCounter)
            FlowSenseTimer_backup.TimerCaptureCounter = FlowSenseTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!FlowSenseTimer_UDB_CONTROL_REG_REMOVED)
            FlowSenseTimer_backup.TimerControlRegister = FlowSenseTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: FlowSenseTimer_RestoreConfig
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
*  FlowSenseTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void FlowSenseTimer_RestoreConfig(void) 
{   
    #if (!FlowSenseTimer_UsingFixedFunction)

        FlowSenseTimer_WriteCounter(FlowSenseTimer_backup.TimerUdb);
        FlowSenseTimer_STATUS_MASK =FlowSenseTimer_backup.InterruptMaskValue;
        #if (FlowSenseTimer_UsingHWCaptureCounter)
            FlowSenseTimer_SetCaptureCount(FlowSenseTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!FlowSenseTimer_UDB_CONTROL_REG_REMOVED)
            FlowSenseTimer_WriteControlRegister(FlowSenseTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: FlowSenseTimer_Sleep
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
*  FlowSenseTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void FlowSenseTimer_Sleep(void) 
{
    #if(!FlowSenseTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(FlowSenseTimer_CTRL_ENABLE == (FlowSenseTimer_CONTROL & FlowSenseTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            FlowSenseTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            FlowSenseTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    FlowSenseTimer_Stop();
    FlowSenseTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: FlowSenseTimer_Wakeup
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
*  FlowSenseTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void FlowSenseTimer_Wakeup(void) 
{
    FlowSenseTimer_RestoreConfig();
    #if(!FlowSenseTimer_UDB_CONTROL_REG_REMOVED)
        if(FlowSenseTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                FlowSenseTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
