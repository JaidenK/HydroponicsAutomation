/*******************************************************************************
* File Name: PeristalticPWM_PM.c
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

#include "PeristalticPWM.h"

static PeristalticPWM_backupStruct PeristalticPWM_backup;


/*******************************************************************************
* Function Name: PeristalticPWM_SaveConfig
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
*  PeristalticPWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PeristalticPWM_SaveConfig(void) 
{

    #if(!PeristalticPWM_UsingFixedFunction)
        #if(!PeristalticPWM_PWMModeIsCenterAligned)
            PeristalticPWM_backup.PWMPeriod = PeristalticPWM_ReadPeriod();
        #endif /* (!PeristalticPWM_PWMModeIsCenterAligned) */
        PeristalticPWM_backup.PWMUdb = PeristalticPWM_ReadCounter();
        #if (PeristalticPWM_UseStatus)
            PeristalticPWM_backup.InterruptMaskValue = PeristalticPWM_STATUS_MASK;
        #endif /* (PeristalticPWM_UseStatus) */

        #if(PeristalticPWM_DeadBandMode == PeristalticPWM__B_PWM__DBM_256_CLOCKS || \
            PeristalticPWM_DeadBandMode == PeristalticPWM__B_PWM__DBM_2_4_CLOCKS)
            PeristalticPWM_backup.PWMdeadBandValue = PeristalticPWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PeristalticPWM_KillModeMinTime)
             PeristalticPWM_backup.PWMKillCounterPeriod = PeristalticPWM_ReadKillTime();
        #endif /* (PeristalticPWM_KillModeMinTime) */

        #if(PeristalticPWM_UseControl)
            PeristalticPWM_backup.PWMControlRegister = PeristalticPWM_ReadControlRegister();
        #endif /* (PeristalticPWM_UseControl) */
    #endif  /* (!PeristalticPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PeristalticPWM_RestoreConfig
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
*  PeristalticPWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PeristalticPWM_RestoreConfig(void) 
{
        #if(!PeristalticPWM_UsingFixedFunction)
            #if(!PeristalticPWM_PWMModeIsCenterAligned)
                PeristalticPWM_WritePeriod(PeristalticPWM_backup.PWMPeriod);
            #endif /* (!PeristalticPWM_PWMModeIsCenterAligned) */

            PeristalticPWM_WriteCounter(PeristalticPWM_backup.PWMUdb);

            #if (PeristalticPWM_UseStatus)
                PeristalticPWM_STATUS_MASK = PeristalticPWM_backup.InterruptMaskValue;
            #endif /* (PeristalticPWM_UseStatus) */

            #if(PeristalticPWM_DeadBandMode == PeristalticPWM__B_PWM__DBM_256_CLOCKS || \
                PeristalticPWM_DeadBandMode == PeristalticPWM__B_PWM__DBM_2_4_CLOCKS)
                PeristalticPWM_WriteDeadTime(PeristalticPWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PeristalticPWM_KillModeMinTime)
                PeristalticPWM_WriteKillTime(PeristalticPWM_backup.PWMKillCounterPeriod);
            #endif /* (PeristalticPWM_KillModeMinTime) */

            #if(PeristalticPWM_UseControl)
                PeristalticPWM_WriteControlRegister(PeristalticPWM_backup.PWMControlRegister);
            #endif /* (PeristalticPWM_UseControl) */
        #endif  /* (!PeristalticPWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PeristalticPWM_Sleep
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
*  PeristalticPWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PeristalticPWM_Sleep(void) 
{
    #if(PeristalticPWM_UseControl)
        if(PeristalticPWM_CTRL_ENABLE == (PeristalticPWM_CONTROL & PeristalticPWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            PeristalticPWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PeristalticPWM_backup.PWMEnableState = 0u;
        }
    #endif /* (PeristalticPWM_UseControl) */

    /* Stop component */
    PeristalticPWM_Stop();

    /* Save registers configuration */
    PeristalticPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: PeristalticPWM_Wakeup
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
*  PeristalticPWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PeristalticPWM_Wakeup(void) 
{
     /* Restore registers values */
    PeristalticPWM_RestoreConfig();

    if(PeristalticPWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PeristalticPWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
