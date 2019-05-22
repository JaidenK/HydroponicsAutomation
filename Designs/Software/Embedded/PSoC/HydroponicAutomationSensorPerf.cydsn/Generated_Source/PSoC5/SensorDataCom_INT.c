/*******************************************************************************
* File Name: SensorDataComINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SensorDataCom.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (SensorDataCom_RX_INTERRUPT_ENABLED && (SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED))
    /*******************************************************************************
    * Function Name: SensorDataCom_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  SensorDataCom_rxBuffer - RAM buffer pointer for save received data.
    *  SensorDataCom_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  SensorDataCom_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  SensorDataCom_rxBufferOverflow - software overflow flag. Set to one
    *     when SensorDataCom_rxBufferWrite index overtakes
    *     SensorDataCom_rxBufferRead index.
    *  SensorDataCom_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when SensorDataCom_rxBufferWrite is equal to
    *    SensorDataCom_rxBufferRead
    *  SensorDataCom_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  SensorDataCom_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(SensorDataCom_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef SensorDataCom_RXISR_ENTRY_CALLBACK
        SensorDataCom_RXISR_EntryCallback();
    #endif /* SensorDataCom_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START SensorDataCom_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = SensorDataCom_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in SensorDataCom_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (SensorDataCom_RX_STS_BREAK | 
                            SensorDataCom_RX_STS_PAR_ERROR |
                            SensorDataCom_RX_STS_STOP_ERROR | 
                            SensorDataCom_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                SensorDataCom_errorStatus |= readStatus & ( SensorDataCom_RX_STS_BREAK | 
                                                            SensorDataCom_RX_STS_PAR_ERROR | 
                                                            SensorDataCom_RX_STS_STOP_ERROR | 
                                                            SensorDataCom_RX_STS_OVERRUN);
                /* `#START SensorDataCom_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef SensorDataCom_RXISR_ERROR_CALLBACK
                SensorDataCom_RXISR_ERROR_Callback();
            #endif /* SensorDataCom_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & SensorDataCom_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = SensorDataCom_RXDATA_REG;
            #if (SensorDataCom_RXHW_ADDRESS_ENABLED)
                if(SensorDataCom_rxAddressMode == (uint8)SensorDataCom__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & SensorDataCom_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & SensorDataCom_RX_STS_ADDR_MATCH) != 0u)
                        {
                            SensorDataCom_rxAddressDetected = 1u;
                        }
                        else
                        {
                            SensorDataCom_rxAddressDetected = 0u;
                        }
                    }
                    if(SensorDataCom_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        SensorDataCom_rxBuffer[SensorDataCom_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    SensorDataCom_rxBuffer[SensorDataCom_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                SensorDataCom_rxBuffer[SensorDataCom_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (SensorDataCom_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(SensorDataCom_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        SensorDataCom_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    SensorDataCom_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(SensorDataCom_rxBufferWrite >= SensorDataCom_RX_BUFFER_SIZE)
                    {
                        SensorDataCom_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(SensorDataCom_rxBufferWrite == SensorDataCom_rxBufferRead)
                    {
                        SensorDataCom_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (SensorDataCom_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            SensorDataCom_RXSTATUS_MASK_REG  &= (uint8)~SensorDataCom_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(SensorDataCom_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (SensorDataCom_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & SensorDataCom_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START SensorDataCom_RXISR_END` */

        /* `#END` */

    #ifdef SensorDataCom_RXISR_EXIT_CALLBACK
        SensorDataCom_RXISR_ExitCallback();
    #endif /* SensorDataCom_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (SensorDataCom_RX_INTERRUPT_ENABLED && (SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED)) */


#if (SensorDataCom_TX_INTERRUPT_ENABLED && SensorDataCom_TX_ENABLED)
    /*******************************************************************************
    * Function Name: SensorDataCom_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  SensorDataCom_txBuffer - RAM buffer pointer for transmit data from.
    *  SensorDataCom_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  SensorDataCom_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(SensorDataCom_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef SensorDataCom_TXISR_ENTRY_CALLBACK
        SensorDataCom_TXISR_EntryCallback();
    #endif /* SensorDataCom_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START SensorDataCom_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((SensorDataCom_txBufferRead != SensorDataCom_txBufferWrite) &&
             ((SensorDataCom_TXSTATUS_REG & SensorDataCom_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(SensorDataCom_txBufferRead >= SensorDataCom_TX_BUFFER_SIZE)
            {
                SensorDataCom_txBufferRead = 0u;
            }

            SensorDataCom_TXDATA_REG = SensorDataCom_txBuffer[SensorDataCom_txBufferRead];

            /* Set next pointer */
            SensorDataCom_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START SensorDataCom_TXISR_END` */

        /* `#END` */

    #ifdef SensorDataCom_TXISR_EXIT_CALLBACK
        SensorDataCom_TXISR_ExitCallback();
    #endif /* SensorDataCom_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (SensorDataCom_TX_INTERRUPT_ENABLED && SensorDataCom_TX_ENABLED) */


/* [] END OF FILE */
