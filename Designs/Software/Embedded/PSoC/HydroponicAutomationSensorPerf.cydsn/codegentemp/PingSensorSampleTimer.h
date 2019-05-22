/*******************************************************************************
* File Name: PingSensorSampleTimer.h
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

#if !defined(CY_TIMER_PingSensorSampleTimer_H)
#define CY_TIMER_PingSensorSampleTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 PingSensorSampleTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define PingSensorSampleTimer_Resolution                 24u
#define PingSensorSampleTimer_UsingFixedFunction         0u
#define PingSensorSampleTimer_UsingHWCaptureCounter      0u
#define PingSensorSampleTimer_SoftwareCaptureMode        0u
#define PingSensorSampleTimer_SoftwareTriggerMode        0u
#define PingSensorSampleTimer_UsingHWEnable              0u
#define PingSensorSampleTimer_EnableTriggerMode          0u
#define PingSensorSampleTimer_InterruptOnCaptureCount    0u
#define PingSensorSampleTimer_RunModeUsed                1u
#define PingSensorSampleTimer_ControlRegRemoved          0u

#if defined(PingSensorSampleTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define PingSensorSampleTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (PingSensorSampleTimer_UsingFixedFunction)
    #define PingSensorSampleTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define PingSensorSampleTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End PingSensorSampleTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!PingSensorSampleTimer_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (PingSensorSampleTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!PingSensorSampleTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}PingSensorSampleTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    PingSensorSampleTimer_Start(void) ;
void    PingSensorSampleTimer_Stop(void) ;

void    PingSensorSampleTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   PingSensorSampleTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define PingSensorSampleTimer_GetInterruptSource() PingSensorSampleTimer_ReadStatusRegister()

#if(!PingSensorSampleTimer_UDB_CONTROL_REG_REMOVED)
    uint8   PingSensorSampleTimer_ReadControlRegister(void) ;
    void    PingSensorSampleTimer_WriteControlRegister(uint8 control) ;
#endif /* (!PingSensorSampleTimer_UDB_CONTROL_REG_REMOVED) */

uint32  PingSensorSampleTimer_ReadPeriod(void) ;
void    PingSensorSampleTimer_WritePeriod(uint32 period) ;
uint32  PingSensorSampleTimer_ReadCounter(void) ;
void    PingSensorSampleTimer_WriteCounter(uint32 counter) ;
uint32  PingSensorSampleTimer_ReadCapture(void) ;
void    PingSensorSampleTimer_SoftwareCapture(void) ;

#if(!PingSensorSampleTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (PingSensorSampleTimer_SoftwareCaptureMode)
        void    PingSensorSampleTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!PingSensorSampleTimer_UsingFixedFunction) */

    #if (PingSensorSampleTimer_SoftwareTriggerMode)
        void    PingSensorSampleTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (PingSensorSampleTimer_SoftwareTriggerMode) */

    #if (PingSensorSampleTimer_EnableTriggerMode)
        void    PingSensorSampleTimer_EnableTrigger(void) ;
        void    PingSensorSampleTimer_DisableTrigger(void) ;
    #endif /* (PingSensorSampleTimer_EnableTriggerMode) */


    #if(PingSensorSampleTimer_InterruptOnCaptureCount)
        void    PingSensorSampleTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (PingSensorSampleTimer_InterruptOnCaptureCount) */

    #if (PingSensorSampleTimer_UsingHWCaptureCounter)
        void    PingSensorSampleTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   PingSensorSampleTimer_ReadCaptureCount(void) ;
    #endif /* (PingSensorSampleTimer_UsingHWCaptureCounter) */

    void PingSensorSampleTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void PingSensorSampleTimer_Init(void)          ;
