/*******************************************************************************
* File Name: ECSenseUART.h
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


#if !defined(CY_UART_ECSenseUART_H)
#define CY_UART_ECSenseUART_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define ECSenseUART_RX_ENABLED                     (1u)
#define ECSenseUART_TX_ENABLED                     (0u)
#define ECSenseUART_HD_ENABLED                     (0u)
#define ECSenseUART_RX_INTERRUPT_ENABLED           (0u)
#define ECSenseUART_TX_INTERRUPT_ENABLED           (0u)
#define ECSenseUART_INTERNAL_CLOCK_USED            (1u)
#define ECSenseUART_RXHW_ADDRESS_ENABLED           (0u)
#define ECSenseUART_OVER_SAMPLE_COUNT              (8u)
#define ECSenseUART_PARITY_TYPE                    (0u)
#define ECSenseUART_PARITY_TYPE_SW                 (0u)
#define ECSenseUART_BREAK_DETECT                   (0u)
#define ECSenseUART_BREAK_BITS_TX                  (13u)
#define ECSenseUART_BREAK_BITS_RX                  (13u)
#define ECSenseUART_TXCLKGEN_DP                    (1u)
#define ECSenseUART_USE23POLLING                   (1u)
#define ECSenseUART_FLOW_CONTROL                   (0u)
#define ECSenseUART_CLK_FREQ                       (0u)
#define ECSenseUART_TX_BUFFER_SIZE                 (4u)
#define ECSenseUART_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(ECSenseUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define ECSenseUART_CONTROL_REG_REMOVED            (0u)
#else
    #define ECSenseUART_CONTROL_REG_REMOVED            (1u)
#endif /* End ECSenseUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct ECSenseUART_backupStruct_
{
    uint8 enableState;

    #if(ECSenseUART_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End ECSenseUART_CONTROL_REG_REMOVED */

} ECSenseUART_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void ECSenseUART_Start(void) ;
void ECSenseUART_Stop(void) ;
uint8 ECSenseUART_ReadControlRegister(void) ;
void ECSenseUART_WriteControlRegister(uint8 control) ;

void ECSenseUART_Init(void) ;
void ECSenseUART_Enable(void) ;
void ECSenseUART_SaveConfig(void) ;
void ECSenseUART_RestoreConfig(void) ;
void ECSenseUART_Sleep(void) ;
void ECSenseUART_Wakeup(void) ;

/* Only if RX is enabled */
#if( (ECSenseUART_RX_ENABLED) || (ECSenseUART_HD_ENABLED) )

    #if (ECSenseUART_RX_INTERRUPT_ENABLED)
        #define ECSenseUART_EnableRxInt()  CyIntEnable (ECSenseUART_RX_VECT_NUM)
        #define ECSenseUART_DisableRxInt() CyIntDisable(ECSenseUART_RX_VECT_NUM)
        CY_ISR_PROTO(ECSenseUART_RXISR);
    #endif /* ECSenseUART_RX_INTERRUPT_ENABLED */

    void ECSenseUART_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void ECSenseUART_SetRxAddress1(uint8 address) ;
    void ECSenseUART_SetRxAddress2(uint8 address) ;

    void  ECSenseUART_SetRxInterruptMode(uint8 intSrc) ;
    uint8 ECSenseUART_ReadRxData(void) ;
    uint8 ECSenseUART_ReadRxStatus(void) ;
    uint8 ECSenseUART_GetChar(void) ;
    uint16 ECSenseUART_GetByte(void) ;
    uint8 ECSenseUART_GetRxBufferSize(void)
                                                            ;
    void ECSenseUART_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define ECSenseUART_GetRxInterruptSource   ECSenseUART_ReadRxStatus

#endif /* End (ECSenseUART_RX_ENABLED) || (ECSenseUART_HD_ENABLED) */

