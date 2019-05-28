/*******************************************************************************
* File Name: ECSenseUARTINT.c
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

#include "ECSenseUART.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (ECSenseUART_RX_INTERRUPT_ENABLED && (ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED))
    /*******************************************************************************
    * Function Name: ECSenseUART_RXISR
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
    *  ECSenseUART_rxBuffer - RAM buffer pointer for save received data.
    *  ECSenseUART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  ECSenseUART_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  ECSenseUART_rxBufferOverflow - software overflow flag. Set to one
    *     when ECSenseUART_rxBufferWrite index overtakes
    *     ECSenseUART_rxBufferRead index.
    *  ECSenseUART_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when ECSenseUART_rxBufferWrite is equal to
    *    ECSenseUART_rxBufferRead
    *  ECSenseUART_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  ECSenseUART_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(ECSenseUART_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef ECSenseUART_RXISR_ENTRY_CALLBACK
        ECSenseUART_RXISR_EntryCallback();
    #endif /* ECSenseUART_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START ECSenseUART_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = ECSenseUART_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in ECSenseUART_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (ECSenseUART_RX_STS_BREAK | 
                            ECSenseUART_RX_STS_PAR_ERROR |
                            ECSenseUART_RX_STS_STOP_ERROR | 
                            ECSenseUART_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                ECSenseUART_errorStatus |= readStatus & ( ECSenseUART_RX_STS_BREAK | 
                                                            ECSenseUART_RX_STS_PAR_ERROR | 
                                                            ECSenseUART_RX_STS_STOP_ERROR | 
                                                            ECSenseUART_RX_STS_OVERRUN);
                /* `#START ECSenseUART_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef ECSenseUART_RXISR_ERROR_CALLBACK
                ECSenseUART_RXISR_ERROR_Callback();
            #endif /* ECSenseUART_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & ECSenseUART_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = ECSenseUART_RXDATA_REG;
            #if (ECSenseUART_RXHW_ADDRESS_ENABLED)
                if(ECSenseUART_rxAddressMode == (uint8)ECSenseUART__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & ECSenseUART_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & ECSenseUART_RX_STS_ADDR_MATCH) != 0u)
                        {
                            ECSenseUART_rxAddressDetected = 1u;
                        }
                        else
                        {
                            ECSenseUART_rxAddressDetected = 0u;
                        }
                    }
                    if(ECSenseUART_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        ECSenseUART_rxBuffer[ECSenseUART_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    ECSenseUART_rxBuffer[ECSenseUART_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                ECSenseUART_rxBuffer[ECSenseUART_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (ECSenseUART_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(ECSenseUART_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        ECSenseUART_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    ECSenseUART_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(ECSenseUART_rxBufferWrite >= ECSenseUART_RX_BUFFER_SIZE)
                    {
                        ECSenseUART_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(ECSenseUART_rxBufferWrite == ECSenseUART_rxBufferRead)
                    {
                        ECSenseUART_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (ECSenseUART_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            ECSenseUART_RXSTATUS_MASK_REG  &= (uint8)~ECSenseUART_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(ECSenseUART_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (ECSenseUART_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & ECSenseUART_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START ECSenseUART_RXISR_END` */

        /* `#END` */

    #ifdef ECSenseUART_RXISR_EXIT_CALLBACK
        ECSenseUART_RXISR_ExitCallback();
    #endif /* ECSenseUART_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (ECSenseUART_RX_INTERRUPT_ENABLED && (ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED)) */


#if (ECSenseUART_TX_INTERRUPT_ENABLED && ECSenseUART_TX_ENABLED)
    /*******************************************************************************
    * Function Name: ECSenseUART_TXISR
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
    *  ECSenseUART_txBuffer - RAM buffer pointer for transmit data from.
    *  ECSenseUART_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  ECSenseUART_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(ECSenseUART_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef ECSenseUART_TXISR_ENTRY_CALLBACK
        ECSenseUART_TXISR_EntryCallback();
    #endif /* ECSenseUART_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START ECSenseUART_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((ECSenseUART_txBufferRead != ECSenseUART_txBufferWrite) &&
             ((ECSenseUART_TXSTATUS_REG & ECSenseUART_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(ECSenseUART_txBufferRead >= ECSenseUART_TX_BUFFER_SIZE)
            {
                ECSenseUART_txBufferRead = 0u;
            }

            ECSenseUART_TXDATA_REG = ECSenseUART_txBuffer[ECSenseUART_txBufferRead];

            /* Set next pointer */
            ECSenseUART_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START ECSenseUART_TXISR_END` */

        /* `#END` */

    #ifdef ECSenseUART_TXISR_EXIT_CALLBACK
        ECSenseUART_TXISR_ExitCallback();
    #endif /* ECSenseUART_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (ECSenseUART_TX_INTERRUPT_ENABLED && ECSenseUART_TX_ENABLED) */


/* [] END OF FILE */