void PingSensorSampleTimer_Enable(void)        ;
void PingSensorSampleTimer_SaveConfig(void)    ;
void PingSensorSampleTimer_RestoreConfig(void) ;
void PingSensorSampleTimer_Sleep(void)         ;
void PingSensorSampleTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define PingSensorSampleTimer__B_TIMER__CM_NONE 0
#define PingSensorSampleTimer__B_TIMER__CM_RISINGEDGE 1
#define PingSensorSampleTimer__B_TIMER__CM_FALLINGEDGE 2
#define PingSensorSampleTimer__B_TIMER__CM_EITHEREDGE 3
#define PingSensorSampleTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define PingSensorSampleTimer__B_TIMER__TM_NONE 0x00u
#define PingSensorSampleTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define PingSensorSampleTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define PingSensorSampleTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define PingSensorSampleTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define PingSensorSampleTimer_INIT_PERIOD             19999u
#define PingSensorSampleTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << PingSensorSampleTimer_CTRL_CAP_MODE_SHIFT))
#define PingSensorSampleTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << PingSensorSampleTimer_CTRL_TRIG_MODE_SHIFT))
#if (PingSensorSampleTimer_UsingFixedFunction)
    #define PingSensorSampleTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << PingSensorSampleTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << PingSensorSampleTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define PingSensorSampleTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << PingSensorSampleTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << PingSensorSampleTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << PingSensorSampleTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (PingSensorSampleTimer_UsingFixedFunction) */
