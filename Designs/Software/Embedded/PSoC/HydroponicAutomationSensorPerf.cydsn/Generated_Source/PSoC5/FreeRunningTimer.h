/*******************************************************************************
* File Name: FreeRunningTimer.h
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

#if !defined(CY_TIMER_FreeRunningTimer_H)
#define CY_TIMER_FreeRunningTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 FreeRunningTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define FreeRunningTimer_Resolution                 32u
#define FreeRunningTimer_UsingFixedFunction         0u
#define FreeRunningTimer_UsingHWCaptureCounter      0u
#define FreeRunningTimer_SoftwareCaptureMode        0u
#define FreeRunningTimer_SoftwareTriggerMode        0u
#define FreeRunningTimer_UsingHWEnable              0u
#define FreeRunningTimer_EnableTriggerMode          0u
#define FreeRunningTimer_InterruptOnCaptureCount    0u
#define FreeRunningTimer_RunModeUsed                0u
#define FreeRunningTimer_ControlRegRemoved          0u

#if defined(FreeRunningTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define FreeRunningTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (FreeRunningTimer_UsingFixedFunction)
    #define FreeRunningTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define FreeRunningTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End FreeRunningTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!FreeRunningTimer_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (FreeRunningTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!FreeRunningTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}FreeRunningTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    FreeRunningTimer_Start(void) ;
void    FreeRunningTimer_Stop(void) ;

void    FreeRunningTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   FreeRunningTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define FreeRunningTimer_GetInterruptSource() FreeRunningTimer_ReadStatusRegister()

#if(!FreeRunningTimer_UDB_CONTROL_REG_REMOVED)
    uint8   FreeRunningTimer_ReadControlRegister(void) ;
    void    FreeRunningTimer_WriteControlRegister(uint8 control) ;
#endif /* (!FreeRunningTimer_UDB_CONTROL_REG_REMOVED) */

uint32  FreeRunningTimer_ReadPeriod(void) ;
void    FreeRunningTimer_WritePeriod(uint32 period) ;
uint32  FreeRunningTimer_ReadCounter(void) ;
void    FreeRunningTimer_WriteCounter(uint32 counter) ;
uint32  FreeRunningTimer_ReadCapture(void) ;
void    FreeRunningTimer_SoftwareCapture(void) ;

#if(!FreeRunningTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (FreeRunningTimer_SoftwareCaptureMode)
        void    FreeRunningTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!FreeRunningTimer_UsingFixedFunction) */

    #if (FreeRunningTimer_SoftwareTriggerMode)
        void    FreeRunningTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (FreeRunningTimer_SoftwareTriggerMode) */

    #if (FreeRunningTimer_EnableTriggerMode)
        void    FreeRunningTimer_EnableTrigger(void) ;
        void    FreeRunningTimer_DisableTrigger(void) ;
    #endif /* (FreeRunningTimer_EnableTriggerMode) */


    #if(FreeRunningTimer_InterruptOnCaptureCount)
        void    FreeRunningTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (FreeRunningTimer_InterruptOnCaptureCount) */

    #if (FreeRunningTimer_UsingHWCaptureCounter)
        void    FreeRunningTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   FreeRunningTimer_ReadCaptureCount(void) ;
    #endif /* (FreeRunningTimer_UsingHWCaptureCounter) */

    void FreeRunningTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void FreeRunningTimer_Init(void)          ;
void FreeRunningTimer_Enable(void)        ;
void FreeRunningTimer_SaveConfig(void)    ;
void FreeRunningTimer_RestoreConfig(void) ;
void FreeRunningTimer_Sleep(void)         ;
void FreeRunningTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define FreeRunningTimer__B_TIMER__CM_NONE 0
#define FreeRunningTimer__B_TIMER__CM_RISINGEDGE 1
#define FreeRunningTimer__B_TIMER__CM_FALLINGEDGE 2
#define FreeRunningTimer__B_TIMER__CM_EITHEREDGE 3
#define FreeRunningTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define FreeRunningTimer__B_TIMER__TM_NONE 0x00u
#define FreeRunningTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define FreeRunningTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define FreeRunningTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define FreeRunningTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define FreeRunningTimer_INIT_PERIOD             4294967295u
#define FreeRunningTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << FreeRunningTimer_CTRL_CAP_MODE_SHIFT))
#define FreeRunningTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << FreeRunningTimer_CTRL_TRIG_MODE_SHIFT))
#if (FreeRunningTimer_UsingFixedFunction)
    #define FreeRunningTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << FreeRunningTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << FreeRunningTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define FreeRunningTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << FreeRunningTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << FreeRunningTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << FreeRunningTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (FreeRunningTimer_UsingFixedFunction) */
