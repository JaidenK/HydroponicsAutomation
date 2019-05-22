/*******************************************************************************
* File Name: SensorDataCom.c
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

#include "SensorDataCom.h"
#if (SensorDataCom_INTERNAL_CLOCK_USED)
    #include "SensorDataCom_IntClock.h"
#endif /* End SensorDataCom_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 SensorDataCom_initVar = 0u;

#if (SensorDataCom_TX_INTERRUPT_ENABLED && SensorDataCom_TX_ENABLED)
    volatile uint8 SensorDataCom_txBuffer[SensorDataCom_TX_BUFFER_SIZE];
    volatile uint8 SensorDataCom_txBufferRead = 0u;
    uint8 SensorDataCom_txBufferWrite = 0u;
#endif /* (SensorDataCom_TX_INTERRUPT_ENABLED && SensorDataCom_TX_ENABLED) */

#if (SensorDataCom_RX_INTERRUPT_ENABLED && (SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED))
    uint8 SensorDataCom_errorStatus = 0u;
    volatile uint8 SensorDataCom_rxBuffer[SensorDataCom_RX_BUFFER_SIZE];
    volatile uint8 SensorDataCom_rxBufferRead  = 0u;
    volatile uint8 SensorDataCom_rxBufferWrite = 0u;
    volatile uint8 SensorDataCom_rxBufferLoopDetect = 0u;
    volatile uint8 SensorDataCom_rxBufferOverflow   = 0u;
    #if (SensorDataCom_RXHW_ADDRESS_ENABLED)
        volatile uint8 SensorDataCom_rxAddressMode = SensorDataCom_RX_ADDRESS_MODE;
        volatile uint8 SensorDataCom_rxAddressDetected = 0u;
    #endif /* (SensorDataCom_RXHW_ADDRESS_ENABLED) */
#endif /* (SensorDataCom_RX_INTERRUPT_ENABLED && (SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED)) */


