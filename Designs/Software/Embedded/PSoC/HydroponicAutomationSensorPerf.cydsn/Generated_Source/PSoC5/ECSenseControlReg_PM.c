/*******************************************************************************
* File Name: ECSenseControlReg_PM.c
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

#include "ECSenseControlReg.h"

/* Check for removal by optimization */
#if !defined(ECSenseControlReg_Sync_ctrl_reg__REMOVED)

static ECSenseControlReg_BACKUP_STRUCT  ECSenseControlReg_backup = {0u};

    
/*******************************************************************************
* Function Name: ECSenseControlReg_SaveConfig
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
void ECSenseControlReg_SaveConfig(void) 
{
    ECSenseControlReg_backup.controlState = ECSenseControlReg_Control;
}


/*******************************************************************************
* Function Name: ECSenseControlReg_RestoreConfig
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
void ECSenseControlReg_RestoreConfig(void) 
{
     ECSenseControlReg_Control = ECSenseControlReg_backup.controlState;
}


/*******************************************************************************
* Function Name: ECSenseControlReg_Sleep
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
void ECSenseControlReg_Sleep(void) 
{
    ECSenseControlReg_SaveConfig();
}


/*******************************************************************************
* Function Name: ECSenseControlReg_Wakeup
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
void ECSenseControlReg_Wakeup(void)  
{
    ECSenseControlReg_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
