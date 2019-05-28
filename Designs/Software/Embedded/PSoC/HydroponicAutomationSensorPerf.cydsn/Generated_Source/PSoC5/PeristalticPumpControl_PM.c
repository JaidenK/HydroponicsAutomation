/*******************************************************************************
* File Name: PeristalticPumpControl_PM.c
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

#include "PeristalticPumpControl.h"

/* Check for removal by optimization */
#if !defined(PeristalticPumpControl_Sync_ctrl_reg__REMOVED)

static PeristalticPumpControl_BACKUP_STRUCT  PeristalticPumpControl_backup = {0u};

    
/*******************************************************************************
* Function Name: PeristalticPumpControl_SaveConfig
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
void PeristalticPumpControl_SaveConfig(void) 
{
    PeristalticPumpControl_backup.controlState = PeristalticPumpControl_Control;
}


/*******************************************************************************
* Function Name: PeristalticPumpControl_RestoreConfig
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
void PeristalticPumpControl_RestoreConfig(void) 
{
     PeristalticPumpControl_Control = PeristalticPumpControl_backup.controlState;
}


/*******************************************************************************
* Function Name: PeristalticPumpControl_Sleep
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
void PeristalticPumpControl_Sleep(void) 
{
    PeristalticPumpControl_SaveConfig();
}


/*******************************************************************************
* Function Name: PeristalticPumpControl_Wakeup
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
void PeristalticPumpControl_Wakeup(void)  
{
    PeristalticPumpControl_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
