/*******************************************************************************
* File Name: ECADC_PM.c
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

#include "ECADC.h"

static ECADC_BACKUP_STRUCT ECADC_backup =
{
    ECADC_DISABLED,
    ECADC_CFG1_DEC_CR
};


/*******************************************************************************
* Function Name: ECADC_SaveConfig
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
*  ECADC_backup:  This global structure variable is used to store
*  configuration registers which are non retention whenever user wants to go
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void ECADC_SaveConfig(void) 
{
    ECADC_backup.deccr = ECADC_DEC_CR_REG;
}


/*******************************************************************************
* Function Name: ECADC_RestoreConfig
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
*  ECADC_backup:  This global structure variable is used to restore
*  configuration registers which are non retention whenever user wants to switch
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void ECADC_RestoreConfig(void) 
{
    ECADC_DEC_CR_REG = ECADC_backup.deccr;
}


/*******************************************************************************
* Function Name: ECADC_Sleep
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
*  ECADC_backup:  The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ECADC_Sleep(void) 
{
    /* Save ADC enable state */
    if((ECADC_ACT_PWR_DEC_EN == (ECADC_PWRMGR_DEC_REG & ECADC_ACT_PWR_DEC_EN)) &&
       (ECADC_ACT_PWR_DSM_EN == (ECADC_PWRMGR_DSM_REG & ECADC_ACT_PWR_DSM_EN)))
    {
        /* Component is enabled */
        ECADC_backup.enableState = ECADC_ENABLED;
        if((ECADC_DEC_CR_REG & ECADC_DEC_START_CONV) != 0u)
        {   
            /* Conversion is started */
            ECADC_backup.enableState |= ECADC_STARTED;
        }
		
        /* Stop the configuration */
        ECADC_Stop();
    }
    else
    {
        /* Component is disabled */
        ECADC_backup.enableState = ECADC_DISABLED;
    }

    /* Save the user configuration */
    ECADC_SaveConfig();
}


/*******************************************************************************
* Function Name: ECADC_Wakeup
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
*  ECADC_backup:  The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void ECADC_Wakeup(void) 
{
    /* Restore the configuration */
    ECADC_RestoreConfig();

    /* Enables the component operation */
    if(ECADC_backup.enableState != ECADC_DISABLED)
    {
        ECADC_Enable();
        if((ECADC_backup.enableState & ECADC_STARTED) != 0u)
        {
            ECADC_StartConvert();
        }
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
