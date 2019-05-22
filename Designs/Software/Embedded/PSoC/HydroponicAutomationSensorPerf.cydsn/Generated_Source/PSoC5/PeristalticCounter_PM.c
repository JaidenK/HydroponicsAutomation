/*******************************************************************************
* File Name: PeristalticCounter_PM.c  
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

#include "PeristalticCounter.h"

static PeristalticCounter_backupStruct PeristalticCounter_backup;


/*******************************************************************************
* Function Name: PeristalticCounter_SaveConfig
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
*  PeristalticCounter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PeristalticCounter_SaveConfig(void) 
{
    #if (!PeristalticCounter_UsingFixedFunction)

        PeristalticCounter_backup.CounterUdb = PeristalticCounter_ReadCounter();

        #if(!PeristalticCounter_ControlRegRemoved)
            PeristalticCounter_backup.CounterControlRegister = PeristalticCounter_ReadControlRegister();
        #endif /* (!PeristalticCounter_ControlRegRemoved) */

    #endif /* (!PeristalticCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PeristalticCounter_RestoreConfig
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
*  PeristalticCounter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PeristalticCounter_RestoreConfig(void) 
{      
    #if (!PeristalticCounter_UsingFixedFunction)

       PeristalticCounter_WriteCounter(PeristalticCounter_backup.CounterUdb);

        #if(!PeristalticCounter_ControlRegRemoved)
            PeristalticCounter_WriteControlRegister(PeristalticCounter_backup.CounterControlRegister);
        #endif /* (!PeristalticCounter_ControlRegRemoved) */

    #endif /* (!PeristalticCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PeristalticCounter_Sleep
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
*  PeristalticCounter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PeristalticCounter_Sleep(void) 
{
    #if(!PeristalticCounter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(PeristalticCounter_CTRL_ENABLE == (PeristalticCounter_CONTROL & PeristalticCounter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            PeristalticCounter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            PeristalticCounter_backup.CounterEnableState = 0u;
        }
    #else
        PeristalticCounter_backup.CounterEnableState = 1u;
        if(PeristalticCounter_backup.CounterEnableState != 0u)
        {
            PeristalticCounter_backup.CounterEnableState = 0u;
        }
    #endif /* (!PeristalticCounter_ControlRegRemoved) */
    
    PeristalticCounter_Stop();
    PeristalticCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: PeristalticCounter_Wakeup
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
*  PeristalticCounter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PeristalticCounter_Wakeup(void) 
{
    PeristalticCounter_RestoreConfig();
    #if(!PeristalticCounter_ControlRegRemoved)
        if(PeristalticCounter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            PeristalticCounter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!PeristalticCounter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
