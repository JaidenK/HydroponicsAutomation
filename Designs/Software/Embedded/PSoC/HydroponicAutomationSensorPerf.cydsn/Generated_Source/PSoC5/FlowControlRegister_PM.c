/*******************************************************************************
* File Name: FlowControlRegister_PM.c
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

#include "FlowControlRegister.h"

/* Check for removal by optimization */
#if !defined(FlowControlRegister_Sync_ctrl_reg__REMOVED)

static FlowControlRegister_BACKUP_STRUCT  FlowControlRegister_backup = {0u};

    
/*******************************************************************************
* Function Name: FlowControlRegister_SaveConfig
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
void FlowControlRegister_SaveConfig(void) 
{
    FlowControlRegister_backup.controlState = FlowControlRegister_Control;
}


/*******************************************************************************
* Function Name: FlowControlRegister_RestoreConfig
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
void FlowControlRegister_RestoreConfig(void) 
{
     FlowControlRegister_Control = FlowControlRegister_backup.controlState;
}


/*******************************************************************************
* Function Name: FlowControlRegister_Sleep
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
void FlowControlRegister_Sleep(void) 
{
    FlowControlRegister_SaveConfig();
}


/*******************************************************************************
* Function Name: FlowControlRegister_Wakeup
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
void FlowControlRegister_Wakeup(void)  
{
    FlowControlRegister_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
