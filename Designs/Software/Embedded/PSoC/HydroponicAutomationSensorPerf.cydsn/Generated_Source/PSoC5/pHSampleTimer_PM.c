/*******************************************************************************
* File Name: pHSampleTimer_PM.c
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

#include "pHSampleTimer.h"

static pHSampleTimer_backupStruct pHSampleTimer_backup;


/*******************************************************************************
* Function Name: pHSampleTimer_SaveConfig
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
*  pHSampleTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void pHSampleTimer_SaveConfig(void) 
{
    #if (!pHSampleTimer_UsingFixedFunction)
        pHSampleTimer_backup.TimerUdb = pHSampleTimer_ReadCounter();
        pHSampleTimer_backup.InterruptMaskValue = pHSampleTimer_STATUS_MASK;
        #if (pHSampleTimer_UsingHWCaptureCounter)
            pHSampleTimer_backup.TimerCaptureCounter = pHSampleTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!pHSampleTimer_UDB_CONTROL_REG_REMOVED)
            pHSampleTimer_backup.TimerControlRegister = pHSampleTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: pHSampleTimer_RestoreConfig
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
*  pHSampleTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void pHSampleTimer_RestoreConfig(void) 
{   
    #if (!pHSampleTimer_UsingFixedFunction)

        pHSampleTimer_WriteCounter(pHSampleTimer_backup.TimerUdb);
        pHSampleTimer_STATUS_MASK =pHSampleTimer_backup.InterruptMaskValue;
        #if (pHSampleTimer_UsingHWCaptureCounter)
            pHSampleTimer_SetCaptureCount(pHSampleTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!pHSampleTimer_UDB_CONTROL_REG_REMOVED)
            pHSampleTimer_WriteControlRegister(pHSampleTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: pHSampleTimer_Sleep
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
*  pHSampleTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void pHSampleTimer_Sleep(void) 
{
    #if(!pHSampleTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(pHSampleTimer_CTRL_ENABLE == (pHSampleTimer_CONTROL & pHSampleTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            pHSampleTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            pHSampleTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    pHSampleTimer_Stop();
    pHSampleTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: pHSampleTimer_Wakeup
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
*  pHSampleTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void pHSampleTimer_Wakeup(void) 
{
    pHSampleTimer_RestoreConfig();
    #if(!pHSampleTimer_UDB_CONTROL_REG_REMOVED)
        if(pHSampleTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                pHSampleTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
