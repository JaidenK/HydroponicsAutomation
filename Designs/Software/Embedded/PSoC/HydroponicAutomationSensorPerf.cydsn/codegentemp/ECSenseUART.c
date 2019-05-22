/*******************************************************************************
* File Name: ECSenseUART.c
* Version 2.50
*
* Description:
*  This file provides all API functionality of the UART component
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
#if (ECSenseUART_INTERNAL_CLOCK_USED)
    #include "ECSenseUART_IntClock.h"
#endif /* End ECSenseUART_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 ECSenseUART_initVar = 0u;

#if (ECSenseUART_TX_INTERRUPT_ENABLED && ECSenseUART_TX_ENABLED)
    volatile uint8 ECSenseUART_txBuffer[ECSenseUART_TX_BUFFER_SIZE];
    volatile uint8 ECSenseUART_txBufferRead = 0u;
    uint8 ECSenseUART_txBufferWrite = 0u;
#endif /* (ECSenseUART_TX_INTERRUPT_ENABLED && ECSenseUART_TX_ENABLED) */

#if (ECSenseUART_RX_INTERRUPT_ENABLED && (ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED))
    uint8 ECSenseUART_errorStatus = 0u;
    volatile uint8 ECSenseUART_rxBuffer[ECSenseUART_RX_BUFFER_SIZE];
    volatile uint8 ECSenseUART_rxBufferRead  = 0u;
    volatile uint8 ECSenseUART_rxBufferWrite = 0u;
    volatile uint8 ECSenseUART_rxBufferLoopDetect = 0u;
    volatile uint8 ECSenseUART_rxBufferOverflow   = 0u;
    #if (ECSenseUART_RXHW_ADDRESS_ENABLED)
        volatile uint8 ECSenseUART_rxAddressMode = ECSenseUART_RX_ADDRESS_MODE;
        volatile uint8 ECSenseUART_rxAddressDetected = 0u;
    #endif /* (ECSenseUART_RXHW_ADDRESS_ENABLED) */
#endif /* (ECSenseUART_RX_INTERRUPT_ENABLED && (ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED)) */


