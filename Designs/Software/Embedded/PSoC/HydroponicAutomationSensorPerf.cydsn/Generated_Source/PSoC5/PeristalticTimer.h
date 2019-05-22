/*******************************************************************************
* File Name: PeristalticTimer.h
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

#if !defined(CY_TIMER_PeristalticTimer_H)
#define CY_TIMER_PeristalticTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 PeristalticTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define PeristalticTimer_Resolution                 16u
#define PeristalticTimer_UsingFixedFunction         1u
#define PeristalticTimer_UsingHWCaptureCounter      0u
#define PeristalticTimer_SoftwareCaptureMode        0u
#define PeristalticTimer_SoftwareTriggerMode        0u
#define PeristalticTimer_UsingHWEnable              0u
#define PeristalticTimer_EnableTriggerMode          0u
#define PeristalticTimer_InterruptOnCaptureCount    0u
#define PeristalticTimer_RunModeUsed                1u
#define PeristalticTimer_ControlRegRemoved          0u

#if defined(PeristalticTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define PeristalticTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (PeristalticTimer_UsingFixedFunction)
    #define PeristalticTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define PeristalticTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End PeristalticTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!PeristalticTimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (PeristalticTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!PeristalticTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}PeristalticTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    PeristalticTimer_Start(void) ;
void    PeristalticTimer_Stop(void) ;

void    PeristalticTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   PeristalticTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define PeristalticTimer_GetInterruptSource() PeristalticTimer_ReadStatusRegister()

#if(!PeristalticTimer_UDB_CONTROL_REG_REMOVED)
    uint8   PeristalticTimer_ReadControlRegister(void) ;
    void    PeristalticTimer_WriteControlRegister(uint8 control) ;
#endif /* (!PeristalticTimer_UDB_CONTROL_REG_REMOVED) */

uint16  PeristalticTimer_ReadPeriod(void) ;
void    PeristalticTimer_WritePeriod(uint16 period) ;
uint16  PeristalticTimer_ReadCounter(void) ;
void    PeristalticTimer_WriteCounter(uint16 counter) ;
uint16  PeristalticTimer_ReadCapture(void) ;
void    PeristalticTimer_SoftwareCapture(void) ;

#if(!PeristalticTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (PeristalticTimer_SoftwareCaptureMode)
        void    PeristalticTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!PeristalticTimer_UsingFixedFunction) */

    #if (PeristalticTimer_SoftwareTriggerMode)
        void    PeristalticTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (PeristalticTimer_SoftwareTriggerMode) */

    #if (PeristalticTimer_EnableTriggerMode)
        void    PeristalticTimer_EnableTrigger(void) ;
        void    PeristalticTimer_DisableTrigger(void) ;
    #endif /* (PeristalticTimer_EnableTriggerMode) */


    #if(PeristalticTimer_InterruptOnCaptureCount)
        void    PeristalticTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (PeristalticTimer_InterruptOnCaptureCount) */

    #if (PeristalticTimer_UsingHWCaptureCounter)
        void    PeristalticTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   PeristalticTimer_ReadCaptureCount(void) ;
    #endif /* (PeristalticTimer_UsingHWCaptureCounter) */

    void PeristalticTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void PeristalticTimer_Init(void)          ;
void PeristalticTimer_Enable(void)        ;
void PeristalticTimer_SaveConfig(void)    ;
void PeristalticTimer_RestoreConfig(void) ;
void PeristalticTimer_Sleep(void)         ;
void PeristalticTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define PeristalticTimer__B_TIMER__CM_NONE 0
#define PeristalticTimer__B_TIMER__CM_RISINGEDGE 1
#define PeristalticTimer__B_TIMER__CM_FALLINGEDGE 2
#define PeristalticTimer__B_TIMER__CM_EITHEREDGE 3
#define PeristalticTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define PeristalticTimer__B_TIMER__TM_NONE 0x00u
#define PeristalticTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define PeristalticTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define PeristalticTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define PeristalticTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define PeristalticTimer_INIT_PERIOD             65535u
#define PeristalticTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << PeristalticTimer_CTRL_CAP_MODE_SHIFT))
#define PeristalticTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << PeristalticTimer_CTRL_TRIG_MODE_SHIFT))
#if (PeristalticTimer_UsingFixedFunction)
    #define PeristalticTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << PeristalticTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << PeristalticTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define PeristalticTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << PeristalticTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << PeristalticTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << PeristalticTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (PeristalticTimer_UsingFixedFunction) */
