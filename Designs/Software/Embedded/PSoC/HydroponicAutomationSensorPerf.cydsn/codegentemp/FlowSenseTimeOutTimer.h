/*******************************************************************************
* File Name: FlowSenseTimeOutTimer.h
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

#if !defined(CY_TIMER_FlowSenseTimeOutTimer_H)
#define CY_TIMER_FlowSenseTimeOutTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 FlowSenseTimeOutTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define FlowSenseTimeOutTimer_Resolution                 24u
#define FlowSenseTimeOutTimer_UsingFixedFunction         0u
#define FlowSenseTimeOutTimer_UsingHWCaptureCounter      0u
#define FlowSenseTimeOutTimer_SoftwareCaptureMode        0u
#define FlowSenseTimeOutTimer_SoftwareTriggerMode        0u
#define FlowSenseTimeOutTimer_UsingHWEnable              0u
#define FlowSenseTimeOutTimer_EnableTriggerMode          0u
#define FlowSenseTimeOutTimer_InterruptOnCaptureCount    0u
#define FlowSenseTimeOutTimer_RunModeUsed                1u
#define FlowSenseTimeOutTimer_ControlRegRemoved          0u

#if defined(FlowSenseTimeOutTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define FlowSenseTimeOutTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (FlowSenseTimeOutTimer_UsingFixedFunction)
    #define FlowSenseTimeOutTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define FlowSenseTimeOutTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End FlowSenseTimeOutTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!FlowSenseTimeOutTimer_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (FlowSenseTimeOutTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!FlowSenseTimeOutTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}FlowSenseTimeOutTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    FlowSenseTimeOutTimer_Start(void) ;
void    FlowSenseTimeOutTimer_Stop(void) ;

void    FlowSenseTimeOutTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   FlowSenseTimeOutTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define FlowSenseTimeOutTimer_GetInterruptSource() FlowSenseTimeOutTimer_ReadStatusRegister()

#if(!FlowSenseTimeOutTimer_UDB_CONTROL_REG_REMOVED)
    uint8   FlowSenseTimeOutTimer_ReadControlRegister(void) ;
    void    FlowSenseTimeOutTimer_WriteControlRegister(uint8 control) ;
#endif /* (!FlowSenseTimeOutTimer_UDB_CONTROL_REG_REMOVED) */

uint32  FlowSenseTimeOutTimer_ReadPeriod(void) ;
void    FlowSenseTimeOutTimer_WritePeriod(uint32 period) ;
uint32  FlowSenseTimeOutTimer_ReadCounter(void) ;
void    FlowSenseTimeOutTimer_WriteCounter(uint32 counter) ;
uint32  FlowSenseTimeOutTimer_ReadCapture(void) ;
void    FlowSenseTimeOutTimer_SoftwareCapture(void) ;

#if(!FlowSenseTimeOutTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (FlowSenseTimeOutTimer_SoftwareCaptureMode)
        void    FlowSenseTimeOutTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!FlowSenseTimeOutTimer_UsingFixedFunction) */

    #if (FlowSenseTimeOutTimer_SoftwareTriggerMode)
        void    FlowSenseTimeOutTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (FlowSenseTimeOutTimer_SoftwareTriggerMode) */

    #if (FlowSenseTimeOutTimer_EnableTriggerMode)
        void    FlowSenseTimeOutTimer_EnableTrigger(void) ;
        void    FlowSenseTimeOutTimer_DisableTrigger(void) ;
    #endif /* (FlowSenseTimeOutTimer_EnableTriggerMode) */


    #if(FlowSenseTimeOutTimer_InterruptOnCaptureCount)
        void    FlowSenseTimeOutTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (FlowSenseTimeOutTimer_InterruptOnCaptureCount) */

    #if (FlowSenseTimeOutTimer_UsingHWCaptureCounter)
        void    FlowSenseTimeOutTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   FlowSenseTimeOutTimer_ReadCaptureCount(void) ;
    #endif /* (FlowSenseTimeOutTimer_UsingHWCaptureCounter) */

    void FlowSenseTimeOutTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void FlowSenseTimeOutTimer_Init(void)          ;
