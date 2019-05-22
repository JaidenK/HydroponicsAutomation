/*******************************************************************************
* File Name: FlowSpeedPWM.h
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

#if !defined(CY_PWM_FlowSpeedPWM_H)
#define CY_PWM_FlowSpeedPWM_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 FlowSpeedPWM_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define FlowSpeedPWM_Resolution                     (16u)
#define FlowSpeedPWM_UsingFixedFunction             (0u)
#define FlowSpeedPWM_DeadBandMode                   (0u)
#define FlowSpeedPWM_KillModeMinTime                (0u)
#define FlowSpeedPWM_KillMode                       (0u)
#define FlowSpeedPWM_PWMMode                        (0u)
#define FlowSpeedPWM_PWMModeIsCenterAligned         (0u)
#define FlowSpeedPWM_DeadBandUsed                   (0u)
#define FlowSpeedPWM_DeadBand2_4                    (0u)

#if !defined(FlowSpeedPWM_PWMUDB_genblk8_stsreg__REMOVED)
    #define FlowSpeedPWM_UseStatus                  (1u)
#else
    #define FlowSpeedPWM_UseStatus                  (0u)
#endif /* !defined(FlowSpeedPWM_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(FlowSpeedPWM_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define FlowSpeedPWM_UseControl                 (1u)
#else
    #define FlowSpeedPWM_UseControl                 (0u)
#endif /* !defined(FlowSpeedPWM_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define FlowSpeedPWM_UseOneCompareMode              (1u)
#define FlowSpeedPWM_MinimumKillTime                (1u)
#define FlowSpeedPWM_EnableMode                     (0u)

#define FlowSpeedPWM_CompareMode1SW                 (0u)
#define FlowSpeedPWM_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define FlowSpeedPWM__B_PWM__DISABLED 0
#define FlowSpeedPWM__B_PWM__ASYNCHRONOUS 1
#define FlowSpeedPWM__B_PWM__SINGLECYCLE 2
#define FlowSpeedPWM__B_PWM__LATCHED 3
#define FlowSpeedPWM__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define FlowSpeedPWM__B_PWM__DBMDISABLED 0
#define FlowSpeedPWM__B_PWM__DBM_2_4_CLOCKS 1
#define FlowSpeedPWM__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define FlowSpeedPWM__B_PWM__ONE_OUTPUT 0
#define FlowSpeedPWM__B_PWM__TWO_OUTPUTS 1
#define FlowSpeedPWM__B_PWM__DUAL_EDGE 2
#define FlowSpeedPWM__B_PWM__CENTER_ALIGN 3
#define FlowSpeedPWM__B_PWM__DITHER 5
#define FlowSpeedPWM__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define FlowSpeedPWM__B_PWM__LESS_THAN 1
#define FlowSpeedPWM__B_PWM__LESS_THAN_OR_EQUAL 2
#define FlowSpeedPWM__B_PWM__GREATER_THAN 3
#define FlowSpeedPWM__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define FlowSpeedPWM__B_PWM__EQUAL 0
#define FlowSpeedPWM__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!FlowSpeedPWM_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!FlowSpeedPWM_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!FlowSpeedPWM_PWMModeIsCenterAligned) */
        #if (FlowSpeedPWM_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (FlowSpeedPWM_UseStatus) */

        /* Backup for Deadband parameters */
        #if(FlowSpeedPWM_DeadBandMode == FlowSpeedPWM__B_PWM__DBM_256_CLOCKS || \
            FlowSpeedPWM_DeadBandMode == FlowSpeedPWM__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(FlowSpeedPWM_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (FlowSpeedPWM_KillModeMinTime) */

        /* Backup control register */
        #if(FlowSpeedPWM_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (FlowSpeedPWM_UseControl) */

    #endif /* (!FlowSpeedPWM_UsingFixedFunction) */

}FlowSpeedPWM_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    FlowSpeedPWM_Start(void) ;
void    FlowSpeedPWM_Stop(void) ;

#if (FlowSpeedPWM_UseStatus || FlowSpeedPWM_UsingFixedFunction)
    void  FlowSpeedPWM_SetInterruptMode(uint8 interruptMode) ;
    uint8 FlowSpeedPWM_ReadStatusRegister(void) ;
