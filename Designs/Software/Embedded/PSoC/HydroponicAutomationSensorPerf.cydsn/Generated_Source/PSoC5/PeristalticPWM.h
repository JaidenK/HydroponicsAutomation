/*******************************************************************************
* File Name: PeristalticPWM.h
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

#if !defined(CY_PWM_PeristalticPWM_H)
#define CY_PWM_PeristalticPWM_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 PeristalticPWM_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define PeristalticPWM_Resolution                     (8u)
#define PeristalticPWM_UsingFixedFunction             (0u)
#define PeristalticPWM_DeadBandMode                   (0u)
#define PeristalticPWM_KillModeMinTime                (0u)
#define PeristalticPWM_KillMode                       (0u)
#define PeristalticPWM_PWMMode                        (0u)
#define PeristalticPWM_PWMModeIsCenterAligned         (0u)
#define PeristalticPWM_DeadBandUsed                   (0u)
#define PeristalticPWM_DeadBand2_4                    (0u)

#if !defined(PeristalticPWM_PWMUDB_genblk8_stsreg__REMOVED)
    #define PeristalticPWM_UseStatus                  (1u)
#else
    #define PeristalticPWM_UseStatus                  (0u)
#endif /* !defined(PeristalticPWM_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(PeristalticPWM_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define PeristalticPWM_UseControl                 (0u)
#else
    #define PeristalticPWM_UseControl                 (0u)
#endif /* !defined(PeristalticPWM_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define PeristalticPWM_UseOneCompareMode              (1u)
#define PeristalticPWM_MinimumKillTime                (1u)
#define PeristalticPWM_EnableMode                     (1u)

#define PeristalticPWM_CompareMode1SW                 (0u)
#define PeristalticPWM_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define PeristalticPWM__B_PWM__DISABLED 0
#define PeristalticPWM__B_PWM__ASYNCHRONOUS 1
#define PeristalticPWM__B_PWM__SINGLECYCLE 2
#define PeristalticPWM__B_PWM__LATCHED 3
#define PeristalticPWM__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define PeristalticPWM__B_PWM__DBMDISABLED 0
#define PeristalticPWM__B_PWM__DBM_2_4_CLOCKS 1
#define PeristalticPWM__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define PeristalticPWM__B_PWM__ONE_OUTPUT 0
#define PeristalticPWM__B_PWM__TWO_OUTPUTS 1
#define PeristalticPWM__B_PWM__DUAL_EDGE 2
#define PeristalticPWM__B_PWM__CENTER_ALIGN 3
#define PeristalticPWM__B_PWM__DITHER 5
#define PeristalticPWM__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define PeristalticPWM__B_PWM__LESS_THAN 1
#define PeristalticPWM__B_PWM__LESS_THAN_OR_EQUAL 2
#define PeristalticPWM__B_PWM__GREATER_THAN 3
#define PeristalticPWM__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define PeristalticPWM__B_PWM__EQUAL 0
#define PeristalticPWM__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!PeristalticPWM_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!PeristalticPWM_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!PeristalticPWM_PWMModeIsCenterAligned) */
        #if (PeristalticPWM_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (PeristalticPWM_UseStatus) */

        /* Backup for Deadband parameters */
        #if(PeristalticPWM_DeadBandMode == PeristalticPWM__B_PWM__DBM_256_CLOCKS || \
            PeristalticPWM_DeadBandMode == PeristalticPWM__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(PeristalticPWM_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (PeristalticPWM_KillModeMinTime) */

        /* Backup control register */
        #if(PeristalticPWM_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (PeristalticPWM_UseControl) */

    #endif /* (!PeristalticPWM_UsingFixedFunction) */

}PeristalticPWM_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    PeristalticPWM_Start(void) ;
void    PeristalticPWM_Stop(void) ;

#if (PeristalticPWM_UseStatus || PeristalticPWM_UsingFixedFunction)
    void  PeristalticPWM_SetInterruptMode(uint8 interruptMode) ;
    uint8 PeristalticPWM_ReadStatusRegister(void) ;
