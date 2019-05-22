/*******************************************************************************
* File Name: HalfBridgeTimer.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_HalfBridgeTimer_H)
#define CY_TIMER_HalfBridgeTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 HalfBridgeTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define HalfBridgeTimer_Resolution                 32u
#define HalfBridgeTimer_UsingFixedFunction         0u
#define HalfBridgeTimer_UsingHWCaptureCounter      0u
#define HalfBridgeTimer_SoftwareCaptureMode        0u
#define HalfBridgeTimer_SoftwareTriggerMode        0u
#define HalfBridgeTimer_UsingHWEnable              0u
#define HalfBridgeTimer_EnableTriggerMode          0u
#define HalfBridgeTimer_InterruptOnCaptureCount    0u
#define HalfBridgeTimer_RunModeUsed                1u
#define HalfBridgeTimer_ControlRegRemoved          0u

#if defined(HalfBridgeTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define HalfBridgeTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (HalfBridgeTimer_UsingFixedFunction)
    #define HalfBridgeTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define HalfBridgeTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End HalfBridgeTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!HalfBridgeTimer_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (HalfBridgeTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!HalfBridgeTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}HalfBridgeTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    HalfBridgeTimer_Start(void) ;
void    HalfBridgeTimer_Stop(void) ;

void    HalfBridgeTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   HalfBridgeTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define HalfBridgeTimer_GetInterruptSource() HalfBridgeTimer_ReadStatusRegister()

#if(!HalfBridgeTimer_UDB_CONTROL_REG_REMOVED)
    uint8   HalfBridgeTimer_ReadControlRegister(void) ;
    void    HalfBridgeTimer_WriteControlRegister(uint8 control) ;
#endif /* (!HalfBridgeTimer_UDB_CONTROL_REG_REMOVED) */

uint32  HalfBridgeTimer_ReadPeriod(void) ;
void    HalfBridgeTimer_WritePeriod(uint32 period) ;
uint32  HalfBridgeTimer_ReadCounter(void) ;
void    HalfBridgeTimer_WriteCounter(uint32 counter) ;
uint32  HalfBridgeTimer_ReadCapture(void) ;
void    HalfBridgeTimer_SoftwareCapture(void) ;

#if(!HalfBridgeTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (HalfBridgeTimer_SoftwareCaptureMode)
        void    HalfBridgeTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!HalfBridgeTimer_UsingFixedFunction) */

    #if (HalfBridgeTimer_SoftwareTriggerMode)
        void    HalfBridgeTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (HalfBridgeTimer_SoftwareTriggerMode) */

    #if (HalfBridgeTimer_EnableTriggerMode)
        void    HalfBridgeTimer_EnableTrigger(void) ;
        void    HalfBridgeTimer_DisableTrigger(void) ;
    #endif /* (HalfBridgeTimer_EnableTriggerMode) */


    #if(HalfBridgeTimer_InterruptOnCaptureCount)
        void    HalfBridgeTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (HalfBridgeTimer_InterruptOnCaptureCount) */

    #if (HalfBridgeTimer_UsingHWCaptureCounter)
        void    HalfBridgeTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   HalfBridgeTimer_ReadCaptureCount(void) ;
    #endif /* (HalfBridgeTimer_UsingHWCaptureCounter) */

    void HalfBridgeTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void HalfBridgeTimer_Init(void)          ;
void HalfBridgeTimer_Enable(void)        ;
void HalfBridgeTimer_SaveConfig(void)    ;
void HalfBridgeTimer_RestoreConfig(void) ;
void HalfBridgeTimer_Sleep(void)         ;
void HalfBridgeTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define HalfBridgeTimer__B_TIMER__CM_NONE 0
#define HalfBridgeTimer__B_TIMER__CM_RISINGEDGE 1
#define HalfBridgeTimer__B_TIMER__CM_FALLINGEDGE 2
#define HalfBridgeTimer__B_TIMER__CM_EITHEREDGE 3
#define HalfBridgeTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define HalfBridgeTimer__B_TIMER__TM_NONE 0x00u
#define HalfBridgeTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define HalfBridgeTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define HalfBridgeTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define HalfBridgeTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define HalfBridgeTimer_INIT_PERIOD             71999u
#define HalfBridgeTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << HalfBridgeTimer_CTRL_CAP_MODE_SHIFT))
#define HalfBridgeTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << HalfBridgeTimer_CTRL_TRIG_MODE_SHIFT))
#if (HalfBridgeTimer_UsingFixedFunction)
    #define HalfBridgeTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << HalfBridgeTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << HalfBridgeTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define HalfBridgeTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << HalfBridgeTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << HalfBridgeTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << HalfBridgeTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (HalfBridgeTimer_UsingFixedFunction) */
