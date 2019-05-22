/*******************************************************************************
* File Name: FlowSensorCounter_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "FlowSensorCounter.h"

static FlowSensorCounter_backupStruct FlowSensorCounter_backup;


/*******************************************************************************
* Function Name: FlowSensorCounter_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  FlowSensorCounter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void FlowSensorCounter_SaveConfig(void) 
{
    #if (!FlowSensorCounter_UsingFixedFunction)

        FlowSensorCounter_backup.CounterUdb = FlowSensorCounter_ReadCounter();

        #if(!FlowSensorCounter_ControlRegRemoved)
            FlowSensorCounter_backup.CounterControlRegister = FlowSensorCounter_ReadControlRegister();
        #endif /* (!FlowSensorCounter_ControlRegRemoved) */

    #endif /* (!FlowSensorCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FlowSensorCounter_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  FlowSensorCounter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void FlowSensorCounter_RestoreConfig(void) 
{      
    #if (!FlowSensorCounter_UsingFixedFunction)

       FlowSensorCounter_WriteCounter(FlowSensorCounter_backup.CounterUdb);

        #if(!FlowSensorCounter_ControlRegRemoved)
            FlowSensorCounter_WriteControlRegister(FlowSensorCounter_backup.CounterControlRegister);
        #endif /* (!FlowSensorCounter_ControlRegRemoved) */

    #endif /* (!FlowSensorCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FlowSensorCounter_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  FlowSensorCounter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void FlowSensorCounter_Sleep(void) 
{
    #if(!FlowSensorCounter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(FlowSensorCounter_CTRL_ENABLE == (FlowSensorCounter_CONTROL & FlowSensorCounter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            FlowSensorCounter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            FlowSensorCounter_backup.CounterEnableState = 0u;
        }
    #else
        FlowSensorCounter_backup.CounterEnableState = 1u;
        if(FlowSensorCounter_backup.CounterEnableState != 0u)
        {
            FlowSensorCounter_backup.CounterEnableState = 0u;
        }
    #endif /* (!FlowSensorCounter_ControlRegRemoved) */
    
    FlowSensorCounter_Stop();
    FlowSensorCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: FlowSensorCounter_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  FlowSensorCounter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void FlowSensorCounter_Wakeup(void) 
{
    FlowSensorCounter_RestoreConfig();
    #if(!FlowSensorCounter_ControlRegRemoved)
        if(FlowSensorCounter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            FlowSensorCounter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!FlowSensorCounter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
