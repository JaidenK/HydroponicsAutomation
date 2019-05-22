/*******************************************************************************
* File Name: pHControllerpHDir_PM.c
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

#include "pHControllerpHDir.h"

/* Check for removal by optimization */
#if !defined(pHControllerpHDir_Sync_ctrl_reg__REMOVED)

static pHControllerpHDir_BACKUP_STRUCT  pHControllerpHDir_backup = {0u};

    
/*******************************************************************************
* Function Name: pHControllerpHDir_SaveConfig
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
void pHControllerpHDir_SaveConfig(void) 
{
    pHControllerpHDir_backup.controlState = pHControllerpHDir_Control;
}


/*******************************************************************************
* Function Name: pHControllerpHDir_RestoreConfig
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
void pHControllerpHDir_RestoreConfig(void) 
{
     pHControllerpHDir_Control = pHControllerpHDir_backup.controlState;
}


/*******************************************************************************
* Function Name: pHControllerpHDir_Sleep
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
void pHControllerpHDir_Sleep(void) 
{
    pHControllerpHDir_SaveConfig();
}


/*******************************************************************************
* Function Name: pHControllerpHDir_Wakeup
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
void pHControllerpHDir_Wakeup(void)  
{
    pHControllerpHDir_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