#define PeristalticTimer_INIT_CAPTURE_COUNT      (2u)
#define PeristalticTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << PeristalticTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (PeristalticTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define PeristalticTimer_STATUS         (*(reg8 *) PeristalticTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define PeristalticTimer_STATUS_MASK    (*(reg8 *) PeristalticTimer_TimerHW__SR0 )
    #define PeristalticTimer_CONTROL        (*(reg8 *) PeristalticTimer_TimerHW__CFG0)
    #define PeristalticTimer_CONTROL2       (*(reg8 *) PeristalticTimer_TimerHW__CFG1)
    #define PeristalticTimer_CONTROL2_PTR   ( (reg8 *) PeristalticTimer_TimerHW__CFG1)
    #define PeristalticTimer_RT1            (*(reg8 *) PeristalticTimer_TimerHW__RT1)
    #define PeristalticTimer_RT1_PTR        ( (reg8 *) PeristalticTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define PeristalticTimer_CONTROL3       (*(reg8 *) PeristalticTimer_TimerHW__CFG2)
        #define PeristalticTimer_CONTROL3_PTR   ( (reg8 *) PeristalticTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define PeristalticTimer_GLOBAL_ENABLE  (*(reg8 *) PeristalticTimer_TimerHW__PM_ACT_CFG)
    #define PeristalticTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) PeristalticTimer_TimerHW__PM_STBY_CFG)

    #define PeristalticTimer_CAPTURE_LSB         (* (reg16 *) PeristalticTimer_TimerHW__CAP0 )
    #define PeristalticTimer_CAPTURE_LSB_PTR       ((reg16 *) PeristalticTimer_TimerHW__CAP0 )
    #define PeristalticTimer_PERIOD_LSB          (* (reg16 *) PeristalticTimer_TimerHW__PER0 )
    #define PeristalticTimer_PERIOD_LSB_PTR        ((reg16 *) PeristalticTimer_TimerHW__PER0 )
    #define PeristalticTimer_COUNTER_LSB         (* (reg16 *) PeristalticTimer_TimerHW__CNT_CMP0 )
    #define PeristalticTimer_COUNTER_LSB_PTR       ((reg16 *) PeristalticTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define PeristalticTimer_BLOCK_EN_MASK                     PeristalticTimer_TimerHW__PM_ACT_MSK
    #define PeristalticTimer_BLOCK_STBY_EN_MASK                PeristalticTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define PeristalticTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define PeristalticTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define PeristalticTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define PeristalticTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define PeristalticTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define PeristalticTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << PeristalticTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define PeristalticTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define PeristalticTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << PeristalticTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define PeristalticTimer_CTRL_MODE_SHIFT                 0x01u
        #define PeristalticTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << PeristalticTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define PeristalticTimer_CTRL_RCOD_SHIFT        0x02u
        #define PeristalticTimer_CTRL_ENBL_SHIFT        0x00u
        #define PeristalticTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define PeristalticTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << PeristalticTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define PeristalticTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << PeristalticTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define PeristalticTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << PeristalticTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define PeristalticTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << PeristalticTimer_CTRL_RCOD_SHIFT))
        #define PeristalticTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << PeristalticTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define PeristalticTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define PeristalticTimer_RT1_MASK                        ((uint8)((uint8)0x03u << PeristalticTimer_RT1_SHIFT))
    #define PeristalticTimer_SYNC                            ((uint8)((uint8)0x03u << PeristalticTimer_RT1_SHIFT))
    #define PeristalticTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define PeristalticTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << PeristalticTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define PeristalticTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << PeristalticTimer_SYNCDSI_SHIFT))

    #define PeristalticTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << PeristalticTimer_CTRL_MODE_SHIFT))
    #define PeristalticTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << PeristalticTimer_CTRL_MODE_SHIFT))
    #define PeristalticTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << PeristalticTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define PeristalticTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define PeristalticTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define PeristalticTimer_STATUS_TC_INT_MASK_SHIFT        (PeristalticTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define PeristalticTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (PeristalticTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define PeristalticTimer_STATUS_TC                       ((uint8)((uint8)0x01u << PeristalticTimer_STATUS_TC_SHIFT))
    #define PeristalticTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << PeristalticTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define PeristalticTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << PeristalticTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define PeristalticTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << PeristalticTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define PeristalticTimer_STATUS              (* (reg8 *) PeristalticTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define PeristalticTimer_STATUS_MASK         (* (reg8 *) PeristalticTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define PeristalticTimer_STATUS_AUX_CTRL     (* (reg8 *) PeristalticTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define PeristalticTimer_CONTROL             (* (reg8 *) PeristalticTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(PeristalticTimer_Resolution <= 8u) /* 8-bit Timer */
        #define PeristalticTimer_CAPTURE_LSB         (* (reg8 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define PeristalticTimer_CAPTURE_LSB_PTR       ((reg8 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define PeristalticTimer_PERIOD_LSB          (* (reg8 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define PeristalticTimer_PERIOD_LSB_PTR        ((reg8 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define PeristalticTimer_COUNTER_LSB         (* (reg8 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define PeristalticTimer_COUNTER_LSB_PTR       ((reg8 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(PeristalticTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define PeristalticTimer_CAPTURE_LSB         (* (reg16 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define PeristalticTimer_CAPTURE_LSB_PTR       ((reg16 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define PeristalticTimer_PERIOD_LSB          (* (reg16 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define PeristalticTimer_PERIOD_LSB_PTR        ((reg16 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define PeristalticTimer_COUNTER_LSB         (* (reg16 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define PeristalticTimer_COUNTER_LSB_PTR       ((reg16 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define PeristalticTimer_CAPTURE_LSB         (* (reg16 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define PeristalticTimer_CAPTURE_LSB_PTR       ((reg16 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define PeristalticTimer_PERIOD_LSB          (* (reg16 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define PeristalticTimer_PERIOD_LSB_PTR        ((reg16 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define PeristalticTimer_COUNTER_LSB         (* (reg16 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define PeristalticTimer_COUNTER_LSB_PTR       ((reg16 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(PeristalticTimer_Resolution <= 24u)/* 24-bit Timer */
        #define PeristalticTimer_CAPTURE_LSB         (* (reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define PeristalticTimer_CAPTURE_LSB_PTR       ((reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define PeristalticTimer_PERIOD_LSB          (* (reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define PeristalticTimer_PERIOD_LSB_PTR        ((reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define PeristalticTimer_COUNTER_LSB         (* (reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define PeristalticTimer_COUNTER_LSB_PTR       ((reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define PeristalticTimer_CAPTURE_LSB         (* (reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define PeristalticTimer_CAPTURE_LSB_PTR       ((reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define PeristalticTimer_PERIOD_LSB          (* (reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define PeristalticTimer_PERIOD_LSB_PTR        ((reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define PeristalticTimer_COUNTER_LSB         (* (reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define PeristalticTimer_COUNTER_LSB_PTR       ((reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define PeristalticTimer_CAPTURE_LSB         (* (reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define PeristalticTimer_CAPTURE_LSB_PTR       ((reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define PeristalticTimer_PERIOD_LSB          (* (reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define PeristalticTimer_PERIOD_LSB_PTR        ((reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define PeristalticTimer_COUNTER_LSB         (* (reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define PeristalticTimer_COUNTER_LSB_PTR       ((reg32 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define PeristalticTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) PeristalticTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (PeristalticTimer_UsingHWCaptureCounter)
        #define PeristalticTimer_CAP_COUNT              (*(reg8 *) PeristalticTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define PeristalticTimer_CAP_COUNT_PTR          ( (reg8 *) PeristalticTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define PeristalticTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) PeristalticTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define PeristalticTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) PeristalticTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (PeristalticTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define PeristalticTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define PeristalticTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define PeristalticTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define PeristalticTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define PeristalticTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define PeristalticTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << PeristalticTimer_CTRL_INTCNT_SHIFT))
    #define PeristalticTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << PeristalticTimer_CTRL_TRIG_MODE_SHIFT))
    #define PeristalticTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << PeristalticTimer_CTRL_TRIG_EN_SHIFT))
    #define PeristalticTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << PeristalticTimer_CTRL_CAP_MODE_SHIFT))
    #define PeristalticTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << PeristalticTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define PeristalticTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define PeristalticTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define PeristalticTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define PeristalticTimer_STATUS_TC_INT_MASK_SHIFT       PeristalticTimer_STATUS_TC_SHIFT
    #define PeristalticTimer_STATUS_CAPTURE_INT_MASK_SHIFT  PeristalticTimer_STATUS_CAPTURE_SHIFT
    #define PeristalticTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define PeristalticTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define PeristalticTimer_STATUS_FIFOFULL_INT_MASK_SHIFT PeristalticTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define PeristalticTimer_STATUS_TC                      ((uint8)((uint8)0x01u << PeristalticTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define PeristalticTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << PeristalticTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define PeristalticTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << PeristalticTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define PeristalticTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << PeristalticTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define PeristalticTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << PeristalticTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define PeristalticTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << PeristalticTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define PeristalticTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << PeristalticTimer_STATUS_FIFOFULL_SHIFT))

    #define PeristalticTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define PeristalticTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define PeristalticTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define PeristalticTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define PeristalticTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define PeristalticTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_PeristalticTimer_H */


/* [] END OF FILE */
