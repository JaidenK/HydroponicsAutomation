/*******************************************************************************
* File Name: SensorDataCom.h
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


#if !defined(CY_UART_SensorDataCom_H)
#define CY_UART_SensorDataCom_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define SensorDataCom_RX_ENABLED                     (0u)
#define SensorDataCom_TX_ENABLED                     (1u)
#define SensorDataCom_HD_ENABLED                     (0u)
#define SensorDataCom_RX_INTERRUPT_ENABLED           (0u)
#define SensorDataCom_TX_INTERRUPT_ENABLED           (0u)
#define SensorDataCom_INTERNAL_CLOCK_USED            (1u)
#define SensorDataCom_RXHW_ADDRESS_ENABLED           (0u)
#define SensorDataCom_OVER_SAMPLE_COUNT              (8u)
#define SensorDataCom_PARITY_TYPE                    (0u)
#define SensorDataCom_PARITY_TYPE_SW                 (0u)
#define SensorDataCom_BREAK_DETECT                   (0u)
#define SensorDataCom_BREAK_BITS_TX                  (13u)
#define SensorDataCom_BREAK_BITS_RX                  (13u)
#define SensorDataCom_TXCLKGEN_DP                    (1u)
#define SensorDataCom_USE23POLLING                   (1u)
#define SensorDataCom_FLOW_CONTROL                   (0u)
#define SensorDataCom_CLK_FREQ                       (0u)
#define SensorDataCom_TX_BUFFER_SIZE                 (4u)
#define SensorDataCom_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(SensorDataCom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define SensorDataCom_CONTROL_REG_REMOVED            (0u)
#else
    #define SensorDataCom_CONTROL_REG_REMOVED            (1u)
#endif /* End SensorDataCom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct SensorDataCom_backupStruct_
{
    uint8 enableState;

    #if(SensorDataCom_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End SensorDataCom_CONTROL_REG_REMOVED */

} SensorDataCom_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void SensorDataCom_Start(void) ;
void SensorDataCom_Stop(void) ;
uint8 SensorDataCom_ReadControlRegister(void) ;
void SensorDataCom_WriteControlRegister(uint8 control) ;

void SensorDataCom_Init(void) ;
void SensorDataCom_Enable(void) ;
void SensorDataCom_SaveConfig(void) ;
void SensorDataCom_RestoreConfig(void) ;
void SensorDataCom_Sleep(void) ;
void SensorDataCom_Wakeup(void) ;

/* Only if RX is enabled */
#if( (SensorDataCom_RX_ENABLED) || (SensorDataCom_HD_ENABLED) )

    #if (SensorDataCom_RX_INTERRUPT_ENABLED)
        #define SensorDataCom_EnableRxInt()  CyIntEnable (SensorDataCom_RX_VECT_NUM)
        #define SensorDataCom_DisableRxInt() CyIntDisable(SensorDataCom_RX_VECT_NUM)
        CY_ISR_PROTO(SensorDataCom_RXISR);
    #endif /* SensorDataCom_RX_INTERRUPT_ENABLED */

    void SensorDataCom_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void SensorDataCom_SetRxAddress1(uint8 address) ;
    void SensorDataCom_SetRxAddress2(uint8 address) ;

    void  SensorDataCom_SetRxInterruptMode(uint8 intSrc) ;
    uint8 SensorDataCom_ReadRxData(void) ;
    uint8 SensorDataCom_ReadRxStatus(void) ;
    uint8 SensorDataCom_GetChar(void) ;
    uint16 SensorDataCom_GetByte(void) ;
    uint8 SensorDataCom_GetRxBufferSize(void)
                                                            ;
    void SensorDataCom_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define SensorDataCom_GetRxInterruptSource   SensorDataCom_ReadRxStatus

#endif /* End (SensorDataCom_RX_ENABLED) || (SensorDataCom_HD_ENABLED) */