void FlowSenseTimeOutTimer_Enable(void)        ;
void FlowSenseTimeOutTimer_SaveConfig(void)    ;
void FlowSenseTimeOutTimer_RestoreConfig(void) ;
void FlowSenseTimeOutTimer_Sleep(void)         ;
void FlowSenseTimeOutTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define FlowSenseTimeOutTimer__B_TIMER__CM_NONE 0
#define FlowSenseTimeOutTimer__B_TIMER__CM_RISINGEDGE 1
#define FlowSenseTimeOutTimer__B_TIMER__CM_FALLINGEDGE 2
#define FlowSenseTimeOutTimer__B_TIMER__CM_EITHEREDGE 3
#define FlowSenseTimeOutTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define FlowSenseTimeOutTimer__B_TIMER__TM_NONE 0x00u
#define FlowSenseTimeOutTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define FlowSenseTimeOutTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define FlowSenseTimeOutTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define FlowSenseTimeOutTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define FlowSenseTimeOutTimer_INIT_PERIOD             199999u
#define FlowSenseTimeOutTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << FlowSenseTimeOutTimer_CTRL_CAP_MODE_SHIFT))
#define FlowSenseTimeOutTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << FlowSenseTimeOutTimer_CTRL_TRIG_MODE_SHIFT))
#if (FlowSenseTimeOutTimer_UsingFixedFunction)
    #define FlowSenseTimeOutTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << FlowSenseTimeOutTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << FlowSenseTimeOutTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define FlowSenseTimeOutTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << FlowSenseTimeOutTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << FlowSenseTimeOutTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << FlowSenseTimeOutTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (FlowSenseTimeOutTimer_UsingFixedFunction) */
