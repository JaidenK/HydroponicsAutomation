/*******************************************************************************
* File Name: pHDelSigADC_PM.c
* Version 3.30
*
* Description:
*  This file provides the power manager source code to the API for the
*  Delta-Sigma ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "pHDelSigADC.h"

static pHDelSigADC_BACKUP_STRUCT pHDelSigADC_backup =
{
    pHDelSigADC_DISABLED,
    pHDelSigADC_CFG1_DEC_CR
};


/*******************************************************************************
* Function Name: pHDelSigADC_SaveConfig
********************************************************************************
*
* Summary:
*  Save the register configuration which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  pHDelSigADC_backup:  This global structure variable is used to store
*  configuration registers which are non retention whenever user wants to go
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void pHDelSigADC_SaveConfig(void) 
{
    pHDelSigADC_backup.deccr = pHDelSigADC_DEC_CR_REG;
}


/*******************************************************************************
* Function Name: pHDelSigADC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  pHDelSigADC_backup:  This global structure variable is used to restore
*  configuration registers which are non retention whenever user wants to switch
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void pHDelSigADC_RestoreConfig(void) 
{
    pHDelSigADC_DEC_CR_REG = pHDelSigADC_backup.deccr;
}


/*******************************************************************************
* Function Name: pHDelSigADC_Sleep
********************************************************************************
*
* Summary:
*  Stops the operation of the block and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  pHDelSigADC_backup:  The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void pHDelSigADC_Sleep(void) 
{
    /* Save ADC enable state */
    if((pHDelSigADC_ACT_PWR_DEC_EN == (pHDelSigADC_PWRMGR_DEC_REG & pHDelSigADC_ACT_PWR_DEC_EN)) &&
       (pHDelSigADC_ACT_PWR_DSM_EN == (pHDelSigADC_PWRMGR_DSM_REG & pHDelSigADC_ACT_PWR_DSM_EN)))
    {
        /* Component is enabled */
        pHDelSigADC_backup.enableState = pHDelSigADC_ENABLED;
        if((pHDelSigADC_DEC_CR_REG & pHDelSigADC_DEC_START_CONV) != 0u)
        {   
            /* Conversion is started */
            pHDelSigADC_backup.enableState |= pHDelSigADC_STARTED;
        }
		
        /* Stop the configuration */
        pHDelSigADC_Stop();
    }
    else
    {
        /* Component is disabled */
        pHDelSigADC_backup.enableState = pHDelSigADC_DISABLED;
    }

    /* Save the user configuration */
    pHDelSigADC_SaveConfig();
}


/*******************************************************************************
* Function Name: pHDelSigADC_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and enables the power to the block.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  pHDelSigADC_backup:  The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void pHDelSigADC_Wakeup(void) 
{
    /* Restore the configuration */
    pHDelSigADC_RestoreConfig();

    /* Enables the component operation */
    if(pHDelSigADC_backup.enableState != pHDelSigADC_DISABLED)
    {
        pHDelSigADC_Enable();
        if((pHDelSigADC_backup.enableState & pHDelSigADC_STARTED) != 0u)
        {
            pHDelSigADC_StartConvert();
        }
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