#define PingSensorSampleTimer_INIT_CAPTURE_COUNT      (2u)
#define PingSensorSampleTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << PingSensorSampleTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (PingSensorSampleTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define PingSensorSampleTimer_STATUS         (*(reg8 *) PingSensorSampleTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define PingSensorSampleTimer_STATUS_MASK    (*(reg8 *) PingSensorSampleTimer_TimerHW__SR0 )
    #define PingSensorSampleTimer_CONTROL        (*(reg8 *) PingSensorSampleTimer_TimerHW__CFG0)
    #define PingSensorSampleTimer_CONTROL2       (*(reg8 *) PingSensorSampleTimer_TimerHW__CFG1)
    #define PingSensorSampleTimer_CONTROL2_PTR   ( (reg8 *) PingSensorSampleTimer_TimerHW__CFG1)
    #define PingSensorSampleTimer_RT1            (*(reg8 *) PingSensorSampleTimer_TimerHW__RT1)
    #define PingSensorSampleTimer_RT1_PTR        ( (reg8 *) PingSensorSampleTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define PingSensorSampleTimer_CONTROL3       (*(reg8 *) PingSensorSampleTimer_TimerHW__CFG2)
        #define PingSensorSampleTimer_CONTROL3_PTR   ( (reg8 *) PingSensorSampleTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define PingSensorSampleTimer_GLOBAL_ENABLE  (*(reg8 *) PingSensorSampleTimer_TimerHW__PM_ACT_CFG)
    #define PingSensorSampleTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) PingSensorSampleTimer_TimerHW__PM_STBY_CFG)

    #define PingSensorSampleTimer_CAPTURE_LSB         (* (reg16 *) PingSensorSampleTimer_TimerHW__CAP0 )
    #define PingSensorSampleTimer_CAPTURE_LSB_PTR       ((reg16 *) PingSensorSampleTimer_TimerHW__CAP0 )
    #define PingSensorSampleTimer_PERIOD_LSB          (* (reg16 *) PingSensorSampleTimer_TimerHW__PER0 )
    #define PingSensorSampleTimer_PERIOD_LSB_PTR        ((reg16 *) PingSensorSampleTimer_TimerHW__PER0 )
    #define PingSensorSampleTimer_COUNTER_LSB         (* (reg16 *) PingSensorSampleTimer_TimerHW__CNT_CMP0 )
    #define PingSensorSampleTimer_COUNTER_LSB_PTR       ((reg16 *) PingSensorSampleTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define PingSensorSampleTimer_BLOCK_EN_MASK                     PingSensorSampleTimer_TimerHW__PM_ACT_MSK
    #define PingSensorSampleTimer_BLOCK_STBY_EN_MASK                PingSensorSampleTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define PingSensorSampleTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define PingSensorSampleTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define PingSensorSampleTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define PingSensorSampleTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define PingSensorSampleTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define PingSensorSampleTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << PingSensorSampleTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define PingSensorSampleTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define PingSensorSampleTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << PingSensorSampleTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define PingSensorSampleTimer_CTRL_MODE_SHIFT                 0x01u
        #define PingSensorSampleTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << PingSensorSampleTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define PingSensorSampleTimer_CTRL_RCOD_SHIFT        0x02u
        #define PingSensorSampleTimer_CTRL_ENBL_SHIFT        0x00u
        #define PingSensorSampleTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define PingSensorSampleTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << PingSensorSampleTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define PingSensorSampleTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << PingSensorSampleTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define PingSensorSampleTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << PingSensorSampleTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define PingSensorSampleTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << PingSensorSampleTimer_CTRL_RCOD_SHIFT))
        #define PingSensorSampleTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << PingSensorSampleTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define PingSensorSampleTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define PingSensorSampleTimer_RT1_MASK                        ((uint8)((uint8)0x03u << PingSensorSampleTimer_RT1_SHIFT))
    #define PingSensorSampleTimer_SYNC                            ((uint8)((uint8)0x03u << PingSensorSampleTimer_RT1_SHIFT))
    #define PingSensorSampleTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define PingSensorSampleTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << PingSensorSampleTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define PingSensorSampleTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << PingSensorSampleTimer_SYNCDSI_SHIFT))

    #define PingSensorSampleTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << PingSensorSampleTimer_CTRL_MODE_SHIFT))
    #define PingSensorSampleTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << PingSensorSampleTimer_CTRL_MODE_SHIFT))
    #define PingSensorSampleTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << PingSensorSampleTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define PingSensorSampleTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define PingSensorSampleTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define PingSensorSampleTimer_STATUS_TC_INT_MASK_SHIFT        (PingSensorSampleTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define PingSensorSampleTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (PingSensorSampleTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define PingSensorSampleTimer_STATUS_TC                       ((uint8)((uint8)0x01u << PingSensorSampleTimer_STATUS_TC_SHIFT))
    #define PingSensorSampleTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << PingSensorSampleTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define PingSensorSampleTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << PingSensorSampleTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define PingSensorSampleTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << PingSensorSampleTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define PingSensorSampleTimer_STATUS              (* (reg8 *) PingSensorSampleTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define PingSensorSampleTimer_STATUS_MASK         (* (reg8 *) PingSensorSampleTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define PingSensorSampleTimer_STATUS_AUX_CTRL     (* (reg8 *) PingSensorSampleTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define PingSensorSampleTimer_CONTROL             (* (reg8 *) PingSensorSampleTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(PingSensorSampleTimer_Resolution <= 8u) /* 8-bit Timer */
        #define PingSensorSampleTimer_CAPTURE_LSB         (* (reg8 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define PingSensorSampleTimer_CAPTURE_LSB_PTR       ((reg8 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define PingSensorSampleTimer_PERIOD_LSB          (* (reg8 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define PingSensorSampleTimer_PERIOD_LSB_PTR        ((reg8 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define PingSensorSampleTimer_COUNTER_LSB         (* (reg8 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define PingSensorSampleTimer_COUNTER_LSB_PTR       ((reg8 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
    #elif(PingSensorSampleTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define PingSensorSampleTimer_CAPTURE_LSB         (* (reg16 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define PingSensorSampleTimer_CAPTURE_LSB_PTR       ((reg16 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define PingSensorSampleTimer_PERIOD_LSB          (* (reg16 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define PingSensorSampleTimer_PERIOD_LSB_PTR        ((reg16 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define PingSensorSampleTimer_COUNTER_LSB         (* (reg16 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define PingSensorSampleTimer_COUNTER_LSB_PTR       ((reg16 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define PingSensorSampleTimer_CAPTURE_LSB         (* (reg16 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define PingSensorSampleTimer_CAPTURE_LSB_PTR       ((reg16 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define PingSensorSampleTimer_PERIOD_LSB          (* (reg16 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define PingSensorSampleTimer_PERIOD_LSB_PTR        ((reg16 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define PingSensorSampleTimer_COUNTER_LSB         (* (reg16 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
            #define PingSensorSampleTimer_COUNTER_LSB_PTR       ((reg16 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(PingSensorSampleTimer_Resolution <= 24u)/* 24-bit Timer */
        #define PingSensorSampleTimer_CAPTURE_LSB         (* (reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define PingSensorSampleTimer_CAPTURE_LSB_PTR       ((reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define PingSensorSampleTimer_PERIOD_LSB          (* (reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define PingSensorSampleTimer_PERIOD_LSB_PTR        ((reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define PingSensorSampleTimer_COUNTER_LSB         (* (reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define PingSensorSampleTimer_COUNTER_LSB_PTR       ((reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define PingSensorSampleTimer_CAPTURE_LSB         (* (reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define PingSensorSampleTimer_CAPTURE_LSB_PTR       ((reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define PingSensorSampleTimer_PERIOD_LSB          (* (reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define PingSensorSampleTimer_PERIOD_LSB_PTR        ((reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define PingSensorSampleTimer_COUNTER_LSB         (* (reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define PingSensorSampleTimer_COUNTER_LSB_PTR       ((reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define PingSensorSampleTimer_CAPTURE_LSB         (* (reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define PingSensorSampleTimer_CAPTURE_LSB_PTR       ((reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define PingSensorSampleTimer_PERIOD_LSB          (* (reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define PingSensorSampleTimer_PERIOD_LSB_PTR        ((reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define PingSensorSampleTimer_COUNTER_LSB         (* (reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
            #define PingSensorSampleTimer_COUNTER_LSB_PTR       ((reg32 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define PingSensorSampleTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) PingSensorSampleTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
    
    #if (PingSensorSampleTimer_UsingHWCaptureCounter)
        #define PingSensorSampleTimer_CAP_COUNT              (*(reg8 *) PingSensorSampleTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define PingSensorSampleTimer_CAP_COUNT_PTR          ( (reg8 *) PingSensorSampleTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define PingSensorSampleTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) PingSensorSampleTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define PingSensorSampleTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) PingSensorSampleTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (PingSensorSampleTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define PingSensorSampleTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define PingSensorSampleTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define PingSensorSampleTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define PingSensorSampleTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define PingSensorSampleTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define PingSensorSampleTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << PingSensorSampleTimer_CTRL_INTCNT_SHIFT))
    #define PingSensorSampleTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << PingSensorSampleTimer_CTRL_TRIG_MODE_SHIFT))
    #define PingSensorSampleTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << PingSensorSampleTimer_CTRL_TRIG_EN_SHIFT))
    #define PingSensorSampleTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << PingSensorSampleTimer_CTRL_CAP_MODE_SHIFT))
    #define PingSensorSampleTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << PingSensorSampleTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define PingSensorSampleTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define PingSensorSampleTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define PingSensorSampleTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define PingSensorSampleTimer_STATUS_TC_INT_MASK_SHIFT       PingSensorSampleTimer_STATUS_TC_SHIFT
    #define PingSensorSampleTimer_STATUS_CAPTURE_INT_MASK_SHIFT  PingSensorSampleTimer_STATUS_CAPTURE_SHIFT
    #define PingSensorSampleTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define PingSensorSampleTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define PingSensorSampleTimer_STATUS_FIFOFULL_INT_MASK_SHIFT PingSensorSampleTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define PingSensorSampleTimer_STATUS_TC                      ((uint8)((uint8)0x01u << PingSensorSampleTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define PingSensorSampleTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << PingSensorSampleTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define PingSensorSampleTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << PingSensorSampleTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define PingSensorSampleTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << PingSensorSampleTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define PingSensorSampleTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << PingSensorSampleTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define PingSensorSampleTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << PingSensorSampleTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define PingSensorSampleTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << PingSensorSampleTimer_STATUS_FIFOFULL_SHIFT))

    #define PingSensorSampleTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define PingSensorSampleTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define PingSensorSampleTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define PingSensorSampleTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define PingSensorSampleTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define PingSensorSampleTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_PingSensorSampleTimer_H */


/* [] END OF FILE */