#endif /* (PeristalticPWM_UseStatus || PeristalticPWM_UsingFixedFunction) */

#define PeristalticPWM_GetInterruptSource() PeristalticPWM_ReadStatusRegister()

#if (PeristalticPWM_UseControl)
    uint8 PeristalticPWM_ReadControlRegister(void) ;
    void  PeristalticPWM_WriteControlRegister(uint8 control)
          ;
#endif /* (PeristalticPWM_UseControl) */

#if (PeristalticPWM_UseOneCompareMode)
   #if (PeristalticPWM_CompareMode1SW)
       void    PeristalticPWM_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (PeristalticPWM_CompareMode1SW) */
#else
    #if (PeristalticPWM_CompareMode1SW)
        void    PeristalticPWM_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (PeristalticPWM_CompareMode1SW) */
    #if (PeristalticPWM_CompareMode2SW)
        void    PeristalticPWM_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (PeristalticPWM_CompareMode2SW) */
#endif /* (PeristalticPWM_UseOneCompareMode) */

#if (!PeristalticPWM_UsingFixedFunction)
    uint8   PeristalticPWM_ReadCounter(void) ;
    uint8 PeristalticPWM_ReadCapture(void) ;

    #if (PeristalticPWM_UseStatus)
            void PeristalticPWM_ClearFIFO(void) ;
    #endif /* (PeristalticPWM_UseStatus) */

    void    PeristalticPWM_WriteCounter(uint8 counter)
            ;
#endif /* (!PeristalticPWM_UsingFixedFunction) */

void    PeristalticPWM_WritePeriod(uint8 period)
        ;
uint8 PeristalticPWM_ReadPeriod(void) ;

#if (PeristalticPWM_UseOneCompareMode)
    void    PeristalticPWM_WriteCompare(uint8 compare)
            ;
    uint8 PeristalticPWM_ReadCompare(void) ;
#else
    void    PeristalticPWM_WriteCompare1(uint8 compare)
            ;
    uint8 PeristalticPWM_ReadCompare1(void) ;
    void    PeristalticPWM_WriteCompare2(uint8 compare)
            ;
    uint8 PeristalticPWM_ReadCompare2(void) ;
#endif /* (PeristalticPWM_UseOneCompareMode) */


#if (PeristalticPWM_DeadBandUsed)
    void    PeristalticPWM_WriteDeadTime(uint8 deadtime) ;
    uint8   PeristalticPWM_ReadDeadTime(void) ;
#endif /* (PeristalticPWM_DeadBandUsed) */

#if ( PeristalticPWM_KillModeMinTime)
    void PeristalticPWM_WriteKillTime(uint8 killtime) ;
    uint8 PeristalticPWM_ReadKillTime(void) ;
#endif /* ( PeristalticPWM_KillModeMinTime) */

