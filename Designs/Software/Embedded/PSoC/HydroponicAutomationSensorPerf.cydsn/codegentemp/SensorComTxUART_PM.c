/*******************************************************************************
* File Name: SensorComTxUART_PM.c
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

#include "SensorComTxUART.h"


/***************************************
* Local data allocation
***************************************/

static SensorComTxUART_BACKUP_STRUCT  SensorComTxUART_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: SensorComTxUART_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the SensorComTxUART_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SensorComTxUART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SensorComTxUART_SaveConfig(void)
{
    #if(SensorComTxUART_CONTROL_REG_REMOVED == 0u)
        SensorComTxUART_backup.cr = SensorComTxUART_CONTROL_REG;
    #endif /* End SensorComTxUART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: SensorComTxUART_RestoreConfig
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
*  SensorComTxUART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling SensorComTxUART_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void SensorComTxUART_RestoreConfig(void)
{
    #if(SensorComTxUART_CONTROL_REG_REMOVED == 0u)
        SensorComTxUART_CONTROL_REG = SensorComTxUART_backup.cr;
    #endif /* End SensorComTxUART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: SensorComTxUART_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The SensorComTxUART_Sleep() API saves the current component state. Then it
*  calls the SensorComTxUART_Stop() function and calls 
*  SensorComTxUART_SaveConfig() to save the hardware configuration.
*  Call the SensorComTxUART_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SensorComTxUART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SensorComTxUART_Sleep(void)
{
    #if(SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED)
        if((SensorComTxUART_RXSTATUS_ACTL_REG  & SensorComTxUART_INT_ENABLE) != 0u)
        {
            SensorComTxUART_backup.enableState = 1u;
        }
        else
        {
            SensorComTxUART_backup.enableState = 0u;
        }
    #else
        if((SensorComTxUART_TXSTATUS_ACTL_REG  & SensorComTxUART_INT_ENABLE) !=0u)
        {
            SensorComTxUART_backup.enableState = 1u;
        }
        else
        {
            SensorComTxUART_backup.enableState = 0u;
        }
    #endif /* End SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED*/

    SensorComTxUART_Stop();
    SensorComTxUART_SaveConfig();
}


/*******************************************************************************
* Function Name: SensorComTxUART_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  SensorComTxUART_Sleep() was called. The SensorComTxUART_Wakeup() function
*  calls the SensorComTxUART_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  SensorComTxUART_Sleep() function was called, the SensorComTxUART_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SensorComTxUART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SensorComTxUART_Wakeup(void)
{
    SensorComTxUART_RestoreConfig();
    #if( (SensorComTxUART_RX_ENABLED) || (SensorComTxUART_HD_ENABLED) )
        SensorComTxUART_ClearRxBuffer();
    #endif /* End (SensorComTxUART_RX_ENABLED) || (SensorComTxUART_HD_ENABLED) */
    #if(SensorComTxUART_TX_ENABLED || SensorComTxUART_HD_ENABLED)
        SensorComTxUART_ClearTxBuffer();
    #endif /* End SensorComTxUART_TX_ENABLED || SensorComTxUART_HD_ENABLED */

    if(SensorComTxUART_backup.enableState != 0u)
    {
        SensorComTxUART_Enable();
    }
}


/* [] END OF FILE */
