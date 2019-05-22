/*******************************************************************************
* File Name: pHADC_PM.c
* Version 3.10
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "pHADC.h"


/***************************************
* Local data allocation
***************************************/

static pHADC_BACKUP_STRUCT  pHADC_backup =
{
    pHADC_DISABLED
};


/*******************************************************************************
* Function Name: pHADC_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void pHADC_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: pHADC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void pHADC_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: pHADC_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The pHADC_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  pHADC_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void pHADC_Sleep(void)
{
    if((pHADC_PWRMGR_SAR_REG  & pHADC_ACT_PWR_SAR_EN) != 0u)
    {
        if((pHADC_SAR_CSR0_REG & pHADC_SAR_SOF_START_CONV) != 0u)
        {
            pHADC_backup.enableState = pHADC_ENABLED | pHADC_STARTED;
        }
        else
        {
            pHADC_backup.enableState = pHADC_ENABLED;
        }
        pHADC_Stop();
    }
    else
    {
        pHADC_backup.enableState = pHADC_DISABLED;
    }
}


/*******************************************************************************
* Function Name: pHADC_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  pHADC_Sleep() was called. If the component was enabled before the
*  pHADC_Sleep() function was called, the
*  pHADC_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  pHADC_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void pHADC_Wakeup(void)
{
    if(pHADC_backup.enableState != pHADC_DISABLED)
    {
        pHADC_Enable();
        #if(pHADC_DEFAULT_CONV_MODE != pHADC__HARDWARE_TRIGGER)
            if((pHADC_backup.enableState & pHADC_STARTED) != 0u)
            {
                pHADC_StartConvert();
            }
        #endif /* End pHADC_DEFAULT_CONV_MODE != pHADC__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
