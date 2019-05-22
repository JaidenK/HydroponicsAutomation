/*******************************************************************************
* File Name: PingSensorTrigCounter_PM.c  
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

#include "PingSensorTrigCounter.h"

static PingSensorTrigCounter_backupStruct PingSensorTrigCounter_backup;


/*******************************************************************************
* Function Name: PingSensorTrigCounter_SaveConfig
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
*  PingSensorTrigCounter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PingSensorTrigCounter_SaveConfig(void) 
{
    #if (!PingSensorTrigCounter_UsingFixedFunction)

        PingSensorTrigCounter_backup.CounterUdb = PingSensorTrigCounter_ReadCounter();

        #if(!PingSensorTrigCounter_ControlRegRemoved)
            PingSensorTrigCounter_backup.CounterControlRegister = PingSensorTrigCounter_ReadControlRegister();
        #endif /* (!PingSensorTrigCounter_ControlRegRemoved) */

    #endif /* (!PingSensorTrigCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PingSensorTrigCounter_RestoreConfig
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
*  PingSensorTrigCounter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PingSensorTrigCounter_RestoreConfig(void) 
{      
    #if (!PingSensorTrigCounter_UsingFixedFunction)

       PingSensorTrigCounter_WriteCounter(PingSensorTrigCounter_backup.CounterUdb);

        #if(!PingSensorTrigCounter_ControlRegRemoved)
            PingSensorTrigCounter_WriteControlRegister(PingSensorTrigCounter_backup.CounterControlRegister);
        #endif /* (!PingSensorTrigCounter_ControlRegRemoved) */

    #endif /* (!PingSensorTrigCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PingSensorTrigCounter_Sleep
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
*  PingSensorTrigCounter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PingSensorTrigCounter_Sleep(void) 
{
    #if(!PingSensorTrigCounter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(PingSensorTrigCounter_CTRL_ENABLE == (PingSensorTrigCounter_CONTROL & PingSensorTrigCounter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            PingSensorTrigCounter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            PingSensorTrigCounter_backup.CounterEnableState = 0u;
        }
    #else
        PingSensorTrigCounter_backup.CounterEnableState = 1u;
        if(PingSensorTrigCounter_backup.CounterEnableState != 0u)
        {
            PingSensorTrigCounter_backup.CounterEnableState = 0u;
        }
    #endif /* (!PingSensorTrigCounter_ControlRegRemoved) */
    
    PingSensorTrigCounter_Stop();
    PingSensorTrigCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: PingSensorTrigCounter_Wakeup
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
*  PingSensorTrigCounter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PingSensorTrigCounter_Wakeup(void) 
{
    PingSensorTrigCounter_RestoreConfig();
    #if(!PingSensorTrigCounter_ControlRegRemoved)
        if(PingSensorTrigCounter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            PingSensorTrigCounter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!PingSensorTrigCounter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
