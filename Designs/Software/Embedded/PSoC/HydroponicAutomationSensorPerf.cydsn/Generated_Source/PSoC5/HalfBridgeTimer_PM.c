/*******************************************************************************
* File Name: HalfBridgeTimer_PM.c
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

#include "HalfBridgeTimer.h"

static HalfBridgeTimer_backupStruct HalfBridgeTimer_backup;


/*******************************************************************************
* Function Name: HalfBridgeTimer_SaveConfig
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
*  HalfBridgeTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void HalfBridgeTimer_SaveConfig(void) 
{
    #if (!HalfBridgeTimer_UsingFixedFunction)
        HalfBridgeTimer_backup.TimerUdb = HalfBridgeTimer_ReadCounter();
        HalfBridgeTimer_backup.InterruptMaskValue = HalfBridgeTimer_STATUS_MASK;
        #if (HalfBridgeTimer_UsingHWCaptureCounter)
            HalfBridgeTimer_backup.TimerCaptureCounter = HalfBridgeTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!HalfBridgeTimer_UDB_CONTROL_REG_REMOVED)
            HalfBridgeTimer_backup.TimerControlRegister = HalfBridgeTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: HalfBridgeTimer_RestoreConfig
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
*  HalfBridgeTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void HalfBridgeTimer_RestoreConfig(void) 
{   
    #if (!HalfBridgeTimer_UsingFixedFunction)

        HalfBridgeTimer_WriteCounter(HalfBridgeTimer_backup.TimerUdb);
        HalfBridgeTimer_STATUS_MASK =HalfBridgeTimer_backup.InterruptMaskValue;
        #if (HalfBridgeTimer_UsingHWCaptureCounter)
            HalfBridgeTimer_SetCaptureCount(HalfBridgeTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!HalfBridgeTimer_UDB_CONTROL_REG_REMOVED)
            HalfBridgeTimer_WriteControlRegister(HalfBridgeTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: HalfBridgeTimer_Sleep
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
*  HalfBridgeTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void HalfBridgeTimer_Sleep(void) 
{
    #if(!HalfBridgeTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(HalfBridgeTimer_CTRL_ENABLE == (HalfBridgeTimer_CONTROL & HalfBridgeTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            HalfBridgeTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            HalfBridgeTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    HalfBridgeTimer_Stop();
    HalfBridgeTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: HalfBridgeTimer_Wakeup
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
*  HalfBridgeTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void HalfBridgeTimer_Wakeup(void) 
{
    HalfBridgeTimer_RestoreConfig();
    #if(!HalfBridgeTimer_UDB_CONTROL_REG_REMOVED)
        if(HalfBridgeTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                HalfBridgeTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
