/*******************************************************************************
* File Name: FlowCountTimer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "FlowCountTimer.h"

static FlowCountTimer_backupStruct FlowCountTimer_backup;


/*******************************************************************************
* Function Name: FlowCountTimer_SaveConfig
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
*  FlowCountTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void FlowCountTimer_SaveConfig(void) 
{
    #if (!FlowCountTimer_UsingFixedFunction)
        FlowCountTimer_backup.TimerUdb = FlowCountTimer_ReadCounter();
        FlowCountTimer_backup.InterruptMaskValue = FlowCountTimer_STATUS_MASK;
        #if (FlowCountTimer_UsingHWCaptureCounter)
            FlowCountTimer_backup.TimerCaptureCounter = FlowCountTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!FlowCountTimer_UDB_CONTROL_REG_REMOVED)
            FlowCountTimer_backup.TimerControlRegister = FlowCountTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: FlowCountTimer_RestoreConfig
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
*  FlowCountTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void FlowCountTimer_RestoreConfig(void) 
{   
    #if (!FlowCountTimer_UsingFixedFunction)

        FlowCountTimer_WriteCounter(FlowCountTimer_backup.TimerUdb);
        FlowCountTimer_STATUS_MASK =FlowCountTimer_backup.InterruptMaskValue;
        #if (FlowCountTimer_UsingHWCaptureCounter)
            FlowCountTimer_SetCaptureCount(FlowCountTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!FlowCountTimer_UDB_CONTROL_REG_REMOVED)
            FlowCountTimer_WriteControlRegister(FlowCountTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: FlowCountTimer_Sleep
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
*  FlowCountTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void FlowCountTimer_Sleep(void) 
{
    #if(!FlowCountTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(FlowCountTimer_CTRL_ENABLE == (FlowCountTimer_CONTROL & FlowCountTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            FlowCountTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            FlowCountTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    FlowCountTimer_Stop();
    FlowCountTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: FlowCountTimer_Wakeup
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
*  FlowCountTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void FlowCountTimer_Wakeup(void) 
{
    FlowCountTimer_RestoreConfig();
    #if(!FlowCountTimer_UDB_CONTROL_REG_REMOVED)
        if(FlowCountTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                FlowCountTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
