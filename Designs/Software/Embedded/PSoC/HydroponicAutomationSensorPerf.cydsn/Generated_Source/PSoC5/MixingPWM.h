/*******************************************************************************
* File Name: MixingPWM.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_MixingPWM_H)
#define CY_PWM_MixingPWM_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 MixingPWM_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define MixingPWM_Resolution                     (16u)
#define MixingPWM_UsingFixedFunction             (0u)
#define MixingPWM_DeadBandMode                   (0u)
#define MixingPWM_KillModeMinTime                (0u)
#define MixingPWM_KillMode                       (0u)
#define MixingPWM_PWMMode                        (0u)
#define MixingPWM_PWMModeIsCenterAligned         (0u)
#define MixingPWM_DeadBandUsed                   (0u)
#define MixingPWM_DeadBand2_4                    (0u)

#if !defined(MixingPWM_PWMUDB_genblk8_stsreg__REMOVED)
    #define MixingPWM_UseStatus                  (1u)
#else
    #define MixingPWM_UseStatus                  (0u)
#endif /* !defined(MixingPWM_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(MixingPWM_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define MixingPWM_UseControl                 (1u)
#else
    #define MixingPWM_UseControl                 (0u)
#endif /* !defined(MixingPWM_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define MixingPWM_UseOneCompareMode              (1u)
#define MixingPWM_MinimumKillTime                (1u)
#define MixingPWM_EnableMode                     (0u)

#define MixingPWM_CompareMode1SW                 (0u)
#define MixingPWM_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define MixingPWM__B_PWM__DISABLED 0
#define MixingPWM__B_PWM__ASYNCHRONOUS 1
#define MixingPWM__B_PWM__SINGLECYCLE 2
#define MixingPWM__B_PWM__LATCHED 3
#define MixingPWM__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define MixingPWM__B_PWM__DBMDISABLED 0
#define MixingPWM__B_PWM__DBM_2_4_CLOCKS 1
#define MixingPWM__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define MixingPWM__B_PWM__ONE_OUTPUT 0
#define MixingPWM__B_PWM__TWO_OUTPUTS 1
#define MixingPWM__B_PWM__DUAL_EDGE 2
#define MixingPWM__B_PWM__CENTER_ALIGN 3
#define MixingPWM__B_PWM__DITHER 5
#define MixingPWM__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define MixingPWM__B_PWM__LESS_THAN 1
#define MixingPWM__B_PWM__LESS_THAN_OR_EQUAL 2
#define MixingPWM__B_PWM__GREATER_THAN 3
#define MixingPWM__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define MixingPWM__B_PWM__EQUAL 0
#define MixingPWM__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!MixingPWM_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!MixingPWM_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!MixingPWM_PWMModeIsCenterAligned) */
        #if (MixingPWM_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (MixingPWM_UseStatus) */

        /* Backup for Deadband parameters */
        #if(MixingPWM_DeadBandMode == MixingPWM__B_PWM__DBM_256_CLOCKS || \
            MixingPWM_DeadBandMode == MixingPWM__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(MixingPWM_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (MixingPWM_KillModeMinTime) */

        /* Backup control register */
        #if(MixingPWM_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (MixingPWM_UseControl) */

    #endif /* (!MixingPWM_UsingFixedFunction) */

}MixingPWM_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    MixingPWM_Start(void) ;
void    MixingPWM_Stop(void) ;

#if (MixingPWM_UseStatus || MixingPWM_UsingFixedFunction)
    void  MixingPWM_SetInterruptMode(uint8 interruptMode) ;
    uint8 MixingPWM_ReadStatusRegister(void) ;
#endif /* (MixingPWM_UseStatus || MixingPWM_UsingFixedFunction) */

#define MixingPWM_GetInterruptSource() MixingPWM_ReadStatusRegister()

#if (MixingPWM_UseControl)
    uint8 MixingPWM_ReadControlRegister(void) ;
    void  MixingPWM_WriteControlRegister(uint8 control)
          ;
#endif /* (MixingPWM_UseControl) */

#if (MixingPWM_UseOneCompareMode)
   #if (MixingPWM_CompareMode1SW)
       void    MixingPWM_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (MixingPWM_CompareMode1SW) */
