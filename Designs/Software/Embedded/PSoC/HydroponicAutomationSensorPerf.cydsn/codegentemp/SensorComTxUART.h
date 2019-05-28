/*******************************************************************************
* File Name: SensorComTxUART.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_SensorComTxUART_H)
#define CY_UART_SensorComTxUART_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define SensorComTxUART_RX_ENABLED                     (0u)
#define SensorComTxUART_TX_ENABLED                     (1u)
#define SensorComTxUART_HD_ENABLED                     (0u)
#define SensorComTxUART_RX_INTERRUPT_ENABLED           (0u)
#define SensorComTxUART_TX_INTERRUPT_ENABLED           (0u)
#define SensorComTxUART_INTERNAL_CLOCK_USED            (1u)
#define SensorComTxUART_RXHW_ADDRESS_ENABLED           (0u)
#define SensorComTxUART_OVER_SAMPLE_COUNT              (8u)
#define SensorComTxUART_PARITY_TYPE                    (0u)
#define SensorComTxUART_PARITY_TYPE_SW                 (0u)
#define SensorComTxUART_BREAK_DETECT                   (0u)
#define SensorComTxUART_BREAK_BITS_TX                  (13u)
#define SensorComTxUART_BREAK_BITS_RX                  (13u)
#define SensorComTxUART_TXCLKGEN_DP                    (1u)
#define SensorComTxUART_USE23POLLING                   (1u)
#define SensorComTxUART_FLOW_CONTROL                   (0u)
#define SensorComTxUART_CLK_FREQ                       (0u)
#define SensorComTxUART_TX_BUFFER_SIZE                 (4u)
#define SensorComTxUART_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(SensorComTxUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define SensorComTxUART_CONTROL_REG_REMOVED            (0u)
#else
    #define SensorComTxUART_CONTROL_REG_REMOVED            (1u)
#endif /* End SensorComTxUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct SensorComTxUART_backupStruct_
{
    uint8 enableState;

    #if(SensorComTxUART_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End SensorComTxUART_CONTROL_REG_REMOVED */

} SensorComTxUART_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void SensorComTxUART_Start(void) ;
void SensorComTxUART_Stop(void) ;
uint8 SensorComTxUART_ReadControlRegister(void) ;
void SensorComTxUART_WriteControlRegister(uint8 control) ;

void SensorComTxUART_Init(void) ;
void SensorComTxUART_Enable(void) ;
void SensorComTxUART_SaveConfig(void) ;
void SensorComTxUART_RestoreConfig(void) ;
void SensorComTxUART_Sleep(void) ;
void SensorComTxUART_Wakeup(void) ;

/* Only if RX is enabled */
#if( (SensorComTxUART_RX_ENABLED) || (SensorComTxUART_HD_ENABLED) )

    #if (SensorComTxUART_RX_INTERRUPT_ENABLED)
        #define SensorComTxUART_EnableRxInt()  CyIntEnable (SensorComTxUART_RX_VECT_NUM)
        #define SensorComTxUART_DisableRxInt() CyIntDisable(SensorComTxUART_RX_VECT_NUM)
        CY_ISR_PROTO(SensorComTxUART_RXISR);
    #endif /* SensorComTxUART_RX_INTERRUPT_ENABLED */

    void SensorComTxUART_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void SensorComTxUART_SetRxAddress1(uint8 address) ;
    void SensorComTxUART_SetRxAddress2(uint8 address) ;

    void  SensorComTxUART_SetRxInterruptMode(uint8 intSrc) ;
    uint8 SensorComTxUART_ReadRxData(void) ;
    uint8 SensorComTxUART_ReadRxStatus(void) ;
    uint8 SensorComTxUART_GetChar(void) ;
    uint16 SensorComTxUART_GetByte(void) ;
    uint8 SensorComTxUART_GetRxBufferSize(void)
                                                            ;
    void SensorComTxUART_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define SensorComTxUART_GetRxInterruptSource   SensorComTxUART_ReadRxStatus

#endif /* End (SensorComTxUART_RX_ENABLED) || (SensorComTxUART_HD_ENABLED) */