/* Only if TX is enabled */
#if(SensorDataCom_TX_ENABLED || SensorDataCom_HD_ENABLED)

    #if(SensorDataCom_TX_INTERRUPT_ENABLED)
        #define SensorDataCom_EnableTxInt()  CyIntEnable (SensorDataCom_TX_VECT_NUM)
        #define SensorDataCom_DisableTxInt() CyIntDisable(SensorDataCom_TX_VECT_NUM)
        #define SensorDataCom_SetPendingTxInt() CyIntSetPending(SensorDataCom_TX_VECT_NUM)
        #define SensorDataCom_ClearPendingTxInt() CyIntClearPending(SensorDataCom_TX_VECT_NUM)
        CY_ISR_PROTO(SensorDataCom_TXISR);
    #endif /* SensorDataCom_TX_INTERRUPT_ENABLED */

    void SensorDataCom_SetTxInterruptMode(uint8 intSrc) ;
    void SensorDataCom_WriteTxData(uint8 txDataByte) ;
    uint8 SensorDataCom_ReadTxStatus(void) ;
    void SensorDataCom_PutChar(uint8 txDataByte) ;
    void SensorDataCom_PutString(const char8 string[]) ;
    void SensorDataCom_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void SensorDataCom_PutCRLF(uint8 txDataByte) ;
    void SensorDataCom_ClearTxBuffer(void) ;
    void SensorDataCom_SetTxAddressMode(uint8 addressMode) ;
    void SensorDataCom_SendBreak(uint8 retMode) ;
    uint8 SensorDataCom_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define SensorDataCom_PutStringConst         SensorDataCom_PutString
    #define SensorDataCom_PutArrayConst          SensorDataCom_PutArray
    #define SensorDataCom_GetTxInterruptSource   SensorDataCom_ReadTxStatus

#endif /* End SensorDataCom_TX_ENABLED || SensorDataCom_HD_ENABLED */

#if(SensorDataCom_HD_ENABLED)
    void SensorDataCom_LoadRxConfig(void) ;
    void SensorDataCom_LoadTxConfig(void) ;
#endif /* End SensorDataCom_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SensorDataCom) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    SensorDataCom_CyBtldrCommStart(void) CYSMALL ;
    void    SensorDataCom_CyBtldrCommStop(void) CYSMALL ;
    void    SensorDataCom_CyBtldrCommReset(void) CYSMALL ;
    cystatus SensorDataCom_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus SensorDataCom_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SensorDataCom)
        #define CyBtldrCommStart    SensorDataCom_CyBtldrCommStart
        #define CyBtldrCommStop     SensorDataCom_CyBtldrCommStop
        #define CyBtldrCommReset    SensorDataCom_CyBtldrCommReset
        #define CyBtldrCommWrite    SensorDataCom_CyBtldrCommWrite
        #define CyBtldrCommRead     SensorDataCom_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SensorDataCom) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define SensorDataCom_BYTE2BYTE_TIME_OUT (25u)
    #define SensorDataCom_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define SensorDataCom_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define SensorDataCom_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define SensorDataCom_SET_SPACE      (0x00u)
#define SensorDataCom_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (SensorDataCom_TX_ENABLED) || (SensorDataCom_HD_ENABLED) )
    #if(SensorDataCom_TX_INTERRUPT_ENABLED)
        #define SensorDataCom_TX_VECT_NUM            (uint8)SensorDataCom_TXInternalInterrupt__INTC_NUMBER
        #define SensorDataCom_TX_PRIOR_NUM           (uint8)SensorDataCom_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* SensorDataCom_TX_INTERRUPT_ENABLED */

    #define SensorDataCom_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define SensorDataCom_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define SensorDataCom_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(SensorDataCom_TX_ENABLED)
        #define SensorDataCom_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (SensorDataCom_HD_ENABLED) */
        #define SensorDataCom_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (SensorDataCom_TX_ENABLED) */

    #define SensorDataCom_TX_STS_COMPLETE            (uint8)(0x01u << SensorDataCom_TX_STS_COMPLETE_SHIFT)
    #define SensorDataCom_TX_STS_FIFO_EMPTY          (uint8)(0x01u << SensorDataCom_TX_STS_FIFO_EMPTY_SHIFT)
    #define SensorDataCom_TX_STS_FIFO_FULL           (uint8)(0x01u << SensorDataCom_TX_STS_FIFO_FULL_SHIFT)
    #define SensorDataCom_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << SensorDataCom_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (SensorDataCom_TX_ENABLED) || (SensorDataCom_HD_ENABLED)*/