#endif /* (FlowSpeedPWM_UseStatus || FlowSpeedPWM_UsingFixedFunction) */

#define FlowSpeedPWM_GetInterruptSource() FlowSpeedPWM_ReadStatusRegister()

#if (FlowSpeedPWM_UseControl)
    uint8 FlowSpeedPWM_ReadControlRegister(void) ;
    void  FlowSpeedPWM_WriteControlRegister(uint8 control)
          ;
#endif /* (FlowSpeedPWM_UseControl) */

#if (FlowSpeedPWM_UseOneCompareMode)
   #if (FlowSpeedPWM_CompareMode1SW)
       void    FlowSpeedPWM_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (FlowSpeedPWM_CompareMode1SW) */
#else
    #if (FlowSpeedPWM_CompareMode1SW)
        void    FlowSpeedPWM_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (FlowSpeedPWM_CompareMode1SW) */
    #if (FlowSpeedPWM_CompareMode2SW)
        void    FlowSpeedPWM_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (FlowSpeedPWM_CompareMode2SW) */
#endif /* (FlowSpeedPWM_UseOneCompareMode) */

#if (!FlowSpeedPWM_UsingFixedFunction)
    uint16   FlowSpeedPWM_ReadCounter(void) ;
    uint16 FlowSpeedPWM_ReadCapture(void) ;

    #if (FlowSpeedPWM_UseStatus)
            void FlowSpeedPWM_ClearFIFO(void) ;
    #endif /* (FlowSpeedPWM_UseStatus) */

    void    FlowSpeedPWM_WriteCounter(uint16 counter)
            ;
#endif /* (!FlowSpeedPWM_UsingFixedFunction) */

void    FlowSpeedPWM_WritePeriod(uint16 period)
        ;
uint16 FlowSpeedPWM_ReadPeriod(void) ;

#if (FlowSpeedPWM_UseOneCompareMode)
    void    FlowSpeedPWM_WriteCompare(uint16 compare)
            ;
    uint16 FlowSpeedPWM_ReadCompare(void) ;
#else
    void    FlowSpeedPWM_WriteCompare1(uint16 compare)
            ;
    uint16 FlowSpeedPWM_ReadCompare1(void) ;
    void    FlowSpeedPWM_WriteCompare2(uint16 compare)
            ;
    uint16 FlowSpeedPWM_ReadCompare2(void) ;
#endif /* (FlowSpeedPWM_UseOneCompareMode) */


#if (FlowSpeedPWM_DeadBandUsed)
    void    FlowSpeedPWM_WriteDeadTime(uint8 deadtime) ;
    uint8   FlowSpeedPWM_ReadDeadTime(void) ;
#endif /* (FlowSpeedPWM_DeadBandUsed) */

#if ( FlowSpeedPWM_KillModeMinTime)
    void FlowSpeedPWM_WriteKillTime(uint8 killtime) ;
    uint8 FlowSpeedPWM_ReadKillTime(void) ;
#endif /* ( FlowSpeedPWM_KillModeMinTime) */