/* Only if TX is enabled */
#if(SensorComTxUART_TX_ENABLED || SensorComTxUART_HD_ENABLED)

    #if(SensorComTxUART_TX_INTERRUPT_ENABLED)
        #define SensorComTxUART_EnableTxInt()  CyIntEnable (SensorComTxUART_TX_VECT_NUM)
        #define SensorComTxUART_DisableTxInt() CyIntDisable(SensorComTxUART_TX_VECT_NUM)
        #define SensorComTxUART_SetPendingTxInt() CyIntSetPending(SensorComTxUART_TX_VECT_NUM)
        #define SensorComTxUART_ClearPendingTxInt() CyIntClearPending(SensorComTxUART_TX_VECT_NUM)
        CY_ISR_PROTO(SensorComTxUART_TXISR);
    #endif /* SensorComTxUART_TX_INTERRUPT_ENABLED */

    void SensorComTxUART_SetTxInterruptMode(uint8 intSrc) ;
    void SensorComTxUART_WriteTxData(uint8 txDataByte) ;
    uint8 SensorComTxUART_ReadTxStatus(void) ;
    void SensorComTxUART_PutChar(uint8 txDataByte) ;
    void SensorComTxUART_PutString(const char8 string[]) ;
    void SensorComTxUART_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void SensorComTxUART_PutCRLF(uint8 txDataByte) ;
    void SensorComTxUART_ClearTxBuffer(void) ;
    void SensorComTxUART_SetTxAddressMode(uint8 addressMode) ;
    void SensorComTxUART_SendBreak(uint8 retMode) ;
    uint8 SensorComTxUART_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define SensorComTxUART_PutStringConst         SensorComTxUART_PutString
    #define SensorComTxUART_PutArrayConst          SensorComTxUART_PutArray
    #define SensorComTxUART_GetTxInterruptSource   SensorComTxUART_ReadTxStatus

#endif /* End SensorComTxUART_TX_ENABLED || SensorComTxUART_HD_ENABLED */

#if(SensorComTxUART_HD_ENABLED)
    void SensorComTxUART_LoadRxConfig(void) ;
    void SensorComTxUART_LoadTxConfig(void) ;
#endif /* End SensorComTxUART_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SensorComTxUART) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    SensorComTxUART_CyBtldrCommStart(void) CYSMALL ;
    void    SensorComTxUART_CyBtldrCommStop(void) CYSMALL ;
    void    SensorComTxUART_CyBtldrCommReset(void) CYSMALL ;
    cystatus SensorComTxUART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus SensorComTxUART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SensorComTxUART)
        #define CyBtldrCommStart    SensorComTxUART_CyBtldrCommStart
        #define CyBtldrCommStop     SensorComTxUART_CyBtldrCommStop
        #define CyBtldrCommReset    SensorComTxUART_CyBtldrCommReset
        #define CyBtldrCommWrite    SensorComTxUART_CyBtldrCommWrite
        #define CyBtldrCommRead     SensorComTxUART_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SensorComTxUART) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define SensorComTxUART_BYTE2BYTE_TIME_OUT (25u)
    #define SensorComTxUART_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define SensorComTxUART_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define SensorComTxUART_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define SensorComTxUART_SET_SPACE      (0x00u)
