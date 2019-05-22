/*******************************************************************************
* File Name: HalfBridgeControl_PM.c
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

#include "HalfBridgeControl.h"

/* Check for removal by optimization */
#if !defined(HalfBridgeControl_Sync_ctrl_reg__REMOVED)

static HalfBridgeControl_BACKUP_STRUCT  HalfBridgeControl_backup = {0u};

    
/*******************************************************************************
* Function Name: HalfBridgeControl_SaveConfig
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
void HalfBridgeControl_SaveConfig(void) 
{
    HalfBridgeControl_backup.controlState = HalfBridgeControl_Control;
}


/*******************************************************************************
* Function Name: HalfBridgeControl_RestoreConfig
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
void HalfBridgeControl_RestoreConfig(void) 
{
     HalfBridgeControl_Control = HalfBridgeControl_backup.controlState;
}


/*******************************************************************************
* Function Name: HalfBridgeControl_Sleep
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
void HalfBridgeControl_Sleep(void) 
{
    HalfBridgeControl_SaveConfig();
}


/*******************************************************************************
* Function Name: HalfBridgeControl_Wakeup
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
void HalfBridgeControl_Wakeup(void)  
{
    HalfBridgeControl_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
