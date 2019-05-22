/*******************************************************************************
* File Name: SensorDataCom_PM.c
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

#include "SensorDataCom.h"


/***************************************
* Local data allocation
***************************************/

static SensorDataCom_BACKUP_STRUCT  SensorDataCom_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: SensorDataCom_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the SensorDataCom_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SensorDataCom_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SensorDataCom_SaveConfig(void)
{
    #if(SensorDataCom_CONTROL_REG_REMOVED == 0u)
        SensorDataCom_backup.cr = SensorDataCom_CONTROL_REG;
    #endif /* End SensorDataCom_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: SensorDataCom_RestoreConfig
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
*  SensorDataCom_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling SensorDataCom_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void SensorDataCom_RestoreConfig(void)
{
    #if(SensorDataCom_CONTROL_REG_REMOVED == 0u)
        SensorDataCom_CONTROL_REG = SensorDataCom_backup.cr;
    #endif /* End SensorDataCom_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: SensorDataCom_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The SensorDataCom_Sleep() API saves the current component state. Then it
*  calls the SensorDataCom_Stop() function and calls 
*  SensorDataCom_SaveConfig() to save the hardware configuration.
*  Call the SensorDataCom_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SensorDataCom_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SensorDataCom_Sleep(void)
{
    #if(SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED)
        if((SensorDataCom_RXSTATUS_ACTL_REG  & SensorDataCom_INT_ENABLE) != 0u)
        {
            SensorDataCom_backup.enableState = 1u;
        }
        else
        {
            SensorDataCom_backup.enableState = 0u;
        }
    #else
        if((SensorDataCom_TXSTATUS_ACTL_REG  & SensorDataCom_INT_ENABLE) !=0u)
        {
            SensorDataCom_backup.enableState = 1u;
        }
        else
        {
            SensorDataCom_backup.enableState = 0u;
        }
    #endif /* End SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED*/

    SensorDataCom_Stop();
    SensorDataCom_SaveConfig();
}


/*******************************************************************************
* Function Name: SensorDataCom_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  SensorDataCom_Sleep() was called. The SensorDataCom_Wakeup() function
*  calls the SensorDataCom_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  SensorDataCom_Sleep() function was called, the SensorDataCom_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SensorDataCom_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SensorDataCom_Wakeup(void)
{
    SensorDataCom_RestoreConfig();
    #if( (SensorDataCom_RX_ENABLED) || (SensorDataCom_HD_ENABLED) )
        SensorDataCom_ClearRxBuffer();
    #endif /* End (SensorDataCom_RX_ENABLED) || (SensorDataCom_HD_ENABLED) */
    #if(SensorDataCom_TX_ENABLED || SensorDataCom_HD_ENABLED)
        SensorDataCom_ClearTxBuffer();
    #endif /* End SensorDataCom_TX_ENABLED || SensorDataCom_HD_ENABLED */

    if(SensorDataCom_backup.enableState != 0u)
    {
        SensorDataCom_Enable();
    }
}


/* [] END OF FILE */