#define HalfBridgeTimer_INIT_CAPTURE_COUNT      (2u)
#define HalfBridgeTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << HalfBridgeTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (HalfBridgeTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define HalfBridgeTimer_STATUS         (*(reg8 *) HalfBridgeTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define HalfBridgeTimer_STATUS_MASK    (*(reg8 *) HalfBridgeTimer_TimerHW__SR0 )
    #define HalfBridgeTimer_CONTROL        (*(reg8 *) HalfBridgeTimer_TimerHW__CFG0)
    #define HalfBridgeTimer_CONTROL2       (*(reg8 *) HalfBridgeTimer_TimerHW__CFG1)
    #define HalfBridgeTimer_CONTROL2_PTR   ( (reg8 *) HalfBridgeTimer_TimerHW__CFG1)
    #define HalfBridgeTimer_RT1            (*(reg8 *) HalfBridgeTimer_TimerHW__RT1)
    #define HalfBridgeTimer_RT1_PTR        ( (reg8 *) HalfBridgeTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define HalfBridgeTimer_CONTROL3       (*(reg8 *) HalfBridgeTimer_TimerHW__CFG2)
        #define HalfBridgeTimer_CONTROL3_PTR   ( (reg8 *) HalfBridgeTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define HalfBridgeTimer_GLOBAL_ENABLE  (*(reg8 *) HalfBridgeTimer_TimerHW__PM_ACT_CFG)
    #define HalfBridgeTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) HalfBridgeTimer_TimerHW__PM_STBY_CFG)

    #define HalfBridgeTimer_CAPTURE_LSB         (* (reg16 *) HalfBridgeTimer_TimerHW__CAP0 )
    #define HalfBridgeTimer_CAPTURE_LSB_PTR       ((reg16 *) HalfBridgeTimer_TimerHW__CAP0 )
    #define HalfBridgeTimer_PERIOD_LSB          (* (reg16 *) HalfBridgeTimer_TimerHW__PER0 )
    #define HalfBridgeTimer_PERIOD_LSB_PTR        ((reg16 *) HalfBridgeTimer_TimerHW__PER0 )
    #define HalfBridgeTimer_COUNTER_LSB         (* (reg16 *) HalfBridgeTimer_TimerHW__CNT_CMP0 )
    #define HalfBridgeTimer_COUNTER_LSB_PTR       ((reg16 *) HalfBridgeTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define HalfBridgeTimer_BLOCK_EN_MASK                     HalfBridgeTimer_TimerHW__PM_ACT_MSK
    #define HalfBridgeTimer_BLOCK_STBY_EN_MASK                HalfBridgeTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define HalfBridgeTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define HalfBridgeTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define HalfBridgeTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define HalfBridgeTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define HalfBridgeTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define HalfBridgeTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << HalfBridgeTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define HalfBridgeTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define HalfBridgeTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << HalfBridgeTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define HalfBridgeTimer_CTRL_MODE_SHIFT                 0x01u
        #define HalfBridgeTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << HalfBridgeTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define HalfBridgeTimer_CTRL_RCOD_SHIFT        0x02u
        #define HalfBridgeTimer_CTRL_ENBL_SHIFT        0x00u
        #define HalfBridgeTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define HalfBridgeTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << HalfBridgeTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define HalfBridgeTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << HalfBridgeTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define HalfBridgeTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << HalfBridgeTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define HalfBridgeTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << HalfBridgeTimer_CTRL_RCOD_SHIFT))
        #define HalfBridgeTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << HalfBridgeTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define HalfBridgeTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define HalfBridgeTimer_RT1_MASK                        ((uint8)((uint8)0x03u << HalfBridgeTimer_RT1_SHIFT))
    #define HalfBridgeTimer_SYNC                            ((uint8)((uint8)0x03u << HalfBridgeTimer_RT1_SHIFT))
    #define HalfBridgeTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define HalfBridgeTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << HalfBridgeTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define HalfBridgeTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << HalfBridgeTimer_SYNCDSI_SHIFT))

    #define HalfBridgeTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << HalfBridgeTimer_CTRL_MODE_SHIFT))
    #define HalfBridgeTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << HalfBridgeTimer_CTRL_MODE_SHIFT))
    #define HalfBridgeTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << HalfBridgeTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define HalfBridgeTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define HalfBridgeTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define HalfBridgeTimer_STATUS_TC_INT_MASK_SHIFT        (HalfBridgeTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define HalfBridgeTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (HalfBridgeTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define HalfBridgeTimer_STATUS_TC                       ((uint8)((uint8)0x01u << HalfBridgeTimer_STATUS_TC_SHIFT))
    #define HalfBridgeTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << HalfBridgeTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define HalfBridgeTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << HalfBridgeTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define HalfBridgeTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << HalfBridgeTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define HalfBridgeTimer_STATUS              (* (reg8 *) HalfBridgeTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define HalfBridgeTimer_STATUS_MASK         (* (reg8 *) HalfBridgeTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define HalfBridgeTimer_STATUS_AUX_CTRL     (* (reg8 *) HalfBridgeTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define HalfBridgeTimer_CONTROL             (* (reg8 *) HalfBridgeTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(HalfBridgeTimer_Resolution <= 8u) /* 8-bit Timer */
        #define HalfBridgeTimer_CAPTURE_LSB         (* (reg8 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define HalfBridgeTimer_CAPTURE_LSB_PTR       ((reg8 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define HalfBridgeTimer_PERIOD_LSB          (* (reg8 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define HalfBridgeTimer_PERIOD_LSB_PTR        ((reg8 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define HalfBridgeTimer_COUNTER_LSB         (* (reg8 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define HalfBridgeTimer_COUNTER_LSB_PTR       ((reg8 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    #elif(HalfBridgeTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define HalfBridgeTimer_CAPTURE_LSB         (* (reg16 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define HalfBridgeTimer_CAPTURE_LSB_PTR       ((reg16 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define HalfBridgeTimer_PERIOD_LSB          (* (reg16 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define HalfBridgeTimer_PERIOD_LSB_PTR        ((reg16 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define HalfBridgeTimer_COUNTER_LSB         (* (reg16 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define HalfBridgeTimer_COUNTER_LSB_PTR       ((reg16 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define HalfBridgeTimer_CAPTURE_LSB         (* (reg16 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define HalfBridgeTimer_CAPTURE_LSB_PTR       ((reg16 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define HalfBridgeTimer_PERIOD_LSB          (* (reg16 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define HalfBridgeTimer_PERIOD_LSB_PTR        ((reg16 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define HalfBridgeTimer_COUNTER_LSB         (* (reg16 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
            #define HalfBridgeTimer_COUNTER_LSB_PTR       ((reg16 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(HalfBridgeTimer_Resolution <= 24u)/* 24-bit Timer */
        #define HalfBridgeTimer_CAPTURE_LSB         (* (reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define HalfBridgeTimer_CAPTURE_LSB_PTR       ((reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define HalfBridgeTimer_PERIOD_LSB          (* (reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define HalfBridgeTimer_PERIOD_LSB_PTR        ((reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define HalfBridgeTimer_COUNTER_LSB         (* (reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define HalfBridgeTimer_COUNTER_LSB_PTR       ((reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define HalfBridgeTimer_CAPTURE_LSB         (* (reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define HalfBridgeTimer_CAPTURE_LSB_PTR       ((reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define HalfBridgeTimer_PERIOD_LSB          (* (reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define HalfBridgeTimer_PERIOD_LSB_PTR        ((reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define HalfBridgeTimer_COUNTER_LSB         (* (reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define HalfBridgeTimer_COUNTER_LSB_PTR       ((reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define HalfBridgeTimer_CAPTURE_LSB         (* (reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define HalfBridgeTimer_CAPTURE_LSB_PTR       ((reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define HalfBridgeTimer_PERIOD_LSB          (* (reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define HalfBridgeTimer_PERIOD_LSB_PTR        ((reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define HalfBridgeTimer_COUNTER_LSB         (* (reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
            #define HalfBridgeTimer_COUNTER_LSB_PTR       ((reg32 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define HalfBridgeTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) HalfBridgeTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    
    #if (HalfBridgeTimer_UsingHWCaptureCounter)
        #define HalfBridgeTimer_CAP_COUNT              (*(reg8 *) HalfBridgeTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define HalfBridgeTimer_CAP_COUNT_PTR          ( (reg8 *) HalfBridgeTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define HalfBridgeTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) HalfBridgeTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define HalfBridgeTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) HalfBridgeTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (HalfBridgeTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define HalfBridgeTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define HalfBridgeTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define HalfBridgeTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define HalfBridgeTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define HalfBridgeTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define HalfBridgeTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << HalfBridgeTimer_CTRL_INTCNT_SHIFT))
    #define HalfBridgeTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << HalfBridgeTimer_CTRL_TRIG_MODE_SHIFT))
    #define HalfBridgeTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << HalfBridgeTimer_CTRL_TRIG_EN_SHIFT))
    #define HalfBridgeTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << HalfBridgeTimer_CTRL_CAP_MODE_SHIFT))
    #define HalfBridgeTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << HalfBridgeTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define HalfBridgeTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define HalfBridgeTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define HalfBridgeTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define HalfBridgeTimer_STATUS_TC_INT_MASK_SHIFT       HalfBridgeTimer_STATUS_TC_SHIFT
    #define HalfBridgeTimer_STATUS_CAPTURE_INT_MASK_SHIFT  HalfBridgeTimer_STATUS_CAPTURE_SHIFT
    #define HalfBridgeTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define HalfBridgeTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define HalfBridgeTimer_STATUS_FIFOFULL_INT_MASK_SHIFT HalfBridgeTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define HalfBridgeTimer_STATUS_TC                      ((uint8)((uint8)0x01u << HalfBridgeTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define HalfBridgeTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << HalfBridgeTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define HalfBridgeTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << HalfBridgeTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define HalfBridgeTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << HalfBridgeTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define HalfBridgeTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << HalfBridgeTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define HalfBridgeTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << HalfBridgeTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define HalfBridgeTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << HalfBridgeTimer_STATUS_FIFOFULL_SHIFT))

    #define HalfBridgeTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define HalfBridgeTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define HalfBridgeTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define HalfBridgeTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define HalfBridgeTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define HalfBridgeTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_HalfBridgeTimer_H */


/* [] END OF FILE */
