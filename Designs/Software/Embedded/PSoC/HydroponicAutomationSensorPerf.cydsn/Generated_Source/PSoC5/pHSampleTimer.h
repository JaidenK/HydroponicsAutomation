/*******************************************************************************
* File Name: pHSampleTimer.h
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

#if !defined(CY_TIMER_pHSampleTimer_H)
#define CY_TIMER_pHSampleTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 pHSampleTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define pHSampleTimer_Resolution                 16u
#define pHSampleTimer_UsingFixedFunction         0u
#define pHSampleTimer_UsingHWCaptureCounter      0u
#define pHSampleTimer_SoftwareCaptureMode        0u
#define pHSampleTimer_SoftwareTriggerMode        0u
#define pHSampleTimer_UsingHWEnable              0u
#define pHSampleTimer_EnableTriggerMode          0u
#define pHSampleTimer_InterruptOnCaptureCount    0u
#define pHSampleTimer_RunModeUsed                1u
#define pHSampleTimer_ControlRegRemoved          0u

#if defined(pHSampleTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define pHSampleTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (pHSampleTimer_UsingFixedFunction)
    #define pHSampleTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define pHSampleTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End pHSampleTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!pHSampleTimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (pHSampleTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!pHSampleTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}pHSampleTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    pHSampleTimer_Start(void) ;
void    pHSampleTimer_Stop(void) ;

void    pHSampleTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   pHSampleTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define pHSampleTimer_GetInterruptSource() pHSampleTimer_ReadStatusRegister()

#if(!pHSampleTimer_UDB_CONTROL_REG_REMOVED)
    uint8   pHSampleTimer_ReadControlRegister(void) ;
    void    pHSampleTimer_WriteControlRegister(uint8 control) ;
#endif /* (!pHSampleTimer_UDB_CONTROL_REG_REMOVED) */

uint16  pHSampleTimer_ReadPeriod(void) ;
void    pHSampleTimer_WritePeriod(uint16 period) ;
uint16  pHSampleTimer_ReadCounter(void) ;
void    pHSampleTimer_WriteCounter(uint16 counter) ;
uint16  pHSampleTimer_ReadCapture(void) ;
void    pHSampleTimer_SoftwareCapture(void) ;

#if(!pHSampleTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (pHSampleTimer_SoftwareCaptureMode)
        void    pHSampleTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!pHSampleTimer_UsingFixedFunction) */

    #if (pHSampleTimer_SoftwareTriggerMode)
        void    pHSampleTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (pHSampleTimer_SoftwareTriggerMode) */

    #if (pHSampleTimer_EnableTriggerMode)
        void    pHSampleTimer_EnableTrigger(void) ;
        void    pHSampleTimer_DisableTrigger(void) ;
    #endif /* (pHSampleTimer_EnableTriggerMode) */


    #if(pHSampleTimer_InterruptOnCaptureCount)
        void    pHSampleTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (pHSampleTimer_InterruptOnCaptureCount) */

    #if (pHSampleTimer_UsingHWCaptureCounter)
        void    pHSampleTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   pHSampleTimer_ReadCaptureCount(void) ;
    #endif /* (pHSampleTimer_UsingHWCaptureCounter) */

    void pHSampleTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void pHSampleTimer_Init(void)          ;
void pHSampleTimer_Enable(void)        ;
void pHSampleTimer_SaveConfig(void)    ;
void pHSampleTimer_RestoreConfig(void) ;
void pHSampleTimer_Sleep(void)         ;
void pHSampleTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define pHSampleTimer__B_TIMER__CM_NONE 0
#define pHSampleTimer__B_TIMER__CM_RISINGEDGE 1
#define pHSampleTimer__B_TIMER__CM_FALLINGEDGE 2
#define pHSampleTimer__B_TIMER__CM_EITHEREDGE 3
#define pHSampleTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define pHSampleTimer__B_TIMER__TM_NONE 0x00u
#define pHSampleTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define pHSampleTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define pHSampleTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define pHSampleTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define pHSampleTimer_INIT_PERIOD             23999u
#define pHSampleTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << pHSampleTimer_CTRL_CAP_MODE_SHIFT))
#define pHSampleTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << pHSampleTimer_CTRL_TRIG_MODE_SHIFT))
#if (pHSampleTimer_UsingFixedFunction)
    #define pHSampleTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << pHSampleTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << pHSampleTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define pHSampleTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << pHSampleTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << pHSampleTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << pHSampleTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (pHSampleTimer_UsingFixedFunction) */
