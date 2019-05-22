/*******************************************************************************
* File Name: pHControlTimer.h
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

#if !defined(CY_TIMER_pHControlTimer_H)
#define CY_TIMER_pHControlTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 pHControlTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define pHControlTimer_Resolution                 16u
#define pHControlTimer_UsingFixedFunction         1u
#define pHControlTimer_UsingHWCaptureCounter      0u
#define pHControlTimer_SoftwareCaptureMode        0u
#define pHControlTimer_SoftwareTriggerMode        0u
#define pHControlTimer_UsingHWEnable              0u
#define pHControlTimer_EnableTriggerMode          0u
#define pHControlTimer_InterruptOnCaptureCount    0u
#define pHControlTimer_RunModeUsed                1u
#define pHControlTimer_ControlRegRemoved          0u

#if defined(pHControlTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define pHControlTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (pHControlTimer_UsingFixedFunction)
    #define pHControlTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define pHControlTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End pHControlTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!pHControlTimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (pHControlTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!pHControlTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}pHControlTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    pHControlTimer_Start(void) ;
void    pHControlTimer_Stop(void) ;

void    pHControlTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   pHControlTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define pHControlTimer_GetInterruptSource() pHControlTimer_ReadStatusRegister()

#if(!pHControlTimer_UDB_CONTROL_REG_REMOVED)
    uint8   pHControlTimer_ReadControlRegister(void) ;
    void    pHControlTimer_WriteControlRegister(uint8 control) ;
#endif /* (!pHControlTimer_UDB_CONTROL_REG_REMOVED) */

uint16  pHControlTimer_ReadPeriod(void) ;
void    pHControlTimer_WritePeriod(uint16 period) ;
uint16  pHControlTimer_ReadCounter(void) ;
void    pHControlTimer_WriteCounter(uint16 counter) ;
uint16  pHControlTimer_ReadCapture(void) ;
void    pHControlTimer_SoftwareCapture(void) ;

#if(!pHControlTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (pHControlTimer_SoftwareCaptureMode)
        void    pHControlTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!pHControlTimer_UsingFixedFunction) */

    #if (pHControlTimer_SoftwareTriggerMode)
        void    pHControlTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (pHControlTimer_SoftwareTriggerMode) */

    #if (pHControlTimer_EnableTriggerMode)
        void    pHControlTimer_EnableTrigger(void) ;
        void    pHControlTimer_DisableTrigger(void) ;
    #endif /* (pHControlTimer_EnableTriggerMode) */


    #if(pHControlTimer_InterruptOnCaptureCount)
        void    pHControlTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (pHControlTimer_InterruptOnCaptureCount) */

    #if (pHControlTimer_UsingHWCaptureCounter)
        void    pHControlTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   pHControlTimer_ReadCaptureCount(void) ;
    #endif /* (pHControlTimer_UsingHWCaptureCounter) */

    void pHControlTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void pHControlTimer_Init(void)          ;
void pHControlTimer_Enable(void)        ;
void pHControlTimer_SaveConfig(void)    ;
void pHControlTimer_RestoreConfig(void) ;
void pHControlTimer_Sleep(void)         ;
void pHControlTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define pHControlTimer__B_TIMER__CM_NONE 0
#define pHControlTimer__B_TIMER__CM_RISINGEDGE 1
#define pHControlTimer__B_TIMER__CM_FALLINGEDGE 2
#define pHControlTimer__B_TIMER__CM_EITHEREDGE 3
#define pHControlTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define pHControlTimer__B_TIMER__TM_NONE 0x00u
#define pHControlTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define pHControlTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define pHControlTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define pHControlTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define pHControlTimer_INIT_PERIOD             14999u
#define pHControlTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << pHControlTimer_CTRL_CAP_MODE_SHIFT))
#define pHControlTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << pHControlTimer_CTRL_TRIG_MODE_SHIFT))
#if (pHControlTimer_UsingFixedFunction)
    #define pHControlTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << pHControlTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << pHControlTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define pHControlTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << pHControlTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << pHControlTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << pHControlTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (pHControlTimer_UsingFixedFunction) */