void PeristalticPWM_Init(void) ;
void PeristalticPWM_Enable(void) ;
void PeristalticPWM_Sleep(void) ;
void PeristalticPWM_Wakeup(void) ;
void PeristalticPWM_SaveConfig(void) ;
void PeristalticPWM_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define PeristalticPWM_INIT_PERIOD_VALUE          (255u)
#define PeristalticPWM_INIT_COMPARE_VALUE1        (127u)
#define PeristalticPWM_INIT_COMPARE_VALUE2        (63u)
#define PeristalticPWM_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    PeristalticPWM_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PeristalticPWM_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PeristalticPWM_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PeristalticPWM_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define PeristalticPWM_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  PeristalticPWM_CTRL_CMPMODE2_SHIFT)
#define PeristalticPWM_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  PeristalticPWM_CTRL_CMPMODE1_SHIFT)
#define PeristalticPWM_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (PeristalticPWM_UsingFixedFunction)
   #define PeristalticPWM_PERIOD_LSB              (*(reg16 *) PeristalticPWM_PWMHW__PER0)
   #define PeristalticPWM_PERIOD_LSB_PTR          ( (reg16 *) PeristalticPWM_PWMHW__PER0)
   #define PeristalticPWM_COMPARE1_LSB            (*(reg16 *) PeristalticPWM_PWMHW__CNT_CMP0)
   #define PeristalticPWM_COMPARE1_LSB_PTR        ( (reg16 *) PeristalticPWM_PWMHW__CNT_CMP0)
   #define PeristalticPWM_COMPARE2_LSB            (0x00u)
   #define PeristalticPWM_COMPARE2_LSB_PTR        (0x00u)
   #define PeristalticPWM_COUNTER_LSB             (*(reg16 *) PeristalticPWM_PWMHW__CNT_CMP0)
   #define PeristalticPWM_COUNTER_LSB_PTR         ( (reg16 *) PeristalticPWM_PWMHW__CNT_CMP0)
   #define PeristalticPWM_CAPTURE_LSB             (*(reg16 *) PeristalticPWM_PWMHW__CAP0)
   #define PeristalticPWM_CAPTURE_LSB_PTR         ( (reg16 *) PeristalticPWM_PWMHW__CAP0)
   #define PeristalticPWM_RT1                     (*(reg8 *)  PeristalticPWM_PWMHW__RT1)
   #define PeristalticPWM_RT1_PTR                 ( (reg8 *)  PeristalticPWM_PWMHW__RT1)

#else
   #if (PeristalticPWM_Resolution == 8u) /* 8bit - PWM */

       #if(PeristalticPWM_PWMModeIsCenterAligned)
           #define PeristalticPWM_PERIOD_LSB      (*(reg8 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
           #define PeristalticPWM_PERIOD_LSB_PTR  ((reg8 *)   PeristalticPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #else
           #define PeristalticPWM_PERIOD_LSB      (*(reg8 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
           #define PeristalticPWM_PERIOD_LSB_PTR  ((reg8 *)   PeristalticPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
       #endif /* (PeristalticPWM_PWMModeIsCenterAligned) */

       #define PeristalticPWM_COMPARE1_LSB        (*(reg8 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define PeristalticPWM_COMPARE1_LSB_PTR    ((reg8 *)   PeristalticPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define PeristalticPWM_COMPARE2_LSB        (*(reg8 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define PeristalticPWM_COMPARE2_LSB_PTR    ((reg8 *)   PeristalticPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define PeristalticPWM_COUNTERCAP_LSB      (*(reg8 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define PeristalticPWM_COUNTERCAP_LSB_PTR  ((reg8 *)   PeristalticPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define PeristalticPWM_COUNTER_LSB         (*(reg8 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define PeristalticPWM_COUNTER_LSB_PTR     ((reg8 *)   PeristalticPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define PeristalticPWM_CAPTURE_LSB         (*(reg8 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
       #define PeristalticPWM_CAPTURE_LSB_PTR     ((reg8 *)   PeristalticPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(PeristalticPWM_PWMModeIsCenterAligned)
               #define PeristalticPWM_PERIOD_LSB      (*(reg16 *) PeristalticPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
               #define PeristalticPWM_PERIOD_LSB_PTR  ((reg16 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #else
               #define PeristalticPWM_PERIOD_LSB      (*(reg16 *) PeristalticPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
               #define PeristalticPWM_PERIOD_LSB_PTR  ((reg16 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
            #endif /* (PeristalticPWM_PWMModeIsCenterAligned) */

            #define PeristalticPWM_COMPARE1_LSB       (*(reg16 *) PeristalticPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define PeristalticPWM_COMPARE1_LSB_PTR   ((reg16 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define PeristalticPWM_COMPARE2_LSB       (*(reg16 *) PeristalticPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define PeristalticPWM_COMPARE2_LSB_PTR   ((reg16 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define PeristalticPWM_COUNTERCAP_LSB     (*(reg16 *) PeristalticPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define PeristalticPWM_COUNTERCAP_LSB_PTR ((reg16 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define PeristalticPWM_COUNTER_LSB        (*(reg16 *) PeristalticPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define PeristalticPWM_COUNTER_LSB_PTR    ((reg16 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define PeristalticPWM_CAPTURE_LSB        (*(reg16 *) PeristalticPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
            #define PeristalticPWM_CAPTURE_LSB_PTR    ((reg16 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
        #else
            #if(PeristalticPWM_PWMModeIsCenterAligned)
               #define PeristalticPWM_PERIOD_LSB      (*(reg16 *) PeristalticPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
               #define PeristalticPWM_PERIOD_LSB_PTR  ((reg16 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #else
               #define PeristalticPWM_PERIOD_LSB      (*(reg16 *) PeristalticPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
               #define PeristalticPWM_PERIOD_LSB_PTR  ((reg16 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
            #endif /* (PeristalticPWM_PWMModeIsCenterAligned) */

            #define PeristalticPWM_COMPARE1_LSB       (*(reg16 *) PeristalticPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define PeristalticPWM_COMPARE1_LSB_PTR   ((reg16 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define PeristalticPWM_COMPARE2_LSB       (*(reg16 *) PeristalticPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define PeristalticPWM_COMPARE2_LSB_PTR   ((reg16 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define PeristalticPWM_COUNTERCAP_LSB     (*(reg16 *) PeristalticPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define PeristalticPWM_COUNTERCAP_LSB_PTR ((reg16 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define PeristalticPWM_COUNTER_LSB        (*(reg16 *) PeristalticPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define PeristalticPWM_COUNTER_LSB_PTR    ((reg16 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define PeristalticPWM_CAPTURE_LSB        (*(reg16 *) PeristalticPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
            #define PeristalticPWM_CAPTURE_LSB_PTR    ((reg16 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define PeristalticPWM_AUX_CONTROLDP1          (*(reg8 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define PeristalticPWM_AUX_CONTROLDP1_PTR      ((reg8 *)   PeristalticPWM_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (PeristalticPWM_Resolution == 8) */

   #define PeristalticPWM_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define PeristalticPWM_AUX_CONTROLDP0          (*(reg8 *)  PeristalticPWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define PeristalticPWM_AUX_CONTROLDP0_PTR      ((reg8 *)   PeristalticPWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (PeristalticPWM_UsingFixedFunction) */

