/*******************************************************************************
* File Name: FlowSpeedPWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "FlowSpeedPWM.h"

static FlowSpeedPWM_backupStruct FlowSpeedPWM_backup;


/*******************************************************************************
* Function Name: FlowSpeedPWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  FlowSpeedPWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void FlowSpeedPWM_SaveConfig(void) 
{

    #if(!FlowSpeedPWM_UsingFixedFunction)
        #if(!FlowSpeedPWM_PWMModeIsCenterAligned)
            FlowSpeedPWM_backup.PWMPeriod = FlowSpeedPWM_ReadPeriod();
        #endif /* (!FlowSpeedPWM_PWMModeIsCenterAligned) */
        FlowSpeedPWM_backup.PWMUdb = FlowSpeedPWM_ReadCounter();
        #if (FlowSpeedPWM_UseStatus)
            FlowSpeedPWM_backup.InterruptMaskValue = FlowSpeedPWM_STATUS_MASK;
        #endif /* (FlowSpeedPWM_UseStatus) */

        #if(FlowSpeedPWM_DeadBandMode == FlowSpeedPWM__B_PWM__DBM_256_CLOCKS || \
            FlowSpeedPWM_DeadBandMode == FlowSpeedPWM__B_PWM__DBM_2_4_CLOCKS)
            FlowSpeedPWM_backup.PWMdeadBandValue = FlowSpeedPWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(FlowSpeedPWM_KillModeMinTime)
             FlowSpeedPWM_backup.PWMKillCounterPeriod = FlowSpeedPWM_ReadKillTime();
        #endif /* (FlowSpeedPWM_KillModeMinTime) */

        #if(FlowSpeedPWM_UseControl)
            FlowSpeedPWM_backup.PWMControlRegister = FlowSpeedPWM_ReadControlRegister();
        #endif /* (FlowSpeedPWM_UseControl) */
    #endif  /* (!FlowSpeedPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FlowSpeedPWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  FlowSpeedPWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void FlowSpeedPWM_RestoreConfig(void) 
{
        #if(!FlowSpeedPWM_UsingFixedFunction)
            #if(!FlowSpeedPWM_PWMModeIsCenterAligned)
                FlowSpeedPWM_WritePeriod(FlowSpeedPWM_backup.PWMPeriod);
            #endif /* (!FlowSpeedPWM_PWMModeIsCenterAligned) */

            FlowSpeedPWM_WriteCounter(FlowSpeedPWM_backup.PWMUdb);

            #if (FlowSpeedPWM_UseStatus)
                FlowSpeedPWM_STATUS_MASK = FlowSpeedPWM_backup.InterruptMaskValue;
            #endif /* (FlowSpeedPWM_UseStatus) */

            #if(FlowSpeedPWM_DeadBandMode == FlowSpeedPWM__B_PWM__DBM_256_CLOCKS || \
                FlowSpeedPWM_DeadBandMode == FlowSpeedPWM__B_PWM__DBM_2_4_CLOCKS)
                FlowSpeedPWM_WriteDeadTime(FlowSpeedPWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(FlowSpeedPWM_KillModeMinTime)
                FlowSpeedPWM_WriteKillTime(FlowSpeedPWM_backup.PWMKillCounterPeriod);
            #endif /* (FlowSpeedPWM_KillModeMinTime) */

            #if(FlowSpeedPWM_UseControl)
                FlowSpeedPWM_WriteControlRegister(FlowSpeedPWM_backup.PWMControlRegister);
            #endif /* (FlowSpeedPWM_UseControl) */
        #endif  /* (!FlowSpeedPWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: FlowSpeedPWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  FlowSpeedPWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void FlowSpeedPWM_Sleep(void) 
{
    #if(FlowSpeedPWM_UseControl)
        if(FlowSpeedPWM_CTRL_ENABLE == (FlowSpeedPWM_CONTROL & FlowSpeedPWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            FlowSpeedPWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            FlowSpeedPWM_backup.PWMEnableState = 0u;
        }
    #endif /* (FlowSpeedPWM_UseControl) */

    /* Stop component */
    FlowSpeedPWM_Stop();

    /* Save registers configuration */
    FlowSpeedPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: FlowSpeedPWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  FlowSpeedPWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void FlowSpeedPWM_Wakeup(void) 
{
     /* Restore registers values */
    FlowSpeedPWM_RestoreConfig();

    if(FlowSpeedPWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        FlowSpeedPWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