#else
    #if (MixingPWM_CompareMode1SW)
        void    MixingPWM_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (MixingPWM_CompareMode1SW) */
    #if (MixingPWM_CompareMode2SW)
        void    MixingPWM_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (MixingPWM_CompareMode2SW) */
#endif /* (MixingPWM_UseOneCompareMode) */

#if (!MixingPWM_UsingFixedFunction)
    uint16   MixingPWM_ReadCounter(void) ;
    uint16 MixingPWM_ReadCapture(void) ;

    #if (MixingPWM_UseStatus)
            void MixingPWM_ClearFIFO(void) ;
    #endif /* (MixingPWM_UseStatus) */

    void    MixingPWM_WriteCounter(uint16 counter)
            ;
#endif /* (!MixingPWM_UsingFixedFunction) */

void    MixingPWM_WritePeriod(uint16 period)
        ;
uint16 MixingPWM_ReadPeriod(void) ;

#if (MixingPWM_UseOneCompareMode)
    void    MixingPWM_WriteCompare(uint16 compare)
            ;
    uint16 MixingPWM_ReadCompare(void) ;
#else
    void    MixingPWM_WriteCompare1(uint16 compare)
            ;
    uint16 MixingPWM_ReadCompare1(void) ;
    void    MixingPWM_WriteCompare2(uint16 compare)
            ;
    uint16 MixingPWM_ReadCompare2(void) ;
#endif /* (MixingPWM_UseOneCompareMode) */


#if (MixingPWM_DeadBandUsed)
    void    MixingPWM_WriteDeadTime(uint8 deadtime) ;
    uint8   MixingPWM_ReadDeadTime(void) ;
#endif /* (MixingPWM_DeadBandUsed) */

#if ( MixingPWM_KillModeMinTime)
    void MixingPWM_WriteKillTime(uint8 killtime) ;
    uint8 MixingPWM_ReadKillTime(void) ;
#endif /* ( MixingPWM_KillModeMinTime) */

void MixingPWM_Init(void) ;
void MixingPWM_Enable(void) ;
void MixingPWM_Sleep(void) ;
void MixingPWM_Wakeup(void) ;
void MixingPWM_SaveConfig(void) ;
void MixingPWM_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define MixingPWM_INIT_PERIOD_VALUE          (65535u)
#define MixingPWM_INIT_COMPARE_VALUE1        (0u)
#define MixingPWM_INIT_COMPARE_VALUE2        (63u)
#define MixingPWM_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    MixingPWM_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    MixingPWM_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    MixingPWM_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    MixingPWM_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define MixingPWM_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  MixingPWM_CTRL_CMPMODE2_SHIFT)
#define MixingPWM_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  MixingPWM_CTRL_CMPMODE1_SHIFT)
#define MixingPWM_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (MixingPWM_UsingFixedFunction)
   #define MixingPWM_PERIOD_LSB              (*(reg16 *) MixingPWM_PWMHW__PER0)
   #define MixingPWM_PERIOD_LSB_PTR          ( (reg16 *) MixingPWM_PWMHW__PER0)
   #define MixingPWM_COMPARE1_LSB            (*(reg16 *) MixingPWM_PWMHW__CNT_CMP0)
   #define MixingPWM_COMPARE1_LSB_PTR        ( (reg16 *) MixingPWM_PWMHW__CNT_CMP0)
   #define MixingPWM_COMPARE2_LSB            (0x00u)
   #define MixingPWM_COMPARE2_LSB_PTR        (0x00u)
   #define MixingPWM_COUNTER_LSB             (*(reg16 *) MixingPWM_PWMHW__CNT_CMP0)
   #define MixingPWM_COUNTER_LSB_PTR         ( (reg16 *) MixingPWM_PWMHW__CNT_CMP0)
   #define MixingPWM_CAPTURE_LSB             (*(reg16 *) MixingPWM_PWMHW__CAP0)
   #define MixingPWM_CAPTURE_LSB_PTR         ( (reg16 *) MixingPWM_PWMHW__CAP0)
   #define MixingPWM_RT1                     (*(reg8 *)  MixingPWM_PWMHW__RT1)
   #define MixingPWM_RT1_PTR                 ( (reg8 *)  MixingPWM_PWMHW__RT1)

