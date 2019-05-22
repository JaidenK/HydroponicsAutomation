/*******************************************************************************
* File Name: SensorComTxUART.c
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

#include "SensorComTxUART.h"
#if (SensorComTxUART_INTERNAL_CLOCK_USED)
    #include "SensorComTxUART_IntClock.h"
#endif /* End SensorComTxUART_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 SensorComTxUART_initVar = 0u;

#if (SensorComTxUART_TX_INTERRUPT_ENABLED && SensorComTxUART_TX_ENABLED)
    volatile uint8 SensorComTxUART_txBuffer[SensorComTxUART_TX_BUFFER_SIZE];
    volatile uint8 SensorComTxUART_txBufferRead = 0u;
    uint8 SensorComTxUART_txBufferWrite = 0u;
#endif /* (SensorComTxUART_TX_INTERRUPT_ENABLED && SensorComTxUART_TX_ENABLED) */

#if (SensorComTxUART_RX_INTERRUPT_ENABLED && (SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED))
    uint8 SensorComTxUART_errorStatus = 0u;
    volatile uint8 SensorComTxUART_rxBuffer[SensorComTxUART_RX_BUFFER_SIZE];
    volatile uint8 SensorComTxUART_rxBufferRead  = 0u;
    volatile uint8 SensorComTxUART_rxBufferWrite = 0u;
    volatile uint8 SensorComTxUART_rxBufferLoopDetect = 0u;
    volatile uint8 SensorComTxUART_rxBufferOverflow   = 0u;
    #if (SensorComTxUART_RXHW_ADDRESS_ENABLED)
        volatile uint8 SensorComTxUART_rxAddressMode = SensorComTxUART_RX_ADDRESS_MODE;
        volatile uint8 SensorComTxUART_rxAddressDetected = 0u;
    #endif /* (SensorComTxUART_RXHW_ADDRESS_ENABLED) */
#endif /* (SensorComTxUART_RX_INTERRUPT_ENABLED && (SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED)) */