#define FreeRunningTimer_INIT_CAPTURE_COUNT      (2u)
#define FreeRunningTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << FreeRunningTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (FreeRunningTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define FreeRunningTimer_STATUS         (*(reg8 *) FreeRunningTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define FreeRunningTimer_STATUS_MASK    (*(reg8 *) FreeRunningTimer_TimerHW__SR0 )
    #define FreeRunningTimer_CONTROL        (*(reg8 *) FreeRunningTimer_TimerHW__CFG0)
    #define FreeRunningTimer_CONTROL2       (*(reg8 *) FreeRunningTimer_TimerHW__CFG1)
    #define FreeRunningTimer_CONTROL2_PTR   ( (reg8 *) FreeRunningTimer_TimerHW__CFG1)
    #define FreeRunningTimer_RT1            (*(reg8 *) FreeRunningTimer_TimerHW__RT1)
    #define FreeRunningTimer_RT1_PTR        ( (reg8 *) FreeRunningTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define FreeRunningTimer_CONTROL3       (*(reg8 *) FreeRunningTimer_TimerHW__CFG2)
        #define FreeRunningTimer_CONTROL3_PTR   ( (reg8 *) FreeRunningTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define FreeRunningTimer_GLOBAL_ENABLE  (*(reg8 *) FreeRunningTimer_TimerHW__PM_ACT_CFG)
    #define FreeRunningTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) FreeRunningTimer_TimerHW__PM_STBY_CFG)

    #define FreeRunningTimer_CAPTURE_LSB         (* (reg16 *) FreeRunningTimer_TimerHW__CAP0 )
    #define FreeRunningTimer_CAPTURE_LSB_PTR       ((reg16 *) FreeRunningTimer_TimerHW__CAP0 )
    #define FreeRunningTimer_PERIOD_LSB          (* (reg16 *) FreeRunningTimer_TimerHW__PER0 )
    #define FreeRunningTimer_PERIOD_LSB_PTR        ((reg16 *) FreeRunningTimer_TimerHW__PER0 )
    #define FreeRunningTimer_COUNTER_LSB         (* (reg16 *) FreeRunningTimer_TimerHW__CNT_CMP0 )
    #define FreeRunningTimer_COUNTER_LSB_PTR       ((reg16 *) FreeRunningTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define FreeRunningTimer_BLOCK_EN_MASK                     FreeRunningTimer_TimerHW__PM_ACT_MSK
    #define FreeRunningTimer_BLOCK_STBY_EN_MASK                FreeRunningTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define FreeRunningTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define FreeRunningTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define FreeRunningTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define FreeRunningTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define FreeRunningTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define FreeRunningTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << FreeRunningTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define FreeRunningTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define FreeRunningTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << FreeRunningTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define FreeRunningTimer_CTRL_MODE_SHIFT                 0x01u
        #define FreeRunningTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << FreeRunningTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define FreeRunningTimer_CTRL_RCOD_SHIFT        0x02u
        #define FreeRunningTimer_CTRL_ENBL_SHIFT        0x00u
        #define FreeRunningTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define FreeRunningTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << FreeRunningTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define FreeRunningTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << FreeRunningTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define FreeRunningTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << FreeRunningTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define FreeRunningTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << FreeRunningTimer_CTRL_RCOD_SHIFT))
        #define FreeRunningTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << FreeRunningTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define FreeRunningTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define FreeRunningTimer_RT1_MASK                        ((uint8)((uint8)0x03u << FreeRunningTimer_RT1_SHIFT))
    #define FreeRunningTimer_SYNC                            ((uint8)((uint8)0x03u << FreeRunningTimer_RT1_SHIFT))
    #define FreeRunningTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define FreeRunningTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << FreeRunningTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define FreeRunningTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << FreeRunningTimer_SYNCDSI_SHIFT))

    #define FreeRunningTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << FreeRunningTimer_CTRL_MODE_SHIFT))
    #define FreeRunningTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << FreeRunningTimer_CTRL_MODE_SHIFT))
    #define FreeRunningTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << FreeRunningTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define FreeRunningTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define FreeRunningTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define FreeRunningTimer_STATUS_TC_INT_MASK_SHIFT        (FreeRunningTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define FreeRunningTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (FreeRunningTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define FreeRunningTimer_STATUS_TC                       ((uint8)((uint8)0x01u << FreeRunningTimer_STATUS_TC_SHIFT))
    #define FreeRunningTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << FreeRunningTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define FreeRunningTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << FreeRunningTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define FreeRunningTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << FreeRunningTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define FreeRunningTimer_STATUS              (* (reg8 *) FreeRunningTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define FreeRunningTimer_STATUS_MASK         (* (reg8 *) FreeRunningTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define FreeRunningTimer_STATUS_AUX_CTRL     (* (reg8 *) FreeRunningTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define FreeRunningTimer_CONTROL             (* (reg8 *) FreeRunningTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(FreeRunningTimer_Resolution <= 8u) /* 8-bit Timer */
        #define FreeRunningTimer_CAPTURE_LSB         (* (reg8 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define FreeRunningTimer_CAPTURE_LSB_PTR       ((reg8 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define FreeRunningTimer_PERIOD_LSB          (* (reg8 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define FreeRunningTimer_PERIOD_LSB_PTR        ((reg8 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define FreeRunningTimer_COUNTER_LSB         (* (reg8 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define FreeRunningTimer_COUNTER_LSB_PTR       ((reg8 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    #elif(FreeRunningTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define FreeRunningTimer_CAPTURE_LSB         (* (reg16 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define FreeRunningTimer_CAPTURE_LSB_PTR       ((reg16 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define FreeRunningTimer_PERIOD_LSB          (* (reg16 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define FreeRunningTimer_PERIOD_LSB_PTR        ((reg16 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define FreeRunningTimer_COUNTER_LSB         (* (reg16 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define FreeRunningTimer_COUNTER_LSB_PTR       ((reg16 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define FreeRunningTimer_CAPTURE_LSB         (* (reg16 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define FreeRunningTimer_CAPTURE_LSB_PTR       ((reg16 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define FreeRunningTimer_PERIOD_LSB          (* (reg16 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define FreeRunningTimer_PERIOD_LSB_PTR        ((reg16 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define FreeRunningTimer_COUNTER_LSB         (* (reg16 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
            #define FreeRunningTimer_COUNTER_LSB_PTR       ((reg16 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(FreeRunningTimer_Resolution <= 24u)/* 24-bit Timer */
        #define FreeRunningTimer_CAPTURE_LSB         (* (reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define FreeRunningTimer_CAPTURE_LSB_PTR       ((reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define FreeRunningTimer_PERIOD_LSB          (* (reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define FreeRunningTimer_PERIOD_LSB_PTR        ((reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define FreeRunningTimer_COUNTER_LSB         (* (reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define FreeRunningTimer_COUNTER_LSB_PTR       ((reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define FreeRunningTimer_CAPTURE_LSB         (* (reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define FreeRunningTimer_CAPTURE_LSB_PTR       ((reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define FreeRunningTimer_PERIOD_LSB          (* (reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define FreeRunningTimer_PERIOD_LSB_PTR        ((reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define FreeRunningTimer_COUNTER_LSB         (* (reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define FreeRunningTimer_COUNTER_LSB_PTR       ((reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define FreeRunningTimer_CAPTURE_LSB         (* (reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define FreeRunningTimer_CAPTURE_LSB_PTR       ((reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define FreeRunningTimer_PERIOD_LSB          (* (reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define FreeRunningTimer_PERIOD_LSB_PTR        ((reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define FreeRunningTimer_COUNTER_LSB         (* (reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
            #define FreeRunningTimer_COUNTER_LSB_PTR       ((reg32 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define FreeRunningTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) FreeRunningTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    
    #if (FreeRunningTimer_UsingHWCaptureCounter)
        #define FreeRunningTimer_CAP_COUNT              (*(reg8 *) FreeRunningTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define FreeRunningTimer_CAP_COUNT_PTR          ( (reg8 *) FreeRunningTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define FreeRunningTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) FreeRunningTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define FreeRunningTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) FreeRunningTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (FreeRunningTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define FreeRunningTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define FreeRunningTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define FreeRunningTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define FreeRunningTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define FreeRunningTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define FreeRunningTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << FreeRunningTimer_CTRL_INTCNT_SHIFT))
    #define FreeRunningTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << FreeRunningTimer_CTRL_TRIG_MODE_SHIFT))
    #define FreeRunningTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << FreeRunningTimer_CTRL_TRIG_EN_SHIFT))
    #define FreeRunningTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << FreeRunningTimer_CTRL_CAP_MODE_SHIFT))
    #define FreeRunningTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << FreeRunningTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define FreeRunningTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define FreeRunningTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define FreeRunningTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define FreeRunningTimer_STATUS_TC_INT_MASK_SHIFT       FreeRunningTimer_STATUS_TC_SHIFT
    #define FreeRunningTimer_STATUS_CAPTURE_INT_MASK_SHIFT  FreeRunningTimer_STATUS_CAPTURE_SHIFT
    #define FreeRunningTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define FreeRunningTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define FreeRunningTimer_STATUS_FIFOFULL_INT_MASK_SHIFT FreeRunningTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define FreeRunningTimer_STATUS_TC                      ((uint8)((uint8)0x01u << FreeRunningTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define FreeRunningTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << FreeRunningTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define FreeRunningTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << FreeRunningTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define FreeRunningTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << FreeRunningTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define FreeRunningTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << FreeRunningTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define FreeRunningTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << FreeRunningTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define FreeRunningTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << FreeRunningTimer_STATUS_FIFOFULL_SHIFT))

    #define FreeRunningTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define FreeRunningTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define FreeRunningTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define FreeRunningTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define FreeRunningTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define FreeRunningTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_FreeRunningTimer_H */


/* [] END OF FILE */