/* Only if TX is enabled */
#if(ECSenseUART_TX_ENABLED || ECSenseUART_HD_ENABLED)

    #if(ECSenseUART_TX_INTERRUPT_ENABLED)
        #define ECSenseUART_EnableTxInt()  CyIntEnable (ECSenseUART_TX_VECT_NUM)
        #define ECSenseUART_DisableTxInt() CyIntDisable(ECSenseUART_TX_VECT_NUM)
        #define ECSenseUART_SetPendingTxInt() CyIntSetPending(ECSenseUART_TX_VECT_NUM)
        #define ECSenseUART_ClearPendingTxInt() CyIntClearPending(ECSenseUART_TX_VECT_NUM)
        CY_ISR_PROTO(ECSenseUART_TXISR);
    #endif /* ECSenseUART_TX_INTERRUPT_ENABLED */

    void ECSenseUART_SetTxInterruptMode(uint8 intSrc) ;
    void ECSenseUART_WriteTxData(uint8 txDataByte) ;
    uint8 ECSenseUART_ReadTxStatus(void) ;
    void ECSenseUART_PutChar(uint8 txDataByte) ;
    void ECSenseUART_PutString(const char8 string[]) ;
    void ECSenseUART_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void ECSenseUART_PutCRLF(uint8 txDataByte) ;
    void ECSenseUART_ClearTxBuffer(void) ;
    void ECSenseUART_SetTxAddressMode(uint8 addressMode) ;
    void ECSenseUART_SendBreak(uint8 retMode) ;
    uint8 ECSenseUART_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define ECSenseUART_PutStringConst         ECSenseUART_PutString
    #define ECSenseUART_PutArrayConst          ECSenseUART_PutArray
    #define ECSenseUART_GetTxInterruptSource   ECSenseUART_ReadTxStatus

#endif /* End ECSenseUART_TX_ENABLED || ECSenseUART_HD_ENABLED */

#if(ECSenseUART_HD_ENABLED)
    void ECSenseUART_LoadRxConfig(void) ;
    void ECSenseUART_LoadTxConfig(void) ;
#endif /* End ECSenseUART_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ECSenseUART) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    ECSenseUART_CyBtldrCommStart(void) CYSMALL ;
    void    ECSenseUART_CyBtldrCommStop(void) CYSMALL ;
    void    ECSenseUART_CyBtldrCommReset(void) CYSMALL ;
    cystatus ECSenseUART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus ECSenseUART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ECSenseUART)
        #define CyBtldrCommStart    ECSenseUART_CyBtldrCommStart
        #define CyBtldrCommStop     ECSenseUART_CyBtldrCommStop
        #define CyBtldrCommReset    ECSenseUART_CyBtldrCommReset
        #define CyBtldrCommWrite    ECSenseUART_CyBtldrCommWrite
        #define CyBtldrCommRead     ECSenseUART_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ECSenseUART) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define ECSenseUART_BYTE2BYTE_TIME_OUT (25u)
    #define ECSenseUART_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define ECSenseUART_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define ECSenseUART_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define ECSenseUART_SET_SPACE      (0x00u)
#define ECSenseUART_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (ECSenseUART_TX_ENABLED) || (ECSenseUART_HD_ENABLED) )
    #if(ECSenseUART_TX_INTERRUPT_ENABLED)
        #define ECSenseUART_TX_VECT_NUM            (uint8)ECSenseUART_TXInternalInterrupt__INTC_NUMBER
        #define ECSenseUART_TX_PRIOR_NUM           (uint8)ECSenseUART_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* ECSenseUART_TX_INTERRUPT_ENABLED */

    #define ECSenseUART_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define ECSenseUART_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define ECSenseUART_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(ECSenseUART_TX_ENABLED)
        #define ECSenseUART_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (ECSenseUART_HD_ENABLED) */
        #define ECSenseUART_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (ECSenseUART_TX_ENABLED) */

    #define ECSenseUART_TX_STS_COMPLETE            (uint8)(0x01u << ECSenseUART_TX_STS_COMPLETE_SHIFT)
    #define ECSenseUART_TX_STS_FIFO_EMPTY          (uint8)(0x01u << ECSenseUART_TX_STS_FIFO_EMPTY_SHIFT)
    #define ECSenseUART_TX_STS_FIFO_FULL           (uint8)(0x01u << ECSenseUART_TX_STS_FIFO_FULL_SHIFT)
    #define ECSenseUART_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << ECSenseUART_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (ECSenseUART_TX_ENABLED) || (ECSenseUART_HD_ENABLED)*/

