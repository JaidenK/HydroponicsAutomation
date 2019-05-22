/*******************************************************************************
* File Name: pHControlTimer_PM.c
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

#include "pHControlTimer.h"

static pHControlTimer_backupStruct pHControlTimer_backup;


/*******************************************************************************
* Function Name: pHControlTimer_SaveConfig
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
*  pHControlTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void pHControlTimer_SaveConfig(void) 
{
    #if (!pHControlTimer_UsingFixedFunction)
        pHControlTimer_backup.TimerUdb = pHControlTimer_ReadCounter();
        pHControlTimer_backup.InterruptMaskValue = pHControlTimer_STATUS_MASK;
        #if (pHControlTimer_UsingHWCaptureCounter)
            pHControlTimer_backup.TimerCaptureCounter = pHControlTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!pHControlTimer_UDB_CONTROL_REG_REMOVED)
            pHControlTimer_backup.TimerControlRegister = pHControlTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: pHControlTimer_RestoreConfig
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
*  pHControlTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void pHControlTimer_RestoreConfig(void) 
{   
    #if (!pHControlTimer_UsingFixedFunction)

        pHControlTimer_WriteCounter(pHControlTimer_backup.TimerUdb);
        pHControlTimer_STATUS_MASK =pHControlTimer_backup.InterruptMaskValue;
        #if (pHControlTimer_UsingHWCaptureCounter)
            pHControlTimer_SetCaptureCount(pHControlTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!pHControlTimer_UDB_CONTROL_REG_REMOVED)
            pHControlTimer_WriteControlRegister(pHControlTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: pHControlTimer_Sleep
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
*  pHControlTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void pHControlTimer_Sleep(void) 
{
    #if(!pHControlTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(pHControlTimer_CTRL_ENABLE == (pHControlTimer_CONTROL & pHControlTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            pHControlTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            pHControlTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    pHControlTimer_Stop();
    pHControlTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: pHControlTimer_Wakeup
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
*  pHControlTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void pHControlTimer_Wakeup(void) 
{
    pHControlTimer_RestoreConfig();
    #if(!pHControlTimer_UDB_CONTROL_REG_REMOVED)
        if(pHControlTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                pHControlTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