#if(PeristalticPWM_KillModeMinTime )
    #define PeristalticPWM_KILLMODEMINTIME        (*(reg8 *)  PeristalticPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define PeristalticPWM_KILLMODEMINTIME_PTR    ((reg8 *)   PeristalticPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (PeristalticPWM_KillModeMinTime ) */

#if(PeristalticPWM_DeadBandMode == PeristalticPWM__B_PWM__DBM_256_CLOCKS)
    #define PeristalticPWM_DEADBAND_COUNT         (*(reg8 *)  PeristalticPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PeristalticPWM_DEADBAND_COUNT_PTR     ((reg8 *)   PeristalticPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PeristalticPWM_DEADBAND_LSB_PTR       ((reg8 *)   PeristalticPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define PeristalticPWM_DEADBAND_LSB           (*(reg8 *)  PeristalticPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(PeristalticPWM_DeadBandMode == PeristalticPWM__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (PeristalticPWM_UsingFixedFunction)
        #define PeristalticPWM_DEADBAND_COUNT         (*(reg8 *)  PeristalticPWM_PWMHW__CFG0)
        #define PeristalticPWM_DEADBAND_COUNT_PTR     ((reg8 *)   PeristalticPWM_PWMHW__CFG0)
        #define PeristalticPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PeristalticPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define PeristalticPWM_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define PeristalticPWM_DEADBAND_COUNT         (*(reg8 *)  PeristalticPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PeristalticPWM_DEADBAND_COUNT_PTR     ((reg8 *)   PeristalticPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PeristalticPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PeristalticPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define PeristalticPWM_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (PeristalticPWM_UsingFixedFunction) */
#endif /* (PeristalticPWM_DeadBandMode == PeristalticPWM__B_PWM__DBM_256_CLOCKS) */