/*******************************************************************************
* Function Name: SensorDataCom_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  SensorDataCom_Start() sets the initVar variable, calls the
*  SensorDataCom_Init() function, and then calls the
*  SensorDataCom_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The SensorDataCom_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time SensorDataCom_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the SensorDataCom_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SensorDataCom_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(SensorDataCom_initVar == 0u)
    {
        SensorDataCom_Init();
        SensorDataCom_initVar = 1u;
    }

    SensorDataCom_Enable();
}


/*******************************************************************************
* Function Name: SensorDataCom_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call SensorDataCom_Init() because
*  the SensorDataCom_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SensorDataCom_Init(void) 
{
    #if(SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED)

        #if (SensorDataCom_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(SensorDataCom_RX_VECT_NUM, &SensorDataCom_RXISR);
            CyIntSetPriority(SensorDataCom_RX_VECT_NUM, SensorDataCom_RX_PRIOR_NUM);
            SensorDataCom_errorStatus = 0u;
        #endif /* (SensorDataCom_RX_INTERRUPT_ENABLED) */

        #if (SensorDataCom_RXHW_ADDRESS_ENABLED)
            SensorDataCom_SetRxAddressMode(SensorDataCom_RX_ADDRESS_MODE);
            SensorDataCom_SetRxAddress1(SensorDataCom_RX_HW_ADDRESS1);
            SensorDataCom_SetRxAddress2(SensorDataCom_RX_HW_ADDRESS2);
        #endif /* End SensorDataCom_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        SensorDataCom_RXBITCTR_PERIOD_REG = SensorDataCom_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        SensorDataCom_RXSTATUS_MASK_REG  = SensorDataCom_INIT_RX_INTERRUPTS_MASK;
    #endif /* End SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED*/

    #if(SensorDataCom_TX_ENABLED)
        #if (SensorDataCom_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(SensorDataCom_TX_VECT_NUM, &SensorDataCom_TXISR);
            CyIntSetPriority(SensorDataCom_TX_VECT_NUM, SensorDataCom_TX_PRIOR_NUM);
        #endif /* (SensorDataCom_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (SensorDataCom_TXCLKGEN_DP)
            SensorDataCom_TXBITCLKGEN_CTR_REG = SensorDataCom_BIT_CENTER;
            SensorDataCom_TXBITCLKTX_COMPLETE_REG = ((SensorDataCom_NUMBER_OF_DATA_BITS +
                        SensorDataCom_NUMBER_OF_START_BIT) * SensorDataCom_OVER_SAMPLE_COUNT) - 1u;
        #else
            SensorDataCom_TXBITCTR_PERIOD_REG = ((SensorDataCom_NUMBER_OF_DATA_BITS +
                        SensorDataCom_NUMBER_OF_START_BIT) * SensorDataCom_OVER_SAMPLE_8) - 1u;
        #endif /* End SensorDataCom_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (SensorDataCom_TX_INTERRUPT_ENABLED)
            SensorDataCom_TXSTATUS_MASK_REG = SensorDataCom_TX_STS_FIFO_EMPTY;
        #else
            SensorDataCom_TXSTATUS_MASK_REG = SensorDataCom_INIT_TX_INTERRUPTS_MASK;
        #endif /*End SensorDataCom_TX_INTERRUPT_ENABLED*/

    #endif /* End SensorDataCom_TX_ENABLED */

    #if(SensorDataCom_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        SensorDataCom_WriteControlRegister( \
            (SensorDataCom_ReadControlRegister() & (uint8)~SensorDataCom_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(SensorDataCom_PARITY_TYPE << SensorDataCom_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End SensorDataCom_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: SensorDataCom_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call SensorDataCom_Enable() because the SensorDataCom_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SensorDataCom_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void SensorDataCom_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        SensorDataCom_RXBITCTR_CONTROL_REG |= SensorDataCom_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        SensorDataCom_RXSTATUS_ACTL_REG  |= SensorDataCom_INT_ENABLE;

        #if (SensorDataCom_RX_INTERRUPT_ENABLED)
            SensorDataCom_EnableRxInt();

            #if (SensorDataCom_RXHW_ADDRESS_ENABLED)
                SensorDataCom_rxAddressDetected = 0u;
            #endif /* (SensorDataCom_RXHW_ADDRESS_ENABLED) */
        #endif /* (SensorDataCom_RX_INTERRUPT_ENABLED) */
    #endif /* (SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED) */

    #if(SensorDataCom_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!SensorDataCom_TXCLKGEN_DP)
            SensorDataCom_TXBITCTR_CONTROL_REG |= SensorDataCom_CNTR_ENABLE;
        #endif /* End SensorDataCom_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        SensorDataCom_TXSTATUS_ACTL_REG |= SensorDataCom_INT_ENABLE;
        #if (SensorDataCom_TX_INTERRUPT_ENABLED)
            SensorDataCom_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            SensorDataCom_EnableTxInt();
        #endif /* (SensorDataCom_TX_INTERRUPT_ENABLED) */
     #endif /* (SensorDataCom_TX_INTERRUPT_ENABLED) */

    #if (SensorDataCom_INTERNAL_CLOCK_USED)
        SensorDataCom_IntClock_Start();  /* Enable the clock */
    #endif /* (SensorDataCom_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SensorDataCom_Stop
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
void SensorDataCom_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED)
        SensorDataCom_RXBITCTR_CONTROL_REG &= (uint8) ~SensorDataCom_CNTR_ENABLE;
    #endif /* (SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED) */

    #if (SensorDataCom_TX_ENABLED)
        #if(!SensorDataCom_TXCLKGEN_DP)
            SensorDataCom_TXBITCTR_CONTROL_REG &= (uint8) ~SensorDataCom_CNTR_ENABLE;
        #endif /* (!SensorDataCom_TXCLKGEN_DP) */
    #endif /* (SensorDataCom_TX_ENABLED) */

    #if (SensorDataCom_INTERNAL_CLOCK_USED)
        SensorDataCom_IntClock_Stop();   /* Disable the clock */
    #endif /* (SensorDataCom_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED)
        SensorDataCom_RXSTATUS_ACTL_REG  &= (uint8) ~SensorDataCom_INT_ENABLE;

        #if (SensorDataCom_RX_INTERRUPT_ENABLED)
            SensorDataCom_DisableRxInt();
        #endif /* (SensorDataCom_RX_INTERRUPT_ENABLED) */
    #endif /* (SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED) */

    #if (SensorDataCom_TX_ENABLED)
        SensorDataCom_TXSTATUS_ACTL_REG &= (uint8) ~SensorDataCom_INT_ENABLE;

        #if (SensorDataCom_TX_INTERRUPT_ENABLED)
            SensorDataCom_DisableTxInt();
        #endif /* (SensorDataCom_TX_INTERRUPT_ENABLED) */
    #endif /* (SensorDataCom_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SensorDataCom_ReadControlRegister
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
uint8 SensorDataCom_ReadControlRegister(void) 
{
    #if (SensorDataCom_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(SensorDataCom_CONTROL_REG);
    #endif /* (SensorDataCom_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: SensorDataCom_WriteControlRegister
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
void  SensorDataCom_WriteControlRegister(uint8 control) 
{
    #if (SensorDataCom_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       SensorDataCom_CONTROL_REG = control;
    #endif /* (SensorDataCom_CONTROL_REG_REMOVED) */
}


#if(SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED)
    /*******************************************************************************
    * Function Name: SensorDataCom_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      SensorDataCom_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      SensorDataCom_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      SensorDataCom_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      SensorDataCom_RX_STS_BREAK            Interrupt on break.
    *      SensorDataCom_RX_STS_OVERRUN          Interrupt on overrun error.
    *      SensorDataCom_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      SensorDataCom_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void SensorDataCom_SetRxInterruptMode(uint8 intSrc) 
    {
        SensorDataCom_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_ReadRxData
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
    *  SensorDataCom_rxBuffer - RAM buffer pointer for save received data.
    *  SensorDataCom_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  SensorDataCom_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  SensorDataCom_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 SensorDataCom_ReadRxData(void) 
    {
        uint8 rxData;

    #if (SensorDataCom_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        SensorDataCom_DisableRxInt();

        locRxBufferRead  = SensorDataCom_rxBufferRead;
        locRxBufferWrite = SensorDataCom_rxBufferWrite;

        if( (SensorDataCom_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = SensorDataCom_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= SensorDataCom_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            SensorDataCom_rxBufferRead = locRxBufferRead;

            if(SensorDataCom_rxBufferLoopDetect != 0u)
            {
                SensorDataCom_rxBufferLoopDetect = 0u;
                #if ((SensorDataCom_RX_INTERRUPT_ENABLED) && (SensorDataCom_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( SensorDataCom_HD_ENABLED )
                        if((SensorDataCom_CONTROL_REG & SensorDataCom_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            SensorDataCom_RXSTATUS_MASK_REG  |= SensorDataCom_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        SensorDataCom_RXSTATUS_MASK_REG  |= SensorDataCom_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end SensorDataCom_HD_ENABLED */
                #endif /* ((SensorDataCom_RX_INTERRUPT_ENABLED) && (SensorDataCom_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = SensorDataCom_RXDATA_REG;
        }

        SensorDataCom_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = SensorDataCom_RXDATA_REG;

    #endif /* (SensorDataCom_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_ReadRxStatus
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
    *  SensorDataCom_RX_STS_FIFO_NOTEMPTY.
    *  SensorDataCom_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  SensorDataCom_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   SensorDataCom_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   SensorDataCom_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 SensorDataCom_ReadRxStatus(void) 
    {
        uint8 status;

        status = SensorDataCom_RXSTATUS_REG & SensorDataCom_RX_HW_MASK;

    #if (SensorDataCom_RX_INTERRUPT_ENABLED)
        if(SensorDataCom_rxBufferOverflow != 0u)
        {
            status |= SensorDataCom_RX_STS_SOFT_BUFF_OVER;
            SensorDataCom_rxBufferOverflow = 0u;
        }
    #endif /* (SensorDataCom_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. SensorDataCom_GetChar() is
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
    *  SensorDataCom_rxBuffer - RAM buffer pointer for save received data.
    *  SensorDataCom_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  SensorDataCom_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  SensorDataCom_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 SensorDataCom_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (SensorDataCom_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        SensorDataCom_DisableRxInt();

        locRxBufferRead  = SensorDataCom_rxBufferRead;
        locRxBufferWrite = SensorDataCom_rxBufferWrite;

        if( (SensorDataCom_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = SensorDataCom_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= SensorDataCom_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            SensorDataCom_rxBufferRead = locRxBufferRead;

            if(SensorDataCom_rxBufferLoopDetect != 0u)
            {
                SensorDataCom_rxBufferLoopDetect = 0u;
                #if( (SensorDataCom_RX_INTERRUPT_ENABLED) && (SensorDataCom_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( SensorDataCom_HD_ENABLED )
                        if((SensorDataCom_CONTROL_REG & SensorDataCom_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            SensorDataCom_RXSTATUS_MASK_REG |= SensorDataCom_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        SensorDataCom_RXSTATUS_MASK_REG |= SensorDataCom_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end SensorDataCom_HD_ENABLED */
                #endif /* SensorDataCom_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = SensorDataCom_RXSTATUS_REG;
            if((rxStatus & SensorDataCom_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = SensorDataCom_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (SensorDataCom_RX_STS_BREAK | SensorDataCom_RX_STS_PAR_ERROR |
                                SensorDataCom_RX_STS_STOP_ERROR | SensorDataCom_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        SensorDataCom_EnableRxInt();

    #else

        rxStatus =SensorDataCom_RXSTATUS_REG;
        if((rxStatus & SensorDataCom_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = SensorDataCom_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (SensorDataCom_RX_STS_BREAK | SensorDataCom_RX_STS_PAR_ERROR |
                            SensorDataCom_RX_STS_STOP_ERROR | SensorDataCom_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (SensorDataCom_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_GetByte
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
    uint16 SensorDataCom_GetByte(void) 
    {
        
    #if (SensorDataCom_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        SensorDataCom_DisableRxInt();
        locErrorStatus = (uint16)SensorDataCom_errorStatus;
        SensorDataCom_errorStatus = 0u;
        SensorDataCom_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | SensorDataCom_ReadRxData() );
    #else
        return ( ((uint16)SensorDataCom_ReadRxStatus() << 8u) | SensorDataCom_ReadRxData() );
    #endif /* SensorDataCom_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_GetRxBufferSize
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
    *  SensorDataCom_rxBufferWrite - used to calculate left bytes.
    *  SensorDataCom_rxBufferRead - used to calculate left bytes.
    *  SensorDataCom_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 SensorDataCom_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (SensorDataCom_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        SensorDataCom_DisableRxInt();

        if(SensorDataCom_rxBufferRead == SensorDataCom_rxBufferWrite)
        {
            if(SensorDataCom_rxBufferLoopDetect != 0u)
            {
                size = SensorDataCom_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(SensorDataCom_rxBufferRead < SensorDataCom_rxBufferWrite)
        {
            size = (SensorDataCom_rxBufferWrite - SensorDataCom_rxBufferRead);
        }
        else
        {
            size = (SensorDataCom_RX_BUFFER_SIZE - SensorDataCom_rxBufferRead) + SensorDataCom_rxBufferWrite;
        }

        SensorDataCom_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((SensorDataCom_RXSTATUS_REG & SensorDataCom_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (SensorDataCom_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_ClearRxBuffer
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
    *  SensorDataCom_rxBufferWrite - cleared to zero.
    *  SensorDataCom_rxBufferRead - cleared to zero.
    *  SensorDataCom_rxBufferLoopDetect - cleared to zero.
    *  SensorDataCom_rxBufferOverflow - cleared to zero.
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
    void SensorDataCom_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        SensorDataCom_RXDATA_AUX_CTL_REG |= (uint8)  SensorDataCom_RX_FIFO_CLR;
        SensorDataCom_RXDATA_AUX_CTL_REG &= (uint8) ~SensorDataCom_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (SensorDataCom_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        SensorDataCom_DisableRxInt();

        SensorDataCom_rxBufferRead = 0u;
        SensorDataCom_rxBufferWrite = 0u;
        SensorDataCom_rxBufferLoopDetect = 0u;
        SensorDataCom_rxBufferOverflow = 0u;

        SensorDataCom_EnableRxInt();

    #endif /* (SensorDataCom_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: SensorDataCom_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  SensorDataCom__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  SensorDataCom__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  SensorDataCom__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  SensorDataCom__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  SensorDataCom__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  SensorDataCom_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  SensorDataCom_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void SensorDataCom_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(SensorDataCom_RXHW_ADDRESS_ENABLED)
            #if(SensorDataCom_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* SensorDataCom_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = SensorDataCom_CONTROL_REG & (uint8)~SensorDataCom_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << SensorDataCom_CTRL_RXADDR_MODE0_SHIFT);
                SensorDataCom_CONTROL_REG = tmpCtrl;

                #if(SensorDataCom_RX_INTERRUPT_ENABLED && \
                   (SensorDataCom_RXBUFFERSIZE > SensorDataCom_FIFO_LENGTH) )
                    SensorDataCom_rxAddressMode = addressMode;
                    SensorDataCom_rxAddressDetected = 0u;
                #endif /* End SensorDataCom_RXBUFFERSIZE > SensorDataCom_FIFO_LENGTH*/
            #endif /* End SensorDataCom_CONTROL_REG_REMOVED */
        #else /* SensorDataCom_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End SensorDataCom_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_SetRxAddress1
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
    void SensorDataCom_SetRxAddress1(uint8 address) 
    {
        SensorDataCom_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_SetRxAddress2
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
    void SensorDataCom_SetRxAddress2(uint8 address) 
    {
        SensorDataCom_RXADDRESS2_REG = address;
    }

#endif  /* SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED*/


#if( (SensorDataCom_TX_ENABLED) || (SensorDataCom_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: SensorDataCom_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   SensorDataCom_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   SensorDataCom_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   SensorDataCom_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   SensorDataCom_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void SensorDataCom_SetTxInterruptMode(uint8 intSrc) 
    {
        SensorDataCom_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_WriteTxData
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
    *  SensorDataCom_txBuffer - RAM buffer pointer for save data for transmission
    *  SensorDataCom_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  SensorDataCom_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  SensorDataCom_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void SensorDataCom_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(SensorDataCom_initVar != 0u)
        {
        #if (SensorDataCom_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            SensorDataCom_DisableTxInt();

            if( (SensorDataCom_txBufferRead == SensorDataCom_txBufferWrite) &&
                ((SensorDataCom_TXSTATUS_REG & SensorDataCom_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                SensorDataCom_TXDATA_REG = txDataByte;
            }
            else
            {
                if(SensorDataCom_txBufferWrite >= SensorDataCom_TX_BUFFER_SIZE)
                {
                    SensorDataCom_txBufferWrite = 0u;
                }

                SensorDataCom_txBuffer[SensorDataCom_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                SensorDataCom_txBufferWrite++;
            }

            SensorDataCom_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            SensorDataCom_TXDATA_REG = txDataByte;

        #endif /*(SensorDataCom_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_ReadTxStatus
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
    uint8 SensorDataCom_ReadTxStatus(void) 
    {
        return(SensorDataCom_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_PutChar
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
    *  SensorDataCom_txBuffer - RAM buffer pointer for save data for transmission
    *  SensorDataCom_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  SensorDataCom_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  SensorDataCom_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void SensorDataCom_PutChar(uint8 txDataByte) 
    {
    #if (SensorDataCom_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((SensorDataCom_TX_BUFFER_SIZE > SensorDataCom_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            SensorDataCom_DisableTxInt();
        #endif /* (SensorDataCom_TX_BUFFER_SIZE > SensorDataCom_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = SensorDataCom_txBufferWrite;
            locTxBufferRead  = SensorDataCom_txBufferRead;

        #if ((SensorDataCom_TX_BUFFER_SIZE > SensorDataCom_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            SensorDataCom_EnableTxInt();
        #endif /* (SensorDataCom_TX_BUFFER_SIZE > SensorDataCom_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(SensorDataCom_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((SensorDataCom_TXSTATUS_REG & SensorDataCom_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            SensorDataCom_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= SensorDataCom_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            SensorDataCom_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((SensorDataCom_TX_BUFFER_SIZE > SensorDataCom_MAX_BYTE_VALUE) && (CY_PSOC3))
            SensorDataCom_DisableTxInt();
        #endif /* (SensorDataCom_TX_BUFFER_SIZE > SensorDataCom_MAX_BYTE_VALUE) && (CY_PSOC3) */

            SensorDataCom_txBufferWrite = locTxBufferWrite;

        #if ((SensorDataCom_TX_BUFFER_SIZE > SensorDataCom_MAX_BYTE_VALUE) && (CY_PSOC3))
            SensorDataCom_EnableTxInt();
        #endif /* (SensorDataCom_TX_BUFFER_SIZE > SensorDataCom_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (SensorDataCom_TXSTATUS_REG & SensorDataCom_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                SensorDataCom_SetPendingTxInt();
            }
        }

    #else

        while((SensorDataCom_TXSTATUS_REG & SensorDataCom_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        SensorDataCom_TXDATA_REG = txDataByte;

    #endif /* SensorDataCom_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_PutString
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
    *  SensorDataCom_initVar - checked to identify that the component has been
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
    void SensorDataCom_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(SensorDataCom_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                SensorDataCom_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_PutArray
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
    *  SensorDataCom_initVar - checked to identify that the component has been
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
    void SensorDataCom_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(SensorDataCom_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                SensorDataCom_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_PutCRLF
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
    *  SensorDataCom_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void SensorDataCom_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(SensorDataCom_initVar != 0u)
        {
            SensorDataCom_PutChar(txDataByte);
            SensorDataCom_PutChar(0x0Du);
            SensorDataCom_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_GetTxBufferSize
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
    *  SensorDataCom_txBufferWrite - used to calculate left space.
    *  SensorDataCom_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 SensorDataCom_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (SensorDataCom_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        SensorDataCom_DisableTxInt();

        if(SensorDataCom_txBufferRead == SensorDataCom_txBufferWrite)
        {
            size = 0u;
        }
        else if(SensorDataCom_txBufferRead < SensorDataCom_txBufferWrite)
        {
            size = (SensorDataCom_txBufferWrite - SensorDataCom_txBufferRead);
        }
        else
        {
            size = (SensorDataCom_TX_BUFFER_SIZE - SensorDataCom_txBufferRead) +
                    SensorDataCom_txBufferWrite;
        }

        SensorDataCom_EnableTxInt();

    #else

        size = SensorDataCom_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & SensorDataCom_TX_STS_FIFO_FULL) != 0u)
        {
            size = SensorDataCom_FIFO_LENGTH;
        }
        else if((size & SensorDataCom_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (SensorDataCom_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_ClearTxBuffer
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
    *  SensorDataCom_txBufferWrite - cleared to zero.
    *  SensorDataCom_txBufferRead - cleared to zero.
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
    void SensorDataCom_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        SensorDataCom_TXDATA_AUX_CTL_REG |= (uint8)  SensorDataCom_TX_FIFO_CLR;
        SensorDataCom_TXDATA_AUX_CTL_REG &= (uint8) ~SensorDataCom_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (SensorDataCom_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        SensorDataCom_DisableTxInt();

        SensorDataCom_txBufferRead = 0u;
        SensorDataCom_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        SensorDataCom_EnableTxInt();

    #endif /* (SensorDataCom_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   SensorDataCom_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   SensorDataCom_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   SensorDataCom_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   SensorDataCom_SEND_WAIT_REINIT - Performs both options: 
    *      SensorDataCom_SEND_BREAK and SensorDataCom_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  SensorDataCom_initVar - checked to identify that the component has been
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
    *     When interrupt appear with SensorDataCom_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The SensorDataCom_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void SensorDataCom_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(SensorDataCom_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(SensorDataCom_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == SensorDataCom_SEND_BREAK) ||
                (retMode == SensorDataCom_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                SensorDataCom_WriteControlRegister(SensorDataCom_ReadControlRegister() |
                                                      SensorDataCom_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                SensorDataCom_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = SensorDataCom_TXSTATUS_REG;
                }
                while((tmpStat & SensorDataCom_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == SensorDataCom_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == SensorDataCom_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = SensorDataCom_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & SensorDataCom_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == SensorDataCom_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == SensorDataCom_REINIT) ||
                (retMode == SensorDataCom_SEND_WAIT_REINIT) )
            {
                SensorDataCom_WriteControlRegister(SensorDataCom_ReadControlRegister() &
                                              (uint8)~SensorDataCom_CTRL_HD_SEND_BREAK);
            }

        #else /* SensorDataCom_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == SensorDataCom_SEND_BREAK) ||
                (retMode == SensorDataCom_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (SensorDataCom_PARITY_TYPE != SensorDataCom__B_UART__NONE_REVB) || \
                                    (SensorDataCom_PARITY_TYPE_SW != 0u) )
                    SensorDataCom_WriteControlRegister(SensorDataCom_ReadControlRegister() |
                                                          SensorDataCom_CTRL_HD_SEND_BREAK);
                #endif /* End SensorDataCom_PARITY_TYPE != SensorDataCom__B_UART__NONE_REVB  */

                #if(SensorDataCom_TXCLKGEN_DP)
                    txPeriod = SensorDataCom_TXBITCLKTX_COMPLETE_REG;
                    SensorDataCom_TXBITCLKTX_COMPLETE_REG = SensorDataCom_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = SensorDataCom_TXBITCTR_PERIOD_REG;
                    SensorDataCom_TXBITCTR_PERIOD_REG = SensorDataCom_TXBITCTR_BREAKBITS8X;
                #endif /* End SensorDataCom_TXCLKGEN_DP */

                /* Send zeros */
                SensorDataCom_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = SensorDataCom_TXSTATUS_REG;
                }
                while((tmpStat & SensorDataCom_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == SensorDataCom_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == SensorDataCom_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = SensorDataCom_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & SensorDataCom_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == SensorDataCom_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == SensorDataCom_REINIT) ||
                (retMode == SensorDataCom_SEND_WAIT_REINIT) )
            {

            #if(SensorDataCom_TXCLKGEN_DP)
                SensorDataCom_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                SensorDataCom_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End SensorDataCom_TXCLKGEN_DP */

            #if( (SensorDataCom_PARITY_TYPE != SensorDataCom__B_UART__NONE_REVB) || \
                 (SensorDataCom_PARITY_TYPE_SW != 0u) )
                SensorDataCom_WriteControlRegister(SensorDataCom_ReadControlRegister() &
                                                      (uint8) ~SensorDataCom_CTRL_HD_SEND_BREAK);
            #endif /* End SensorDataCom_PARITY_TYPE != NONE */
            }
        #endif    /* End SensorDataCom_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       SensorDataCom_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       SensorDataCom_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears SensorDataCom_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void SensorDataCom_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( SensorDataCom_CONTROL_REG_REMOVED == 0u )
            SensorDataCom_WriteControlRegister(SensorDataCom_ReadControlRegister() |
                                                  SensorDataCom_CTRL_MARK);
        #endif /* End SensorDataCom_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( SensorDataCom_CONTROL_REG_REMOVED == 0u )
            SensorDataCom_WriteControlRegister(SensorDataCom_ReadControlRegister() &
                                                  (uint8) ~SensorDataCom_CTRL_MARK);
        #endif /* End SensorDataCom_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndSensorDataCom_TX_ENABLED */

#if(SensorDataCom_HD_ENABLED)


    /*******************************************************************************
    * Function Name: SensorDataCom_LoadRxConfig
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
    void SensorDataCom_LoadRxConfig(void) 
    {
        SensorDataCom_WriteControlRegister(SensorDataCom_ReadControlRegister() &
                                                (uint8)~SensorDataCom_CTRL_HD_SEND);
        SensorDataCom_RXBITCTR_PERIOD_REG = SensorDataCom_HD_RXBITCTR_INIT;

    #if (SensorDataCom_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        SensorDataCom_SetRxInterruptMode(SensorDataCom_INIT_RX_INTERRUPTS_MASK);
    #endif /* (SensorDataCom_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: SensorDataCom_LoadTxConfig
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
    void SensorDataCom_LoadTxConfig(void) 
    {
    #if (SensorDataCom_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        SensorDataCom_SetRxInterruptMode(0u);
    #endif /* (SensorDataCom_RX_INTERRUPT_ENABLED) */

        SensorDataCom_WriteControlRegister(SensorDataCom_ReadControlRegister() | SensorDataCom_CTRL_HD_SEND);
        SensorDataCom_RXBITCTR_PERIOD_REG = SensorDataCom_HD_TXBITCTR_INIT;
    }

#endif  /* SensorDataCom_HD_ENABLED */


/* [] END OF FILE */