#if( (SensorDataCom_RX_ENABLED) || (SensorDataCom_HD_ENABLED) )
    #if(SensorDataCom_RX_INTERRUPT_ENABLED)
        #define SensorDataCom_RX_VECT_NUM            (uint8)SensorDataCom_RXInternalInterrupt__INTC_NUMBER
        #define SensorDataCom_RX_PRIOR_NUM           (uint8)SensorDataCom_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* SensorDataCom_RX_INTERRUPT_ENABLED */
    #define SensorDataCom_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define SensorDataCom_RX_STS_BREAK_SHIFT             (0x01u)
    #define SensorDataCom_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define SensorDataCom_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define SensorDataCom_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define SensorDataCom_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define SensorDataCom_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define SensorDataCom_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define SensorDataCom_RX_STS_MRKSPC           (uint8)(0x01u << SensorDataCom_RX_STS_MRKSPC_SHIFT)
    #define SensorDataCom_RX_STS_BREAK            (uint8)(0x01u << SensorDataCom_RX_STS_BREAK_SHIFT)
    #define SensorDataCom_RX_STS_PAR_ERROR        (uint8)(0x01u << SensorDataCom_RX_STS_PAR_ERROR_SHIFT)
    #define SensorDataCom_RX_STS_STOP_ERROR       (uint8)(0x01u << SensorDataCom_RX_STS_STOP_ERROR_SHIFT)
    #define SensorDataCom_RX_STS_OVERRUN          (uint8)(0x01u << SensorDataCom_RX_STS_OVERRUN_SHIFT)
    #define SensorDataCom_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << SensorDataCom_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define SensorDataCom_RX_STS_ADDR_MATCH       (uint8)(0x01u << SensorDataCom_RX_STS_ADDR_MATCH_SHIFT)
    #define SensorDataCom_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << SensorDataCom_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define SensorDataCom_RX_HW_MASK                     (0x7Fu)
#endif /* End (SensorDataCom_RX_ENABLED) || (SensorDataCom_HD_ENABLED) */

/* Control Register definitions */
#define SensorDataCom_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define SensorDataCom_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define SensorDataCom_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define SensorDataCom_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define SensorDataCom_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define SensorDataCom_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define SensorDataCom_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define SensorDataCom_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define SensorDataCom_CTRL_HD_SEND               (uint8)(0x01u << SensorDataCom_CTRL_HD_SEND_SHIFT)
#define SensorDataCom_CTRL_HD_SEND_BREAK         (uint8)(0x01u << SensorDataCom_CTRL_HD_SEND_BREAK_SHIFT)
#define SensorDataCom_CTRL_MARK                  (uint8)(0x01u << SensorDataCom_CTRL_MARK_SHIFT)
#define SensorDataCom_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << SensorDataCom_CTRL_PARITY_TYPE0_SHIFT)
#define SensorDataCom_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << SensorDataCom_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define SensorDataCom_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define SensorDataCom_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define SensorDataCom_SEND_BREAK                         (0x00u)
#define SensorDataCom_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define SensorDataCom_REINIT                             (0x02u)
#define SensorDataCom_SEND_WAIT_REINIT                   (0x03u)

#define SensorDataCom_OVER_SAMPLE_8                      (8u)
#define SensorDataCom_OVER_SAMPLE_16                     (16u)

#define SensorDataCom_BIT_CENTER                         (SensorDataCom_OVER_SAMPLE_COUNT - 2u)

#define SensorDataCom_FIFO_LENGTH                        (4u)
#define SensorDataCom_NUMBER_OF_START_BIT                (1u)
#define SensorDataCom_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define SensorDataCom_TXBITCTR_BREAKBITS8X   ((SensorDataCom_BREAK_BITS_TX * SensorDataCom_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define SensorDataCom_TXBITCTR_BREAKBITS ((SensorDataCom_BREAK_BITS_TX * SensorDataCom_OVER_SAMPLE_COUNT) - 1u)

#define SensorDataCom_HALF_BIT_COUNT   \
                            (((SensorDataCom_OVER_SAMPLE_COUNT / 2u) + (SensorDataCom_USE23POLLING * 1u)) - 2u)
#if (SensorDataCom_OVER_SAMPLE_COUNT == SensorDataCom_OVER_SAMPLE_8)
    #define SensorDataCom_HD_TXBITCTR_INIT   (((SensorDataCom_BREAK_BITS_TX + \
                            SensorDataCom_NUMBER_OF_START_BIT) * SensorDataCom_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define SensorDataCom_RXBITCTR_INIT  ((((SensorDataCom_BREAK_BITS_RX + SensorDataCom_NUMBER_OF_START_BIT) \
                            * SensorDataCom_OVER_SAMPLE_COUNT) + SensorDataCom_HALF_BIT_COUNT) - 1u)