#define SensorComTxUART_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (SensorComTxUART_TX_ENABLED) || (SensorComTxUART_HD_ENABLED) )
    #if(SensorComTxUART_TX_INTERRUPT_ENABLED)
        #define SensorComTxUART_TX_VECT_NUM            (uint8)SensorComTxUART_TXInternalInterrupt__INTC_NUMBER
        #define SensorComTxUART_TX_PRIOR_NUM           (uint8)SensorComTxUART_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* SensorComTxUART_TX_INTERRUPT_ENABLED */

    #define SensorComTxUART_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define SensorComTxUART_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define SensorComTxUART_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(SensorComTxUART_TX_ENABLED)
        #define SensorComTxUART_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (SensorComTxUART_HD_ENABLED) */
        #define SensorComTxUART_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (SensorComTxUART_TX_ENABLED) */

    #define SensorComTxUART_TX_STS_COMPLETE            (uint8)(0x01u << SensorComTxUART_TX_STS_COMPLETE_SHIFT)
    #define SensorComTxUART_TX_STS_FIFO_EMPTY          (uint8)(0x01u << SensorComTxUART_TX_STS_FIFO_EMPTY_SHIFT)
    #define SensorComTxUART_TX_STS_FIFO_FULL           (uint8)(0x01u << SensorComTxUART_TX_STS_FIFO_FULL_SHIFT)
    #define SensorComTxUART_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << SensorComTxUART_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (SensorComTxUART_TX_ENABLED) || (SensorComTxUART_HD_ENABLED)*/

#if( (SensorComTxUART_RX_ENABLED) || (SensorComTxUART_HD_ENABLED) )
    #if(SensorComTxUART_RX_INTERRUPT_ENABLED)
        #define SensorComTxUART_RX_VECT_NUM            (uint8)SensorComTxUART_RXInternalInterrupt__INTC_NUMBER
        #define SensorComTxUART_RX_PRIOR_NUM           (uint8)SensorComTxUART_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* SensorComTxUART_RX_INTERRUPT_ENABLED */
    #define SensorComTxUART_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define SensorComTxUART_RX_STS_BREAK_SHIFT             (0x01u)
    #define SensorComTxUART_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define SensorComTxUART_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define SensorComTxUART_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define SensorComTxUART_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define SensorComTxUART_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define SensorComTxUART_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define SensorComTxUART_RX_STS_MRKSPC           (uint8)(0x01u << SensorComTxUART_RX_STS_MRKSPC_SHIFT)
    #define SensorComTxUART_RX_STS_BREAK            (uint8)(0x01u << SensorComTxUART_RX_STS_BREAK_SHIFT)
    #define SensorComTxUART_RX_STS_PAR_ERROR        (uint8)(0x01u << SensorComTxUART_RX_STS_PAR_ERROR_SHIFT)
    #define SensorComTxUART_RX_STS_STOP_ERROR       (uint8)(0x01u << SensorComTxUART_RX_STS_STOP_ERROR_SHIFT)
    #define SensorComTxUART_RX_STS_OVERRUN          (uint8)(0x01u << SensorComTxUART_RX_STS_OVERRUN_SHIFT)
    #define SensorComTxUART_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << SensorComTxUART_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define SensorComTxUART_RX_STS_ADDR_MATCH       (uint8)(0x01u << SensorComTxUART_RX_STS_ADDR_MATCH_SHIFT)
    #define SensorComTxUART_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << SensorComTxUART_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define SensorComTxUART_RX_HW_MASK                     (0x7Fu)
#endif /* End (SensorComTxUART_RX_ENABLED) || (SensorComTxUART_HD_ENABLED) */

/* Control Register definitions */
#define SensorComTxUART_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define SensorComTxUART_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define SensorComTxUART_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define SensorComTxUART_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define SensorComTxUART_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define SensorComTxUART_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define SensorComTxUART_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define SensorComTxUART_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define SensorComTxUART_CTRL_HD_SEND               (uint8)(0x01u << SensorComTxUART_CTRL_HD_SEND_SHIFT)
#define SensorComTxUART_CTRL_HD_SEND_BREAK         (uint8)(0x01u << SensorComTxUART_CTRL_HD_SEND_BREAK_SHIFT)
#define SensorComTxUART_CTRL_MARK                  (uint8)(0x01u << SensorComTxUART_CTRL_MARK_SHIFT)
#define SensorComTxUART_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << SensorComTxUART_CTRL_PARITY_TYPE0_SHIFT)
#define SensorComTxUART_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << SensorComTxUART_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define SensorComTxUART_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define SensorComTxUART_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define SensorComTxUART_SEND_BREAK                         (0x00u)
#define SensorComTxUART_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define SensorComTxUART_REINIT                             (0x02u)
#define SensorComTxUART_SEND_WAIT_REINIT                   (0x03u)