#define FlowSenseTimeOutTimer_INIT_CAPTURE_COUNT      (2u)
#define FlowSenseTimeOutTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << FlowSenseTimeOutTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (FlowSenseTimeOutTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define FlowSenseTimeOutTimer_STATUS         (*(reg8 *) FlowSenseTimeOutTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define FlowSenseTimeOutTimer_STATUS_MASK    (*(reg8 *) FlowSenseTimeOutTimer_TimerHW__SR0 )
    #define FlowSenseTimeOutTimer_CONTROL        (*(reg8 *) FlowSenseTimeOutTimer_TimerHW__CFG0)
    #define FlowSenseTimeOutTimer_CONTROL2       (*(reg8 *) FlowSenseTimeOutTimer_TimerHW__CFG1)
    #define FlowSenseTimeOutTimer_CONTROL2_PTR   ( (reg8 *) FlowSenseTimeOutTimer_TimerHW__CFG1)
    #define FlowSenseTimeOutTimer_RT1            (*(reg8 *) FlowSenseTimeOutTimer_TimerHW__RT1)
    #define FlowSenseTimeOutTimer_RT1_PTR        ( (reg8 *) FlowSenseTimeOutTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define FlowSenseTimeOutTimer_CONTROL3       (*(reg8 *) FlowSenseTimeOutTimer_TimerHW__CFG2)
        #define FlowSenseTimeOutTimer_CONTROL3_PTR   ( (reg8 *) FlowSenseTimeOutTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define FlowSenseTimeOutTimer_GLOBAL_ENABLE  (*(reg8 *) FlowSenseTimeOutTimer_TimerHW__PM_ACT_CFG)
    #define FlowSenseTimeOutTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) FlowSenseTimeOutTimer_TimerHW__PM_STBY_CFG)

    #define FlowSenseTimeOutTimer_CAPTURE_LSB         (* (reg16 *) FlowSenseTimeOutTimer_TimerHW__CAP0 )
    #define FlowSenseTimeOutTimer_CAPTURE_LSB_PTR       ((reg16 *) FlowSenseTimeOutTimer_TimerHW__CAP0 )
    #define FlowSenseTimeOutTimer_PERIOD_LSB          (* (reg16 *) FlowSenseTimeOutTimer_TimerHW__PER0 )
    #define FlowSenseTimeOutTimer_PERIOD_LSB_PTR        ((reg16 *) FlowSenseTimeOutTimer_TimerHW__PER0 )
    #define FlowSenseTimeOutTimer_COUNTER_LSB         (* (reg16 *) FlowSenseTimeOutTimer_TimerHW__CNT_CMP0 )
    #define FlowSenseTimeOutTimer_COUNTER_LSB_PTR       ((reg16 *) FlowSenseTimeOutTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define FlowSenseTimeOutTimer_BLOCK_EN_MASK                     FlowSenseTimeOutTimer_TimerHW__PM_ACT_MSK
    #define FlowSenseTimeOutTimer_BLOCK_STBY_EN_MASK                FlowSenseTimeOutTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define FlowSenseTimeOutTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define FlowSenseTimeOutTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define FlowSenseTimeOutTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define FlowSenseTimeOutTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define FlowSenseTimeOutTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define FlowSenseTimeOutTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define FlowSenseTimeOutTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define FlowSenseTimeOutTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define FlowSenseTimeOutTimer_CTRL_MODE_SHIFT                 0x01u
        #define FlowSenseTimeOutTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << FlowSenseTimeOutTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define FlowSenseTimeOutTimer_CTRL_RCOD_SHIFT        0x02u
        #define FlowSenseTimeOutTimer_CTRL_ENBL_SHIFT        0x00u
        #define FlowSenseTimeOutTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define FlowSenseTimeOutTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << FlowSenseTimeOutTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define FlowSenseTimeOutTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << FlowSenseTimeOutTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define FlowSenseTimeOutTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << FlowSenseTimeOutTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define FlowSenseTimeOutTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << FlowSenseTimeOutTimer_CTRL_RCOD_SHIFT))
        #define FlowSenseTimeOutTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << FlowSenseTimeOutTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define FlowSenseTimeOutTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define FlowSenseTimeOutTimer_RT1_MASK                        ((uint8)((uint8)0x03u << FlowSenseTimeOutTimer_RT1_SHIFT))
    #define FlowSenseTimeOutTimer_SYNC                            ((uint8)((uint8)0x03u << FlowSenseTimeOutTimer_RT1_SHIFT))
    #define FlowSenseTimeOutTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define FlowSenseTimeOutTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << FlowSenseTimeOutTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define FlowSenseTimeOutTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << FlowSenseTimeOutTimer_SYNCDSI_SHIFT))

    #define FlowSenseTimeOutTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_CTRL_MODE_SHIFT))
    #define FlowSenseTimeOutTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << FlowSenseTimeOutTimer_CTRL_MODE_SHIFT))
    #define FlowSenseTimeOutTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << FlowSenseTimeOutTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define FlowSenseTimeOutTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define FlowSenseTimeOutTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define FlowSenseTimeOutTimer_STATUS_TC_INT_MASK_SHIFT        (FlowSenseTimeOutTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define FlowSenseTimeOutTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (FlowSenseTimeOutTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define FlowSenseTimeOutTimer_STATUS_TC                       ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_STATUS_TC_SHIFT))
    #define FlowSenseTimeOutTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define FlowSenseTimeOutTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define FlowSenseTimeOutTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define FlowSenseTimeOutTimer_STATUS              (* (reg8 *) FlowSenseTimeOutTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define FlowSenseTimeOutTimer_STATUS_MASK         (* (reg8 *) FlowSenseTimeOutTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define FlowSenseTimeOutTimer_STATUS_AUX_CTRL     (* (reg8 *) FlowSenseTimeOutTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define FlowSenseTimeOutTimer_CONTROL             (* (reg8 *) FlowSenseTimeOutTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(FlowSenseTimeOutTimer_Resolution <= 8u) /* 8-bit Timer */
        #define FlowSenseTimeOutTimer_CAPTURE_LSB         (* (reg8 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define FlowSenseTimeOutTimer_CAPTURE_LSB_PTR       ((reg8 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define FlowSenseTimeOutTimer_PERIOD_LSB          (* (reg8 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define FlowSenseTimeOutTimer_PERIOD_LSB_PTR        ((reg8 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define FlowSenseTimeOutTimer_COUNTER_LSB         (* (reg8 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define FlowSenseTimeOutTimer_COUNTER_LSB_PTR       ((reg8 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
    #elif(FlowSenseTimeOutTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define FlowSenseTimeOutTimer_CAPTURE_LSB         (* (reg16 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define FlowSenseTimeOutTimer_CAPTURE_LSB_PTR       ((reg16 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define FlowSenseTimeOutTimer_PERIOD_LSB          (* (reg16 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define FlowSenseTimeOutTimer_PERIOD_LSB_PTR        ((reg16 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define FlowSenseTimeOutTimer_COUNTER_LSB         (* (reg16 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define FlowSenseTimeOutTimer_COUNTER_LSB_PTR       ((reg16 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define FlowSenseTimeOutTimer_CAPTURE_LSB         (* (reg16 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define FlowSenseTimeOutTimer_CAPTURE_LSB_PTR       ((reg16 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define FlowSenseTimeOutTimer_PERIOD_LSB          (* (reg16 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define FlowSenseTimeOutTimer_PERIOD_LSB_PTR        ((reg16 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define FlowSenseTimeOutTimer_COUNTER_LSB         (* (reg16 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
            #define FlowSenseTimeOutTimer_COUNTER_LSB_PTR       ((reg16 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(FlowSenseTimeOutTimer_Resolution <= 24u)/* 24-bit Timer */
        #define FlowSenseTimeOutTimer_CAPTURE_LSB         (* (reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define FlowSenseTimeOutTimer_CAPTURE_LSB_PTR       ((reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define FlowSenseTimeOutTimer_PERIOD_LSB          (* (reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define FlowSenseTimeOutTimer_PERIOD_LSB_PTR        ((reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define FlowSenseTimeOutTimer_COUNTER_LSB         (* (reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define FlowSenseTimeOutTimer_COUNTER_LSB_PTR       ((reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define FlowSenseTimeOutTimer_CAPTURE_LSB         (* (reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define FlowSenseTimeOutTimer_CAPTURE_LSB_PTR       ((reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define FlowSenseTimeOutTimer_PERIOD_LSB          (* (reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define FlowSenseTimeOutTimer_PERIOD_LSB_PTR        ((reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define FlowSenseTimeOutTimer_COUNTER_LSB         (* (reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define FlowSenseTimeOutTimer_COUNTER_LSB_PTR       ((reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define FlowSenseTimeOutTimer_CAPTURE_LSB         (* (reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define FlowSenseTimeOutTimer_CAPTURE_LSB_PTR       ((reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define FlowSenseTimeOutTimer_PERIOD_LSB          (* (reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define FlowSenseTimeOutTimer_PERIOD_LSB_PTR        ((reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define FlowSenseTimeOutTimer_COUNTER_LSB         (* (reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
            #define FlowSenseTimeOutTimer_COUNTER_LSB_PTR       ((reg32 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define FlowSenseTimeOutTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) FlowSenseTimeOutTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
    
    #if (FlowSenseTimeOutTimer_UsingHWCaptureCounter)
        #define FlowSenseTimeOutTimer_CAP_COUNT              (*(reg8 *) FlowSenseTimeOutTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define FlowSenseTimeOutTimer_CAP_COUNT_PTR          ( (reg8 *) FlowSenseTimeOutTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define FlowSenseTimeOutTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) FlowSenseTimeOutTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define FlowSenseTimeOutTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) FlowSenseTimeOutTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (FlowSenseTimeOutTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define FlowSenseTimeOutTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define FlowSenseTimeOutTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define FlowSenseTimeOutTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define FlowSenseTimeOutTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define FlowSenseTimeOutTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define FlowSenseTimeOutTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << FlowSenseTimeOutTimer_CTRL_INTCNT_SHIFT))
    #define FlowSenseTimeOutTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << FlowSenseTimeOutTimer_CTRL_TRIG_MODE_SHIFT))
    #define FlowSenseTimeOutTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_CTRL_TRIG_EN_SHIFT))
    #define FlowSenseTimeOutTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << FlowSenseTimeOutTimer_CTRL_CAP_MODE_SHIFT))
    #define FlowSenseTimeOutTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define FlowSenseTimeOutTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define FlowSenseTimeOutTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define FlowSenseTimeOutTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define FlowSenseTimeOutTimer_STATUS_TC_INT_MASK_SHIFT       FlowSenseTimeOutTimer_STATUS_TC_SHIFT
    #define FlowSenseTimeOutTimer_STATUS_CAPTURE_INT_MASK_SHIFT  FlowSenseTimeOutTimer_STATUS_CAPTURE_SHIFT
    #define FlowSenseTimeOutTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define FlowSenseTimeOutTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define FlowSenseTimeOutTimer_STATUS_FIFOFULL_INT_MASK_SHIFT FlowSenseTimeOutTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define FlowSenseTimeOutTimer_STATUS_TC                      ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define FlowSenseTimeOutTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define FlowSenseTimeOutTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define FlowSenseTimeOutTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define FlowSenseTimeOutTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define FlowSenseTimeOutTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define FlowSenseTimeOutTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << FlowSenseTimeOutTimer_STATUS_FIFOFULL_SHIFT))

    #define FlowSenseTimeOutTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define FlowSenseTimeOutTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define FlowSenseTimeOutTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define FlowSenseTimeOutTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define FlowSenseTimeOutTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define FlowSenseTimeOutTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_FlowSenseTimeOutTimer_H */


/* [] END OF FILE */