/*******************************************************************************
* Function Name: ECSenseUART_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  ECSenseUART_Start() sets the initVar variable, calls the
*  ECSenseUART_Init() function, and then calls the
*  ECSenseUART_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The ECSenseUART_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time ECSenseUART_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the ECSenseUART_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ECSenseUART_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(ECSenseUART_initVar == 0u)
    {
        ECSenseUART_Init();
        ECSenseUART_initVar = 1u;
    }

    ECSenseUART_Enable();
}


/*******************************************************************************
* Function Name: ECSenseUART_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call ECSenseUART_Init() because
*  the ECSenseUART_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ECSenseUART_Init(void) 
{
    #if(ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED)

        #if (ECSenseUART_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(ECSenseUART_RX_VECT_NUM, &ECSenseUART_RXISR);
            CyIntSetPriority(ECSenseUART_RX_VECT_NUM, ECSenseUART_RX_PRIOR_NUM);
            ECSenseUART_errorStatus = 0u;
        #endif /* (ECSenseUART_RX_INTERRUPT_ENABLED) */

        #if (ECSenseUART_RXHW_ADDRESS_ENABLED)
            ECSenseUART_SetRxAddressMode(ECSenseUART_RX_ADDRESS_MODE);
            ECSenseUART_SetRxAddress1(ECSenseUART_RX_HW_ADDRESS1);
            ECSenseUART_SetRxAddress2(ECSenseUART_RX_HW_ADDRESS2);
        #endif /* End ECSenseUART_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        ECSenseUART_RXBITCTR_PERIOD_REG = ECSenseUART_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        ECSenseUART_RXSTATUS_MASK_REG  = ECSenseUART_INIT_RX_INTERRUPTS_MASK;
    #endif /* End ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED*/

    #if(ECSenseUART_TX_ENABLED)
        #if (ECSenseUART_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(ECSenseUART_TX_VECT_NUM, &ECSenseUART_TXISR);
            CyIntSetPriority(ECSenseUART_TX_VECT_NUM, ECSenseUART_TX_PRIOR_NUM);
        #endif /* (ECSenseUART_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (ECSenseUART_TXCLKGEN_DP)
            ECSenseUART_TXBITCLKGEN_CTR_REG = ECSenseUART_BIT_CENTER;
            ECSenseUART_TXBITCLKTX_COMPLETE_REG = ((ECSenseUART_NUMBER_OF_DATA_BITS +
                        ECSenseUART_NUMBER_OF_START_BIT) * ECSenseUART_OVER_SAMPLE_COUNT) - 1u;
        #else
            ECSenseUART_TXBITCTR_PERIOD_REG = ((ECSenseUART_NUMBER_OF_DATA_BITS +
                        ECSenseUART_NUMBER_OF_START_BIT) * ECSenseUART_OVER_SAMPLE_8) - 1u;
        #endif /* End ECSenseUART_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (ECSenseUART_TX_INTERRUPT_ENABLED)
            ECSenseUART_TXSTATUS_MASK_REG = ECSenseUART_TX_STS_FIFO_EMPTY;
        #else
            ECSenseUART_TXSTATUS_MASK_REG = ECSenseUART_INIT_TX_INTERRUPTS_MASK;
        #endif /*End ECSenseUART_TX_INTERRUPT_ENABLED*/

    #endif /* End ECSenseUART_TX_ENABLED */

    #if(ECSenseUART_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        ECSenseUART_WriteControlRegister( \
            (ECSenseUART_ReadControlRegister() & (uint8)~ECSenseUART_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(ECSenseUART_PARITY_TYPE << ECSenseUART_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End ECSenseUART_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: ECSenseUART_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call ECSenseUART_Enable() because the ECSenseUART_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ECSenseUART_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void ECSenseUART_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        ECSenseUART_RXBITCTR_CONTROL_REG |= ECSenseUART_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        ECSenseUART_RXSTATUS_ACTL_REG  |= ECSenseUART_INT_ENABLE;

        #if (ECSenseUART_RX_INTERRUPT_ENABLED)
            ECSenseUART_EnableRxInt();

            #if (ECSenseUART_RXHW_ADDRESS_ENABLED)
                ECSenseUART_rxAddressDetected = 0u;
            #endif /* (ECSenseUART_RXHW_ADDRESS_ENABLED) */
        #endif /* (ECSenseUART_RX_INTERRUPT_ENABLED) */
    #endif /* (ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED) */

    #if(ECSenseUART_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!ECSenseUART_TXCLKGEN_DP)
            ECSenseUART_TXBITCTR_CONTROL_REG |= ECSenseUART_CNTR_ENABLE;
        #endif /* End ECSenseUART_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        ECSenseUART_TXSTATUS_ACTL_REG |= ECSenseUART_INT_ENABLE;
        #if (ECSenseUART_TX_INTERRUPT_ENABLED)
            ECSenseUART_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            ECSenseUART_EnableTxInt();
        #endif /* (ECSenseUART_TX_INTERRUPT_ENABLED) */
     #endif /* (ECSenseUART_TX_INTERRUPT_ENABLED) */

    #if (ECSenseUART_INTERNAL_CLOCK_USED)
        ECSenseUART_IntClock_Start();  /* Enable the clock */
    #endif /* (ECSenseUART_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ECSenseUART_Stop
********************************************************************************
*
* Summary:
*  Disables the UART operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ECSenseUART_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED)
        ECSenseUART_RXBITCTR_CONTROL_REG &= (uint8) ~ECSenseUART_CNTR_ENABLE;
    #endif /* (ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED) */

    #if (ECSenseUART_TX_ENABLED)
        #if(!ECSenseUART_TXCLKGEN_DP)
            ECSenseUART_TXBITCTR_CONTROL_REG &= (uint8) ~ECSenseUART_CNTR_ENABLE;
        #endif /* (!ECSenseUART_TXCLKGEN_DP) */
    #endif /* (ECSenseUART_TX_ENABLED) */

    #if (ECSenseUART_INTERNAL_CLOCK_USED)
        ECSenseUART_IntClock_Stop();   /* Disable the clock */
    #endif /* (ECSenseUART_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED)
        ECSenseUART_RXSTATUS_ACTL_REG  &= (uint8) ~ECSenseUART_INT_ENABLE;

        #if (ECSenseUART_RX_INTERRUPT_ENABLED)
            ECSenseUART_DisableRxInt();
        #endif /* (ECSenseUART_RX_INTERRUPT_ENABLED) */
    #endif /* (ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED) */

    #if (ECSenseUART_TX_ENABLED)
        ECSenseUART_TXSTATUS_ACTL_REG &= (uint8) ~ECSenseUART_INT_ENABLE;

        #if (ECSenseUART_TX_INTERRUPT_ENABLED)
            ECSenseUART_DisableTxInt();
        #endif /* (ECSenseUART_TX_INTERRUPT_ENABLED) */
    #endif /* (ECSenseUART_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ECSenseUART_ReadControlRegister
********************************************************************************
*
* Summary:
*  Returns the current value of the control register.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the control register.
*
*******************************************************************************/
uint8 ECSenseUART_ReadControlRegister(void) 
{
    #if (ECSenseUART_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(ECSenseUART_CONTROL_REG);
    #endif /* (ECSenseUART_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: ECSenseUART_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  ECSenseUART_WriteControlRegister(uint8 control) 
{
    #if (ECSenseUART_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       ECSenseUART_CONTROL_REG = control;
    #endif /* (ECSenseUART_CONTROL_REG_REMOVED) */
}


#if(ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED)
    /*******************************************************************************
    * Function Name: ECSenseUART_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      ECSenseUART_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      ECSenseUART_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      ECSenseUART_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      ECSenseUART_RX_STS_BREAK            Interrupt on break.
    *      ECSenseUART_RX_STS_OVERRUN          Interrupt on overrun error.
    *      ECSenseUART_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      ECSenseUART_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void ECSenseUART_SetRxInterruptMode(uint8 intSrc) 
    {
        ECSenseUART_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns the next byte of received data. This function returns data without
    *  checking the status. You must check the status separately.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  ECSenseUART_rxBuffer - RAM buffer pointer for save received data.
    *  ECSenseUART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  ECSenseUART_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  ECSenseUART_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 ECSenseUART_ReadRxData(void) 
    {
        uint8 rxData;

    #if (ECSenseUART_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        ECSenseUART_DisableRxInt();

        locRxBufferRead  = ECSenseUART_rxBufferRead;
        locRxBufferWrite = ECSenseUART_rxBufferWrite;

        if( (ECSenseUART_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = ECSenseUART_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= ECSenseUART_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            ECSenseUART_rxBufferRead = locRxBufferRead;

            if(ECSenseUART_rxBufferLoopDetect != 0u)
            {
                ECSenseUART_rxBufferLoopDetect = 0u;
                #if ((ECSenseUART_RX_INTERRUPT_ENABLED) && (ECSenseUART_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( ECSenseUART_HD_ENABLED )
                        if((ECSenseUART_CONTROL_REG & ECSenseUART_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            ECSenseUART_RXSTATUS_MASK_REG  |= ECSenseUART_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        ECSenseUART_RXSTATUS_MASK_REG  |= ECSenseUART_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end ECSenseUART_HD_ENABLED */
                #endif /* ((ECSenseUART_RX_INTERRUPT_ENABLED) && (ECSenseUART_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = ECSenseUART_RXDATA_REG;
        }

        ECSenseUART_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = ECSenseUART_RXDATA_REG;

    #endif /* (ECSenseUART_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the receiver status register and the software
    *  buffer overflow status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Side Effect:
    *  All status register bits are clear-on-read except
    *  ECSenseUART_RX_STS_FIFO_NOTEMPTY.
    *  ECSenseUART_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  ECSenseUART_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   ECSenseUART_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   ECSenseUART_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 ECSenseUART_ReadRxStatus(void) 
    {
        uint8 status;

        status = ECSenseUART_RXSTATUS_REG & ECSenseUART_RX_HW_MASK;

    #if (ECSenseUART_RX_INTERRUPT_ENABLED)
        if(ECSenseUART_rxBufferOverflow != 0u)
        {
            status |= ECSenseUART_RX_STS_SOFT_BUFF_OVER;
            ECSenseUART_rxBufferOverflow = 0u;
        }
    #endif /* (ECSenseUART_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. ECSenseUART_GetChar() is
    *  designed for ASCII characters and returns a uint8 where 1 to 255 are values
    *  for valid characters and 0 indicates an error occurred or no data is present.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  ECSenseUART_rxBuffer - RAM buffer pointer for save received data.
    *  ECSenseUART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  ECSenseUART_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  ECSenseUART_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 ECSenseUART_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (ECSenseUART_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        ECSenseUART_DisableRxInt();

        locRxBufferRead  = ECSenseUART_rxBufferRead;
        locRxBufferWrite = ECSenseUART_rxBufferWrite;

        if( (ECSenseUART_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = ECSenseUART_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= ECSenseUART_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            ECSenseUART_rxBufferRead = locRxBufferRead;

            if(ECSenseUART_rxBufferLoopDetect != 0u)
            {
                ECSenseUART_rxBufferLoopDetect = 0u;
                #if( (ECSenseUART_RX_INTERRUPT_ENABLED) && (ECSenseUART_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( ECSenseUART_HD_ENABLED )
                        if((ECSenseUART_CONTROL_REG & ECSenseUART_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            ECSenseUART_RXSTATUS_MASK_REG |= ECSenseUART_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        ECSenseUART_RXSTATUS_MASK_REG |= ECSenseUART_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end ECSenseUART_HD_ENABLED */
                #endif /* ECSenseUART_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = ECSenseUART_RXSTATUS_REG;
            if((rxStatus & ECSenseUART_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = ECSenseUART_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (ECSenseUART_RX_STS_BREAK | ECSenseUART_RX_STS_PAR_ERROR |
                                ECSenseUART_RX_STS_STOP_ERROR | ECSenseUART_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        ECSenseUART_EnableRxInt();

    #else

        rxStatus =ECSenseUART_RXSTATUS_REG;
        if((rxStatus & ECSenseUART_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = ECSenseUART_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (ECSenseUART_RX_STS_BREAK | ECSenseUART_RX_STS_PAR_ERROR |
                            ECSenseUART_RX_STS_STOP_ERROR | ECSenseUART_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (ECSenseUART_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, returns received character and error
    *  condition.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains status and LSB contains UART RX data. If the MSB is nonzero,
    *  an error has occurred.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 ECSenseUART_GetByte(void) 
    {
        
    #if (ECSenseUART_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        ECSenseUART_DisableRxInt();
        locErrorStatus = (uint16)ECSenseUART_errorStatus;
        ECSenseUART_errorStatus = 0u;
        ECSenseUART_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | ECSenseUART_ReadRxData() );
    #else
        return ( ((uint16)ECSenseUART_ReadRxStatus() << 8u) | ECSenseUART_ReadRxData() );
    #endif /* ECSenseUART_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received bytes available in the RX buffer.
    *  * RX software buffer is disabled (RX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty RX FIFO or 1 for not empty RX FIFO.
    *  * RX software buffer is enabled: returns the number of bytes available in 
    *    the RX software buffer. Bytes available in the RX FIFO do not take to 
    *    account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Number of bytes in the RX buffer. 
    *    Return value type depends on RX Buffer Size parameter.
    *
    * Global Variables:
    *  ECSenseUART_rxBufferWrite - used to calculate left bytes.
    *  ECSenseUART_rxBufferRead - used to calculate left bytes.
    *  ECSenseUART_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 ECSenseUART_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (ECSenseUART_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        ECSenseUART_DisableRxInt();

        if(ECSenseUART_rxBufferRead == ECSenseUART_rxBufferWrite)
        {
            if(ECSenseUART_rxBufferLoopDetect != 0u)
            {
                size = ECSenseUART_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(ECSenseUART_rxBufferRead < ECSenseUART_rxBufferWrite)
        {
            size = (ECSenseUART_rxBufferWrite - ECSenseUART_rxBufferRead);
        }
        else
        {
            size = (ECSenseUART_RX_BUFFER_SIZE - ECSenseUART_rxBufferRead) + ECSenseUART_rxBufferWrite;
        }

        ECSenseUART_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((ECSenseUART_RXSTATUS_REG & ECSenseUART_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (ECSenseUART_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receiver memory buffer and hardware RX FIFO of all received data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ECSenseUART_rxBufferWrite - cleared to zero.
    *  ECSenseUART_rxBufferRead - cleared to zero.
    *  ECSenseUART_rxBufferLoopDetect - cleared to zero.
    *  ECSenseUART_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *
    *******************************************************************************/
    void ECSenseUART_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        ECSenseUART_RXDATA_AUX_CTL_REG |= (uint8)  ECSenseUART_RX_FIFO_CLR;
        ECSenseUART_RXDATA_AUX_CTL_REG &= (uint8) ~ECSenseUART_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (ECSenseUART_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        ECSenseUART_DisableRxInt();

        ECSenseUART_rxBufferRead = 0u;
        ECSenseUART_rxBufferWrite = 0u;
        ECSenseUART_rxBufferLoopDetect = 0u;
        ECSenseUART_rxBufferOverflow = 0u;

        ECSenseUART_EnableRxInt();

    #endif /* (ECSenseUART_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: ECSenseUART_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  ECSenseUART__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  ECSenseUART__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  ECSenseUART__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  ECSenseUART__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  ECSenseUART__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ECSenseUART_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  ECSenseUART_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void ECSenseUART_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(ECSenseUART_RXHW_ADDRESS_ENABLED)
            #if(ECSenseUART_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* ECSenseUART_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = ECSenseUART_CONTROL_REG & (uint8)~ECSenseUART_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << ECSenseUART_CTRL_RXADDR_MODE0_SHIFT);
                ECSenseUART_CONTROL_REG = tmpCtrl;

                #if(ECSenseUART_RX_INTERRUPT_ENABLED && \
                   (ECSenseUART_RXBUFFERSIZE > ECSenseUART_FIFO_LENGTH) )
                    ECSenseUART_rxAddressMode = addressMode;
                    ECSenseUART_rxAddressDetected = 0u;
                #endif /* End ECSenseUART_RXBUFFERSIZE > ECSenseUART_FIFO_LENGTH*/
            #endif /* End ECSenseUART_CONTROL_REG_REMOVED */
        #else /* ECSenseUART_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End ECSenseUART_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Sets the first of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #1 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void ECSenseUART_SetRxAddress1(uint8 address) 
    {
        ECSenseUART_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the second of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #2 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void ECSenseUART_SetRxAddress2(uint8 address) 
    {
        ECSenseUART_RXADDRESS2_REG = address;
    }

#endif  /* ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED*/


#if( (ECSenseUART_TX_ENABLED) || (ECSenseUART_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: ECSenseUART_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   ECSenseUART_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   ECSenseUART_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   ECSenseUART_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   ECSenseUART_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void ECSenseUART_SetTxInterruptMode(uint8 intSrc) 
    {
        ECSenseUART_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data into the transmit buffer to be sent when the bus is
    *  available without checking the TX status register. You must check status
    *  separately.
    *
    * Parameters:
    *  txDataByte: data byte
    *
    * Return:
    * None.
    *
    * Global Variables:
    *  ECSenseUART_txBuffer - RAM buffer pointer for save data for transmission
    *  ECSenseUART_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  ECSenseUART_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  ECSenseUART_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void ECSenseUART_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(ECSenseUART_initVar != 0u)
        {
        #if (ECSenseUART_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            ECSenseUART_DisableTxInt();

            if( (ECSenseUART_txBufferRead == ECSenseUART_txBufferWrite) &&
                ((ECSenseUART_TXSTATUS_REG & ECSenseUART_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                ECSenseUART_TXDATA_REG = txDataByte;
            }
            else
            {
                if(ECSenseUART_txBufferWrite >= ECSenseUART_TX_BUFFER_SIZE)
                {
                    ECSenseUART_txBufferWrite = 0u;
                }

                ECSenseUART_txBuffer[ECSenseUART_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                ECSenseUART_txBufferWrite++;
            }

            ECSenseUART_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            ECSenseUART_TXDATA_REG = txDataByte;

        #endif /*(ECSenseUART_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the status register for the TX portion of the UART.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the TX status register, which is cleared on read.
    *  It is up to the user to handle all bits in this return value accordingly,
    *  even if the bit was not enabled as an interrupt source the event happened
    *  and must be handled accordingly.
    *
    *******************************************************************************/
    uint8 ECSenseUART_ReadTxStatus(void) 
    {
        return(ECSenseUART_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Puts a byte of data into the transmit buffer to be sent when the bus is
    *  available. This is a blocking API that waits until the TX buffer has room to
    *  hold the data.
    *
    * Parameters:
    *  txDataByte: Byte containing the data to transmit
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ECSenseUART_txBuffer - RAM buffer pointer for save data for transmission
    *  ECSenseUART_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  ECSenseUART_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  ECSenseUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void ECSenseUART_PutChar(uint8 txDataByte) 
    {
    #if (ECSenseUART_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((ECSenseUART_TX_BUFFER_SIZE > ECSenseUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            ECSenseUART_DisableTxInt();
        #endif /* (ECSenseUART_TX_BUFFER_SIZE > ECSenseUART_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = ECSenseUART_txBufferWrite;
            locTxBufferRead  = ECSenseUART_txBufferRead;

        #if ((ECSenseUART_TX_BUFFER_SIZE > ECSenseUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            ECSenseUART_EnableTxInt();
        #endif /* (ECSenseUART_TX_BUFFER_SIZE > ECSenseUART_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(ECSenseUART_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((ECSenseUART_TXSTATUS_REG & ECSenseUART_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            ECSenseUART_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= ECSenseUART_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            ECSenseUART_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((ECSenseUART_TX_BUFFER_SIZE > ECSenseUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            ECSenseUART_DisableTxInt();
        #endif /* (ECSenseUART_TX_BUFFER_SIZE > ECSenseUART_MAX_BYTE_VALUE) && (CY_PSOC3) */

            ECSenseUART_txBufferWrite = locTxBufferWrite;

        #if ((ECSenseUART_TX_BUFFER_SIZE > ECSenseUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            ECSenseUART_EnableTxInt();
        #endif /* (ECSenseUART_TX_BUFFER_SIZE > ECSenseUART_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (ECSenseUART_TXSTATUS_REG & ECSenseUART_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                ECSenseUART_SetPendingTxInt();
            }
        }

    #else

        while((ECSenseUART_TXSTATUS_REG & ECSenseUART_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        ECSenseUART_TXDATA_REG = txDataByte;

    #endif /* ECSenseUART_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a NULL terminated string to the TX buffer for transmission.
    *
    * Parameters:
    *  string[]: Pointer to the null terminated string array residing in RAM or ROM
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ECSenseUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void ECSenseUART_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(ECSenseUART_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                ECSenseUART_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Places N bytes of data from a memory array into the TX buffer for
    *  transmission.
    *
    * Parameters:
    *  string[]: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of bytes to be transmitted. The type depends on TX Buffer
    *             Size parameter.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ECSenseUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void ECSenseUART_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(ECSenseUART_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                ECSenseUART_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Writes a byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) to the transmit buffer.
    *
    * Parameters:
    *  txDataByte: Data byte to transmit before the carriage return and line feed.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ECSenseUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void ECSenseUART_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(ECSenseUART_initVar != 0u)
        {
            ECSenseUART_PutChar(txDataByte);
            ECSenseUART_PutChar(0x0Du);
            ECSenseUART_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of bytes in the TX buffer which are waiting to be 
    *  transmitted.
    *  * TX software buffer is disabled (TX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty TX FIFO, 1 for not full TX FIFO or 4 for full TX FIFO.
    *  * TX software buffer is enabled: returns the number of bytes in the TX 
    *    software buffer which are waiting to be transmitted. Bytes available in the
    *    TX FIFO do not count.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Number of bytes used in the TX buffer. Return value type depends on the TX 
    *  Buffer Size parameter.
    *
    * Global Variables:
    *  ECSenseUART_txBufferWrite - used to calculate left space.
    *  ECSenseUART_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 ECSenseUART_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (ECSenseUART_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        ECSenseUART_DisableTxInt();

        if(ECSenseUART_txBufferRead == ECSenseUART_txBufferWrite)
        {
            size = 0u;
        }
        else if(ECSenseUART_txBufferRead < ECSenseUART_txBufferWrite)
        {
            size = (ECSenseUART_txBufferWrite - ECSenseUART_txBufferRead);
        }
        else
        {
            size = (ECSenseUART_TX_BUFFER_SIZE - ECSenseUART_txBufferRead) +
                    ECSenseUART_txBufferWrite;
        }

        ECSenseUART_EnableTxInt();

    #else

        size = ECSenseUART_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & ECSenseUART_TX_STS_FIFO_FULL) != 0u)
        {
            size = ECSenseUART_FIFO_LENGTH;
        }
        else if((size & ECSenseUART_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (ECSenseUART_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears all data from the TX buffer and hardware TX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ECSenseUART_txBufferWrite - cleared to zero.
    *  ECSenseUART_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Data waiting in the transmit buffer is not sent; a byte that is currently
    *  transmitting finishes transmitting.
    *
    *******************************************************************************/
    void ECSenseUART_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        ECSenseUART_TXDATA_AUX_CTL_REG |= (uint8)  ECSenseUART_TX_FIFO_CLR;
        ECSenseUART_TXDATA_AUX_CTL_REG &= (uint8) ~ECSenseUART_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (ECSenseUART_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        ECSenseUART_DisableTxInt();

        ECSenseUART_txBufferRead = 0u;
        ECSenseUART_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        ECSenseUART_EnableTxInt();

    #endif /* (ECSenseUART_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   ECSenseUART_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   ECSenseUART_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   ECSenseUART_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   ECSenseUART_SEND_WAIT_REINIT - Performs both options: 
    *      ECSenseUART_SEND_BREAK and ECSenseUART_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  ECSenseUART_initVar - checked to identify that the component has been
    *     initialized.
    *  txPeriod - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  There are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Function will block CPU until transmission
    *     complete.
    *  2) User may want to use blocking time if UART configured to the low speed
    *     operation
    *     Example for this case:
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to initialize and use the interrupt to
    *     complete break operation.
    *     Example for this case:
    *     Initialize TX interrupt with "TX - On TX Complete" parameter
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     When interrupt appear with ECSenseUART_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The ECSenseUART_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void ECSenseUART_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(ECSenseUART_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(ECSenseUART_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == ECSenseUART_SEND_BREAK) ||
                (retMode == ECSenseUART_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                ECSenseUART_WriteControlRegister(ECSenseUART_ReadControlRegister() |
                                                      ECSenseUART_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                ECSenseUART_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = ECSenseUART_TXSTATUS_REG;
                }
                while((tmpStat & ECSenseUART_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == ECSenseUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == ECSenseUART_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = ECSenseUART_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & ECSenseUART_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == ECSenseUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == ECSenseUART_REINIT) ||
                (retMode == ECSenseUART_SEND_WAIT_REINIT) )
            {
                ECSenseUART_WriteControlRegister(ECSenseUART_ReadControlRegister() &
                                              (uint8)~ECSenseUART_CTRL_HD_SEND_BREAK);
            }

        #else /* ECSenseUART_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == ECSenseUART_SEND_BREAK) ||
                (retMode == ECSenseUART_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (ECSenseUART_PARITY_TYPE != ECSenseUART__B_UART__NONE_REVB) || \
                                    (ECSenseUART_PARITY_TYPE_SW != 0u) )
                    ECSenseUART_WriteControlRegister(ECSenseUART_ReadControlRegister() |
                                                          ECSenseUART_CTRL_HD_SEND_BREAK);
                #endif /* End ECSenseUART_PARITY_TYPE != ECSenseUART__B_UART__NONE_REVB  */

                #if(ECSenseUART_TXCLKGEN_DP)
                    txPeriod = ECSenseUART_TXBITCLKTX_COMPLETE_REG;
                    ECSenseUART_TXBITCLKTX_COMPLETE_REG = ECSenseUART_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = ECSenseUART_TXBITCTR_PERIOD_REG;
                    ECSenseUART_TXBITCTR_PERIOD_REG = ECSenseUART_TXBITCTR_BREAKBITS8X;
                #endif /* End ECSenseUART_TXCLKGEN_DP */

                /* Send zeros */
                ECSenseUART_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = ECSenseUART_TXSTATUS_REG;
                }
                while((tmpStat & ECSenseUART_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == ECSenseUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == ECSenseUART_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = ECSenseUART_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & ECSenseUART_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == ECSenseUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == ECSenseUART_REINIT) ||
                (retMode == ECSenseUART_SEND_WAIT_REINIT) )
            {

            #if(ECSenseUART_TXCLKGEN_DP)
                ECSenseUART_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                ECSenseUART_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End ECSenseUART_TXCLKGEN_DP */

            #if( (ECSenseUART_PARITY_TYPE != ECSenseUART__B_UART__NONE_REVB) || \
                 (ECSenseUART_PARITY_TYPE_SW != 0u) )
                ECSenseUART_WriteControlRegister(ECSenseUART_ReadControlRegister() &
                                                      (uint8) ~ECSenseUART_CTRL_HD_SEND_BREAK);
            #endif /* End ECSenseUART_PARITY_TYPE != NONE */
            }
        #endif    /* End ECSenseUART_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       ECSenseUART_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       ECSenseUART_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears ECSenseUART_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void ECSenseUART_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( ECSenseUART_CONTROL_REG_REMOVED == 0u )
            ECSenseUART_WriteControlRegister(ECSenseUART_ReadControlRegister() |
                                                  ECSenseUART_CTRL_MARK);
        #endif /* End ECSenseUART_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( ECSenseUART_CONTROL_REG_REMOVED == 0u )
            ECSenseUART_WriteControlRegister(ECSenseUART_ReadControlRegister() &
                                                  (uint8) ~ECSenseUART_CTRL_MARK);
        #endif /* End ECSenseUART_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndECSenseUART_TX_ENABLED */

#if(ECSenseUART_HD_ENABLED)


    /*******************************************************************************
    * Function Name: ECSenseUART_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the receiver configuration in half duplex mode. After calling this
    *  function, the UART is ready to receive data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the transmitter
    *  configuration.
    *
    *******************************************************************************/
    void ECSenseUART_LoadRxConfig(void) 
    {
        ECSenseUART_WriteControlRegister(ECSenseUART_ReadControlRegister() &
                                                (uint8)~ECSenseUART_CTRL_HD_SEND);
        ECSenseUART_RXBITCTR_PERIOD_REG = ECSenseUART_HD_RXBITCTR_INIT;

    #if (ECSenseUART_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        ECSenseUART_SetRxInterruptMode(ECSenseUART_INIT_RX_INTERRUPTS_MASK);
    #endif /* (ECSenseUART_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: ECSenseUART_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the transmitter configuration in half duplex mode. After calling this
    *  function, the UART is ready to transmit data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the receiver configuration.
    *
    *******************************************************************************/
    void ECSenseUART_LoadTxConfig(void) 
    {
    #if (ECSenseUART_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        ECSenseUART_SetRxInterruptMode(0u);
    #endif /* (ECSenseUART_RX_INTERRUPT_ENABLED) */

        ECSenseUART_WriteControlRegister(ECSenseUART_ReadControlRegister() | ECSenseUART_CTRL_HD_SEND);
        ECSenseUART_RXBITCTR_PERIOD_REG = ECSenseUART_HD_TXBITCTR_INIT;
    }

#endif  /* ECSenseUART_HD_ENABLED */


/* [] END OF FILE */