#define pHSampleTimer_INIT_CAPTURE_COUNT      (2u)
#define pHSampleTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << pHSampleTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (pHSampleTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define pHSampleTimer_STATUS         (*(reg8 *) pHSampleTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define pHSampleTimer_STATUS_MASK    (*(reg8 *) pHSampleTimer_TimerHW__SR0 )
    #define pHSampleTimer_CONTROL        (*(reg8 *) pHSampleTimer_TimerHW__CFG0)
    #define pHSampleTimer_CONTROL2       (*(reg8 *) pHSampleTimer_TimerHW__CFG1)
    #define pHSampleTimer_CONTROL2_PTR   ( (reg8 *) pHSampleTimer_TimerHW__CFG1)
    #define pHSampleTimer_RT1            (*(reg8 *) pHSampleTimer_TimerHW__RT1)
    #define pHSampleTimer_RT1_PTR        ( (reg8 *) pHSampleTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define pHSampleTimer_CONTROL3       (*(reg8 *) pHSampleTimer_TimerHW__CFG2)
        #define pHSampleTimer_CONTROL3_PTR   ( (reg8 *) pHSampleTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define pHSampleTimer_GLOBAL_ENABLE  (*(reg8 *) pHSampleTimer_TimerHW__PM_ACT_CFG)
    #define pHSampleTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) pHSampleTimer_TimerHW__PM_STBY_CFG)

    #define pHSampleTimer_CAPTURE_LSB         (* (reg16 *) pHSampleTimer_TimerHW__CAP0 )
    #define pHSampleTimer_CAPTURE_LSB_PTR       ((reg16 *) pHSampleTimer_TimerHW__CAP0 )
    #define pHSampleTimer_PERIOD_LSB          (* (reg16 *) pHSampleTimer_TimerHW__PER0 )
    #define pHSampleTimer_PERIOD_LSB_PTR        ((reg16 *) pHSampleTimer_TimerHW__PER0 )
    #define pHSampleTimer_COUNTER_LSB         (* (reg16 *) pHSampleTimer_TimerHW__CNT_CMP0 )
    #define pHSampleTimer_COUNTER_LSB_PTR       ((reg16 *) pHSampleTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define pHSampleTimer_BLOCK_EN_MASK                     pHSampleTimer_TimerHW__PM_ACT_MSK
    #define pHSampleTimer_BLOCK_STBY_EN_MASK                pHSampleTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define pHSampleTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define pHSampleTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define pHSampleTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define pHSampleTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define pHSampleTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define pHSampleTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << pHSampleTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define pHSampleTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define pHSampleTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << pHSampleTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define pHSampleTimer_CTRL_MODE_SHIFT                 0x01u
        #define pHSampleTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << pHSampleTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define pHSampleTimer_CTRL_RCOD_SHIFT        0x02u
        #define pHSampleTimer_CTRL_ENBL_SHIFT        0x00u
        #define pHSampleTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define pHSampleTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << pHSampleTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define pHSampleTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << pHSampleTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define pHSampleTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << pHSampleTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define pHSampleTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << pHSampleTimer_CTRL_RCOD_SHIFT))
        #define pHSampleTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << pHSampleTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define pHSampleTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define pHSampleTimer_RT1_MASK                        ((uint8)((uint8)0x03u << pHSampleTimer_RT1_SHIFT))
    #define pHSampleTimer_SYNC                            ((uint8)((uint8)0x03u << pHSampleTimer_RT1_SHIFT))
    #define pHSampleTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define pHSampleTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << pHSampleTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define pHSampleTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << pHSampleTimer_SYNCDSI_SHIFT))

    #define pHSampleTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << pHSampleTimer_CTRL_MODE_SHIFT))
    #define pHSampleTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << pHSampleTimer_CTRL_MODE_SHIFT))
    #define pHSampleTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << pHSampleTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define pHSampleTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define pHSampleTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define pHSampleTimer_STATUS_TC_INT_MASK_SHIFT        (pHSampleTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define pHSampleTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (pHSampleTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define pHSampleTimer_STATUS_TC                       ((uint8)((uint8)0x01u << pHSampleTimer_STATUS_TC_SHIFT))
    #define pHSampleTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << pHSampleTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define pHSampleTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << pHSampleTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define pHSampleTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << pHSampleTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define pHSampleTimer_STATUS              (* (reg8 *) pHSampleTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define pHSampleTimer_STATUS_MASK         (* (reg8 *) pHSampleTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define pHSampleTimer_STATUS_AUX_CTRL     (* (reg8 *) pHSampleTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define pHSampleTimer_CONTROL             (* (reg8 *) pHSampleTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(pHSampleTimer_Resolution <= 8u) /* 8-bit Timer */
        #define pHSampleTimer_CAPTURE_LSB         (* (reg8 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define pHSampleTimer_CAPTURE_LSB_PTR       ((reg8 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define pHSampleTimer_PERIOD_LSB          (* (reg8 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define pHSampleTimer_PERIOD_LSB_PTR        ((reg8 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define pHSampleTimer_COUNTER_LSB         (* (reg8 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define pHSampleTimer_COUNTER_LSB_PTR       ((reg8 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(pHSampleTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define pHSampleTimer_CAPTURE_LSB         (* (reg16 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define pHSampleTimer_CAPTURE_LSB_PTR       ((reg16 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define pHSampleTimer_PERIOD_LSB          (* (reg16 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define pHSampleTimer_PERIOD_LSB_PTR        ((reg16 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define pHSampleTimer_COUNTER_LSB         (* (reg16 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define pHSampleTimer_COUNTER_LSB_PTR       ((reg16 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define pHSampleTimer_CAPTURE_LSB         (* (reg16 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define pHSampleTimer_CAPTURE_LSB_PTR       ((reg16 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define pHSampleTimer_PERIOD_LSB          (* (reg16 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define pHSampleTimer_PERIOD_LSB_PTR        ((reg16 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define pHSampleTimer_COUNTER_LSB         (* (reg16 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define pHSampleTimer_COUNTER_LSB_PTR       ((reg16 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(pHSampleTimer_Resolution <= 24u)/* 24-bit Timer */
        #define pHSampleTimer_CAPTURE_LSB         (* (reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define pHSampleTimer_CAPTURE_LSB_PTR       ((reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define pHSampleTimer_PERIOD_LSB          (* (reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define pHSampleTimer_PERIOD_LSB_PTR        ((reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define pHSampleTimer_COUNTER_LSB         (* (reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define pHSampleTimer_COUNTER_LSB_PTR       ((reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define pHSampleTimer_CAPTURE_LSB         (* (reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define pHSampleTimer_CAPTURE_LSB_PTR       ((reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define pHSampleTimer_PERIOD_LSB          (* (reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define pHSampleTimer_PERIOD_LSB_PTR        ((reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define pHSampleTimer_COUNTER_LSB         (* (reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define pHSampleTimer_COUNTER_LSB_PTR       ((reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define pHSampleTimer_CAPTURE_LSB         (* (reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define pHSampleTimer_CAPTURE_LSB_PTR       ((reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define pHSampleTimer_PERIOD_LSB          (* (reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define pHSampleTimer_PERIOD_LSB_PTR        ((reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define pHSampleTimer_COUNTER_LSB         (* (reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define pHSampleTimer_COUNTER_LSB_PTR       ((reg32 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define pHSampleTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) pHSampleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (pHSampleTimer_UsingHWCaptureCounter)
        #define pHSampleTimer_CAP_COUNT              (*(reg8 *) pHSampleTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define pHSampleTimer_CAP_COUNT_PTR          ( (reg8 *) pHSampleTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define pHSampleTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) pHSampleTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define pHSampleTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) pHSampleTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (pHSampleTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define pHSampleTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define pHSampleTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define pHSampleTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define pHSampleTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define pHSampleTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define pHSampleTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << pHSampleTimer_CTRL_INTCNT_SHIFT))
    #define pHSampleTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << pHSampleTimer_CTRL_TRIG_MODE_SHIFT))
    #define pHSampleTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << pHSampleTimer_CTRL_TRIG_EN_SHIFT))
    #define pHSampleTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << pHSampleTimer_CTRL_CAP_MODE_SHIFT))
    #define pHSampleTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << pHSampleTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define pHSampleTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define pHSampleTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define pHSampleTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define pHSampleTimer_STATUS_TC_INT_MASK_SHIFT       pHSampleTimer_STATUS_TC_SHIFT
    #define pHSampleTimer_STATUS_CAPTURE_INT_MASK_SHIFT  pHSampleTimer_STATUS_CAPTURE_SHIFT
    #define pHSampleTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define pHSampleTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define pHSampleTimer_STATUS_FIFOFULL_INT_MASK_SHIFT pHSampleTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define pHSampleTimer_STATUS_TC                      ((uint8)((uint8)0x01u << pHSampleTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define pHSampleTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << pHSampleTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define pHSampleTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << pHSampleTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define pHSampleTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << pHSampleTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define pHSampleTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << pHSampleTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define pHSampleTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << pHSampleTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define pHSampleTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << pHSampleTimer_STATUS_FIFOFULL_SHIFT))

    #define pHSampleTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define pHSampleTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define pHSampleTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define pHSampleTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define pHSampleTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define pHSampleTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_pHSampleTimer_H */


/* [] END OF FILE */