#else
   #if (MixingPWM_Resolution == 8u) /* 8bit - PWM */

       #if(MixingPWM_PWMModeIsCenterAligned)
           #define MixingPWM_PERIOD_LSB      (*(reg8 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define MixingPWM_PERIOD_LSB_PTR  ((reg8 *)   MixingPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define MixingPWM_PERIOD_LSB      (*(reg8 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define MixingPWM_PERIOD_LSB_PTR  ((reg8 *)   MixingPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (MixingPWM_PWMModeIsCenterAligned) */

       #define MixingPWM_COMPARE1_LSB        (*(reg8 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define MixingPWM_COMPARE1_LSB_PTR    ((reg8 *)   MixingPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define MixingPWM_COMPARE2_LSB        (*(reg8 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define MixingPWM_COMPARE2_LSB_PTR    ((reg8 *)   MixingPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define MixingPWM_COUNTERCAP_LSB      (*(reg8 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define MixingPWM_COUNTERCAP_LSB_PTR  ((reg8 *)   MixingPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define MixingPWM_COUNTER_LSB         (*(reg8 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define MixingPWM_COUNTER_LSB_PTR     ((reg8 *)   MixingPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define MixingPWM_CAPTURE_LSB         (*(reg8 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define MixingPWM_CAPTURE_LSB_PTR     ((reg8 *)   MixingPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(MixingPWM_PWMModeIsCenterAligned)
               #define MixingPWM_PERIOD_LSB      (*(reg16 *) MixingPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define MixingPWM_PERIOD_LSB_PTR  ((reg16 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define MixingPWM_PERIOD_LSB      (*(reg16 *) MixingPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define MixingPWM_PERIOD_LSB_PTR  ((reg16 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (MixingPWM_PWMModeIsCenterAligned) */

            #define MixingPWM_COMPARE1_LSB       (*(reg16 *) MixingPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define MixingPWM_COMPARE1_LSB_PTR   ((reg16 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define MixingPWM_COMPARE2_LSB       (*(reg16 *) MixingPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define MixingPWM_COMPARE2_LSB_PTR   ((reg16 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define MixingPWM_COUNTERCAP_LSB     (*(reg16 *) MixingPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define MixingPWM_COUNTERCAP_LSB_PTR ((reg16 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define MixingPWM_COUNTER_LSB        (*(reg16 *) MixingPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define MixingPWM_COUNTER_LSB_PTR    ((reg16 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define MixingPWM_CAPTURE_LSB        (*(reg16 *) MixingPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define MixingPWM_CAPTURE_LSB_PTR    ((reg16 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(MixingPWM_PWMModeIsCenterAligned)
               #define MixingPWM_PERIOD_LSB      (*(reg16 *) MixingPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define MixingPWM_PERIOD_LSB_PTR  ((reg16 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define MixingPWM_PERIOD_LSB      (*(reg16 *) MixingPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define MixingPWM_PERIOD_LSB_PTR  ((reg16 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (MixingPWM_PWMModeIsCenterAligned) */

            #define MixingPWM_COMPARE1_LSB       (*(reg16 *) MixingPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define MixingPWM_COMPARE1_LSB_PTR   ((reg16 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define MixingPWM_COMPARE2_LSB       (*(reg16 *) MixingPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define MixingPWM_COMPARE2_LSB_PTR   ((reg16 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define MixingPWM_COUNTERCAP_LSB     (*(reg16 *) MixingPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define MixingPWM_COUNTERCAP_LSB_PTR ((reg16 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define MixingPWM_COUNTER_LSB        (*(reg16 *) MixingPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define MixingPWM_COUNTER_LSB_PTR    ((reg16 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define MixingPWM_CAPTURE_LSB        (*(reg16 *) MixingPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define MixingPWM_CAPTURE_LSB_PTR    ((reg16 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define MixingPWM_AUX_CONTROLDP1          (*(reg8 *)  MixingPWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define MixingPWM_AUX_CONTROLDP1_PTR      ((reg8 *)   MixingPWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (MixingPWM_Resolution == 8) */

   #define MixingPWM_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define MixingPWM_AUX_CONTROLDP0          (*(reg8 *)  MixingPWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define MixingPWM_AUX_CONTROLDP0_PTR      ((reg8 *)   MixingPWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (MixingPWM_UsingFixedFunction) */

#if(MixingPWM_KillModeMinTime )
    #define MixingPWM_KILLMODEMINTIME        (*(reg8 *)  MixingPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define MixingPWM_KILLMODEMINTIME_PTR    ((reg8 *)   MixingPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (MixingPWM_KillModeMinTime ) */

