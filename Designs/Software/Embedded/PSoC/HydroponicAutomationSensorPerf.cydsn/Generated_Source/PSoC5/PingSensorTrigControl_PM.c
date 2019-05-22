/*******************************************************************************
* File Name: PingSensorTrigControl_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "PingSensorTrigControl.h"

/* Check for removal by optimization */
#if !defined(PingSensorTrigControl_Sync_ctrl_reg__REMOVED)

static PingSensorTrigControl_BACKUP_STRUCT  PingSensorTrigControl_backup = {0u};

    
/*******************************************************************************
* Function Name: PingSensorTrigControl_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PingSensorTrigControl_SaveConfig(void) 
{
    PingSensorTrigControl_backup.controlState = PingSensorTrigControl_Control;
}


/*******************************************************************************
* Function Name: PingSensorTrigControl_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void PingSensorTrigControl_RestoreConfig(void) 
{
     PingSensorTrigControl_Control = PingSensorTrigControl_backup.controlState;
}


/*******************************************************************************
* Function Name: PingSensorTrigControl_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PingSensorTrigControl_Sleep(void) 
{
    PingSensorTrigControl_SaveConfig();
}


/*******************************************************************************
* Function Name: PingSensorTrigControl_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PingSensorTrigControl_Wakeup(void)  
{
    PingSensorTrigControl_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