#if( (ECSenseUART_RX_ENABLED) || (ECSenseUART_HD_ENABLED) )
    #if(ECSenseUART_RX_INTERRUPT_ENABLED)
        #define ECSenseUART_RX_VECT_NUM            (uint8)ECSenseUART_RXInternalInterrupt__INTC_NUMBER
        #define ECSenseUART_RX_PRIOR_NUM           (uint8)ECSenseUART_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* ECSenseUART_RX_INTERRUPT_ENABLED */
    #define ECSenseUART_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define ECSenseUART_RX_STS_BREAK_SHIFT             (0x01u)
    #define ECSenseUART_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define ECSenseUART_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define ECSenseUART_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define ECSenseUART_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define ECSenseUART_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define ECSenseUART_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define ECSenseUART_RX_STS_MRKSPC           (uint8)(0x01u << ECSenseUART_RX_STS_MRKSPC_SHIFT)
    #define ECSenseUART_RX_STS_BREAK            (uint8)(0x01u << ECSenseUART_RX_STS_BREAK_SHIFT)
    #define ECSenseUART_RX_STS_PAR_ERROR        (uint8)(0x01u << ECSenseUART_RX_STS_PAR_ERROR_SHIFT)
    #define ECSenseUART_RX_STS_STOP_ERROR       (uint8)(0x01u << ECSenseUART_RX_STS_STOP_ERROR_SHIFT)
    #define ECSenseUART_RX_STS_OVERRUN          (uint8)(0x01u << ECSenseUART_RX_STS_OVERRUN_SHIFT)
    #define ECSenseUART_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << ECSenseUART_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define ECSenseUART_RX_STS_ADDR_MATCH       (uint8)(0x01u << ECSenseUART_RX_STS_ADDR_MATCH_SHIFT)
    #define ECSenseUART_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << ECSenseUART_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define ECSenseUART_RX_HW_MASK                     (0x7Fu)
#endif /* End (ECSenseUART_RX_ENABLED) || (ECSenseUART_HD_ENABLED) */

/* Control Register definitions */
#define ECSenseUART_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define ECSenseUART_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define ECSenseUART_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define ECSenseUART_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define ECSenseUART_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define ECSenseUART_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define ECSenseUART_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define ECSenseUART_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define ECSenseUART_CTRL_HD_SEND               (uint8)(0x01u << ECSenseUART_CTRL_HD_SEND_SHIFT)
#define ECSenseUART_CTRL_HD_SEND_BREAK         (uint8)(0x01u << ECSenseUART_CTRL_HD_SEND_BREAK_SHIFT)
#define ECSenseUART_CTRL_MARK                  (uint8)(0x01u << ECSenseUART_CTRL_MARK_SHIFT)
#define ECSenseUART_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << ECSenseUART_CTRL_PARITY_TYPE0_SHIFT)
#define ECSenseUART_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << ECSenseUART_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define ECSenseUART_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define ECSenseUART_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define ECSenseUART_SEND_BREAK                         (0x00u)
#define ECSenseUART_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define ECSenseUART_REINIT                             (0x02u)
#define ECSenseUART_SEND_WAIT_REINIT                   (0x03u)

#define ECSenseUART_OVER_SAMPLE_8                      (8u)
#define ECSenseUART_OVER_SAMPLE_16                     (16u)

#define ECSenseUART_BIT_CENTER                         (ECSenseUART_OVER_SAMPLE_COUNT - 2u)

#define ECSenseUART_FIFO_LENGTH                        (4u)
#define ECSenseUART_NUMBER_OF_START_BIT                (1u)
#define ECSenseUART_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define ECSenseUART_TXBITCTR_BREAKBITS8X   ((ECSenseUART_BREAK_BITS_TX * ECSenseUART_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define ECSenseUART_TXBITCTR_BREAKBITS ((ECSenseUART_BREAK_BITS_TX * ECSenseUART_OVER_SAMPLE_COUNT) - 1u)

#define ECSenseUART_HALF_BIT_COUNT   \
                            (((ECSenseUART_OVER_SAMPLE_COUNT / 2u) + (ECSenseUART_USE23POLLING * 1u)) - 2u)
#if (ECSenseUART_OVER_SAMPLE_COUNT == ECSenseUART_OVER_SAMPLE_8)
    #define ECSenseUART_HD_TXBITCTR_INIT   (((ECSenseUART_BREAK_BITS_TX + \
                            ECSenseUART_NUMBER_OF_START_BIT) * ECSenseUART_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define ECSenseUART_RXBITCTR_INIT  ((((ECSenseUART_BREAK_BITS_RX + ECSenseUART_NUMBER_OF_START_BIT) \
                            * ECSenseUART_OVER_SAMPLE_COUNT) + ECSenseUART_HALF_BIT_COUNT) - 1u)

