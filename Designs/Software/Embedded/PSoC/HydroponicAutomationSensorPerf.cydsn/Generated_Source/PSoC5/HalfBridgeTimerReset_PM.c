/*******************************************************************************
* File Name: HalfBridgeTimerReset_PM.c
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

#include "HalfBridgeTimerReset.h"

/* Check for removal by optimization */
#if !defined(HalfBridgeTimerReset_Sync_ctrl_reg__REMOVED)

static HalfBridgeTimerReset_BACKUP_STRUCT  HalfBridgeTimerReset_backup = {0u};

    
/*******************************************************************************
* Function Name: HalfBridgeTimerReset_SaveConfig
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
void HalfBridgeTimerReset_SaveConfig(void) 
{
    HalfBridgeTimerReset_backup.controlState = HalfBridgeTimerReset_Control;
}


/*******************************************************************************
* Function Name: HalfBridgeTimerReset_RestoreConfig
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
void HalfBridgeTimerReset_RestoreConfig(void) 
{
     HalfBridgeTimerReset_Control = HalfBridgeTimerReset_backup.controlState;
}


/*******************************************************************************
* Function Name: HalfBridgeTimerReset_Sleep
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
void HalfBridgeTimerReset_Sleep(void) 
{
    HalfBridgeTimerReset_SaveConfig();
}


/*******************************************************************************
* Function Name: HalfBridgeTimerReset_Wakeup
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
void HalfBridgeTimerReset_Wakeup(void)  
{
    HalfBridgeTimerReset_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
