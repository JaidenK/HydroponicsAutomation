/*******************************************************************************
* File Name: TrigControl_PM.c
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

#include "TrigControl.h"

/* Check for removal by optimization */
#if !defined(TrigControl_Sync_ctrl_reg__REMOVED)

static TrigControl_BACKUP_STRUCT  TrigControl_backup = {0u};

    
/*******************************************************************************
* Function Name: TrigControl_SaveConfig
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
void TrigControl_SaveConfig(void) 
{
    TrigControl_backup.controlState = TrigControl_Control;
}


/*******************************************************************************
* Function Name: TrigControl_RestoreConfig
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
void TrigControl_RestoreConfig(void) 
{
     TrigControl_Control = TrigControl_backup.controlState;
}


/*******************************************************************************
* Function Name: TrigControl_Sleep
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
void TrigControl_Sleep(void) 
{
    TrigControl_SaveConfig();
}


/*******************************************************************************
* Function Name: TrigControl_Wakeup
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
void TrigControl_Wakeup(void)  
{
    TrigControl_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