#else /* SensorDataCom_OVER_SAMPLE_COUNT == SensorDataCom_OVER_SAMPLE_16 */
    #define SensorDataCom_HD_TXBITCTR_INIT   ((8u * SensorDataCom_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define SensorDataCom_RXBITCTR_INIT      (((7u * SensorDataCom_OVER_SAMPLE_COUNT) - 1u) + \
                                                      SensorDataCom_HALF_BIT_COUNT)
#endif /* End SensorDataCom_OVER_SAMPLE_COUNT */

#define SensorDataCom_HD_RXBITCTR_INIT                   SensorDataCom_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 SensorDataCom_initVar;
#if (SensorDataCom_TX_INTERRUPT_ENABLED && SensorDataCom_TX_ENABLED)
    extern volatile uint8 SensorDataCom_txBuffer[SensorDataCom_TX_BUFFER_SIZE];
    extern volatile uint8 SensorDataCom_txBufferRead;
    extern uint8 SensorDataCom_txBufferWrite;
#endif /* (SensorDataCom_TX_INTERRUPT_ENABLED && SensorDataCom_TX_ENABLED) */
#if (SensorDataCom_RX_INTERRUPT_ENABLED && (SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED))
    extern uint8 SensorDataCom_errorStatus;
    extern volatile uint8 SensorDataCom_rxBuffer[SensorDataCom_RX_BUFFER_SIZE];
    extern volatile uint8 SensorDataCom_rxBufferRead;
    extern volatile uint8 SensorDataCom_rxBufferWrite;
    extern volatile uint8 SensorDataCom_rxBufferLoopDetect;
    extern volatile uint8 SensorDataCom_rxBufferOverflow;
    #if (SensorDataCom_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 SensorDataCom_rxAddressMode;
        extern volatile uint8 SensorDataCom_rxAddressDetected;
    #endif /* (SensorDataCom_RXHW_ADDRESS_ENABLED) */
#endif /* (SensorDataCom_RX_INTERRUPT_ENABLED && (SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define SensorDataCom__B_UART__AM_SW_BYTE_BYTE 1
#define SensorDataCom__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define SensorDataCom__B_UART__AM_HW_BYTE_BY_BYTE 3
#define SensorDataCom__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define SensorDataCom__B_UART__AM_NONE 0

#define SensorDataCom__B_UART__NONE_REVB 0
#define SensorDataCom__B_UART__EVEN_REVB 1
#define SensorDataCom__B_UART__ODD_REVB 2
#define SensorDataCom__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define SensorDataCom_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define SensorDataCom_NUMBER_OF_STOP_BITS    (1u)

#if (SensorDataCom_RXHW_ADDRESS_ENABLED)
    #define SensorDataCom_RX_ADDRESS_MODE    (0u)
    #define SensorDataCom_RX_HW_ADDRESS1     (0u)
    #define SensorDataCom_RX_HW_ADDRESS2     (0u)
#endif /* (SensorDataCom_RXHW_ADDRESS_ENABLED) */

#define SensorDataCom_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((0 << SensorDataCom_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << SensorDataCom_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << SensorDataCom_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << SensorDataCom_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << SensorDataCom_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << SensorDataCom_RX_STS_BREAK_SHIFT) \
                                        | (0 << SensorDataCom_RX_STS_OVERRUN_SHIFT))