#if (PeristalticPWM_UsingFixedFunction)
    #define PeristalticPWM_STATUS                 (*(reg8 *) PeristalticPWM_PWMHW__SR0)
    #define PeristalticPWM_STATUS_PTR             ((reg8 *) PeristalticPWM_PWMHW__SR0)
    #define PeristalticPWM_STATUS_MASK            (*(reg8 *) PeristalticPWM_PWMHW__SR0)
    #define PeristalticPWM_STATUS_MASK_PTR        ((reg8 *) PeristalticPWM_PWMHW__SR0)
    #define PeristalticPWM_CONTROL                (*(reg8 *) PeristalticPWM_PWMHW__CFG0)
    #define PeristalticPWM_CONTROL_PTR            ((reg8 *) PeristalticPWM_PWMHW__CFG0)
    #define PeristalticPWM_CONTROL2               (*(reg8 *) PeristalticPWM_PWMHW__CFG1)
    #define PeristalticPWM_CONTROL3               (*(reg8 *) PeristalticPWM_PWMHW__CFG2)
    #define PeristalticPWM_GLOBAL_ENABLE          (*(reg8 *) PeristalticPWM_PWMHW__PM_ACT_CFG)
    #define PeristalticPWM_GLOBAL_ENABLE_PTR      ( (reg8 *) PeristalticPWM_PWMHW__PM_ACT_CFG)
    #define PeristalticPWM_GLOBAL_STBY_ENABLE     (*(reg8 *) PeristalticPWM_PWMHW__PM_STBY_CFG)
    #define PeristalticPWM_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) PeristalticPWM_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define PeristalticPWM_BLOCK_EN_MASK          (PeristalticPWM_PWMHW__PM_ACT_MSK)
    #define PeristalticPWM_BLOCK_STBY_EN_MASK     (PeristalticPWM_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define PeristalticPWM_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define PeristalticPWM_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define PeristalticPWM_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define PeristalticPWM_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define PeristalticPWM_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define PeristalticPWM_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define PeristalticPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << PeristalticPWM_CTRL_ENABLE_SHIFT)
    #define PeristalticPWM_CTRL_RESET             (uint8)((uint8)0x01u << PeristalticPWM_CTRL_RESET_SHIFT)
    #define PeristalticPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PeristalticPWM_CTRL_CMPMODE2_SHIFT)
    #define PeristalticPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PeristalticPWM_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define PeristalticPWM_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define PeristalticPWM_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << PeristalticPWM_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define PeristalticPWM_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define PeristalticPWM_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define PeristalticPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define PeristalticPWM_STATUS_TC_INT_EN_MASK_SHIFT            (PeristalticPWM_STATUS_TC_SHIFT - 4u)
    #define PeristalticPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define PeristalticPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (PeristalticPWM_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define PeristalticPWM_STATUS_TC              (uint8)((uint8)0x01u << PeristalticPWM_STATUS_TC_SHIFT)
    #define PeristalticPWM_STATUS_CMP1            (uint8)((uint8)0x01u << PeristalticPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define PeristalticPWM_STATUS_TC_INT_EN_MASK              (uint8)((uint8)PeristalticPWM_STATUS_TC >> 4u)
    #define PeristalticPWM_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)PeristalticPWM_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define PeristalticPWM_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define PeristalticPWM_RT1_MASK              (uint8)((uint8)0x03u << PeristalticPWM_RT1_SHIFT)
    #define PeristalticPWM_SYNC                  (uint8)((uint8)0x03u << PeristalticPWM_RT1_SHIFT)
    #define PeristalticPWM_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define PeristalticPWM_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << PeristalticPWM_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define PeristalticPWM_SYNCDSI_EN            (uint8)((uint8)0x0Fu << PeristalticPWM_SYNCDSI_SHIFT)