/*******************************************************************************
* Function Name: SensorComTxUART_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  SensorComTxUART_Start() sets the initVar variable, calls the
*  SensorComTxUART_Init() function, and then calls the
*  SensorComTxUART_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The SensorComTxUART_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time SensorComTxUART_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the SensorComTxUART_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SensorComTxUART_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(SensorComTxUART_initVar == 0u)
    {
        SensorComTxUART_Init();
        SensorComTxUART_initVar = 1u;
    }

    SensorComTxUART_Enable();
}


/*******************************************************************************
* Function Name: SensorComTxUART_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call SensorComTxUART_Init() because
*  the SensorComTxUART_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SensorComTxUART_Init(void) 
{
    #if(SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED)

        #if (SensorComTxUART_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(SensorComTxUART_RX_VECT_NUM, &SensorComTxUART_RXISR);
            CyIntSetPriority(SensorComTxUART_RX_VECT_NUM, SensorComTxUART_RX_PRIOR_NUM);
            SensorComTxUART_errorStatus = 0u;
        #endif /* (SensorComTxUART_RX_INTERRUPT_ENABLED) */

        #if (SensorComTxUART_RXHW_ADDRESS_ENABLED)
            SensorComTxUART_SetRxAddressMode(SensorComTxUART_RX_ADDRESS_MODE);
            SensorComTxUART_SetRxAddress1(SensorComTxUART_RX_HW_ADDRESS1);
            SensorComTxUART_SetRxAddress2(SensorComTxUART_RX_HW_ADDRESS2);
        #endif /* End SensorComTxUART_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        SensorComTxUART_RXBITCTR_PERIOD_REG = SensorComTxUART_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        SensorComTxUART_RXSTATUS_MASK_REG  = SensorComTxUART_INIT_RX_INTERRUPTS_MASK;
    #endif /* End SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED*/

    #if(SensorComTxUART_TX_ENABLED)
        #if (SensorComTxUART_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(SensorComTxUART_TX_VECT_NUM, &SensorComTxUART_TXISR);
            CyIntSetPriority(SensorComTxUART_TX_VECT_NUM, SensorComTxUART_TX_PRIOR_NUM);
        #endif /* (SensorComTxUART_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (SensorComTxUART_TXCLKGEN_DP)
            SensorComTxUART_TXBITCLKGEN_CTR_REG = SensorComTxUART_BIT_CENTER;
            SensorComTxUART_TXBITCLKTX_COMPLETE_REG = ((SensorComTxUART_NUMBER_OF_DATA_BITS +
                        SensorComTxUART_NUMBER_OF_START_BIT) * SensorComTxUART_OVER_SAMPLE_COUNT) - 1u;
        #else
            SensorComTxUART_TXBITCTR_PERIOD_REG = ((SensorComTxUART_NUMBER_OF_DATA_BITS +
                        SensorComTxUART_NUMBER_OF_START_BIT) * SensorComTxUART_OVER_SAMPLE_8) - 1u;
        #endif /* End SensorComTxUART_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (SensorComTxUART_TX_INTERRUPT_ENABLED)
            SensorComTxUART_TXSTATUS_MASK_REG = SensorComTxUART_TX_STS_FIFO_EMPTY;
        #else
            SensorComTxUART_TXSTATUS_MASK_REG = SensorComTxUART_INIT_TX_INTERRUPTS_MASK;
        #endif /*End SensorComTxUART_TX_INTERRUPT_ENABLED*/

    #endif /* End SensorComTxUART_TX_ENABLED */

    #if(SensorComTxUART_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        SensorComTxUART_WriteControlRegister( \
            (SensorComTxUART_ReadControlRegister() & (uint8)~SensorComTxUART_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(SensorComTxUART_PARITY_TYPE << SensorComTxUART_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End SensorComTxUART_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: SensorComTxUART_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call SensorComTxUART_Enable() because the SensorComTxUART_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SensorComTxUART_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void SensorComTxUART_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        SensorComTxUART_RXBITCTR_CONTROL_REG |= SensorComTxUART_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        SensorComTxUART_RXSTATUS_ACTL_REG  |= SensorComTxUART_INT_ENABLE;

        #if (SensorComTxUART_RX_INTERRUPT_ENABLED)
            SensorComTxUART_EnableRxInt();

            #if (SensorComTxUART_RXHW_ADDRESS_ENABLED)
                SensorComTxUART_rxAddressDetected = 0u;
            #endif /* (SensorComTxUART_RXHW_ADDRESS_ENABLED) */
        #endif /* (SensorComTxUART_RX_INTERRUPT_ENABLED) */
    #endif /* (SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED) */

    #if(SensorComTxUART_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!SensorComTxUART_TXCLKGEN_DP)
            SensorComTxUART_TXBITCTR_CONTROL_REG |= SensorComTxUART_CNTR_ENABLE;
        #endif /* End SensorComTxUART_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        SensorComTxUART_TXSTATUS_ACTL_REG |= SensorComTxUART_INT_ENABLE;
        #if (SensorComTxUART_TX_INTERRUPT_ENABLED)
            SensorComTxUART_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            SensorComTxUART_EnableTxInt();
        #endif /* (SensorComTxUART_TX_INTERRUPT_ENABLED) */
     #endif /* (SensorComTxUART_TX_INTERRUPT_ENABLED) */

    #if (SensorComTxUART_INTERNAL_CLOCK_USED)
        SensorComTxUART_IntClock_Start();  /* Enable the clock */
    #endif /* (SensorComTxUART_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SensorComTxUART_Stop
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
void SensorComTxUART_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED)
        SensorComTxUART_RXBITCTR_CONTROL_REG &= (uint8) ~SensorComTxUART_CNTR_ENABLE;
    #endif /* (SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED) */

    #if (SensorComTxUART_TX_ENABLED)
        #if(!SensorComTxUART_TXCLKGEN_DP)
            SensorComTxUART_TXBITCTR_CONTROL_REG &= (uint8) ~SensorComTxUART_CNTR_ENABLE;
        #endif /* (!SensorComTxUART_TXCLKGEN_DP) */
    #endif /* (SensorComTxUART_TX_ENABLED) */

    #if (SensorComTxUART_INTERNAL_CLOCK_USED)
        SensorComTxUART_IntClock_Stop();   /* Disable the clock */
    #endif /* (SensorComTxUART_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED)
        SensorComTxUART_RXSTATUS_ACTL_REG  &= (uint8) ~SensorComTxUART_INT_ENABLE;

        #if (SensorComTxUART_RX_INTERRUPT_ENABLED)
            SensorComTxUART_DisableRxInt();
        #endif /* (SensorComTxUART_RX_INTERRUPT_ENABLED) */
    #endif /* (SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED) */

    #if (SensorComTxUART_TX_ENABLED)
        SensorComTxUART_TXSTATUS_ACTL_REG &= (uint8) ~SensorComTxUART_INT_ENABLE;

        #if (SensorComTxUART_TX_INTERRUPT_ENABLED)
            SensorComTxUART_DisableTxInt();
        #endif /* (SensorComTxUART_TX_INTERRUPT_ENABLED) */
    #endif /* (SensorComTxUART_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SensorComTxUART_ReadControlRegister
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
uint8 SensorComTxUART_ReadControlRegister(void) 
{
    #if (SensorComTxUART_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(SensorComTxUART_CONTROL_REG);
    #endif /* (SensorComTxUART_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: SensorComTxUART_WriteControlRegister
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
void  SensorComTxUART_WriteControlRegister(uint8 control) 
{
    #if (SensorComTxUART_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       SensorComTxUART_CONTROL_REG = control;
    #endif /* (SensorComTxUART_CONTROL_REG_REMOVED) */
}


#if(SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED)
    /*******************************************************************************
    * Function Name: SensorComTxUART_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      SensorComTxUART_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      SensorComTxUART_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      SensorComTxUART_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      SensorComTxUART_RX_STS_BREAK            Interrupt on break.
    *      SensorComTxUART_RX_STS_OVERRUN          Interrupt on overrun error.
    *      SensorComTxUART_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      SensorComTxUART_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void SensorComTxUART_SetRxInterruptMode(uint8 intSrc) 
    {
        SensorComTxUART_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_ReadRxData
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
    *  SensorComTxUART_rxBuffer - RAM buffer pointer for save received data.
    *  SensorComTxUART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  SensorComTxUART_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  SensorComTxUART_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 SensorComTxUART_ReadRxData(void) 
    {
        uint8 rxData;

    #if (SensorComTxUART_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        SensorComTxUART_DisableRxInt();

        locRxBufferRead  = SensorComTxUART_rxBufferRead;
        locRxBufferWrite = SensorComTxUART_rxBufferWrite;

        if( (SensorComTxUART_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = SensorComTxUART_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= SensorComTxUART_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            SensorComTxUART_rxBufferRead = locRxBufferRead;

            if(SensorComTxUART_rxBufferLoopDetect != 0u)
            {
                SensorComTxUART_rxBufferLoopDetect = 0u;
                #if ((SensorComTxUART_RX_INTERRUPT_ENABLED) && (SensorComTxUART_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( SensorComTxUART_HD_ENABLED )
                        if((SensorComTxUART_CONTROL_REG & SensorComTxUART_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            SensorComTxUART_RXSTATUS_MASK_REG  |= SensorComTxUART_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        SensorComTxUART_RXSTATUS_MASK_REG  |= SensorComTxUART_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end SensorComTxUART_HD_ENABLED */
                #endif /* ((SensorComTxUART_RX_INTERRUPT_ENABLED) && (SensorComTxUART_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = SensorComTxUART_RXDATA_REG;
        }

        SensorComTxUART_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = SensorComTxUART_RXDATA_REG;

    #endif /* (SensorComTxUART_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_ReadRxStatus
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
    *  SensorComTxUART_RX_STS_FIFO_NOTEMPTY.
    *  SensorComTxUART_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  SensorComTxUART_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   SensorComTxUART_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   SensorComTxUART_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 SensorComTxUART_ReadRxStatus(void) 
    {
        uint8 status;

        status = SensorComTxUART_RXSTATUS_REG & SensorComTxUART_RX_HW_MASK;

    #if (SensorComTxUART_RX_INTERRUPT_ENABLED)
        if(SensorComTxUART_rxBufferOverflow != 0u)
        {
            status |= SensorComTxUART_RX_STS_SOFT_BUFF_OVER;
            SensorComTxUART_rxBufferOverflow = 0u;
        }
    #endif /* (SensorComTxUART_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. SensorComTxUART_GetChar() is
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
    *  SensorComTxUART_rxBuffer - RAM buffer pointer for save received data.
    *  SensorComTxUART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  SensorComTxUART_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  SensorComTxUART_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 SensorComTxUART_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (SensorComTxUART_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        SensorComTxUART_DisableRxInt();

        locRxBufferRead  = SensorComTxUART_rxBufferRead;
        locRxBufferWrite = SensorComTxUART_rxBufferWrite;

        if( (SensorComTxUART_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = SensorComTxUART_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= SensorComTxUART_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            SensorComTxUART_rxBufferRead = locRxBufferRead;

            if(SensorComTxUART_rxBufferLoopDetect != 0u)
            {
                SensorComTxUART_rxBufferLoopDetect = 0u;
                #if( (SensorComTxUART_RX_INTERRUPT_ENABLED) && (SensorComTxUART_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( SensorComTxUART_HD_ENABLED )
                        if((SensorComTxUART_CONTROL_REG & SensorComTxUART_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            SensorComTxUART_RXSTATUS_MASK_REG |= SensorComTxUART_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        SensorComTxUART_RXSTATUS_MASK_REG |= SensorComTxUART_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end SensorComTxUART_HD_ENABLED */
                #endif /* SensorComTxUART_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = SensorComTxUART_RXSTATUS_REG;
            if((rxStatus & SensorComTxUART_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = SensorComTxUART_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (SensorComTxUART_RX_STS_BREAK | SensorComTxUART_RX_STS_PAR_ERROR |
                                SensorComTxUART_RX_STS_STOP_ERROR | SensorComTxUART_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        SensorComTxUART_EnableRxInt();

    #else

        rxStatus =SensorComTxUART_RXSTATUS_REG;
        if((rxStatus & SensorComTxUART_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = SensorComTxUART_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (SensorComTxUART_RX_STS_BREAK | SensorComTxUART_RX_STS_PAR_ERROR |
                            SensorComTxUART_RX_STS_STOP_ERROR | SensorComTxUART_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (SensorComTxUART_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_GetByte
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
    uint16 SensorComTxUART_GetByte(void) 
    {
        
    #if (SensorComTxUART_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        SensorComTxUART_DisableRxInt();
        locErrorStatus = (uint16)SensorComTxUART_errorStatus;
        SensorComTxUART_errorStatus = 0u;
        SensorComTxUART_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | SensorComTxUART_ReadRxData() );
    #else
        return ( ((uint16)SensorComTxUART_ReadRxStatus() << 8u) | SensorComTxUART_ReadRxData() );
    #endif /* SensorComTxUART_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_GetRxBufferSize
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
    *  SensorComTxUART_rxBufferWrite - used to calculate left bytes.
    *  SensorComTxUART_rxBufferRead - used to calculate left bytes.
    *  SensorComTxUART_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 SensorComTxUART_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (SensorComTxUART_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        SensorComTxUART_DisableRxInt();

        if(SensorComTxUART_rxBufferRead == SensorComTxUART_rxBufferWrite)
        {
            if(SensorComTxUART_rxBufferLoopDetect != 0u)
            {
                size = SensorComTxUART_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(SensorComTxUART_rxBufferRead < SensorComTxUART_rxBufferWrite)
        {
            size = (SensorComTxUART_rxBufferWrite - SensorComTxUART_rxBufferRead);
        }
        else
        {
            size = (SensorComTxUART_RX_BUFFER_SIZE - SensorComTxUART_rxBufferRead) + SensorComTxUART_rxBufferWrite;
        }

        SensorComTxUART_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((SensorComTxUART_RXSTATUS_REG & SensorComTxUART_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (SensorComTxUART_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_ClearRxBuffer
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
    *  SensorComTxUART_rxBufferWrite - cleared to zero.
    *  SensorComTxUART_rxBufferRead - cleared to zero.
    *  SensorComTxUART_rxBufferLoopDetect - cleared to zero.
    *  SensorComTxUART_rxBufferOverflow - cleared to zero.
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
    void SensorComTxUART_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        SensorComTxUART_RXDATA_AUX_CTL_REG |= (uint8)  SensorComTxUART_RX_FIFO_CLR;
        SensorComTxUART_RXDATA_AUX_CTL_REG &= (uint8) ~SensorComTxUART_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (SensorComTxUART_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        SensorComTxUART_DisableRxInt();

        SensorComTxUART_rxBufferRead = 0u;
        SensorComTxUART_rxBufferWrite = 0u;
        SensorComTxUART_rxBufferLoopDetect = 0u;
        SensorComTxUART_rxBufferOverflow = 0u;

        SensorComTxUART_EnableRxInt();

    #endif /* (SensorComTxUART_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  SensorComTxUART__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  SensorComTxUART__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  SensorComTxUART__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  SensorComTxUART__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  SensorComTxUART__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  SensorComTxUART_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  SensorComTxUART_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void SensorComTxUART_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(SensorComTxUART_RXHW_ADDRESS_ENABLED)
            #if(SensorComTxUART_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* SensorComTxUART_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = SensorComTxUART_CONTROL_REG & (uint8)~SensorComTxUART_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << SensorComTxUART_CTRL_RXADDR_MODE0_SHIFT);
                SensorComTxUART_CONTROL_REG = tmpCtrl;

                #if(SensorComTxUART_RX_INTERRUPT_ENABLED && \
                   (SensorComTxUART_RXBUFFERSIZE > SensorComTxUART_FIFO_LENGTH) )
                    SensorComTxUART_rxAddressMode = addressMode;
                    SensorComTxUART_rxAddressDetected = 0u;
                #endif /* End SensorComTxUART_RXBUFFERSIZE > SensorComTxUART_FIFO_LENGTH*/
            #endif /* End SensorComTxUART_CONTROL_REG_REMOVED */
        #else /* SensorComTxUART_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End SensorComTxUART_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_SetRxAddress1
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
    void SensorComTxUART_SetRxAddress1(uint8 address) 
    {
        SensorComTxUART_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_SetRxAddress2
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
    void SensorComTxUART_SetRxAddress2(uint8 address) 
    {
        SensorComTxUART_RXADDRESS2_REG = address;
    }

#endif  /* SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED*/


#if( (SensorComTxUART_TX_ENABLED) || (SensorComTxUART_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: SensorComTxUART_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   SensorComTxUART_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   SensorComTxUART_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   SensorComTxUART_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   SensorComTxUART_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void SensorComTxUART_SetTxInterruptMode(uint8 intSrc) 
    {
        SensorComTxUART_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_WriteTxData
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
    *  SensorComTxUART_txBuffer - RAM buffer pointer for save data for transmission
    *  SensorComTxUART_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  SensorComTxUART_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  SensorComTxUART_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void SensorComTxUART_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(SensorComTxUART_initVar != 0u)
        {
        #if (SensorComTxUART_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            SensorComTxUART_DisableTxInt();

            if( (SensorComTxUART_txBufferRead == SensorComTxUART_txBufferWrite) &&
                ((SensorComTxUART_TXSTATUS_REG & SensorComTxUART_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                SensorComTxUART_TXDATA_REG = txDataByte;
            }
            else
            {
                if(SensorComTxUART_txBufferWrite >= SensorComTxUART_TX_BUFFER_SIZE)
                {
                    SensorComTxUART_txBufferWrite = 0u;
                }

                SensorComTxUART_txBuffer[SensorComTxUART_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                SensorComTxUART_txBufferWrite++;
            }

            SensorComTxUART_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            SensorComTxUART_TXDATA_REG = txDataByte;

        #endif /*(SensorComTxUART_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_ReadTxStatus
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
    uint8 SensorComTxUART_ReadTxStatus(void) 
    {
        return(SensorComTxUART_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_PutChar
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
    *  SensorComTxUART_txBuffer - RAM buffer pointer for save data for transmission
    *  SensorComTxUART_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  SensorComTxUART_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  SensorComTxUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void SensorComTxUART_PutChar(uint8 txDataByte) 
    {
    #if (SensorComTxUART_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((SensorComTxUART_TX_BUFFER_SIZE > SensorComTxUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            SensorComTxUART_DisableTxInt();
        #endif /* (SensorComTxUART_TX_BUFFER_SIZE > SensorComTxUART_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = SensorComTxUART_txBufferWrite;
            locTxBufferRead  = SensorComTxUART_txBufferRead;

        #if ((SensorComTxUART_TX_BUFFER_SIZE > SensorComTxUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            SensorComTxUART_EnableTxInt();
        #endif /* (SensorComTxUART_TX_BUFFER_SIZE > SensorComTxUART_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(SensorComTxUART_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((SensorComTxUART_TXSTATUS_REG & SensorComTxUART_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            SensorComTxUART_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= SensorComTxUART_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            SensorComTxUART_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((SensorComTxUART_TX_BUFFER_SIZE > SensorComTxUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            SensorComTxUART_DisableTxInt();
        #endif /* (SensorComTxUART_TX_BUFFER_SIZE > SensorComTxUART_MAX_BYTE_VALUE) && (CY_PSOC3) */

            SensorComTxUART_txBufferWrite = locTxBufferWrite;

        #if ((SensorComTxUART_TX_BUFFER_SIZE > SensorComTxUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            SensorComTxUART_EnableTxInt();
        #endif /* (SensorComTxUART_TX_BUFFER_SIZE > SensorComTxUART_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (SensorComTxUART_TXSTATUS_REG & SensorComTxUART_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                SensorComTxUART_SetPendingTxInt();
            }
        }

    #else

        while((SensorComTxUART_TXSTATUS_REG & SensorComTxUART_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        SensorComTxUART_TXDATA_REG = txDataByte;

    #endif /* SensorComTxUART_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_PutString
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
    *  SensorComTxUART_initVar - checked to identify that the component has been
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
    void SensorComTxUART_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(SensorComTxUART_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                SensorComTxUART_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_PutArray
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
    *  SensorComTxUART_initVar - checked to identify that the component has been
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
    void SensorComTxUART_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(SensorComTxUART_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                SensorComTxUART_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_PutCRLF
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
    *  SensorComTxUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void SensorComTxUART_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(SensorComTxUART_initVar != 0u)
        {
            SensorComTxUART_PutChar(txDataByte);
            SensorComTxUART_PutChar(0x0Du);
            SensorComTxUART_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_GetTxBufferSize
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
    *  SensorComTxUART_txBufferWrite - used to calculate left space.
    *  SensorComTxUART_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 SensorComTxUART_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (SensorComTxUART_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        SensorComTxUART_DisableTxInt();

        if(SensorComTxUART_txBufferRead == SensorComTxUART_txBufferWrite)
        {
            size = 0u;
        }
        else if(SensorComTxUART_txBufferRead < SensorComTxUART_txBufferWrite)
        {
            size = (SensorComTxUART_txBufferWrite - SensorComTxUART_txBufferRead);
        }
        else
        {
            size = (SensorComTxUART_TX_BUFFER_SIZE - SensorComTxUART_txBufferRead) +
                    SensorComTxUART_txBufferWrite;
        }

        SensorComTxUART_EnableTxInt();

    #else

        size = SensorComTxUART_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & SensorComTxUART_TX_STS_FIFO_FULL) != 0u)
        {
            size = SensorComTxUART_FIFO_LENGTH;
        }
        else if((size & SensorComTxUART_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (SensorComTxUART_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_ClearTxBuffer
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
    *  SensorComTxUART_txBufferWrite - cleared to zero.
    *  SensorComTxUART_txBufferRead - cleared to zero.
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
    void SensorComTxUART_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        SensorComTxUART_TXDATA_AUX_CTL_REG |= (uint8)  SensorComTxUART_TX_FIFO_CLR;
        SensorComTxUART_TXDATA_AUX_CTL_REG &= (uint8) ~SensorComTxUART_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (SensorComTxUART_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        SensorComTxUART_DisableTxInt();

        SensorComTxUART_txBufferRead = 0u;
        SensorComTxUART_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        SensorComTxUART_EnableTxInt();

    #endif /* (SensorComTxUART_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   SensorComTxUART_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   SensorComTxUART_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   SensorComTxUART_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   SensorComTxUART_SEND_WAIT_REINIT - Performs both options: 
    *      SensorComTxUART_SEND_BREAK and SensorComTxUART_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  SensorComTxUART_initVar - checked to identify that the component has been
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
    *     When interrupt appear with SensorComTxUART_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The SensorComTxUART_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void SensorComTxUART_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(SensorComTxUART_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(SensorComTxUART_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == SensorComTxUART_SEND_BREAK) ||
                (retMode == SensorComTxUART_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                SensorComTxUART_WriteControlRegister(SensorComTxUART_ReadControlRegister() |
                                                      SensorComTxUART_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                SensorComTxUART_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = SensorComTxUART_TXSTATUS_REG;
                }
                while((tmpStat & SensorComTxUART_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == SensorComTxUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == SensorComTxUART_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = SensorComTxUART_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & SensorComTxUART_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == SensorComTxUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == SensorComTxUART_REINIT) ||
                (retMode == SensorComTxUART_SEND_WAIT_REINIT) )
            {
                SensorComTxUART_WriteControlRegister(SensorComTxUART_ReadControlRegister() &
                                              (uint8)~SensorComTxUART_CTRL_HD_SEND_BREAK);
            }

        #else /* SensorComTxUART_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == SensorComTxUART_SEND_BREAK) ||
                (retMode == SensorComTxUART_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (SensorComTxUART_PARITY_TYPE != SensorComTxUART__B_UART__NONE_REVB) || \
                                    (SensorComTxUART_PARITY_TYPE_SW != 0u) )
                    SensorComTxUART_WriteControlRegister(SensorComTxUART_ReadControlRegister() |
                                                          SensorComTxUART_CTRL_HD_SEND_BREAK);
                #endif /* End SensorComTxUART_PARITY_TYPE != SensorComTxUART__B_UART__NONE_REVB  */

                #if(SensorComTxUART_TXCLKGEN_DP)
                    txPeriod = SensorComTxUART_TXBITCLKTX_COMPLETE_REG;
                    SensorComTxUART_TXBITCLKTX_COMPLETE_REG = SensorComTxUART_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = SensorComTxUART_TXBITCTR_PERIOD_REG;
                    SensorComTxUART_TXBITCTR_PERIOD_REG = SensorComTxUART_TXBITCTR_BREAKBITS8X;
                #endif /* End SensorComTxUART_TXCLKGEN_DP */

                /* Send zeros */
                SensorComTxUART_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = SensorComTxUART_TXSTATUS_REG;
                }
                while((tmpStat & SensorComTxUART_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == SensorComTxUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == SensorComTxUART_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = SensorComTxUART_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & SensorComTxUART_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == SensorComTxUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == SensorComTxUART_REINIT) ||
                (retMode == SensorComTxUART_SEND_WAIT_REINIT) )
            {

            #if(SensorComTxUART_TXCLKGEN_DP)
                SensorComTxUART_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                SensorComTxUART_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End SensorComTxUART_TXCLKGEN_DP */

            #if( (SensorComTxUART_PARITY_TYPE != SensorComTxUART__B_UART__NONE_REVB) || \
                 (SensorComTxUART_PARITY_TYPE_SW != 0u) )
                SensorComTxUART_WriteControlRegister(SensorComTxUART_ReadControlRegister() &
                                                      (uint8) ~SensorComTxUART_CTRL_HD_SEND_BREAK);
            #endif /* End SensorComTxUART_PARITY_TYPE != NONE */
            }
        #endif    /* End SensorComTxUART_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       SensorComTxUART_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       SensorComTxUART_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears SensorComTxUART_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void SensorComTxUART_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( SensorComTxUART_CONTROL_REG_REMOVED == 0u )
            SensorComTxUART_WriteControlRegister(SensorComTxUART_ReadControlRegister() |
                                                  SensorComTxUART_CTRL_MARK);
        #endif /* End SensorComTxUART_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( SensorComTxUART_CONTROL_REG_REMOVED == 0u )
            SensorComTxUART_WriteControlRegister(SensorComTxUART_ReadControlRegister() &
                                                  (uint8) ~SensorComTxUART_CTRL_MARK);
        #endif /* End SensorComTxUART_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndSensorComTxUART_TX_ENABLED */

#if(SensorComTxUART_HD_ENABLED)


    /*******************************************************************************
    * Function Name: SensorComTxUART_LoadRxConfig
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
    void SensorComTxUART_LoadRxConfig(void) 
    {
        SensorComTxUART_WriteControlRegister(SensorComTxUART_ReadControlRegister() &
                                                (uint8)~SensorComTxUART_CTRL_HD_SEND);
        SensorComTxUART_RXBITCTR_PERIOD_REG = SensorComTxUART_HD_RXBITCTR_INIT;

    #if (SensorComTxUART_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        SensorComTxUART_SetRxInterruptMode(SensorComTxUART_INIT_RX_INTERRUPTS_MASK);
    #endif /* (SensorComTxUART_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: SensorComTxUART_LoadTxConfig
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
    void SensorComTxUART_LoadTxConfig(void) 
    {
    #if (SensorComTxUART_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        SensorComTxUART_SetRxInterruptMode(0u);
    #endif /* (SensorComTxUART_RX_INTERRUPT_ENABLED) */

        SensorComTxUART_WriteControlRegister(SensorComTxUART_ReadControlRegister() | SensorComTxUART_CTRL_HD_SEND);
        SensorComTxUART_RXBITCTR_PERIOD_REG = SensorComTxUART_HD_TXBITCTR_INIT;
    }

#endif  /* SensorComTxUART_HD_ENABLED */


/* [] END OF FILE */
