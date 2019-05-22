/*******************************************************************************
* File Name: LevelSelect_PM.c
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

#include "LevelSelect.h"

/* Check for removal by optimization */
#if !defined(LevelSelect_Sync_ctrl_reg__REMOVED)

static LevelSelect_BACKUP_STRUCT  LevelSelect_backup = {0u};

    
/*******************************************************************************
* Function Name: LevelSelect_SaveConfig
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
void LevelSelect_SaveConfig(void) 
{
    LevelSelect_backup.controlState = LevelSelect_Control;
}


/*******************************************************************************
* Function Name: LevelSelect_RestoreConfig
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
void LevelSelect_RestoreConfig(void) 
{
     LevelSelect_Control = LevelSelect_backup.controlState;
}


/*******************************************************************************
* Function Name: LevelSelect_Sleep
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
void LevelSelect_Sleep(void) 
{
    LevelSelect_SaveConfig();
}


/*******************************************************************************
* Function Name: LevelSelect_Wakeup
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
void LevelSelect_Wakeup(void)  
{
    LevelSelect_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