#else /* ECSenseUART_OVER_SAMPLE_COUNT == ECSenseUART_OVER_SAMPLE_16 */
    #define ECSenseUART_HD_TXBITCTR_INIT   ((8u * ECSenseUART_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define ECSenseUART_RXBITCTR_INIT      (((7u * ECSenseUART_OVER_SAMPLE_COUNT) - 1u) + \
                                                      ECSenseUART_HALF_BIT_COUNT)
#endif /* End ECSenseUART_OVER_SAMPLE_COUNT */

#define ECSenseUART_HD_RXBITCTR_INIT                   ECSenseUART_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 ECSenseUART_initVar;
#if (ECSenseUART_TX_INTERRUPT_ENABLED && ECSenseUART_TX_ENABLED)
    extern volatile uint8 ECSenseUART_txBuffer[ECSenseUART_TX_BUFFER_SIZE];
    extern volatile uint8 ECSenseUART_txBufferRead;
    extern uint8 ECSenseUART_txBufferWrite;
#endif /* (ECSenseUART_TX_INTERRUPT_ENABLED && ECSenseUART_TX_ENABLED) */
#if (ECSenseUART_RX_INTERRUPT_ENABLED && (ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED))
    extern uint8 ECSenseUART_errorStatus;
    extern volatile uint8 ECSenseUART_rxBuffer[ECSenseUART_RX_BUFFER_SIZE];
    extern volatile uint8 ECSenseUART_rxBufferRead;
    extern volatile uint8 ECSenseUART_rxBufferWrite;
    extern volatile uint8 ECSenseUART_rxBufferLoopDetect;
    extern volatile uint8 ECSenseUART_rxBufferOverflow;
    #if (ECSenseUART_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 ECSenseUART_rxAddressMode;
        extern volatile uint8 ECSenseUART_rxAddressDetected;
    #endif /* (ECSenseUART_RXHW_ADDRESS_ENABLED) */
#endif /* (ECSenseUART_RX_INTERRUPT_ENABLED && (ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define ECSenseUART__B_UART__AM_SW_BYTE_BYTE 1
#define ECSenseUART__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define ECSenseUART__B_UART__AM_HW_BYTE_BY_BYTE 3
#define ECSenseUART__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define ECSenseUART__B_UART__AM_NONE 0

#define ECSenseUART__B_UART__NONE_REVB 0
#define ECSenseUART__B_UART__EVEN_REVB 1
#define ECSenseUART__B_UART__ODD_REVB 2
#define ECSenseUART__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define ECSenseUART_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define ECSenseUART_NUMBER_OF_STOP_BITS    (1u)

#if (ECSenseUART_RXHW_ADDRESS_ENABLED)
    #define ECSenseUART_RX_ADDRESS_MODE    (0u)
    #define ECSenseUART_RX_HW_ADDRESS1     (0u)
    #define ECSenseUART_RX_HW_ADDRESS2     (0u)
#endif /* (ECSenseUART_RXHW_ADDRESS_ENABLED) */

#define ECSenseUART_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << ECSenseUART_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << ECSenseUART_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << ECSenseUART_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (1 << ECSenseUART_RX_STS_PAR_ERROR_SHIFT) \
                                        | (1 << ECSenseUART_RX_STS_STOP_ERROR_SHIFT) \
                                        | (1 << ECSenseUART_RX_STS_BREAK_SHIFT) \
                                        | (1 << ECSenseUART_RX_STS_OVERRUN_SHIFT))