#define SensorComTxUART_OVER_SAMPLE_8                      (8u)
#define SensorComTxUART_OVER_SAMPLE_16                     (16u)

#define SensorComTxUART_BIT_CENTER                         (SensorComTxUART_OVER_SAMPLE_COUNT - 2u)

#define SensorComTxUART_FIFO_LENGTH                        (4u)
#define SensorComTxUART_NUMBER_OF_START_BIT                (1u)
#define SensorComTxUART_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define SensorComTxUART_TXBITCTR_BREAKBITS8X   ((SensorComTxUART_BREAK_BITS_TX * SensorComTxUART_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define SensorComTxUART_TXBITCTR_BREAKBITS ((SensorComTxUART_BREAK_BITS_TX * SensorComTxUART_OVER_SAMPLE_COUNT) - 1u)

#define SensorComTxUART_HALF_BIT_COUNT   \
                            (((SensorComTxUART_OVER_SAMPLE_COUNT / 2u) + (SensorComTxUART_USE23POLLING * 1u)) - 2u)
#if (SensorComTxUART_OVER_SAMPLE_COUNT == SensorComTxUART_OVER_SAMPLE_8)
    #define SensorComTxUART_HD_TXBITCTR_INIT   (((SensorComTxUART_BREAK_BITS_TX + \
                            SensorComTxUART_NUMBER_OF_START_BIT) * SensorComTxUART_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define SensorComTxUART_RXBITCTR_INIT  ((((SensorComTxUART_BREAK_BITS_RX + SensorComTxUART_NUMBER_OF_START_BIT) \
                            * SensorComTxUART_OVER_SAMPLE_COUNT) + SensorComTxUART_HALF_BIT_COUNT) - 1u)

#else /* SensorComTxUART_OVER_SAMPLE_COUNT == SensorComTxUART_OVER_SAMPLE_16 */
    #define SensorComTxUART_HD_TXBITCTR_INIT   ((8u * SensorComTxUART_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define SensorComTxUART_RXBITCTR_INIT      (((7u * SensorComTxUART_OVER_SAMPLE_COUNT) - 1u) + \
                                                      SensorComTxUART_HALF_BIT_COUNT)
#endif /* End SensorComTxUART_OVER_SAMPLE_COUNT */

#define SensorComTxUART_HD_RXBITCTR_INIT                   SensorComTxUART_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 SensorComTxUART_initVar;
#if (SensorComTxUART_TX_INTERRUPT_ENABLED && SensorComTxUART_TX_ENABLED)
    extern volatile uint8 SensorComTxUART_txBuffer[SensorComTxUART_TX_BUFFER_SIZE];
    extern volatile uint8 SensorComTxUART_txBufferRead;
    extern uint8 SensorComTxUART_txBufferWrite;
#endif /* (SensorComTxUART_TX_INTERRUPT_ENABLED && SensorComTxUART_TX_ENABLED) */
#if (SensorComTxUART_RX_INTERRUPT_ENABLED && (SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED))
    extern uint8 SensorComTxUART_errorStatus;
    extern volatile uint8 SensorComTxUART_rxBuffer[SensorComTxUART_RX_BUFFER_SIZE];
    extern volatile uint8 SensorComTxUART_rxBufferRead;
    extern volatile uint8 SensorComTxUART_rxBufferWrite;
    extern volatile uint8 SensorComTxUART_rxBufferLoopDetect;
    extern volatile uint8 SensorComTxUART_rxBufferOverflow;
    #if (SensorComTxUART_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 SensorComTxUART_rxAddressMode;
        extern volatile uint8 SensorComTxUART_rxAddressDetected;
    #endif /* (SensorComTxUART_RXHW_ADDRESS_ENABLED) */
#endif /* (SensorComTxUART_RX_INTERRUPT_ENABLED && (SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define SensorComTxUART__B_UART__AM_SW_BYTE_BYTE 1
#define SensorComTxUART__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define SensorComTxUART__B_UART__AM_HW_BYTE_BY_BYTE 3
#define SensorComTxUART__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define SensorComTxUART__B_UART__AM_NONE 0

