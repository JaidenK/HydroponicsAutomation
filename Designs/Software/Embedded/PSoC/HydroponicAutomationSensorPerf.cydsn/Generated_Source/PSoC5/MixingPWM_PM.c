/*******************************************************************************
* File Name: MixingPWM_PM.c
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

#include "MixingPWM.h"

static MixingPWM_backupStruct MixingPWM_backup;


/*******************************************************************************
* Function Name: MixingPWM_SaveConfig
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
*  MixingPWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void MixingPWM_SaveConfig(void) 
{

    #if(!MixingPWM_UsingFixedFunction)
        #if(!MixingPWM_PWMModeIsCenterAligned)
            MixingPWM_backup.PWMPeriod = MixingPWM_ReadPeriod();
        #endif /* (!MixingPWM_PWMModeIsCenterAligned) */
        MixingPWM_backup.PWMUdb = MixingPWM_ReadCounter();
        #if (MixingPWM_UseStatus)
            MixingPWM_backup.InterruptMaskValue = MixingPWM_STATUS_MASK;
        #endif /* (MixingPWM_UseStatus) */

        #if(MixingPWM_DeadBandMode == MixingPWM__B_PWM__DBM_256_CLOCKS || \
            MixingPWM_DeadBandMode == MixingPWM__B_PWM__DBM_2_4_CLOCKS)
            MixingPWM_backup.PWMdeadBandValue = MixingPWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(MixingPWM_KillModeMinTime)
             MixingPWM_backup.PWMKillCounterPeriod = MixingPWM_ReadKillTime();
        #endif /* (MixingPWM_KillModeMinTime) */

        #if(MixingPWM_UseControl)
            MixingPWM_backup.PWMControlRegister = MixingPWM_ReadControlRegister();
        #endif /* (MixingPWM_UseControl) */
    #endif  /* (!MixingPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MixingPWM_RestoreConfig
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
*  MixingPWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MixingPWM_RestoreConfig(void) 
{
        #if(!MixingPWM_UsingFixedFunction)
            #if(!MixingPWM_PWMModeIsCenterAligned)
                MixingPWM_WritePeriod(MixingPWM_backup.PWMPeriod);
            #endif /* (!MixingPWM_PWMModeIsCenterAligned) */

            MixingPWM_WriteCounter(MixingPWM_backup.PWMUdb);

            #if (MixingPWM_UseStatus)
                MixingPWM_STATUS_MASK = MixingPWM_backup.InterruptMaskValue;
            #endif /* (MixingPWM_UseStatus) */

            #if(MixingPWM_DeadBandMode == MixingPWM__B_PWM__DBM_256_CLOCKS || \
                MixingPWM_DeadBandMode == MixingPWM__B_PWM__DBM_2_4_CLOCKS)
                MixingPWM_WriteDeadTime(MixingPWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(MixingPWM_KillModeMinTime)
                MixingPWM_WriteKillTime(MixingPWM_backup.PWMKillCounterPeriod);
            #endif /* (MixingPWM_KillModeMinTime) */

            #if(MixingPWM_UseControl)
                MixingPWM_WriteControlRegister(MixingPWM_backup.PWMControlRegister);
            #endif /* (MixingPWM_UseControl) */
        #endif  /* (!MixingPWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: MixingPWM_Sleep
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
*  MixingPWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MixingPWM_Sleep(void) 
{
    #if(MixingPWM_UseControl)
        if(MixingPWM_CTRL_ENABLE == (MixingPWM_CONTROL & MixingPWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            MixingPWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            MixingPWM_backup.PWMEnableState = 0u;
        }
    #endif /* (MixingPWM_UseControl) */

    /* Stop component */
    MixingPWM_Stop();

    /* Save registers configuration */
    MixingPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: MixingPWM_Wakeup
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
*  MixingPWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MixingPWM_Wakeup(void) 
{
     /* Restore registers values */
    MixingPWM_RestoreConfig();

    if(MixingPWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        MixingPWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
