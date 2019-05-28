/*******************************************************************************
* File Name: SensorComTxUARTINT.c
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

#include "SensorComTxUART.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (SensorComTxUART_RX_INTERRUPT_ENABLED && (SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED))
    /*******************************************************************************
    * Function Name: SensorComTxUART_RXISR
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
    *  SensorComTxUART_rxBuffer - RAM buffer pointer for save received data.
    *  SensorComTxUART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  SensorComTxUART_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  SensorComTxUART_rxBufferOverflow - software overflow flag. Set to one
    *     when SensorComTxUART_rxBufferWrite index overtakes
    *     SensorComTxUART_rxBufferRead index.
    *  SensorComTxUART_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when SensorComTxUART_rxBufferWrite is equal to
    *    SensorComTxUART_rxBufferRead
    *  SensorComTxUART_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  SensorComTxUART_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(SensorComTxUART_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef SensorComTxUART_RXISR_ENTRY_CALLBACK
        SensorComTxUART_RXISR_EntryCallback();
    #endif /* SensorComTxUART_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START SensorComTxUART_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = SensorComTxUART_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in SensorComTxUART_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (SensorComTxUART_RX_STS_BREAK | 
                            SensorComTxUART_RX_STS_PAR_ERROR |
                            SensorComTxUART_RX_STS_STOP_ERROR | 
                            SensorComTxUART_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                SensorComTxUART_errorStatus |= readStatus & ( SensorComTxUART_RX_STS_BREAK | 
                                                            SensorComTxUART_RX_STS_PAR_ERROR | 
                                                            SensorComTxUART_RX_STS_STOP_ERROR | 
                                                            SensorComTxUART_RX_STS_OVERRUN);
                /* `#START SensorComTxUART_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef SensorComTxUART_RXISR_ERROR_CALLBACK
                SensorComTxUART_RXISR_ERROR_Callback();
            #endif /* SensorComTxUART_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & SensorComTxUART_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = SensorComTxUART_RXDATA_REG;
            #if (SensorComTxUART_RXHW_ADDRESS_ENABLED)
                if(SensorComTxUART_rxAddressMode == (uint8)SensorComTxUART__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & SensorComTxUART_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & SensorComTxUART_RX_STS_ADDR_MATCH) != 0u)
                        {
                            SensorComTxUART_rxAddressDetected = 1u;
                        }
                        else
                        {
                            SensorComTxUART_rxAddressDetected = 0u;
                        }
                    }
                    if(SensorComTxUART_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        SensorComTxUART_rxBuffer[SensorComTxUART_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    SensorComTxUART_rxBuffer[SensorComTxUART_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                SensorComTxUART_rxBuffer[SensorComTxUART_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (SensorComTxUART_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(SensorComTxUART_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        SensorComTxUART_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    SensorComTxUART_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(SensorComTxUART_rxBufferWrite >= SensorComTxUART_RX_BUFFER_SIZE)
                    {
                        SensorComTxUART_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(SensorComTxUART_rxBufferWrite == SensorComTxUART_rxBufferRead)
                    {
                        SensorComTxUART_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (SensorComTxUART_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            SensorComTxUART_RXSTATUS_MASK_REG  &= (uint8)~SensorComTxUART_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(SensorComTxUART_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (SensorComTxUART_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & SensorComTxUART_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START SensorComTxUART_RXISR_END` */

        /* `#END` */

    #ifdef SensorComTxUART_RXISR_EXIT_CALLBACK
        SensorComTxUART_RXISR_ExitCallback();
    #endif /* SensorComTxUART_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (SensorComTxUART_RX_INTERRUPT_ENABLED && (SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED)) */


#if (SensorComTxUART_TX_INTERRUPT_ENABLED && SensorComTxUART_TX_ENABLED)
    /*******************************************************************************
    * Function Name: SensorComTxUART_TXISR
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
    *  SensorComTxUART_txBuffer - RAM buffer pointer for transmit data from.
    *  SensorComTxUART_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  SensorComTxUART_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(SensorComTxUART_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef SensorComTxUART_TXISR_ENTRY_CALLBACK
        SensorComTxUART_TXISR_EntryCallback();
    #endif /* SensorComTxUART_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START SensorComTxUART_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((SensorComTxUART_txBufferRead != SensorComTxUART_txBufferWrite) &&
             ((SensorComTxUART_TXSTATUS_REG & SensorComTxUART_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(SensorComTxUART_txBufferRead >= SensorComTxUART_TX_BUFFER_SIZE)
            {
                SensorComTxUART_txBufferRead = 0u;
            }

            SensorComTxUART_TXDATA_REG = SensorComTxUART_txBuffer[SensorComTxUART_txBufferRead];

            /* Set next pointer */
            SensorComTxUART_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START SensorComTxUART_TXISR_END` */

        /* `#END` */

    #ifdef SensorComTxUART_TXISR_EXIT_CALLBACK
        SensorComTxUART_TXISR_ExitCallback();
    #endif /* SensorComTxUART_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (SensorComTxUART_TX_INTERRUPT_ENABLED && SensorComTxUART_TX_ENABLED) */


/* [] END OF FILE */
