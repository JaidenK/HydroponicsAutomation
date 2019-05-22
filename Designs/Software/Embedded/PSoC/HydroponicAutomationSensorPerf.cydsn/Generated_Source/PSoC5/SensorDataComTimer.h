/*******************************************************************************
* File Name: SensorDataComTimer.h
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

#if !defined(CY_TIMER_SensorDataComTimer_H)
#define CY_TIMER_SensorDataComTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 SensorDataComTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define SensorDataComTimer_Resolution                 24u
#define SensorDataComTimer_UsingFixedFunction         0u
#define SensorDataComTimer_UsingHWCaptureCounter      0u
#define SensorDataComTimer_SoftwareCaptureMode        0u
#define SensorDataComTimer_SoftwareTriggerMode        0u
#define SensorDataComTimer_UsingHWEnable              0u
#define SensorDataComTimer_EnableTriggerMode          0u
#define SensorDataComTimer_InterruptOnCaptureCount    0u
#define SensorDataComTimer_RunModeUsed                1u
#define SensorDataComTimer_ControlRegRemoved          0u

#if defined(SensorDataComTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define SensorDataComTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (SensorDataComTimer_UsingFixedFunction)
    #define SensorDataComTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define SensorDataComTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End SensorDataComTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!SensorDataComTimer_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (SensorDataComTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!SensorDataComTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}SensorDataComTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    SensorDataComTimer_Start(void) ;
void    SensorDataComTimer_Stop(void) ;

void    SensorDataComTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   SensorDataComTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define SensorDataComTimer_GetInterruptSource() SensorDataComTimer_ReadStatusRegister()

#if(!SensorDataComTimer_UDB_CONTROL_REG_REMOVED)
    uint8   SensorDataComTimer_ReadControlRegister(void) ;
    void    SensorDataComTimer_WriteControlRegister(uint8 control) ;
#endif /* (!SensorDataComTimer_UDB_CONTROL_REG_REMOVED) */

uint32  SensorDataComTimer_ReadPeriod(void) ;
void    SensorDataComTimer_WritePeriod(uint32 period) ;
uint32  SensorDataComTimer_ReadCounter(void) ;
void    SensorDataComTimer_WriteCounter(uint32 counter) ;
uint32  SensorDataComTimer_ReadCapture(void) ;
void    SensorDataComTimer_SoftwareCapture(void) ;

#if(!SensorDataComTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (SensorDataComTimer_SoftwareCaptureMode)
        void    SensorDataComTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!SensorDataComTimer_UsingFixedFunction) */

    #if (SensorDataComTimer_SoftwareTriggerMode)
        void    SensorDataComTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (SensorDataComTimer_SoftwareTriggerMode) */

    #if (SensorDataComTimer_EnableTriggerMode)
        void    SensorDataComTimer_EnableTrigger(void) ;
        void    SensorDataComTimer_DisableTrigger(void) ;
    #endif /* (SensorDataComTimer_EnableTriggerMode) */


    #if(SensorDataComTimer_InterruptOnCaptureCount)
        void    SensorDataComTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (SensorDataComTimer_InterruptOnCaptureCount) */

    #if (SensorDataComTimer_UsingHWCaptureCounter)
        void    SensorDataComTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   SensorDataComTimer_ReadCaptureCount(void) ;
    #endif /* (SensorDataComTimer_UsingHWCaptureCounter) */

    void SensorDataComTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void SensorDataComTimer_Init(void)          ;
void SensorDataComTimer_Enable(void)        ;
void SensorDataComTimer_SaveConfig(void)    ;
void SensorDataComTimer_RestoreConfig(void) ;
void SensorDataComTimer_Sleep(void)         ;
void SensorDataComTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define SensorDataComTimer__B_TIMER__CM_NONE 0
#define SensorDataComTimer__B_TIMER__CM_RISINGEDGE 1
#define SensorDataComTimer__B_TIMER__CM_FALLINGEDGE 2
#define SensorDataComTimer__B_TIMER__CM_EITHEREDGE 3
#define SensorDataComTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define SensorDataComTimer__B_TIMER__TM_NONE 0x00u
#define SensorDataComTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define SensorDataComTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define SensorDataComTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define SensorDataComTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define SensorDataComTimer_INIT_PERIOD             19999u
#define SensorDataComTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << SensorDataComTimer_CTRL_CAP_MODE_SHIFT))
#define SensorDataComTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << SensorDataComTimer_CTRL_TRIG_MODE_SHIFT))
#if (SensorDataComTimer_UsingFixedFunction)
    #define SensorDataComTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << SensorDataComTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << SensorDataComTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define SensorDataComTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << SensorDataComTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << SensorDataComTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << SensorDataComTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (SensorDataComTimer_UsingFixedFunction) */