#define ECSenseUART_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << ECSenseUART_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << ECSenseUART_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << ECSenseUART_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << ECSenseUART_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef ECSenseUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define ECSenseUART_CONTROL_REG \
                            (* (reg8 *) ECSenseUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define ECSenseUART_CONTROL_PTR \
                            (  (reg8 *) ECSenseUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End ECSenseUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(ECSenseUART_TX_ENABLED)
    #define ECSenseUART_TXDATA_REG          (* (reg8 *) ECSenseUART_BUART_sTX_TxShifter_u0__F0_REG)
    #define ECSenseUART_TXDATA_PTR          (  (reg8 *) ECSenseUART_BUART_sTX_TxShifter_u0__F0_REG)
    #define ECSenseUART_TXDATA_AUX_CTL_REG  (* (reg8 *) ECSenseUART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define ECSenseUART_TXDATA_AUX_CTL_PTR  (  (reg8 *) ECSenseUART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define ECSenseUART_TXSTATUS_REG        (* (reg8 *) ECSenseUART_BUART_sTX_TxSts__STATUS_REG)
    #define ECSenseUART_TXSTATUS_PTR        (  (reg8 *) ECSenseUART_BUART_sTX_TxSts__STATUS_REG)
    #define ECSenseUART_TXSTATUS_MASK_REG   (* (reg8 *) ECSenseUART_BUART_sTX_TxSts__MASK_REG)
    #define ECSenseUART_TXSTATUS_MASK_PTR   (  (reg8 *) ECSenseUART_BUART_sTX_TxSts__MASK_REG)
    #define ECSenseUART_TXSTATUS_ACTL_REG   (* (reg8 *) ECSenseUART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define ECSenseUART_TXSTATUS_ACTL_PTR   (  (reg8 *) ECSenseUART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(ECSenseUART_TXCLKGEN_DP)
        #define ECSenseUART_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) ECSenseUART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define ECSenseUART_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) ECSenseUART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define ECSenseUART_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) ECSenseUART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define ECSenseUART_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) ECSenseUART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define ECSenseUART_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) ECSenseUART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define ECSenseUART_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) ECSenseUART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define ECSenseUART_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) ECSenseUART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define ECSenseUART_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) ECSenseUART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define ECSenseUART_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) ECSenseUART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define ECSenseUART_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) ECSenseUART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* ECSenseUART_TXCLKGEN_DP */

#endif /* End ECSenseUART_TX_ENABLED */

#if(ECSenseUART_HD_ENABLED)

    #define ECSenseUART_TXDATA_REG             (* (reg8 *) ECSenseUART_BUART_sRX_RxShifter_u0__F1_REG )
    #define ECSenseUART_TXDATA_PTR             (  (reg8 *) ECSenseUART_BUART_sRX_RxShifter_u0__F1_REG )
    #define ECSenseUART_TXDATA_AUX_CTL_REG     (* (reg8 *) ECSenseUART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define ECSenseUART_TXDATA_AUX_CTL_PTR     (  (reg8 *) ECSenseUART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define ECSenseUART_TXSTATUS_REG           (* (reg8 *) ECSenseUART_BUART_sRX_RxSts__STATUS_REG )
    #define ECSenseUART_TXSTATUS_PTR           (  (reg8 *) ECSenseUART_BUART_sRX_RxSts__STATUS_REG )
    #define ECSenseUART_TXSTATUS_MASK_REG      (* (reg8 *) ECSenseUART_BUART_sRX_RxSts__MASK_REG )
    #define ECSenseUART_TXSTATUS_MASK_PTR      (  (reg8 *) ECSenseUART_BUART_sRX_RxSts__MASK_REG )
    #define ECSenseUART_TXSTATUS_ACTL_REG      (* (reg8 *) ECSenseUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define ECSenseUART_TXSTATUS_ACTL_PTR      (  (reg8 *) ECSenseUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End ECSenseUART_HD_ENABLED */

#if( (ECSenseUART_RX_ENABLED) || (ECSenseUART_HD_ENABLED) )
    #define ECSenseUART_RXDATA_REG             (* (reg8 *) ECSenseUART_BUART_sRX_RxShifter_u0__F0_REG )
    #define ECSenseUART_RXDATA_PTR             (  (reg8 *) ECSenseUART_BUART_sRX_RxShifter_u0__F0_REG )
    #define ECSenseUART_RXADDRESS1_REG         (* (reg8 *) ECSenseUART_BUART_sRX_RxShifter_u0__D0_REG )
    #define ECSenseUART_RXADDRESS1_PTR         (  (reg8 *) ECSenseUART_BUART_sRX_RxShifter_u0__D0_REG )
    #define ECSenseUART_RXADDRESS2_REG         (* (reg8 *) ECSenseUART_BUART_sRX_RxShifter_u0__D1_REG )
    #define ECSenseUART_RXADDRESS2_PTR         (  (reg8 *) ECSenseUART_BUART_sRX_RxShifter_u0__D1_REG )
    #define ECSenseUART_RXDATA_AUX_CTL_REG     (* (reg8 *) ECSenseUART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define ECSenseUART_RXBITCTR_PERIOD_REG    (* (reg8 *) ECSenseUART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define ECSenseUART_RXBITCTR_PERIOD_PTR    (  (reg8 *) ECSenseUART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define ECSenseUART_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) ECSenseUART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define ECSenseUART_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) ECSenseUART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define ECSenseUART_RXBITCTR_COUNTER_REG   (* (reg8 *) ECSenseUART_BUART_sRX_RxBitCounter__COUNT_REG )
    #define ECSenseUART_RXBITCTR_COUNTER_PTR   (  (reg8 *) ECSenseUART_BUART_sRX_RxBitCounter__COUNT_REG )

    #define ECSenseUART_RXSTATUS_REG           (* (reg8 *) ECSenseUART_BUART_sRX_RxSts__STATUS_REG )
    #define ECSenseUART_RXSTATUS_PTR           (  (reg8 *) ECSenseUART_BUART_sRX_RxSts__STATUS_REG )
    #define ECSenseUART_RXSTATUS_MASK_REG      (* (reg8 *) ECSenseUART_BUART_sRX_RxSts__MASK_REG )
    #define ECSenseUART_RXSTATUS_MASK_PTR      (  (reg8 *) ECSenseUART_BUART_sRX_RxSts__MASK_REG )
    #define ECSenseUART_RXSTATUS_ACTL_REG      (* (reg8 *) ECSenseUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define ECSenseUART_RXSTATUS_ACTL_PTR      (  (reg8 *) ECSenseUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (ECSenseUART_RX_ENABLED) || (ECSenseUART_HD_ENABLED) */

#if(ECSenseUART_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define ECSenseUART_INTCLOCK_CLKEN_REG     (* (reg8 *) ECSenseUART_IntClock__PM_ACT_CFG)
    #define ECSenseUART_INTCLOCK_CLKEN_PTR     (  (reg8 *) ECSenseUART_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define ECSenseUART_INTCLOCK_CLKEN_MASK    ECSenseUART_IntClock__PM_ACT_MSK
#endif /* End ECSenseUART_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(ECSenseUART_TX_ENABLED)
    #define ECSenseUART_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End ECSenseUART_TX_ENABLED */

#if(ECSenseUART_HD_ENABLED)
    #define ECSenseUART_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End ECSenseUART_HD_ENABLED */

#if( (ECSenseUART_RX_ENABLED) || (ECSenseUART_HD_ENABLED) )
    #define ECSenseUART_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (ECSenseUART_RX_ENABLED) || (ECSenseUART_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define ECSenseUART_WAIT_1_MS      ECSenseUART_BL_CHK_DELAY_MS   

#define ECSenseUART_TXBUFFERSIZE   ECSenseUART_TX_BUFFER_SIZE
#define ECSenseUART_RXBUFFERSIZE   ECSenseUART_RX_BUFFER_SIZE

#if (ECSenseUART_RXHW_ADDRESS_ENABLED)
    #define ECSenseUART_RXADDRESSMODE  ECSenseUART_RX_ADDRESS_MODE
    #define ECSenseUART_RXHWADDRESS1   ECSenseUART_RX_HW_ADDRESS1
    #define ECSenseUART_RXHWADDRESS2   ECSenseUART_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define ECSenseUART_RXAddressMode  ECSenseUART_RXADDRESSMODE
#endif /* (ECSenseUART_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define ECSenseUART_initvar                    ECSenseUART_initVar

#define ECSenseUART_RX_Enabled                 ECSenseUART_RX_ENABLED
#define ECSenseUART_TX_Enabled                 ECSenseUART_TX_ENABLED
#define ECSenseUART_HD_Enabled                 ECSenseUART_HD_ENABLED
#define ECSenseUART_RX_IntInterruptEnabled     ECSenseUART_RX_INTERRUPT_ENABLED
#define ECSenseUART_TX_IntInterruptEnabled     ECSenseUART_TX_INTERRUPT_ENABLED
#define ECSenseUART_InternalClockUsed          ECSenseUART_INTERNAL_CLOCK_USED
#define ECSenseUART_RXHW_Address_Enabled       ECSenseUART_RXHW_ADDRESS_ENABLED
#define ECSenseUART_OverSampleCount            ECSenseUART_OVER_SAMPLE_COUNT
#define ECSenseUART_ParityType                 ECSenseUART_PARITY_TYPE

#if( ECSenseUART_TX_ENABLED && (ECSenseUART_TXBUFFERSIZE > ECSenseUART_FIFO_LENGTH))
    #define ECSenseUART_TXBUFFER               ECSenseUART_txBuffer
    #define ECSenseUART_TXBUFFERREAD           ECSenseUART_txBufferRead
    #define ECSenseUART_TXBUFFERWRITE          ECSenseUART_txBufferWrite
#endif /* End ECSenseUART_TX_ENABLED */
#if( ( ECSenseUART_RX_ENABLED || ECSenseUART_HD_ENABLED ) && \
     (ECSenseUART_RXBUFFERSIZE > ECSenseUART_FIFO_LENGTH) )
    #define ECSenseUART_RXBUFFER               ECSenseUART_rxBuffer
    #define ECSenseUART_RXBUFFERREAD           ECSenseUART_rxBufferRead
    #define ECSenseUART_RXBUFFERWRITE          ECSenseUART_rxBufferWrite
    #define ECSenseUART_RXBUFFERLOOPDETECT     ECSenseUART_rxBufferLoopDetect
    #define ECSenseUART_RXBUFFER_OVERFLOW      ECSenseUART_rxBufferOverflow
#endif /* End ECSenseUART_RX_ENABLED */

#ifdef ECSenseUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define ECSenseUART_CONTROL                ECSenseUART_CONTROL_REG
#endif /* End ECSenseUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(ECSenseUART_TX_ENABLED)
    #define ECSenseUART_TXDATA                 ECSenseUART_TXDATA_REG
    #define ECSenseUART_TXSTATUS               ECSenseUART_TXSTATUS_REG
    #define ECSenseUART_TXSTATUS_MASK          ECSenseUART_TXSTATUS_MASK_REG
    #define ECSenseUART_TXSTATUS_ACTL          ECSenseUART_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(ECSenseUART_TXCLKGEN_DP)
        #define ECSenseUART_TXBITCLKGEN_CTR        ECSenseUART_TXBITCLKGEN_CTR_REG
        #define ECSenseUART_TXBITCLKTX_COMPLETE    ECSenseUART_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define ECSenseUART_TXBITCTR_PERIOD        ECSenseUART_TXBITCTR_PERIOD_REG
        #define ECSenseUART_TXBITCTR_CONTROL       ECSenseUART_TXBITCTR_CONTROL_REG
        #define ECSenseUART_TXBITCTR_COUNTER       ECSenseUART_TXBITCTR_COUNTER_REG
    #endif /* ECSenseUART_TXCLKGEN_DP */
#endif /* End ECSenseUART_TX_ENABLED */

#if(ECSenseUART_HD_ENABLED)
    #define ECSenseUART_TXDATA                 ECSenseUART_TXDATA_REG
    #define ECSenseUART_TXSTATUS               ECSenseUART_TXSTATUS_REG
    #define ECSenseUART_TXSTATUS_MASK          ECSenseUART_TXSTATUS_MASK_REG
    #define ECSenseUART_TXSTATUS_ACTL          ECSenseUART_TXSTATUS_ACTL_REG
#endif /* End ECSenseUART_HD_ENABLED */

#if( (ECSenseUART_RX_ENABLED) || (ECSenseUART_HD_ENABLED) )
    #define ECSenseUART_RXDATA                 ECSenseUART_RXDATA_REG
    #define ECSenseUART_RXADDRESS1             ECSenseUART_RXADDRESS1_REG
    #define ECSenseUART_RXADDRESS2             ECSenseUART_RXADDRESS2_REG
    #define ECSenseUART_RXBITCTR_PERIOD        ECSenseUART_RXBITCTR_PERIOD_REG
    #define ECSenseUART_RXBITCTR_CONTROL       ECSenseUART_RXBITCTR_CONTROL_REG
    #define ECSenseUART_RXBITCTR_COUNTER       ECSenseUART_RXBITCTR_COUNTER_REG
    #define ECSenseUART_RXSTATUS               ECSenseUART_RXSTATUS_REG
    #define ECSenseUART_RXSTATUS_MASK          ECSenseUART_RXSTATUS_MASK_REG
    #define ECSenseUART_RXSTATUS_ACTL          ECSenseUART_RXSTATUS_ACTL_REG
#endif /* End  (ECSenseUART_RX_ENABLED) || (ECSenseUART_HD_ENABLED) */

#if(ECSenseUART_INTERNAL_CLOCK_USED)
    #define ECSenseUART_INTCLOCK_CLKEN         ECSenseUART_INTCLOCK_CLKEN_REG
#endif /* End ECSenseUART_INTERNAL_CLOCK_USED */

#define ECSenseUART_WAIT_FOR_COMLETE_REINIT    ECSenseUART_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_ECSenseUART_H */


/* [] END OF FILE */
