/*******************************************************************************
* File Name: ECSenseUART_PM.c
* Version 2.50
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

#include "ECSenseUART.h"


/***************************************
* Local data allocation
***************************************/

static ECSenseUART_BACKUP_STRUCT  ECSenseUART_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: ECSenseUART_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the ECSenseUART_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ECSenseUART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ECSenseUART_SaveConfig(void)
{
    #if(ECSenseUART_CONTROL_REG_REMOVED == 0u)
        ECSenseUART_backup.cr = ECSenseUART_CONTROL_REG;
    #endif /* End ECSenseUART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: ECSenseUART_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ECSenseUART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling ECSenseUART_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void ECSenseUART_RestoreConfig(void)
{
    #if(ECSenseUART_CONTROL_REG_REMOVED == 0u)
        ECSenseUART_CONTROL_REG = ECSenseUART_backup.cr;
    #endif /* End ECSenseUART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: ECSenseUART_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The ECSenseUART_Sleep() API saves the current component state. Then it
*  calls the ECSenseUART_Stop() function and calls 
*  ECSenseUART_SaveConfig() to save the hardware configuration.
*  Call the ECSenseUART_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ECSenseUART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ECSenseUART_Sleep(void)
{
    #if(ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED)
        if((ECSenseUART_RXSTATUS_ACTL_REG  & ECSenseUART_INT_ENABLE) != 0u)
        {
            ECSenseUART_backup.enableState = 1u;
        }
        else
        {
            ECSenseUART_backup.enableState = 0u;
        }
    #else
        if((ECSenseUART_TXSTATUS_ACTL_REG  & ECSenseUART_INT_ENABLE) !=0u)
        {
            ECSenseUART_backup.enableState = 1u;
        }
        else
        {
            ECSenseUART_backup.enableState = 0u;
        }
    #endif /* End ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED*/

    ECSenseUART_Stop();
    ECSenseUART_SaveConfig();
}


/*******************************************************************************
* Function Name: ECSenseUART_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  ECSenseUART_Sleep() was called. The ECSenseUART_Wakeup() function
*  calls the ECSenseUART_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  ECSenseUART_Sleep() function was called, the ECSenseUART_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ECSenseUART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ECSenseUART_Wakeup(void)
{
    ECSenseUART_RestoreConfig();
    #if( (ECSenseUART_RX_ENABLED) || (ECSenseUART_HD_ENABLED) )
        ECSenseUART_ClearRxBuffer();
    #endif /* End (ECSenseUART_RX_ENABLED) || (ECSenseUART_HD_ENABLED) */
    #if(ECSenseUART_TX_ENABLED || ECSenseUART_HD_ENABLED)
        ECSenseUART_ClearTxBuffer();
    #endif /* End ECSenseUART_TX_ENABLED || ECSenseUART_HD_ENABLED */

    if(ECSenseUART_backup.enableState != 0u)
    {
        ECSenseUART_Enable();
    }
}


/* [] END OF FILE */