#define SensorDataCom_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << SensorDataCom_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << SensorDataCom_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << SensorDataCom_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << SensorDataCom_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef SensorDataCom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define SensorDataCom_CONTROL_REG \
                            (* (reg8 *) SensorDataCom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define SensorDataCom_CONTROL_PTR \
                            (  (reg8 *) SensorDataCom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End SensorDataCom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(SensorDataCom_TX_ENABLED)
    #define SensorDataCom_TXDATA_REG          (* (reg8 *) SensorDataCom_BUART_sTX_TxShifter_u0__F0_REG)
    #define SensorDataCom_TXDATA_PTR          (  (reg8 *) SensorDataCom_BUART_sTX_TxShifter_u0__F0_REG)
    #define SensorDataCom_TXDATA_AUX_CTL_REG  (* (reg8 *) SensorDataCom_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define SensorDataCom_TXDATA_AUX_CTL_PTR  (  (reg8 *) SensorDataCom_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define SensorDataCom_TXSTATUS_REG        (* (reg8 *) SensorDataCom_BUART_sTX_TxSts__STATUS_REG)
    #define SensorDataCom_TXSTATUS_PTR        (  (reg8 *) SensorDataCom_BUART_sTX_TxSts__STATUS_REG)
    #define SensorDataCom_TXSTATUS_MASK_REG   (* (reg8 *) SensorDataCom_BUART_sTX_TxSts__MASK_REG)
    #define SensorDataCom_TXSTATUS_MASK_PTR   (  (reg8 *) SensorDataCom_BUART_sTX_TxSts__MASK_REG)
    #define SensorDataCom_TXSTATUS_ACTL_REG   (* (reg8 *) SensorDataCom_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define SensorDataCom_TXSTATUS_ACTL_PTR   (  (reg8 *) SensorDataCom_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(SensorDataCom_TXCLKGEN_DP)
        #define SensorDataCom_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) SensorDataCom_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define SensorDataCom_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) SensorDataCom_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define SensorDataCom_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) SensorDataCom_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define SensorDataCom_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) SensorDataCom_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define SensorDataCom_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) SensorDataCom_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define SensorDataCom_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) SensorDataCom_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define SensorDataCom_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) SensorDataCom_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define SensorDataCom_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) SensorDataCom_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define SensorDataCom_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) SensorDataCom_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define SensorDataCom_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) SensorDataCom_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* SensorDataCom_TXCLKGEN_DP */

#endif /* End SensorDataCom_TX_ENABLED */

#if(SensorDataCom_HD_ENABLED)

    #define SensorDataCom_TXDATA_REG             (* (reg8 *) SensorDataCom_BUART_sRX_RxShifter_u0__F1_REG )
    #define SensorDataCom_TXDATA_PTR             (  (reg8 *) SensorDataCom_BUART_sRX_RxShifter_u0__F1_REG )
    #define SensorDataCom_TXDATA_AUX_CTL_REG     (* (reg8 *) SensorDataCom_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define SensorDataCom_TXDATA_AUX_CTL_PTR     (  (reg8 *) SensorDataCom_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define SensorDataCom_TXSTATUS_REG           (* (reg8 *) SensorDataCom_BUART_sRX_RxSts__STATUS_REG )
    #define SensorDataCom_TXSTATUS_PTR           (  (reg8 *) SensorDataCom_BUART_sRX_RxSts__STATUS_REG )
    #define SensorDataCom_TXSTATUS_MASK_REG      (* (reg8 *) SensorDataCom_BUART_sRX_RxSts__MASK_REG )
    #define SensorDataCom_TXSTATUS_MASK_PTR      (  (reg8 *) SensorDataCom_BUART_sRX_RxSts__MASK_REG )
    #define SensorDataCom_TXSTATUS_ACTL_REG      (* (reg8 *) SensorDataCom_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define SensorDataCom_TXSTATUS_ACTL_PTR      (  (reg8 *) SensorDataCom_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End SensorDataCom_HD_ENABLED */

#if( (SensorDataCom_RX_ENABLED) || (SensorDataCom_HD_ENABLED) )
    #define SensorDataCom_RXDATA_REG             (* (reg8 *) SensorDataCom_BUART_sRX_RxShifter_u0__F0_REG )
    #define SensorDataCom_RXDATA_PTR             (  (reg8 *) SensorDataCom_BUART_sRX_RxShifter_u0__F0_REG )
    #define SensorDataCom_RXADDRESS1_REG         (* (reg8 *) SensorDataCom_BUART_sRX_RxShifter_u0__D0_REG )
    #define SensorDataCom_RXADDRESS1_PTR         (  (reg8 *) SensorDataCom_BUART_sRX_RxShifter_u0__D0_REG )
    #define SensorDataCom_RXADDRESS2_REG         (* (reg8 *) SensorDataCom_BUART_sRX_RxShifter_u0__D1_REG )
    #define SensorDataCom_RXADDRESS2_PTR         (  (reg8 *) SensorDataCom_BUART_sRX_RxShifter_u0__D1_REG )
    #define SensorDataCom_RXDATA_AUX_CTL_REG     (* (reg8 *) SensorDataCom_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define SensorDataCom_RXBITCTR_PERIOD_REG    (* (reg8 *) SensorDataCom_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define SensorDataCom_RXBITCTR_PERIOD_PTR    (  (reg8 *) SensorDataCom_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define SensorDataCom_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) SensorDataCom_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define SensorDataCom_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) SensorDataCom_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define SensorDataCom_RXBITCTR_COUNTER_REG   (* (reg8 *) SensorDataCom_BUART_sRX_RxBitCounter__COUNT_REG )
    #define SensorDataCom_RXBITCTR_COUNTER_PTR   (  (reg8 *) SensorDataCom_BUART_sRX_RxBitCounter__COUNT_REG )

    #define SensorDataCom_RXSTATUS_REG           (* (reg8 *) SensorDataCom_BUART_sRX_RxSts__STATUS_REG )
    #define SensorDataCom_RXSTATUS_PTR           (  (reg8 *) SensorDataCom_BUART_sRX_RxSts__STATUS_REG )
    #define SensorDataCom_RXSTATUS_MASK_REG      (* (reg8 *) SensorDataCom_BUART_sRX_RxSts__MASK_REG )
    #define SensorDataCom_RXSTATUS_MASK_PTR      (  (reg8 *) SensorDataCom_BUART_sRX_RxSts__MASK_REG )
    #define SensorDataCom_RXSTATUS_ACTL_REG      (* (reg8 *) SensorDataCom_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define SensorDataCom_RXSTATUS_ACTL_PTR      (  (reg8 *) SensorDataCom_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (SensorDataCom_RX_ENABLED) || (SensorDataCom_HD_ENABLED) */

#if(SensorDataCom_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define SensorDataCom_INTCLOCK_CLKEN_REG     (* (reg8 *) SensorDataCom_IntClock__PM_ACT_CFG)
    #define SensorDataCom_INTCLOCK_CLKEN_PTR     (  (reg8 *) SensorDataCom_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define SensorDataCom_INTCLOCK_CLKEN_MASK    SensorDataCom_IntClock__PM_ACT_MSK
#endif /* End SensorDataCom_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(SensorDataCom_TX_ENABLED)
    #define SensorDataCom_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End SensorDataCom_TX_ENABLED */

#if(SensorDataCom_HD_ENABLED)
    #define SensorDataCom_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End SensorDataCom_HD_ENABLED */

#if( (SensorDataCom_RX_ENABLED) || (SensorDataCom_HD_ENABLED) )
    #define SensorDataCom_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (SensorDataCom_RX_ENABLED) || (SensorDataCom_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define SensorDataCom_WAIT_1_MS      SensorDataCom_BL_CHK_DELAY_MS   

#define SensorDataCom_TXBUFFERSIZE   SensorDataCom_TX_BUFFER_SIZE
#define SensorDataCom_RXBUFFERSIZE   SensorDataCom_RX_BUFFER_SIZE

#if (SensorDataCom_RXHW_ADDRESS_ENABLED)
    #define SensorDataCom_RXADDRESSMODE  SensorDataCom_RX_ADDRESS_MODE
    #define SensorDataCom_RXHWADDRESS1   SensorDataCom_RX_HW_ADDRESS1
    #define SensorDataCom_RXHWADDRESS2   SensorDataCom_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define SensorDataCom_RXAddressMode  SensorDataCom_RXADDRESSMODE
#endif /* (SensorDataCom_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define SensorDataCom_initvar                    SensorDataCom_initVar

#define SensorDataCom_RX_Enabled                 SensorDataCom_RX_ENABLED
#define SensorDataCom_TX_Enabled                 SensorDataCom_TX_ENABLED
#define SensorDataCom_HD_Enabled                 SensorDataCom_HD_ENABLED
#define SensorDataCom_RX_IntInterruptEnabled     SensorDataCom_RX_INTERRUPT_ENABLED
#define SensorDataCom_TX_IntInterruptEnabled     SensorDataCom_TX_INTERRUPT_ENABLED
#define SensorDataCom_InternalClockUsed          SensorDataCom_INTERNAL_CLOCK_USED
#define SensorDataCom_RXHW_Address_Enabled       SensorDataCom_RXHW_ADDRESS_ENABLED
#define SensorDataCom_OverSampleCount            SensorDataCom_OVER_SAMPLE_COUNT
#define SensorDataCom_ParityType                 SensorDataCom_PARITY_TYPE

#if( SensorDataCom_TX_ENABLED && (SensorDataCom_TXBUFFERSIZE > SensorDataCom_FIFO_LENGTH))
    #define SensorDataCom_TXBUFFER               SensorDataCom_txBuffer
    #define SensorDataCom_TXBUFFERREAD           SensorDataCom_txBufferRead
    #define SensorDataCom_TXBUFFERWRITE          SensorDataCom_txBufferWrite
#endif /* End SensorDataCom_TX_ENABLED */
#if( ( SensorDataCom_RX_ENABLED || SensorDataCom_HD_ENABLED ) && \
     (SensorDataCom_RXBUFFERSIZE > SensorDataCom_FIFO_LENGTH) )
    #define SensorDataCom_RXBUFFER               SensorDataCom_rxBuffer
    #define SensorDataCom_RXBUFFERREAD           SensorDataCom_rxBufferRead
    #define SensorDataCom_RXBUFFERWRITE          SensorDataCom_rxBufferWrite
    #define SensorDataCom_RXBUFFERLOOPDETECT     SensorDataCom_rxBufferLoopDetect
    #define SensorDataCom_RXBUFFER_OVERFLOW      SensorDataCom_rxBufferOverflow
#endif /* End SensorDataCom_RX_ENABLED */

#ifdef SensorDataCom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define SensorDataCom_CONTROL                SensorDataCom_CONTROL_REG
#endif /* End SensorDataCom_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(SensorDataCom_TX_ENABLED)
    #define SensorDataCom_TXDATA                 SensorDataCom_TXDATA_REG
    #define SensorDataCom_TXSTATUS               SensorDataCom_TXSTATUS_REG
    #define SensorDataCom_TXSTATUS_MASK          SensorDataCom_TXSTATUS_MASK_REG
    #define SensorDataCom_TXSTATUS_ACTL          SensorDataCom_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(SensorDataCom_TXCLKGEN_DP)
        #define SensorDataCom_TXBITCLKGEN_CTR        SensorDataCom_TXBITCLKGEN_CTR_REG
        #define SensorDataCom_TXBITCLKTX_COMPLETE    SensorDataCom_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define SensorDataCom_TXBITCTR_PERIOD        SensorDataCom_TXBITCTR_PERIOD_REG
        #define SensorDataCom_TXBITCTR_CONTROL       SensorDataCom_TXBITCTR_CONTROL_REG
        #define SensorDataCom_TXBITCTR_COUNTER       SensorDataCom_TXBITCTR_COUNTER_REG
    #endif /* SensorDataCom_TXCLKGEN_DP */
#endif /* End SensorDataCom_TX_ENABLED */

#if(SensorDataCom_HD_ENABLED)
    #define SensorDataCom_TXDATA                 SensorDataCom_TXDATA_REG
    #define SensorDataCom_TXSTATUS               SensorDataCom_TXSTATUS_REG
    #define SensorDataCom_TXSTATUS_MASK          SensorDataCom_TXSTATUS_MASK_REG
    #define SensorDataCom_TXSTATUS_ACTL          SensorDataCom_TXSTATUS_ACTL_REG
#endif /* End SensorDataCom_HD_ENABLED */

#if( (SensorDataCom_RX_ENABLED) || (SensorDataCom_HD_ENABLED) )
    #define SensorDataCom_RXDATA                 SensorDataCom_RXDATA_REG
    #define SensorDataCom_RXADDRESS1             SensorDataCom_RXADDRESS1_REG
    #define SensorDataCom_RXADDRESS2             SensorDataCom_RXADDRESS2_REG
    #define SensorDataCom_RXBITCTR_PERIOD        SensorDataCom_RXBITCTR_PERIOD_REG
    #define SensorDataCom_RXBITCTR_CONTROL       SensorDataCom_RXBITCTR_CONTROL_REG
    #define SensorDataCom_RXBITCTR_COUNTER       SensorDataCom_RXBITCTR_COUNTER_REG
    #define SensorDataCom_RXSTATUS               SensorDataCom_RXSTATUS_REG
    #define SensorDataCom_RXSTATUS_MASK          SensorDataCom_RXSTATUS_MASK_REG
    #define SensorDataCom_RXSTATUS_ACTL          SensorDataCom_RXSTATUS_ACTL_REG
#endif /* End  (SensorDataCom_RX_ENABLED) || (SensorDataCom_HD_ENABLED) */

#if(SensorDataCom_INTERNAL_CLOCK_USED)
    #define SensorDataCom_INTCLOCK_CLKEN         SensorDataCom_INTCLOCK_CLKEN_REG
#endif /* End SensorDataCom_INTERNAL_CLOCK_USED */

#define SensorDataCom_WAIT_FOR_COMLETE_REINIT    SensorDataCom_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_SensorDataCom_H */


/* [] END OF FILE */