void FlowSpeedPWM_Init(void) ;
void FlowSpeedPWM_Enable(void) ;
void FlowSpeedPWM_Sleep(void) ;
void FlowSpeedPWM_Wakeup(void) ;
void FlowSpeedPWM_SaveConfig(void) ;
void FlowSpeedPWM_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define FlowSpeedPWM_INIT_PERIOD_VALUE          (65535u)
#define FlowSpeedPWM_INIT_COMPARE_VALUE1        (0u)
#define FlowSpeedPWM_INIT_COMPARE_VALUE2        (60u)
#define FlowSpeedPWM_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    FlowSpeedPWM_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    FlowSpeedPWM_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    FlowSpeedPWM_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    FlowSpeedPWM_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define FlowSpeedPWM_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  FlowSpeedPWM_CTRL_CMPMODE2_SHIFT)
#define FlowSpeedPWM_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  FlowSpeedPWM_CTRL_CMPMODE1_SHIFT)
#define FlowSpeedPWM_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (FlowSpeedPWM_UsingFixedFunction)
   #define FlowSpeedPWM_PERIOD_LSB              (*(reg16 *) FlowSpeedPWM_PWMHW__PER0)
   #define FlowSpeedPWM_PERIOD_LSB_PTR          ( (reg16 *) FlowSpeedPWM_PWMHW__PER0)
   #define FlowSpeedPWM_COMPARE1_LSB            (*(reg16 *) FlowSpeedPWM_PWMHW__CNT_CMP0)
   #define FlowSpeedPWM_COMPARE1_LSB_PTR        ( (reg16 *) FlowSpeedPWM_PWMHW__CNT_CMP0)
   #define FlowSpeedPWM_COMPARE2_LSB            (0x00u)
   #define FlowSpeedPWM_COMPARE2_LSB_PTR        (0x00u)
   #define FlowSpeedPWM_COUNTER_LSB             (*(reg16 *) FlowSpeedPWM_PWMHW__CNT_CMP0)
   #define FlowSpeedPWM_COUNTER_LSB_PTR         ( (reg16 *) FlowSpeedPWM_PWMHW__CNT_CMP0)
   #define FlowSpeedPWM_CAPTURE_LSB             (*(reg16 *) FlowSpeedPWM_PWMHW__CAP0)
   #define FlowSpeedPWM_CAPTURE_LSB_PTR         ( (reg16 *) FlowSpeedPWM_PWMHW__CAP0)
   #define FlowSpeedPWM_RT1                     (*(reg8 *)  FlowSpeedPWM_PWMHW__RT1)
   #define FlowSpeedPWM_RT1_PTR                 ( (reg8 *)  FlowSpeedPWM_PWMHW__RT1)

#else
   #if (FlowSpeedPWM_Resolution == 8u) /* 8bit - PWM */

       #if(FlowSpeedPWM_PWMModeIsCenterAligned)
           #define FlowSpeedPWM_PERIOD_LSB      (*(reg8 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define FlowSpeedPWM_PERIOD_LSB_PTR  ((reg8 *)   FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define FlowSpeedPWM_PERIOD_LSB      (*(reg8 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define FlowSpeedPWM_PERIOD_LSB_PTR  ((reg8 *)   FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (FlowSpeedPWM_PWMModeIsCenterAligned) */

       #define FlowSpeedPWM_COMPARE1_LSB        (*(reg8 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define FlowSpeedPWM_COMPARE1_LSB_PTR    ((reg8 *)   FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define FlowSpeedPWM_COMPARE2_LSB        (*(reg8 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define FlowSpeedPWM_COMPARE2_LSB_PTR    ((reg8 *)   FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define FlowSpeedPWM_COUNTERCAP_LSB      (*(reg8 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define FlowSpeedPWM_COUNTERCAP_LSB_PTR  ((reg8 *)   FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define FlowSpeedPWM_COUNTER_LSB         (*(reg8 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define FlowSpeedPWM_COUNTER_LSB_PTR     ((reg8 *)   FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define FlowSpeedPWM_CAPTURE_LSB         (*(reg8 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define FlowSpeedPWM_CAPTURE_LSB_PTR     ((reg8 *)   FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(FlowSpeedPWM_PWMModeIsCenterAligned)
               #define FlowSpeedPWM_PERIOD_LSB      (*(reg16 *) FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define FlowSpeedPWM_PERIOD_LSB_PTR  ((reg16 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define FlowSpeedPWM_PERIOD_LSB      (*(reg16 *) FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define FlowSpeedPWM_PERIOD_LSB_PTR  ((reg16 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (FlowSpeedPWM_PWMModeIsCenterAligned) */

            #define FlowSpeedPWM_COMPARE1_LSB       (*(reg16 *) FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define FlowSpeedPWM_COMPARE1_LSB_PTR   ((reg16 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define FlowSpeedPWM_COMPARE2_LSB       (*(reg16 *) FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define FlowSpeedPWM_COMPARE2_LSB_PTR   ((reg16 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define FlowSpeedPWM_COUNTERCAP_LSB     (*(reg16 *) FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define FlowSpeedPWM_COUNTERCAP_LSB_PTR ((reg16 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define FlowSpeedPWM_COUNTER_LSB        (*(reg16 *) FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define FlowSpeedPWM_COUNTER_LSB_PTR    ((reg16 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define FlowSpeedPWM_CAPTURE_LSB        (*(reg16 *) FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define FlowSpeedPWM_CAPTURE_LSB_PTR    ((reg16 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(FlowSpeedPWM_PWMModeIsCenterAligned)
               #define FlowSpeedPWM_PERIOD_LSB      (*(reg16 *) FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define FlowSpeedPWM_PERIOD_LSB_PTR  ((reg16 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define FlowSpeedPWM_PERIOD_LSB      (*(reg16 *) FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define FlowSpeedPWM_PERIOD_LSB_PTR  ((reg16 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (FlowSpeedPWM_PWMModeIsCenterAligned) */

            #define FlowSpeedPWM_COMPARE1_LSB       (*(reg16 *) FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define FlowSpeedPWM_COMPARE1_LSB_PTR   ((reg16 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define FlowSpeedPWM_COMPARE2_LSB       (*(reg16 *) FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define FlowSpeedPWM_COMPARE2_LSB_PTR   ((reg16 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define FlowSpeedPWM_COUNTERCAP_LSB     (*(reg16 *) FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define FlowSpeedPWM_COUNTERCAP_LSB_PTR ((reg16 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define FlowSpeedPWM_COUNTER_LSB        (*(reg16 *) FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define FlowSpeedPWM_COUNTER_LSB_PTR    ((reg16 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define FlowSpeedPWM_CAPTURE_LSB        (*(reg16 *) FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define FlowSpeedPWM_CAPTURE_LSB_PTR    ((reg16 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define FlowSpeedPWM_AUX_CONTROLDP1          (*(reg8 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define FlowSpeedPWM_AUX_CONTROLDP1_PTR      ((reg8 *)   FlowSpeedPWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (FlowSpeedPWM_Resolution == 8) */

   #define FlowSpeedPWM_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define FlowSpeedPWM_AUX_CONTROLDP0          (*(reg8 *)  FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define FlowSpeedPWM_AUX_CONTROLDP0_PTR      ((reg8 *)   FlowSpeedPWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (FlowSpeedPWM_UsingFixedFunction) */