#if(MixingPWM_DeadBandMode == MixingPWM__B_PWM__DBM_256_CLOCKS)
    #define MixingPWM_DEADBAND_COUNT         (*(reg8 *)  MixingPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define MixingPWM_DEADBAND_COUNT_PTR     ((reg8 *)   MixingPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define MixingPWM_DEADBAND_LSB_PTR       ((reg8 *)   MixingPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define MixingPWM_DEADBAND_LSB           (*(reg8 *)  MixingPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(MixingPWM_DeadBandMode == MixingPWM__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (MixingPWM_UsingFixedFunction)
        #define MixingPWM_DEADBAND_COUNT         (*(reg8 *)  MixingPWM_PWMHW__CFG0)
        #define MixingPWM_DEADBAND_COUNT_PTR     ((reg8 *)   MixingPWM_PWMHW__CFG0)
        #define MixingPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << MixingPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define MixingPWM_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define MixingPWM_DEADBAND_COUNT         (*(reg8 *)  MixingPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define MixingPWM_DEADBAND_COUNT_PTR     ((reg8 *)   MixingPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define MixingPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << MixingPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define MixingPWM_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (MixingPWM_UsingFixedFunction) */
#endif /* (MixingPWM_DeadBandMode == MixingPWM__B_PWM__DBM_256_CLOCKS) */



#if (MixingPWM_UsingFixedFunction)
    #define MixingPWM_STATUS                 (*(reg8 *) MixingPWM_PWMHW__SR0)
    #define MixingPWM_STATUS_PTR             ((reg8 *) MixingPWM_PWMHW__SR0)
    #define MixingPWM_STATUS_MASK            (*(reg8 *) MixingPWM_PWMHW__SR0)
    #define MixingPWM_STATUS_MASK_PTR        ((reg8 *) MixingPWM_PWMHW__SR0)
    #define MixingPWM_CONTROL                (*(reg8 *) MixingPWM_PWMHW__CFG0)
    #define MixingPWM_CONTROL_PTR            ((reg8 *) MixingPWM_PWMHW__CFG0)
    #define MixingPWM_CONTROL2               (*(reg8 *) MixingPWM_PWMHW__CFG1)
    #define MixingPWM_CONTROL3               (*(reg8 *) MixingPWM_PWMHW__CFG2)
    #define MixingPWM_GLOBAL_ENABLE          (*(reg8 *) MixingPWM_PWMHW__PM_ACT_CFG)
    #define MixingPWM_GLOBAL_ENABLE_PTR      ( (reg8 *) MixingPWM_PWMHW__PM_ACT_CFG)
    #define MixingPWM_GLOBAL_STBY_ENABLE     (*(reg8 *) MixingPWM_PWMHW__PM_STBY_CFG)
    #define MixingPWM_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) MixingPWM_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define MixingPWM_BLOCK_EN_MASK          (MixingPWM_PWMHW__PM_ACT_MSK)
    #define MixingPWM_BLOCK_STBY_EN_MASK     (MixingPWM_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define MixingPWM_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define MixingPWM_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define MixingPWM_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define MixingPWM_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define MixingPWM_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define MixingPWM_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define MixingPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << MixingPWM_CTRL_ENABLE_SHIFT)
    #define MixingPWM_CTRL_RESET             (uint8)((uint8)0x01u << MixingPWM_CTRL_RESET_SHIFT)
    #define MixingPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << MixingPWM_CTRL_CMPMODE2_SHIFT)
    #define MixingPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << MixingPWM_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define MixingPWM_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define MixingPWM_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << MixingPWM_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define MixingPWM_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define MixingPWM_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define MixingPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define MixingPWM_STATUS_TC_INT_EN_MASK_SHIFT            (MixingPWM_STATUS_TC_SHIFT - 4u)
    #define MixingPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define MixingPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (MixingPWM_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define MixingPWM_STATUS_TC              (uint8)((uint8)0x01u << MixingPWM_STATUS_TC_SHIFT)
    #define MixingPWM_STATUS_CMP1            (uint8)((uint8)0x01u << MixingPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define MixingPWM_STATUS_TC_INT_EN_MASK              (uint8)((uint8)MixingPWM_STATUS_TC >> 4u)
    #define MixingPWM_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)MixingPWM_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define MixingPWM_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define MixingPWM_RT1_MASK              (uint8)((uint8)0x03u << MixingPWM_RT1_SHIFT)
    #define MixingPWM_SYNC                  (uint8)((uint8)0x03u << MixingPWM_RT1_SHIFT)
    #define MixingPWM_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define MixingPWM_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << MixingPWM_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define MixingPWM_SYNCDSI_EN            (uint8)((uint8)0x0Fu << MixingPWM_SYNCDSI_SHIFT)