#else
    #define PeristalticPWM_STATUS                (*(reg8 *)   PeristalticPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PeristalticPWM_STATUS_PTR            ((reg8 *)    PeristalticPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PeristalticPWM_STATUS_MASK           (*(reg8 *)   PeristalticPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PeristalticPWM_STATUS_MASK_PTR       ((reg8 *)    PeristalticPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PeristalticPWM_STATUS_AUX_CTRL       (*(reg8 *)   PeristalticPWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define PeristalticPWM_CONTROL               (*(reg8 *)   PeristalticPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define PeristalticPWM_CONTROL_PTR           ((reg8 *)    PeristalticPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define PeristalticPWM_CTRL_ENABLE_SHIFT      (0x07u)
    #define PeristalticPWM_CTRL_RESET_SHIFT       (0x06u)
    #define PeristalticPWM_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define PeristalticPWM_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define PeristalticPWM_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define PeristalticPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << PeristalticPWM_CTRL_ENABLE_SHIFT)
    #define PeristalticPWM_CTRL_RESET             (uint8)((uint8)0x01u << PeristalticPWM_CTRL_RESET_SHIFT)
    #define PeristalticPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PeristalticPWM_CTRL_CMPMODE2_SHIFT)
    #define PeristalticPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PeristalticPWM_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define PeristalticPWM_STATUS_KILL_SHIFT          (0x05u)
    #define PeristalticPWM_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define PeristalticPWM_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define PeristalticPWM_STATUS_TC_SHIFT            (0x02u)
    #define PeristalticPWM_STATUS_CMP2_SHIFT          (0x01u)
    #define PeristalticPWM_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define PeristalticPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (PeristalticPWM_STATUS_KILL_SHIFT)
    #define PeristalticPWM_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (PeristalticPWM_STATUS_FIFONEMPTY_SHIFT)
    #define PeristalticPWM_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (PeristalticPWM_STATUS_FIFOFULL_SHIFT)
    #define PeristalticPWM_STATUS_TC_INT_EN_MASK_SHIFT            (PeristalticPWM_STATUS_TC_SHIFT)
    #define PeristalticPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (PeristalticPWM_STATUS_CMP2_SHIFT)
    #define PeristalticPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (PeristalticPWM_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define PeristalticPWM_STATUS_KILL            (uint8)((uint8)0x00u << PeristalticPWM_STATUS_KILL_SHIFT )
    #define PeristalticPWM_STATUS_FIFOFULL        (uint8)((uint8)0x01u << PeristalticPWM_STATUS_FIFOFULL_SHIFT)
    #define PeristalticPWM_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << PeristalticPWM_STATUS_FIFONEMPTY_SHIFT)
    #define PeristalticPWM_STATUS_TC              (uint8)((uint8)0x01u << PeristalticPWM_STATUS_TC_SHIFT)
    #define PeristalticPWM_STATUS_CMP2            (uint8)((uint8)0x01u << PeristalticPWM_STATUS_CMP2_SHIFT)
    #define PeristalticPWM_STATUS_CMP1            (uint8)((uint8)0x01u << PeristalticPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define PeristalticPWM_STATUS_KILL_INT_EN_MASK            (PeristalticPWM_STATUS_KILL)
    #define PeristalticPWM_STATUS_FIFOFULL_INT_EN_MASK        (PeristalticPWM_STATUS_FIFOFULL)
    #define PeristalticPWM_STATUS_FIFONEMPTY_INT_EN_MASK      (PeristalticPWM_STATUS_FIFONEMPTY)
    #define PeristalticPWM_STATUS_TC_INT_EN_MASK              (PeristalticPWM_STATUS_TC)
    #define PeristalticPWM_STATUS_CMP2_INT_EN_MASK            (PeristalticPWM_STATUS_CMP2)
    #define PeristalticPWM_STATUS_CMP1_INT_EN_MASK            (PeristalticPWM_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define PeristalticPWM_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define PeristalticPWM_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define PeristalticPWM_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define PeristalticPWM_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define PeristalticPWM_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* PeristalticPWM_UsingFixedFunction */

#endif  /* CY_PWM_PeristalticPWM_H */


/* [] END OF FILE */