#if(FlowSpeedPWM_KillModeMinTime )
    #define FlowSpeedPWM_KILLMODEMINTIME        (*(reg8 *)  FlowSpeedPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define FlowSpeedPWM_KILLMODEMINTIME_PTR    ((reg8 *)   FlowSpeedPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (FlowSpeedPWM_KillModeMinTime ) */

#if(FlowSpeedPWM_DeadBandMode == FlowSpeedPWM__B_PWM__DBM_256_CLOCKS)
    #define FlowSpeedPWM_DEADBAND_COUNT         (*(reg8 *)  FlowSpeedPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define FlowSpeedPWM_DEADBAND_COUNT_PTR     ((reg8 *)   FlowSpeedPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define FlowSpeedPWM_DEADBAND_LSB_PTR       ((reg8 *)   FlowSpeedPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define FlowSpeedPWM_DEADBAND_LSB           (*(reg8 *)  FlowSpeedPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(FlowSpeedPWM_DeadBandMode == FlowSpeedPWM__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (FlowSpeedPWM_UsingFixedFunction)
        #define FlowSpeedPWM_DEADBAND_COUNT         (*(reg8 *)  FlowSpeedPWM_PWMHW__CFG0)
        #define FlowSpeedPWM_DEADBAND_COUNT_PTR     ((reg8 *)   FlowSpeedPWM_PWMHW__CFG0)
        #define FlowSpeedPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << FlowSpeedPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define FlowSpeedPWM_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define FlowSpeedPWM_DEADBAND_COUNT         (*(reg8 *)  FlowSpeedPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define FlowSpeedPWM_DEADBAND_COUNT_PTR     ((reg8 *)   FlowSpeedPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define FlowSpeedPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << FlowSpeedPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define FlowSpeedPWM_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (FlowSpeedPWM_UsingFixedFunction) */
#endif /* (FlowSpeedPWM_DeadBandMode == FlowSpeedPWM__B_PWM__DBM_256_CLOCKS) */



