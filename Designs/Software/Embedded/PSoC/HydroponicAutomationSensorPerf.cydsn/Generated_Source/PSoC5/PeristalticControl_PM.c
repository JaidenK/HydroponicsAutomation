/*******************************************************************************
* File Name: PeristalticControl_PM.c
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

#include "PeristalticControl.h"

/* Check for removal by optimization */
#if !defined(PeristalticControl_Sync_ctrl_reg__REMOVED)

static PeristalticControl_BACKUP_STRUCT  PeristalticControl_backup = {0u};

    
/*******************************************************************************
* Function Name: PeristalticControl_SaveConfig
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
void PeristalticControl_SaveConfig(void) 
{
    PeristalticControl_backup.controlState = PeristalticControl_Control;
}


/*******************************************************************************
* Function Name: PeristalticControl_RestoreConfig
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
void PeristalticControl_RestoreConfig(void) 
{
     PeristalticControl_Control = PeristalticControl_backup.controlState;
}


/*******************************************************************************
* Function Name: PeristalticControl_Sleep
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
void PeristalticControl_Sleep(void) 
{
    PeristalticControl_SaveConfig();
}


/*******************************************************************************
* Function Name: PeristalticControl_Wakeup
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
void PeristalticControl_Wakeup(void)  
{
    PeristalticControl_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