#else
    #define MixingPWM_STATUS                (*(reg8 *)   MixingPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define MixingPWM_STATUS_PTR            ((reg8 *)    MixingPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define MixingPWM_STATUS_MASK           (*(reg8 *)   MixingPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define MixingPWM_STATUS_MASK_PTR       ((reg8 *)    MixingPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define MixingPWM_STATUS_AUX_CTRL       (*(reg8 *)   MixingPWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define MixingPWM_CONTROL               (*(reg8 *)   MixingPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define MixingPWM_CONTROL_PTR           ((reg8 *)    MixingPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define MixingPWM_CTRL_ENABLE_SHIFT      (0x07u)
    #define MixingPWM_CTRL_RESET_SHIFT       (0x06u)
    #define MixingPWM_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define MixingPWM_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define MixingPWM_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define MixingPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << MixingPWM_CTRL_ENABLE_SHIFT)
    #define MixingPWM_CTRL_RESET             (uint8)((uint8)0x01u << MixingPWM_CTRL_RESET_SHIFT)
    #define MixingPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << MixingPWM_CTRL_CMPMODE2_SHIFT)
    #define MixingPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << MixingPWM_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define MixingPWM_STATUS_KILL_SHIFT          (0x05u)
    #define MixingPWM_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define MixingPWM_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define MixingPWM_STATUS_TC_SHIFT            (0x02u)
    #define MixingPWM_STATUS_CMP2_SHIFT          (0x01u)
    #define MixingPWM_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define MixingPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (MixingPWM_STATUS_KILL_SHIFT)
    #define MixingPWM_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (MixingPWM_STATUS_FIFONEMPTY_SHIFT)
    #define MixingPWM_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (MixingPWM_STATUS_FIFOFULL_SHIFT)
    #define MixingPWM_STATUS_TC_INT_EN_MASK_SHIFT            (MixingPWM_STATUS_TC_SHIFT)
    #define MixingPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (MixingPWM_STATUS_CMP2_SHIFT)
    #define MixingPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (MixingPWM_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define MixingPWM_STATUS_KILL            (uint8)((uint8)0x00u << MixingPWM_STATUS_KILL_SHIFT )
    #define MixingPWM_STATUS_FIFOFULL        (uint8)((uint8)0x01u << MixingPWM_STATUS_FIFOFULL_SHIFT)
    #define MixingPWM_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << MixingPWM_STATUS_FIFONEMPTY_SHIFT)
    #define MixingPWM_STATUS_TC              (uint8)((uint8)0x01u << MixingPWM_STATUS_TC_SHIFT)
    #define MixingPWM_STATUS_CMP2            (uint8)((uint8)0x01u << MixingPWM_STATUS_CMP2_SHIFT)
    #define MixingPWM_STATUS_CMP1            (uint8)((uint8)0x01u << MixingPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define MixingPWM_STATUS_KILL_INT_EN_MASK            (MixingPWM_STATUS_KILL)
    #define MixingPWM_STATUS_FIFOFULL_INT_EN_MASK        (MixingPWM_STATUS_FIFOFULL)
    #define MixingPWM_STATUS_FIFONEMPTY_INT_EN_MASK      (MixingPWM_STATUS_FIFONEMPTY)
    #define MixingPWM_STATUS_TC_INT_EN_MASK              (MixingPWM_STATUS_TC)
    #define MixingPWM_STATUS_CMP2_INT_EN_MASK            (MixingPWM_STATUS_CMP2)
    #define MixingPWM_STATUS_CMP1_INT_EN_MASK            (MixingPWM_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define MixingPWM_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define MixingPWM_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define MixingPWM_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define MixingPWM_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define MixingPWM_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* MixingPWM_UsingFixedFunction */

#endif  /* CY_PWM_MixingPWM_H */


/* [] END OF FILE */