#define SensorDataComTimer_INIT_CAPTURE_COUNT      (2u)
#define SensorDataComTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << SensorDataComTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (SensorDataComTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define SensorDataComTimer_STATUS         (*(reg8 *) SensorDataComTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define SensorDataComTimer_STATUS_MASK    (*(reg8 *) SensorDataComTimer_TimerHW__SR0 )
    #define SensorDataComTimer_CONTROL        (*(reg8 *) SensorDataComTimer_TimerHW__CFG0)
    #define SensorDataComTimer_CONTROL2       (*(reg8 *) SensorDataComTimer_TimerHW__CFG1)
    #define SensorDataComTimer_CONTROL2_PTR   ( (reg8 *) SensorDataComTimer_TimerHW__CFG1)
    #define SensorDataComTimer_RT1            (*(reg8 *) SensorDataComTimer_TimerHW__RT1)
    #define SensorDataComTimer_RT1_PTR        ( (reg8 *) SensorDataComTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define SensorDataComTimer_CONTROL3       (*(reg8 *) SensorDataComTimer_TimerHW__CFG2)
        #define SensorDataComTimer_CONTROL3_PTR   ( (reg8 *) SensorDataComTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define SensorDataComTimer_GLOBAL_ENABLE  (*(reg8 *) SensorDataComTimer_TimerHW__PM_ACT_CFG)
    #define SensorDataComTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) SensorDataComTimer_TimerHW__PM_STBY_CFG)

    #define SensorDataComTimer_CAPTURE_LSB         (* (reg16 *) SensorDataComTimer_TimerHW__CAP0 )
    #define SensorDataComTimer_CAPTURE_LSB_PTR       ((reg16 *) SensorDataComTimer_TimerHW__CAP0 )
    #define SensorDataComTimer_PERIOD_LSB          (* (reg16 *) SensorDataComTimer_TimerHW__PER0 )
    #define SensorDataComTimer_PERIOD_LSB_PTR        ((reg16 *) SensorDataComTimer_TimerHW__PER0 )
    #define SensorDataComTimer_COUNTER_LSB         (* (reg16 *) SensorDataComTimer_TimerHW__CNT_CMP0 )
    #define SensorDataComTimer_COUNTER_LSB_PTR       ((reg16 *) SensorDataComTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define SensorDataComTimer_BLOCK_EN_MASK                     SensorDataComTimer_TimerHW__PM_ACT_MSK
    #define SensorDataComTimer_BLOCK_STBY_EN_MASK                SensorDataComTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define SensorDataComTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define SensorDataComTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define SensorDataComTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define SensorDataComTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define SensorDataComTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define SensorDataComTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << SensorDataComTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define SensorDataComTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define SensorDataComTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << SensorDataComTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define SensorDataComTimer_CTRL_MODE_SHIFT                 0x01u
        #define SensorDataComTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << SensorDataComTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define SensorDataComTimer_CTRL_RCOD_SHIFT        0x02u
        #define SensorDataComTimer_CTRL_ENBL_SHIFT        0x00u
        #define SensorDataComTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define SensorDataComTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << SensorDataComTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define SensorDataComTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << SensorDataComTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define SensorDataComTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << SensorDataComTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define SensorDataComTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << SensorDataComTimer_CTRL_RCOD_SHIFT))
        #define SensorDataComTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << SensorDataComTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define SensorDataComTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define SensorDataComTimer_RT1_MASK                        ((uint8)((uint8)0x03u << SensorDataComTimer_RT1_SHIFT))
    #define SensorDataComTimer_SYNC                            ((uint8)((uint8)0x03u << SensorDataComTimer_RT1_SHIFT))
    #define SensorDataComTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define SensorDataComTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << SensorDataComTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define SensorDataComTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << SensorDataComTimer_SYNCDSI_SHIFT))

    #define SensorDataComTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << SensorDataComTimer_CTRL_MODE_SHIFT))
    #define SensorDataComTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << SensorDataComTimer_CTRL_MODE_SHIFT))
    #define SensorDataComTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << SensorDataComTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define SensorDataComTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define SensorDataComTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define SensorDataComTimer_STATUS_TC_INT_MASK_SHIFT        (SensorDataComTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define SensorDataComTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (SensorDataComTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define SensorDataComTimer_STATUS_TC                       ((uint8)((uint8)0x01u << SensorDataComTimer_STATUS_TC_SHIFT))
    #define SensorDataComTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << SensorDataComTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define SensorDataComTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << SensorDataComTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define SensorDataComTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << SensorDataComTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define SensorDataComTimer_STATUS              (* (reg8 *) SensorDataComTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define SensorDataComTimer_STATUS_MASK         (* (reg8 *) SensorDataComTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define SensorDataComTimer_STATUS_AUX_CTRL     (* (reg8 *) SensorDataComTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define SensorDataComTimer_CONTROL             (* (reg8 *) SensorDataComTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(SensorDataComTimer_Resolution <= 8u) /* 8-bit Timer */
        #define SensorDataComTimer_CAPTURE_LSB         (* (reg8 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define SensorDataComTimer_CAPTURE_LSB_PTR       ((reg8 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define SensorDataComTimer_PERIOD_LSB          (* (reg8 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define SensorDataComTimer_PERIOD_LSB_PTR        ((reg8 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define SensorDataComTimer_COUNTER_LSB         (* (reg8 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define SensorDataComTimer_COUNTER_LSB_PTR       ((reg8 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
    #elif(SensorDataComTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define SensorDataComTimer_CAPTURE_LSB         (* (reg16 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define SensorDataComTimer_CAPTURE_LSB_PTR       ((reg16 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define SensorDataComTimer_PERIOD_LSB          (* (reg16 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define SensorDataComTimer_PERIOD_LSB_PTR        ((reg16 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define SensorDataComTimer_COUNTER_LSB         (* (reg16 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define SensorDataComTimer_COUNTER_LSB_PTR       ((reg16 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define SensorDataComTimer_CAPTURE_LSB         (* (reg16 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define SensorDataComTimer_CAPTURE_LSB_PTR       ((reg16 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define SensorDataComTimer_PERIOD_LSB          (* (reg16 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define SensorDataComTimer_PERIOD_LSB_PTR        ((reg16 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define SensorDataComTimer_COUNTER_LSB         (* (reg16 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
            #define SensorDataComTimer_COUNTER_LSB_PTR       ((reg16 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(SensorDataComTimer_Resolution <= 24u)/* 24-bit Timer */
        #define SensorDataComTimer_CAPTURE_LSB         (* (reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define SensorDataComTimer_CAPTURE_LSB_PTR       ((reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define SensorDataComTimer_PERIOD_LSB          (* (reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define SensorDataComTimer_PERIOD_LSB_PTR        ((reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define SensorDataComTimer_COUNTER_LSB         (* (reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define SensorDataComTimer_COUNTER_LSB_PTR       ((reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define SensorDataComTimer_CAPTURE_LSB         (* (reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define SensorDataComTimer_CAPTURE_LSB_PTR       ((reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define SensorDataComTimer_PERIOD_LSB          (* (reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define SensorDataComTimer_PERIOD_LSB_PTR        ((reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define SensorDataComTimer_COUNTER_LSB         (* (reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define SensorDataComTimer_COUNTER_LSB_PTR       ((reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define SensorDataComTimer_CAPTURE_LSB         (* (reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define SensorDataComTimer_CAPTURE_LSB_PTR       ((reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define SensorDataComTimer_PERIOD_LSB          (* (reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define SensorDataComTimer_PERIOD_LSB_PTR        ((reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define SensorDataComTimer_COUNTER_LSB         (* (reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
            #define SensorDataComTimer_COUNTER_LSB_PTR       ((reg32 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define SensorDataComTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) SensorDataComTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
    
    #if (SensorDataComTimer_UsingHWCaptureCounter)
        #define SensorDataComTimer_CAP_COUNT              (*(reg8 *) SensorDataComTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define SensorDataComTimer_CAP_COUNT_PTR          ( (reg8 *) SensorDataComTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define SensorDataComTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) SensorDataComTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define SensorDataComTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) SensorDataComTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (SensorDataComTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define SensorDataComTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define SensorDataComTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define SensorDataComTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define SensorDataComTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define SensorDataComTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define SensorDataComTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << SensorDataComTimer_CTRL_INTCNT_SHIFT))
    #define SensorDataComTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << SensorDataComTimer_CTRL_TRIG_MODE_SHIFT))
    #define SensorDataComTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << SensorDataComTimer_CTRL_TRIG_EN_SHIFT))
    #define SensorDataComTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << SensorDataComTimer_CTRL_CAP_MODE_SHIFT))
    #define SensorDataComTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << SensorDataComTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define SensorDataComTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define SensorDataComTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define SensorDataComTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define SensorDataComTimer_STATUS_TC_INT_MASK_SHIFT       SensorDataComTimer_STATUS_TC_SHIFT
    #define SensorDataComTimer_STATUS_CAPTURE_INT_MASK_SHIFT  SensorDataComTimer_STATUS_CAPTURE_SHIFT
    #define SensorDataComTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define SensorDataComTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define SensorDataComTimer_STATUS_FIFOFULL_INT_MASK_SHIFT SensorDataComTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define SensorDataComTimer_STATUS_TC                      ((uint8)((uint8)0x01u << SensorDataComTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define SensorDataComTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << SensorDataComTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define SensorDataComTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << SensorDataComTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define SensorDataComTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << SensorDataComTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define SensorDataComTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << SensorDataComTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define SensorDataComTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << SensorDataComTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define SensorDataComTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << SensorDataComTimer_STATUS_FIFOFULL_SHIFT))

    #define SensorDataComTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define SensorDataComTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define SensorDataComTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define SensorDataComTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define SensorDataComTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define SensorDataComTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_SensorDataComTimer_H */


/* [] END OF FILE */
