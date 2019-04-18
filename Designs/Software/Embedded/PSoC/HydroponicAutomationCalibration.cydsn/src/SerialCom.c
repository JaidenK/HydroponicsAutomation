/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "SerialCom.h"
uint8 errorStatus = 0u;

/*******************************************************************************
* Function Name: RxIsr
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
*******************************************************************************/

CY_ISR(RxIsr)
{
    uint8 rxStatus;         
    uint8 rxData;           
    
    do
    {
        /* Read receiver status register */
        rxStatus = UART_RXSTATUS_REG;

        if((rxStatus & (UART_RX_STS_BREAK      | UART_RX_STS_PAR_ERROR |
                        UART_RX_STS_STOP_ERROR | UART_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            errorStatus |= rxStatus & ( UART_RX_STS_BREAK      | UART_RX_STS_PAR_ERROR | 
                                        UART_RX_STS_STOP_ERROR | UART_RX_STS_OVERRUN);
        }
        
        if((rxStatus & UART_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read data from the RX data register */
            rxData = UART_RXDATA_REG;
            if(errorStatus == 0u)
            {
                /* Send data backward */
                UART_TXDATA_REG = rxData;
            }
        }
    }while((rxStatus & UART_RX_STS_FIFO_NOTEMPTY) != 0u);

}
/**
 * @function SerialCom_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary Serial Communication
 *        through UART and KitProg
 * @author Barron Wong 01/26/19
*/
void SerialCom_Init(){
    UART_Start();
    isr_rx_StartEx(RxIsr);
}

/**
 * @function _write(void)
 * @param None
 * @return None
 * @brief Overriding _write function for printf redirection to UART
 * @author Barron Wong 01/26/19
*/
/* For GCC compiler revise _write() function for printf functionality */
int _write(int file, char *ptr, int len)
    {
        int i;
        file = file;
        for (i = 0; i < len; i++)
        {
            UART_PutChar(*ptr++);
        }
        return (len);
    }
/* [] END OF FILE */