#if (FlowSpeedPWM_UsingFixedFunction)
    #define FlowSpeedPWM_STATUS                 (*(reg8 *) FlowSpeedPWM_PWMHW__SR0)
    #define FlowSpeedPWM_STATUS_PTR             ((reg8 *) FlowSpeedPWM_PWMHW__SR0)
    #define FlowSpeedPWM_STATUS_MASK            (*(reg8 *) FlowSpeedPWM_PWMHW__SR0)
    #define FlowSpeedPWM_STATUS_MASK_PTR        ((reg8 *) FlowSpeedPWM_PWMHW__SR0)
    #define FlowSpeedPWM_CONTROL                (*(reg8 *) FlowSpeedPWM_PWMHW__CFG0)
    #define FlowSpeedPWM_CONTROL_PTR            ((reg8 *) FlowSpeedPWM_PWMHW__CFG0)
    #define FlowSpeedPWM_CONTROL2               (*(reg8 *) FlowSpeedPWM_PWMHW__CFG1)
    #define FlowSpeedPWM_CONTROL3               (*(reg8 *) FlowSpeedPWM_PWMHW__CFG2)
    #define FlowSpeedPWM_GLOBAL_ENABLE          (*(reg8 *) FlowSpeedPWM_PWMHW__PM_ACT_CFG)
    #define FlowSpeedPWM_GLOBAL_ENABLE_PTR      ( (reg8 *) FlowSpeedPWM_PWMHW__PM_ACT_CFG)
    #define FlowSpeedPWM_GLOBAL_STBY_ENABLE     (*(reg8 *) FlowSpeedPWM_PWMHW__PM_STBY_CFG)
    #define FlowSpeedPWM_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) FlowSpeedPWM_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define FlowSpeedPWM_BLOCK_EN_MASK          (FlowSpeedPWM_PWMHW__PM_ACT_MSK)
    #define FlowSpeedPWM_BLOCK_STBY_EN_MASK     (FlowSpeedPWM_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define FlowSpeedPWM_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define FlowSpeedPWM_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define FlowSpeedPWM_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define FlowSpeedPWM_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define FlowSpeedPWM_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define FlowSpeedPWM_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define FlowSpeedPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << FlowSpeedPWM_CTRL_ENABLE_SHIFT)
    #define FlowSpeedPWM_CTRL_RESET             (uint8)((uint8)0x01u << FlowSpeedPWM_CTRL_RESET_SHIFT)
    #define FlowSpeedPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << FlowSpeedPWM_CTRL_CMPMODE2_SHIFT)
    #define FlowSpeedPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << FlowSpeedPWM_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define FlowSpeedPWM_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define FlowSpeedPWM_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << FlowSpeedPWM_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define FlowSpeedPWM_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define FlowSpeedPWM_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define FlowSpeedPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define FlowSpeedPWM_STATUS_TC_INT_EN_MASK_SHIFT            (FlowSpeedPWM_STATUS_TC_SHIFT - 4u)
    #define FlowSpeedPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define FlowSpeedPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (FlowSpeedPWM_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define FlowSpeedPWM_STATUS_TC              (uint8)((uint8)0x01u << FlowSpeedPWM_STATUS_TC_SHIFT)
    #define FlowSpeedPWM_STATUS_CMP1            (uint8)((uint8)0x01u << FlowSpeedPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define FlowSpeedPWM_STATUS_TC_INT_EN_MASK              (uint8)((uint8)FlowSpeedPWM_STATUS_TC >> 4u)
    #define FlowSpeedPWM_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)FlowSpeedPWM_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define FlowSpeedPWM_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define FlowSpeedPWM_RT1_MASK              (uint8)((uint8)0x03u << FlowSpeedPWM_RT1_SHIFT)
    #define FlowSpeedPWM_SYNC                  (uint8)((uint8)0x03u << FlowSpeedPWM_RT1_SHIFT)
    #define FlowSpeedPWM_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define FlowSpeedPWM_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << FlowSpeedPWM_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define FlowSpeedPWM_SYNCDSI_EN            (uint8)((uint8)0x0Fu << FlowSpeedPWM_SYNCDSI_SHIFT)


