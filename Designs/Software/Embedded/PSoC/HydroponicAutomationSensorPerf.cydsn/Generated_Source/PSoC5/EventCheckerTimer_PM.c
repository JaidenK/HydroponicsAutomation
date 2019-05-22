/*******************************************************************************
* File Name: EventCheckerTimer_PM.c
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

#include "EventCheckerTimer.h"

static EventCheckerTimer_backupStruct EventCheckerTimer_backup;


/*******************************************************************************
* Function Name: EventCheckerTimer_SaveConfig
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
*  EventCheckerTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void EventCheckerTimer_SaveConfig(void) 
{
    #if (!EventCheckerTimer_UsingFixedFunction)
        EventCheckerTimer_backup.TimerUdb = EventCheckerTimer_ReadCounter();
        EventCheckerTimer_backup.InterruptMaskValue = EventCheckerTimer_STATUS_MASK;
        #if (EventCheckerTimer_UsingHWCaptureCounter)
            EventCheckerTimer_backup.TimerCaptureCounter = EventCheckerTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!EventCheckerTimer_UDB_CONTROL_REG_REMOVED)
            EventCheckerTimer_backup.TimerControlRegister = EventCheckerTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: EventCheckerTimer_RestoreConfig
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
*  EventCheckerTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void EventCheckerTimer_RestoreConfig(void) 
{   
    #if (!EventCheckerTimer_UsingFixedFunction)

        EventCheckerTimer_WriteCounter(EventCheckerTimer_backup.TimerUdb);
        EventCheckerTimer_STATUS_MASK =EventCheckerTimer_backup.InterruptMaskValue;
        #if (EventCheckerTimer_UsingHWCaptureCounter)
            EventCheckerTimer_SetCaptureCount(EventCheckerTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!EventCheckerTimer_UDB_CONTROL_REG_REMOVED)
            EventCheckerTimer_WriteControlRegister(EventCheckerTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: EventCheckerTimer_Sleep
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
*  EventCheckerTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void EventCheckerTimer_Sleep(void) 
{
    #if(!EventCheckerTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(EventCheckerTimer_CTRL_ENABLE == (EventCheckerTimer_CONTROL & EventCheckerTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            EventCheckerTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            EventCheckerTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    EventCheckerTimer_Stop();
    EventCheckerTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: EventCheckerTimer_Wakeup
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
*  EventCheckerTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void EventCheckerTimer_Wakeup(void) 
{
    EventCheckerTimer_RestoreConfig();
    #if(!EventCheckerTimer_UDB_CONTROL_REG_REMOVED)
        if(EventCheckerTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                EventCheckerTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
