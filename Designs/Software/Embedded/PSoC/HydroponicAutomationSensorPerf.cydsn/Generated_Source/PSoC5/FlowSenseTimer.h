/*******************************************************************************
* File Name: FlowSenseTimer.h
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

#if !defined(CY_TIMER_FlowSenseTimer_H)
#define CY_TIMER_FlowSenseTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 FlowSenseTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define FlowSenseTimer_Resolution                 16u
#define FlowSenseTimer_UsingFixedFunction         0u
#define FlowSenseTimer_UsingHWCaptureCounter      1u
#define FlowSenseTimer_SoftwareCaptureMode        0u
#define FlowSenseTimer_SoftwareTriggerMode        0u
#define FlowSenseTimer_UsingHWEnable              0u
#define FlowSenseTimer_EnableTriggerMode          0u
#define FlowSenseTimer_InterruptOnCaptureCount    1u
#define FlowSenseTimer_RunModeUsed                0u
#define FlowSenseTimer_ControlRegRemoved          0u

#if defined(FlowSenseTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define FlowSenseTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (FlowSenseTimer_UsingFixedFunction)
    #define FlowSenseTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define FlowSenseTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End FlowSenseTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!FlowSenseTimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (FlowSenseTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!FlowSenseTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}FlowSenseTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    FlowSenseTimer_Start(void) ;
void    FlowSenseTimer_Stop(void) ;

void    FlowSenseTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   FlowSenseTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define FlowSenseTimer_GetInterruptSource() FlowSenseTimer_ReadStatusRegister()

#if(!FlowSenseTimer_UDB_CONTROL_REG_REMOVED)
    uint8   FlowSenseTimer_ReadControlRegister(void) ;
    void    FlowSenseTimer_WriteControlRegister(uint8 control) ;
#endif /* (!FlowSenseTimer_UDB_CONTROL_REG_REMOVED) */

uint16  FlowSenseTimer_ReadPeriod(void) ;
void    FlowSenseTimer_WritePeriod(uint16 period) ;
uint16  FlowSenseTimer_ReadCounter(void) ;
void    FlowSenseTimer_WriteCounter(uint16 counter) ;
uint16  FlowSenseTimer_ReadCapture(void) ;
void    FlowSenseTimer_SoftwareCapture(void) ;

#if(!FlowSenseTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (FlowSenseTimer_SoftwareCaptureMode)
        void    FlowSenseTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!FlowSenseTimer_UsingFixedFunction) */

    #if (FlowSenseTimer_SoftwareTriggerMode)
        void    FlowSenseTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (FlowSenseTimer_SoftwareTriggerMode) */

    #if (FlowSenseTimer_EnableTriggerMode)
        void    FlowSenseTimer_EnableTrigger(void) ;
        void    FlowSenseTimer_DisableTrigger(void) ;
    #endif /* (FlowSenseTimer_EnableTriggerMode) */


    #if(FlowSenseTimer_InterruptOnCaptureCount)
        void    FlowSenseTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (FlowSenseTimer_InterruptOnCaptureCount) */

    #if (FlowSenseTimer_UsingHWCaptureCounter)
        void    FlowSenseTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   FlowSenseTimer_ReadCaptureCount(void) ;
    #endif /* (FlowSenseTimer_UsingHWCaptureCounter) */

    void FlowSenseTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void FlowSenseTimer_Init(void)          ;
void FlowSenseTimer_Enable(void)        ;
void FlowSenseTimer_SaveConfig(void)    ;
void FlowSenseTimer_RestoreConfig(void) ;
void FlowSenseTimer_Sleep(void)         ;
void FlowSenseTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define FlowSenseTimer__B_TIMER__CM_NONE 0
#define FlowSenseTimer__B_TIMER__CM_RISINGEDGE 1
#define FlowSenseTimer__B_TIMER__CM_FALLINGEDGE 2
#define FlowSenseTimer__B_TIMER__CM_EITHEREDGE 3
#define FlowSenseTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define FlowSenseTimer__B_TIMER__TM_NONE 0x00u
#define FlowSenseTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define FlowSenseTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define FlowSenseTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define FlowSenseTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define FlowSenseTimer_INIT_PERIOD             65535u
#define FlowSenseTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << FlowSenseTimer_CTRL_CAP_MODE_SHIFT))
#define FlowSenseTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << FlowSenseTimer_CTRL_TRIG_MODE_SHIFT))
#if (FlowSenseTimer_UsingFixedFunction)
    #define FlowSenseTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << FlowSenseTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)1 << FlowSenseTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define FlowSenseTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << FlowSenseTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)1 << FlowSenseTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << FlowSenseTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (FlowSenseTimer_UsingFixedFunction) */