#define SensorComTxUART__B_UART__NONE_REVB 0
#define SensorComTxUART__B_UART__EVEN_REVB 1
#define SensorComTxUART__B_UART__ODD_REVB 2
#define SensorComTxUART__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define SensorComTxUART_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define SensorComTxUART_NUMBER_OF_STOP_BITS    (1u)

#if (SensorComTxUART_RXHW_ADDRESS_ENABLED)
    #define SensorComTxUART_RX_ADDRESS_MODE    (0u)
    #define SensorComTxUART_RX_HW_ADDRESS1     (0u)
    #define SensorComTxUART_RX_HW_ADDRESS2     (0u)
#endif /* (SensorComTxUART_RXHW_ADDRESS_ENABLED) */

#define SensorComTxUART_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((0 << SensorComTxUART_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << SensorComTxUART_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << SensorComTxUART_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << SensorComTxUART_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << SensorComTxUART_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << SensorComTxUART_RX_STS_BREAK_SHIFT) \
                                        | (0 << SensorComTxUART_RX_STS_OVERRUN_SHIFT))

#define SensorComTxUART_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << SensorComTxUART_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << SensorComTxUART_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << SensorComTxUART_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << SensorComTxUART_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef SensorComTxUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define SensorComTxUART_CONTROL_REG \
                            (* (reg8 *) SensorComTxUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define SensorComTxUART_CONTROL_PTR \
                            (  (reg8 *) SensorComTxUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End SensorComTxUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(SensorComTxUART_TX_ENABLED)
    #define SensorComTxUART_TXDATA_REG          (* (reg8 *) SensorComTxUART_BUART_sTX_TxShifter_u0__F0_REG)
    #define SensorComTxUART_TXDATA_PTR          (  (reg8 *) SensorComTxUART_BUART_sTX_TxShifter_u0__F0_REG)
    #define SensorComTxUART_TXDATA_AUX_CTL_REG  (* (reg8 *) SensorComTxUART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define SensorComTxUART_TXDATA_AUX_CTL_PTR  (  (reg8 *) SensorComTxUART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define SensorComTxUART_TXSTATUS_REG        (* (reg8 *) SensorComTxUART_BUART_sTX_TxSts__STATUS_REG)
    #define SensorComTxUART_TXSTATUS_PTR        (  (reg8 *) SensorComTxUART_BUART_sTX_TxSts__STATUS_REG)
    #define SensorComTxUART_TXSTATUS_MASK_REG   (* (reg8 *) SensorComTxUART_BUART_sTX_TxSts__MASK_REG)
    #define SensorComTxUART_TXSTATUS_MASK_PTR   (  (reg8 *) SensorComTxUART_BUART_sTX_TxSts__MASK_REG)
    #define SensorComTxUART_TXSTATUS_ACTL_REG   (* (reg8 *) SensorComTxUART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define SensorComTxUART_TXSTATUS_ACTL_PTR   (  (reg8 *) SensorComTxUART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(SensorComTxUART_TXCLKGEN_DP)
        #define SensorComTxUART_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) SensorComTxUART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define SensorComTxUART_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) SensorComTxUART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define SensorComTxUART_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) SensorComTxUART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define SensorComTxUART_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) SensorComTxUART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define SensorComTxUART_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) SensorComTxUART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define SensorComTxUART_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) SensorComTxUART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define SensorComTxUART_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) SensorComTxUART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define SensorComTxUART_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) SensorComTxUART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define SensorComTxUART_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) SensorComTxUART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define SensorComTxUART_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) SensorComTxUART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* SensorComTxUART_TXCLKGEN_DP */

#endif /* End SensorComTxUART_TX_ENABLED */

#if(SensorComTxUART_HD_ENABLED)

    #define SensorComTxUART_TXDATA_REG             (* (reg8 *) SensorComTxUART_BUART_sRX_RxShifter_u0__F1_REG )
    #define SensorComTxUART_TXDATA_PTR             (  (reg8 *) SensorComTxUART_BUART_sRX_RxShifter_u0__F1_REG )
    #define SensorComTxUART_TXDATA_AUX_CTL_REG     (* (reg8 *) SensorComTxUART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define SensorComTxUART_TXDATA_AUX_CTL_PTR     (  (reg8 *) SensorComTxUART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define SensorComTxUART_TXSTATUS_REG           (* (reg8 *) SensorComTxUART_BUART_sRX_RxSts__STATUS_REG )
    #define SensorComTxUART_TXSTATUS_PTR           (  (reg8 *) SensorComTxUART_BUART_sRX_RxSts__STATUS_REG )
    #define SensorComTxUART_TXSTATUS_MASK_REG      (* (reg8 *) SensorComTxUART_BUART_sRX_RxSts__MASK_REG )
    #define SensorComTxUART_TXSTATUS_MASK_PTR      (  (reg8 *) SensorComTxUART_BUART_sRX_RxSts__MASK_REG )
    #define SensorComTxUART_TXSTATUS_ACTL_REG      (* (reg8 *) SensorComTxUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define SensorComTxUART_TXSTATUS_ACTL_PTR      (  (reg8 *) SensorComTxUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End SensorComTxUART_HD_ENABLED */

#if( (SensorComTxUART_RX_ENABLED) || (SensorComTxUART_HD_ENABLED) )
    #define SensorComTxUART_RXDATA_REG             (* (reg8 *) SensorComTxUART_BUART_sRX_RxShifter_u0__F0_REG )
    #define SensorComTxUART_RXDATA_PTR             (  (reg8 *) SensorComTxUART_BUART_sRX_RxShifter_u0__F0_REG )
    #define SensorComTxUART_RXADDRESS1_REG         (* (reg8 *) SensorComTxUART_BUART_sRX_RxShifter_u0__D0_REG )
    #define SensorComTxUART_RXADDRESS1_PTR         (  (reg8 *) SensorComTxUART_BUART_sRX_RxShifter_u0__D0_REG )
    #define SensorComTxUART_RXADDRESS2_REG         (* (reg8 *) SensorComTxUART_BUART_sRX_RxShifter_u0__D1_REG )
    #define SensorComTxUART_RXADDRESS2_PTR         (  (reg8 *) SensorComTxUART_BUART_sRX_RxShifter_u0__D1_REG )
    #define SensorComTxUART_RXDATA_AUX_CTL_REG     (* (reg8 *) SensorComTxUART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define SensorComTxUART_RXBITCTR_PERIOD_REG    (* (reg8 *) SensorComTxUART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define SensorComTxUART_RXBITCTR_PERIOD_PTR    (  (reg8 *) SensorComTxUART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define SensorComTxUART_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) SensorComTxUART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define SensorComTxUART_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) SensorComTxUART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define SensorComTxUART_RXBITCTR_COUNTER_REG   (* (reg8 *) SensorComTxUART_BUART_sRX_RxBitCounter__COUNT_REG )
    #define SensorComTxUART_RXBITCTR_COUNTER_PTR   (  (reg8 *) SensorComTxUART_BUART_sRX_RxBitCounter__COUNT_REG )

    #define SensorComTxUART_RXSTATUS_REG           (* (reg8 *) SensorComTxUART_BUART_sRX_RxSts__STATUS_REG )
    #define SensorComTxUART_RXSTATUS_PTR           (  (reg8 *) SensorComTxUART_BUART_sRX_RxSts__STATUS_REG )
    #define SensorComTxUART_RXSTATUS_MASK_REG      (* (reg8 *) SensorComTxUART_BUART_sRX_RxSts__MASK_REG )
    #define SensorComTxUART_RXSTATUS_MASK_PTR      (  (reg8 *) SensorComTxUART_BUART_sRX_RxSts__MASK_REG )
    #define SensorComTxUART_RXSTATUS_ACTL_REG      (* (reg8 *) SensorComTxUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define SensorComTxUART_RXSTATUS_ACTL_PTR      (  (reg8 *) SensorComTxUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (SensorComTxUART_RX_ENABLED) || (SensorComTxUART_HD_ENABLED) */

#if(SensorComTxUART_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define SensorComTxUART_INTCLOCK_CLKEN_REG     (* (reg8 *) SensorComTxUART_IntClock__PM_ACT_CFG)
    #define SensorComTxUART_INTCLOCK_CLKEN_PTR     (  (reg8 *) SensorComTxUART_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define SensorComTxUART_INTCLOCK_CLKEN_MASK    SensorComTxUART_IntClock__PM_ACT_MSK
#endif /* End SensorComTxUART_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(SensorComTxUART_TX_ENABLED)
    #define SensorComTxUART_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End SensorComTxUART_TX_ENABLED */

#if(SensorComTxUART_HD_ENABLED)
    #define SensorComTxUART_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End SensorComTxUART_HD_ENABLED */

#if( (SensorComTxUART_RX_ENABLED) || (SensorComTxUART_HD_ENABLED) )
    #define SensorComTxUART_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (SensorComTxUART_RX_ENABLED) || (SensorComTxUART_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define SensorComTxUART_WAIT_1_MS      SensorComTxUART_BL_CHK_DELAY_MS   

#define SensorComTxUART_TXBUFFERSIZE   SensorComTxUART_TX_BUFFER_SIZE
#define SensorComTxUART_RXBUFFERSIZE   SensorComTxUART_RX_BUFFER_SIZE

#if (SensorComTxUART_RXHW_ADDRESS_ENABLED)
    #define SensorComTxUART_RXADDRESSMODE  SensorComTxUART_RX_ADDRESS_MODE
    #define SensorComTxUART_RXHWADDRESS1   SensorComTxUART_RX_HW_ADDRESS1
    #define SensorComTxUART_RXHWADDRESS2   SensorComTxUART_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define SensorComTxUART_RXAddressMode  SensorComTxUART_RXADDRESSMODE
#endif /* (SensorComTxUART_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define SensorComTxUART_initvar                    SensorComTxUART_initVar

#define SensorComTxUART_RX_Enabled                 SensorComTxUART_RX_ENABLED
#define SensorComTxUART_TX_Enabled                 SensorComTxUART_TX_ENABLED
#define SensorComTxUART_HD_Enabled                 SensorComTxUART_HD_ENABLED
#define SensorComTxUART_RX_IntInterruptEnabled     SensorComTxUART_RX_INTERRUPT_ENABLED
#define SensorComTxUART_TX_IntInterruptEnabled     SensorComTxUART_TX_INTERRUPT_ENABLED
#define SensorComTxUART_InternalClockUsed          SensorComTxUART_INTERNAL_CLOCK_USED
#define SensorComTxUART_RXHW_Address_Enabled       SensorComTxUART_RXHW_ADDRESS_ENABLED
#define SensorComTxUART_OverSampleCount            SensorComTxUART_OVER_SAMPLE_COUNT
#define SensorComTxUART_ParityType                 SensorComTxUART_PARITY_TYPE

#if( SensorComTxUART_TX_ENABLED && (SensorComTxUART_TXBUFFERSIZE > SensorComTxUART_FIFO_LENGTH))
    #define SensorComTxUART_TXBUFFER               SensorComTxUART_txBuffer
    #define SensorComTxUART_TXBUFFERREAD           SensorComTxUART_txBufferRead
    #define SensorComTxUART_TXBUFFERWRITE          SensorComTxUART_txBufferWrite
#endif /* End SensorComTxUART_TX_ENABLED */
#if( ( SensorComTxUART_RX_ENABLED || SensorComTxUART_HD_ENABLED ) && \
     (SensorComTxUART_RXBUFFERSIZE > SensorComTxUART_FIFO_LENGTH) )
    #define SensorComTxUART_RXBUFFER               SensorComTxUART_rxBuffer
    #define SensorComTxUART_RXBUFFERREAD           SensorComTxUART_rxBufferRead
    #define SensorComTxUART_RXBUFFERWRITE          SensorComTxUART_rxBufferWrite
    #define SensorComTxUART_RXBUFFERLOOPDETECT     SensorComTxUART_rxBufferLoopDetect
    #define SensorComTxUART_RXBUFFER_OVERFLOW      SensorComTxUART_rxBufferOverflow
#endif /* End SensorComTxUART_RX_ENABLED */

#ifdef SensorComTxUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define SensorComTxUART_CONTROL                SensorComTxUART_CONTROL_REG
#endif /* End SensorComTxUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(SensorComTxUART_TX_ENABLED)
    #define SensorComTxUART_TXDATA                 SensorComTxUART_TXDATA_REG
    #define SensorComTxUART_TXSTATUS               SensorComTxUART_TXSTATUS_REG
    #define SensorComTxUART_TXSTATUS_MASK          SensorComTxUART_TXSTATUS_MASK_REG
    #define SensorComTxUART_TXSTATUS_ACTL          SensorComTxUART_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(SensorComTxUART_TXCLKGEN_DP)
        #define SensorComTxUART_TXBITCLKGEN_CTR        SensorComTxUART_TXBITCLKGEN_CTR_REG
        #define SensorComTxUART_TXBITCLKTX_COMPLETE    SensorComTxUART_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define SensorComTxUART_TXBITCTR_PERIOD        SensorComTxUART_TXBITCTR_PERIOD_REG
        #define SensorComTxUART_TXBITCTR_CONTROL       SensorComTxUART_TXBITCTR_CONTROL_REG
        #define SensorComTxUART_TXBITCTR_COUNTER       SensorComTxUART_TXBITCTR_COUNTER_REG
    #endif /* SensorComTxUART_TXCLKGEN_DP */
#endif /* End SensorComTxUART_TX_ENABLED */

#if(SensorComTxUART_HD_ENABLED)
    #define SensorComTxUART_TXDATA                 SensorComTxUART_TXDATA_REG
    #define SensorComTxUART_TXSTATUS               SensorComTxUART_TXSTATUS_REG
    #define SensorComTxUART_TXSTATUS_MASK          SensorComTxUART_TXSTATUS_MASK_REG
    #define SensorComTxUART_TXSTATUS_ACTL          SensorComTxUART_TXSTATUS_ACTL_REG
#endif /* End SensorComTxUART_HD_ENABLED */

#if( (SensorComTxUART_RX_ENABLED) || (SensorComTxUART_HD_ENABLED) )
    #define SensorComTxUART_RXDATA                 SensorComTxUART_RXDATA_REG
    #define SensorComTxUART_RXADDRESS1             SensorComTxUART_RXADDRESS1_REG
    #define SensorComTxUART_RXADDRESS2             SensorComTxUART_RXADDRESS2_REG
    #define SensorComTxUART_RXBITCTR_PERIOD        SensorComTxUART_RXBITCTR_PERIOD_REG
    #define SensorComTxUART_RXBITCTR_CONTROL       SensorComTxUART_RXBITCTR_CONTROL_REG
    #define SensorComTxUART_RXBITCTR_COUNTER       SensorComTxUART_RXBITCTR_COUNTER_REG
    #define SensorComTxUART_RXSTATUS               SensorComTxUART_RXSTATUS_REG
    #define SensorComTxUART_RXSTATUS_MASK          SensorComTxUART_RXSTATUS_MASK_REG
    #define SensorComTxUART_RXSTATUS_ACTL          SensorComTxUART_RXSTATUS_ACTL_REG
#endif /* End  (SensorComTxUART_RX_ENABLED) || (SensorComTxUART_HD_ENABLED) */

#if(SensorComTxUART_INTERNAL_CLOCK_USED)
    #define SensorComTxUART_INTCLOCK_CLKEN         SensorComTxUART_INTCLOCK_CLKEN_REG
#endif /* End SensorComTxUART_INTERNAL_CLOCK_USED */

#define SensorComTxUART_WAIT_FOR_COMLETE_REINIT    SensorComTxUART_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_SensorComTxUART_H */


/* [] END OF FILE */