#else
    #define FlowSpeedPWM_STATUS                (*(reg8 *)   FlowSpeedPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define FlowSpeedPWM_STATUS_PTR            ((reg8 *)    FlowSpeedPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define FlowSpeedPWM_STATUS_MASK           (*(reg8 *)   FlowSpeedPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define FlowSpeedPWM_STATUS_MASK_PTR       ((reg8 *)    FlowSpeedPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define FlowSpeedPWM_STATUS_AUX_CTRL       (*(reg8 *)   FlowSpeedPWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define FlowSpeedPWM_CONTROL               (*(reg8 *)   FlowSpeedPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define FlowSpeedPWM_CONTROL_PTR           ((reg8 *)    FlowSpeedPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define FlowSpeedPWM_CTRL_ENABLE_SHIFT      (0x07u)
    #define FlowSpeedPWM_CTRL_RESET_SHIFT       (0x06u)
    #define FlowSpeedPWM_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define FlowSpeedPWM_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define FlowSpeedPWM_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define FlowSpeedPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << FlowSpeedPWM_CTRL_ENABLE_SHIFT)
    #define FlowSpeedPWM_CTRL_RESET             (uint8)((uint8)0x01u << FlowSpeedPWM_CTRL_RESET_SHIFT)
    #define FlowSpeedPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << FlowSpeedPWM_CTRL_CMPMODE2_SHIFT)
    #define FlowSpeedPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << FlowSpeedPWM_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define FlowSpeedPWM_STATUS_KILL_SHIFT          (0x05u)
    #define FlowSpeedPWM_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define FlowSpeedPWM_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define FlowSpeedPWM_STATUS_TC_SHIFT            (0x02u)
    #define FlowSpeedPWM_STATUS_CMP2_SHIFT          (0x01u)
    #define FlowSpeedPWM_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define FlowSpeedPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (FlowSpeedPWM_STATUS_KILL_SHIFT)
    #define FlowSpeedPWM_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (FlowSpeedPWM_STATUS_FIFONEMPTY_SHIFT)
    #define FlowSpeedPWM_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (FlowSpeedPWM_STATUS_FIFOFULL_SHIFT)
    #define FlowSpeedPWM_STATUS_TC_INT_EN_MASK_SHIFT            (FlowSpeedPWM_STATUS_TC_SHIFT)
    #define FlowSpeedPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (FlowSpeedPWM_STATUS_CMP2_SHIFT)
    #define FlowSpeedPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (FlowSpeedPWM_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define FlowSpeedPWM_STATUS_KILL            (uint8)((uint8)0x00u << FlowSpeedPWM_STATUS_KILL_SHIFT )
    #define FlowSpeedPWM_STATUS_FIFOFULL        (uint8)((uint8)0x01u << FlowSpeedPWM_STATUS_FIFOFULL_SHIFT)
    #define FlowSpeedPWM_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << FlowSpeedPWM_STATUS_FIFONEMPTY_SHIFT)
    #define FlowSpeedPWM_STATUS_TC              (uint8)((uint8)0x01u << FlowSpeedPWM_STATUS_TC_SHIFT)
    #define FlowSpeedPWM_STATUS_CMP2            (uint8)((uint8)0x01u << FlowSpeedPWM_STATUS_CMP2_SHIFT)
    #define FlowSpeedPWM_STATUS_CMP1            (uint8)((uint8)0x01u << FlowSpeedPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define FlowSpeedPWM_STATUS_KILL_INT_EN_MASK            (FlowSpeedPWM_STATUS_KILL)
    #define FlowSpeedPWM_STATUS_FIFOFULL_INT_EN_MASK        (FlowSpeedPWM_STATUS_FIFOFULL)
    #define FlowSpeedPWM_STATUS_FIFONEMPTY_INT_EN_MASK      (FlowSpeedPWM_STATUS_FIFONEMPTY)
    #define FlowSpeedPWM_STATUS_TC_INT_EN_MASK              (FlowSpeedPWM_STATUS_TC)
    #define FlowSpeedPWM_STATUS_CMP2_INT_EN_MASK            (FlowSpeedPWM_STATUS_CMP2)
    #define FlowSpeedPWM_STATUS_CMP1_INT_EN_MASK            (FlowSpeedPWM_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define FlowSpeedPWM_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define FlowSpeedPWM_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define FlowSpeedPWM_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define FlowSpeedPWM_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define FlowSpeedPWM_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* FlowSpeedPWM_UsingFixedFunction */

#endif  /* CY_PWM_FlowSpeedPWM_H */


/* [] END OF FILE */