#define FlowSenseTimer_INIT_CAPTURE_COUNT      (4u)
#define FlowSenseTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(4u - 1u) << FlowSenseTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (FlowSenseTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define FlowSenseTimer_STATUS         (*(reg8 *) FlowSenseTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define FlowSenseTimer_STATUS_MASK    (*(reg8 *) FlowSenseTimer_TimerHW__SR0 )
    #define FlowSenseTimer_CONTROL        (*(reg8 *) FlowSenseTimer_TimerHW__CFG0)
    #define FlowSenseTimer_CONTROL2       (*(reg8 *) FlowSenseTimer_TimerHW__CFG1)
    #define FlowSenseTimer_CONTROL2_PTR   ( (reg8 *) FlowSenseTimer_TimerHW__CFG1)
    #define FlowSenseTimer_RT1            (*(reg8 *) FlowSenseTimer_TimerHW__RT1)
    #define FlowSenseTimer_RT1_PTR        ( (reg8 *) FlowSenseTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define FlowSenseTimer_CONTROL3       (*(reg8 *) FlowSenseTimer_TimerHW__CFG2)
        #define FlowSenseTimer_CONTROL3_PTR   ( (reg8 *) FlowSenseTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define FlowSenseTimer_GLOBAL_ENABLE  (*(reg8 *) FlowSenseTimer_TimerHW__PM_ACT_CFG)
    #define FlowSenseTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) FlowSenseTimer_TimerHW__PM_STBY_CFG)

    #define FlowSenseTimer_CAPTURE_LSB         (* (reg16 *) FlowSenseTimer_TimerHW__CAP0 )
    #define FlowSenseTimer_CAPTURE_LSB_PTR       ((reg16 *) FlowSenseTimer_TimerHW__CAP0 )
    #define FlowSenseTimer_PERIOD_LSB          (* (reg16 *) FlowSenseTimer_TimerHW__PER0 )
    #define FlowSenseTimer_PERIOD_LSB_PTR        ((reg16 *) FlowSenseTimer_TimerHW__PER0 )
    #define FlowSenseTimer_COUNTER_LSB         (* (reg16 *) FlowSenseTimer_TimerHW__CNT_CMP0 )
    #define FlowSenseTimer_COUNTER_LSB_PTR       ((reg16 *) FlowSenseTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define FlowSenseTimer_BLOCK_EN_MASK                     FlowSenseTimer_TimerHW__PM_ACT_MSK
    #define FlowSenseTimer_BLOCK_STBY_EN_MASK                FlowSenseTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define FlowSenseTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define FlowSenseTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define FlowSenseTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define FlowSenseTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define FlowSenseTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define FlowSenseTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << FlowSenseTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define FlowSenseTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define FlowSenseTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << FlowSenseTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define FlowSenseTimer_CTRL_MODE_SHIFT                 0x01u
        #define FlowSenseTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << FlowSenseTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define FlowSenseTimer_CTRL_RCOD_SHIFT        0x02u
        #define FlowSenseTimer_CTRL_ENBL_SHIFT        0x00u
        #define FlowSenseTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define FlowSenseTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << FlowSenseTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define FlowSenseTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << FlowSenseTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define FlowSenseTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << FlowSenseTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define FlowSenseTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << FlowSenseTimer_CTRL_RCOD_SHIFT))
        #define FlowSenseTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << FlowSenseTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define FlowSenseTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define FlowSenseTimer_RT1_MASK                        ((uint8)((uint8)0x03u << FlowSenseTimer_RT1_SHIFT))
    #define FlowSenseTimer_SYNC                            ((uint8)((uint8)0x03u << FlowSenseTimer_RT1_SHIFT))
    #define FlowSenseTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define FlowSenseTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << FlowSenseTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define FlowSenseTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << FlowSenseTimer_SYNCDSI_SHIFT))

    #define FlowSenseTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << FlowSenseTimer_CTRL_MODE_SHIFT))
    #define FlowSenseTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << FlowSenseTimer_CTRL_MODE_SHIFT))
    #define FlowSenseTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << FlowSenseTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define FlowSenseTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define FlowSenseTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define FlowSenseTimer_STATUS_TC_INT_MASK_SHIFT        (FlowSenseTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define FlowSenseTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (FlowSenseTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define FlowSenseTimer_STATUS_TC                       ((uint8)((uint8)0x01u << FlowSenseTimer_STATUS_TC_SHIFT))
    #define FlowSenseTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << FlowSenseTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define FlowSenseTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << FlowSenseTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define FlowSenseTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << FlowSenseTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define FlowSenseTimer_STATUS              (* (reg8 *) FlowSenseTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define FlowSenseTimer_STATUS_MASK         (* (reg8 *) FlowSenseTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define FlowSenseTimer_STATUS_AUX_CTRL     (* (reg8 *) FlowSenseTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define FlowSenseTimer_CONTROL             (* (reg8 *) FlowSenseTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(FlowSenseTimer_Resolution <= 8u) /* 8-bit Timer */
        #define FlowSenseTimer_CAPTURE_LSB         (* (reg8 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define FlowSenseTimer_CAPTURE_LSB_PTR       ((reg8 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define FlowSenseTimer_PERIOD_LSB          (* (reg8 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define FlowSenseTimer_PERIOD_LSB_PTR        ((reg8 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define FlowSenseTimer_COUNTER_LSB         (* (reg8 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define FlowSenseTimer_COUNTER_LSB_PTR       ((reg8 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(FlowSenseTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define FlowSenseTimer_CAPTURE_LSB         (* (reg16 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define FlowSenseTimer_CAPTURE_LSB_PTR       ((reg16 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define FlowSenseTimer_PERIOD_LSB          (* (reg16 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define FlowSenseTimer_PERIOD_LSB_PTR        ((reg16 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define FlowSenseTimer_COUNTER_LSB         (* (reg16 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define FlowSenseTimer_COUNTER_LSB_PTR       ((reg16 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define FlowSenseTimer_CAPTURE_LSB         (* (reg16 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define FlowSenseTimer_CAPTURE_LSB_PTR       ((reg16 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define FlowSenseTimer_PERIOD_LSB          (* (reg16 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define FlowSenseTimer_PERIOD_LSB_PTR        ((reg16 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define FlowSenseTimer_COUNTER_LSB         (* (reg16 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define FlowSenseTimer_COUNTER_LSB_PTR       ((reg16 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(FlowSenseTimer_Resolution <= 24u)/* 24-bit Timer */
        #define FlowSenseTimer_CAPTURE_LSB         (* (reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define FlowSenseTimer_CAPTURE_LSB_PTR       ((reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define FlowSenseTimer_PERIOD_LSB          (* (reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define FlowSenseTimer_PERIOD_LSB_PTR        ((reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define FlowSenseTimer_COUNTER_LSB         (* (reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define FlowSenseTimer_COUNTER_LSB_PTR       ((reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define FlowSenseTimer_CAPTURE_LSB         (* (reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define FlowSenseTimer_CAPTURE_LSB_PTR       ((reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define FlowSenseTimer_PERIOD_LSB          (* (reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define FlowSenseTimer_PERIOD_LSB_PTR        ((reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define FlowSenseTimer_COUNTER_LSB         (* (reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define FlowSenseTimer_COUNTER_LSB_PTR       ((reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define FlowSenseTimer_CAPTURE_LSB         (* (reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define FlowSenseTimer_CAPTURE_LSB_PTR       ((reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define FlowSenseTimer_PERIOD_LSB          (* (reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define FlowSenseTimer_PERIOD_LSB_PTR        ((reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define FlowSenseTimer_COUNTER_LSB         (* (reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define FlowSenseTimer_COUNTER_LSB_PTR       ((reg32 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define FlowSenseTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) FlowSenseTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (FlowSenseTimer_UsingHWCaptureCounter)
        #define FlowSenseTimer_CAP_COUNT              (*(reg8 *) FlowSenseTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define FlowSenseTimer_CAP_COUNT_PTR          ( (reg8 *) FlowSenseTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define FlowSenseTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) FlowSenseTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define FlowSenseTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) FlowSenseTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (FlowSenseTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define FlowSenseTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define FlowSenseTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define FlowSenseTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define FlowSenseTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define FlowSenseTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define FlowSenseTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << FlowSenseTimer_CTRL_INTCNT_SHIFT))
    #define FlowSenseTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << FlowSenseTimer_CTRL_TRIG_MODE_SHIFT))
    #define FlowSenseTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << FlowSenseTimer_CTRL_TRIG_EN_SHIFT))
    #define FlowSenseTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << FlowSenseTimer_CTRL_CAP_MODE_SHIFT))
    #define FlowSenseTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << FlowSenseTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define FlowSenseTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define FlowSenseTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define FlowSenseTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define FlowSenseTimer_STATUS_TC_INT_MASK_SHIFT       FlowSenseTimer_STATUS_TC_SHIFT
    #define FlowSenseTimer_STATUS_CAPTURE_INT_MASK_SHIFT  FlowSenseTimer_STATUS_CAPTURE_SHIFT
    #define FlowSenseTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define FlowSenseTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define FlowSenseTimer_STATUS_FIFOFULL_INT_MASK_SHIFT FlowSenseTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define FlowSenseTimer_STATUS_TC                      ((uint8)((uint8)0x01u << FlowSenseTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define FlowSenseTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << FlowSenseTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define FlowSenseTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << FlowSenseTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define FlowSenseTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << FlowSenseTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define FlowSenseTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << FlowSenseTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define FlowSenseTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << FlowSenseTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define FlowSenseTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << FlowSenseTimer_STATUS_FIFOFULL_SHIFT))

    #define FlowSenseTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define FlowSenseTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define FlowSenseTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define FlowSenseTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define FlowSenseTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define FlowSenseTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_FlowSenseTimer_H */


/* [] END OF FILE */
