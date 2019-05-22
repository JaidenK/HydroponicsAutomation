/*******************************************************************************
* File Name: PingSensorControl_PM.c
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

#include "PingSensorControl.h"

/* Check for removal by optimization */
#if !defined(PingSensorControl_Sync_ctrl_reg__REMOVED)

static PingSensorControl_BACKUP_STRUCT  PingSensorControl_backup = {0u};

    
/*******************************************************************************
* Function Name: PingSensorControl_SaveConfig
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
void PingSensorControl_SaveConfig(void) 
{
    PingSensorControl_backup.controlState = PingSensorControl_Control;
}


/*******************************************************************************
* Function Name: PingSensorControl_RestoreConfig
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
void PingSensorControl_RestoreConfig(void) 
{
     PingSensorControl_Control = PingSensorControl_backup.controlState;
}


/*******************************************************************************
* Function Name: PingSensorControl_Sleep
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
void PingSensorControl_Sleep(void) 
{
    PingSensorControl_SaveConfig();
}


/*******************************************************************************
* Function Name: PingSensorControl_Wakeup
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
void PingSensorControl_Wakeup(void)  
{
    PingSensorControl_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