#define pHControlTimer_INIT_CAPTURE_COUNT      (2u)
#define pHControlTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << pHControlTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (pHControlTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define pHControlTimer_STATUS         (*(reg8 *) pHControlTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define pHControlTimer_STATUS_MASK    (*(reg8 *) pHControlTimer_TimerHW__SR0 )
    #define pHControlTimer_CONTROL        (*(reg8 *) pHControlTimer_TimerHW__CFG0)
    #define pHControlTimer_CONTROL2       (*(reg8 *) pHControlTimer_TimerHW__CFG1)
    #define pHControlTimer_CONTROL2_PTR   ( (reg8 *) pHControlTimer_TimerHW__CFG1)
    #define pHControlTimer_RT1            (*(reg8 *) pHControlTimer_TimerHW__RT1)
    #define pHControlTimer_RT1_PTR        ( (reg8 *) pHControlTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define pHControlTimer_CONTROL3       (*(reg8 *) pHControlTimer_TimerHW__CFG2)
        #define pHControlTimer_CONTROL3_PTR   ( (reg8 *) pHControlTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define pHControlTimer_GLOBAL_ENABLE  (*(reg8 *) pHControlTimer_TimerHW__PM_ACT_CFG)
    #define pHControlTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) pHControlTimer_TimerHW__PM_STBY_CFG)

    #define pHControlTimer_CAPTURE_LSB         (* (reg16 *) pHControlTimer_TimerHW__CAP0 )
    #define pHControlTimer_CAPTURE_LSB_PTR       ((reg16 *) pHControlTimer_TimerHW__CAP0 )
    #define pHControlTimer_PERIOD_LSB          (* (reg16 *) pHControlTimer_TimerHW__PER0 )
    #define pHControlTimer_PERIOD_LSB_PTR        ((reg16 *) pHControlTimer_TimerHW__PER0 )
    #define pHControlTimer_COUNTER_LSB         (* (reg16 *) pHControlTimer_TimerHW__CNT_CMP0 )
    #define pHControlTimer_COUNTER_LSB_PTR       ((reg16 *) pHControlTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define pHControlTimer_BLOCK_EN_MASK                     pHControlTimer_TimerHW__PM_ACT_MSK
    #define pHControlTimer_BLOCK_STBY_EN_MASK                pHControlTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define pHControlTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define pHControlTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define pHControlTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define pHControlTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define pHControlTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define pHControlTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << pHControlTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define pHControlTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define pHControlTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << pHControlTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define pHControlTimer_CTRL_MODE_SHIFT                 0x01u
        #define pHControlTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << pHControlTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define pHControlTimer_CTRL_RCOD_SHIFT        0x02u
        #define pHControlTimer_CTRL_ENBL_SHIFT        0x00u
        #define pHControlTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define pHControlTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << pHControlTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define pHControlTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << pHControlTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define pHControlTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << pHControlTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define pHControlTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << pHControlTimer_CTRL_RCOD_SHIFT))
        #define pHControlTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << pHControlTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define pHControlTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define pHControlTimer_RT1_MASK                        ((uint8)((uint8)0x03u << pHControlTimer_RT1_SHIFT))
    #define pHControlTimer_SYNC                            ((uint8)((uint8)0x03u << pHControlTimer_RT1_SHIFT))
    #define pHControlTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define pHControlTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << pHControlTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define pHControlTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << pHControlTimer_SYNCDSI_SHIFT))

    #define pHControlTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << pHControlTimer_CTRL_MODE_SHIFT))
    #define pHControlTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << pHControlTimer_CTRL_MODE_SHIFT))
    #define pHControlTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << pHControlTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define pHControlTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define pHControlTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define pHControlTimer_STATUS_TC_INT_MASK_SHIFT        (pHControlTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define pHControlTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (pHControlTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define pHControlTimer_STATUS_TC                       ((uint8)((uint8)0x01u << pHControlTimer_STATUS_TC_SHIFT))
    #define pHControlTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << pHControlTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define pHControlTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << pHControlTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define pHControlTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << pHControlTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define pHControlTimer_STATUS              (* (reg8 *) pHControlTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define pHControlTimer_STATUS_MASK         (* (reg8 *) pHControlTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define pHControlTimer_STATUS_AUX_CTRL     (* (reg8 *) pHControlTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define pHControlTimer_CONTROL             (* (reg8 *) pHControlTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(pHControlTimer_Resolution <= 8u) /* 8-bit Timer */
        #define pHControlTimer_CAPTURE_LSB         (* (reg8 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define pHControlTimer_CAPTURE_LSB_PTR       ((reg8 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define pHControlTimer_PERIOD_LSB          (* (reg8 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define pHControlTimer_PERIOD_LSB_PTR        ((reg8 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define pHControlTimer_COUNTER_LSB         (* (reg8 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define pHControlTimer_COUNTER_LSB_PTR       ((reg8 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(pHControlTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define pHControlTimer_CAPTURE_LSB         (* (reg16 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define pHControlTimer_CAPTURE_LSB_PTR       ((reg16 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define pHControlTimer_PERIOD_LSB          (* (reg16 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define pHControlTimer_PERIOD_LSB_PTR        ((reg16 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define pHControlTimer_COUNTER_LSB         (* (reg16 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define pHControlTimer_COUNTER_LSB_PTR       ((reg16 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define pHControlTimer_CAPTURE_LSB         (* (reg16 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define pHControlTimer_CAPTURE_LSB_PTR       ((reg16 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define pHControlTimer_PERIOD_LSB          (* (reg16 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define pHControlTimer_PERIOD_LSB_PTR        ((reg16 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define pHControlTimer_COUNTER_LSB         (* (reg16 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define pHControlTimer_COUNTER_LSB_PTR       ((reg16 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(pHControlTimer_Resolution <= 24u)/* 24-bit Timer */
        #define pHControlTimer_CAPTURE_LSB         (* (reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define pHControlTimer_CAPTURE_LSB_PTR       ((reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define pHControlTimer_PERIOD_LSB          (* (reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define pHControlTimer_PERIOD_LSB_PTR        ((reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define pHControlTimer_COUNTER_LSB         (* (reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define pHControlTimer_COUNTER_LSB_PTR       ((reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define pHControlTimer_CAPTURE_LSB         (* (reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define pHControlTimer_CAPTURE_LSB_PTR       ((reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define pHControlTimer_PERIOD_LSB          (* (reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define pHControlTimer_PERIOD_LSB_PTR        ((reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define pHControlTimer_COUNTER_LSB         (* (reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define pHControlTimer_COUNTER_LSB_PTR       ((reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define pHControlTimer_CAPTURE_LSB         (* (reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define pHControlTimer_CAPTURE_LSB_PTR       ((reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define pHControlTimer_PERIOD_LSB          (* (reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define pHControlTimer_PERIOD_LSB_PTR        ((reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define pHControlTimer_COUNTER_LSB         (* (reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define pHControlTimer_COUNTER_LSB_PTR       ((reg32 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define pHControlTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) pHControlTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (pHControlTimer_UsingHWCaptureCounter)
        #define pHControlTimer_CAP_COUNT              (*(reg8 *) pHControlTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define pHControlTimer_CAP_COUNT_PTR          ( (reg8 *) pHControlTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define pHControlTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) pHControlTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define pHControlTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) pHControlTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (pHControlTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define pHControlTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define pHControlTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define pHControlTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define pHControlTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define pHControlTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define pHControlTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << pHControlTimer_CTRL_INTCNT_SHIFT))
    #define pHControlTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << pHControlTimer_CTRL_TRIG_MODE_SHIFT))
    #define pHControlTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << pHControlTimer_CTRL_TRIG_EN_SHIFT))
    #define pHControlTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << pHControlTimer_CTRL_CAP_MODE_SHIFT))
    #define pHControlTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << pHControlTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define pHControlTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define pHControlTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define pHControlTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define pHControlTimer_STATUS_TC_INT_MASK_SHIFT       pHControlTimer_STATUS_TC_SHIFT
    #define pHControlTimer_STATUS_CAPTURE_INT_MASK_SHIFT  pHControlTimer_STATUS_CAPTURE_SHIFT
    #define pHControlTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define pHControlTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define pHControlTimer_STATUS_FIFOFULL_INT_MASK_SHIFT pHControlTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define pHControlTimer_STATUS_TC                      ((uint8)((uint8)0x01u << pHControlTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define pHControlTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << pHControlTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define pHControlTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << pHControlTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define pHControlTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << pHControlTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define pHControlTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << pHControlTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define pHControlTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << pHControlTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define pHControlTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << pHControlTimer_STATUS_FIFOFULL_SHIFT))

    #define pHControlTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define pHControlTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define pHControlTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define pHControlTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define pHControlTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define pHControlTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_pHControlTimer_H */


/* [] END OF FILE */
