/*******************************************************************************
* File Name: PeristalticPWM.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "PeristalticPWM.h"

/* Error message for removed <resource> through optimization */
#ifdef PeristalticPWM_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* PeristalticPWM_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 PeristalticPWM_initVar = 0u;


/*******************************************************************************
* Function Name: PeristalticPWM_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PeristalticPWM_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void PeristalticPWM_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(PeristalticPWM_initVar == 0u)
    {
        PeristalticPWM_Init();
        PeristalticPWM_initVar = 1u;
    }
    PeristalticPWM_Enable();

}


/*******************************************************************************
* Function Name: PeristalticPWM_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  PeristalticPWM_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PeristalticPWM_Init(void) 
{
    #if (PeristalticPWM_UsingFixedFunction || PeristalticPWM_UseControl)
        uint8 ctrl;
    #endif /* (PeristalticPWM_UsingFixedFunction || PeristalticPWM_UseControl) */

    #if(!PeristalticPWM_UsingFixedFunction)
        #if(PeristalticPWM_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 PeristalticPWM_interruptState;
        #endif /* (PeristalticPWM_UseStatus) */
    #endif /* (!PeristalticPWM_UsingFixedFunction) */

    #if (PeristalticPWM_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        PeristalticPWM_CONTROL |= PeristalticPWM_CFG0_MODE;
        #if (PeristalticPWM_DeadBand2_4)
            PeristalticPWM_CONTROL |= PeristalticPWM_CFG0_DB;
        #endif /* (PeristalticPWM_DeadBand2_4) */

        ctrl = PeristalticPWM_CONTROL3 & ((uint8 )(~PeristalticPWM_CTRL_CMPMODE1_MASK));
        PeristalticPWM_CONTROL3 = ctrl | PeristalticPWM_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        PeristalticPWM_RT1 &= ((uint8)(~PeristalticPWM_RT1_MASK));
        PeristalticPWM_RT1 |= PeristalticPWM_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        PeristalticPWM_RT1 &= ((uint8)(~PeristalticPWM_SYNCDSI_MASK));
        PeristalticPWM_RT1 |= PeristalticPWM_SYNCDSI_EN;

    #elif (PeristalticPWM_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = PeristalticPWM_CONTROL & ((uint8)(~PeristalticPWM_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~PeristalticPWM_CTRL_CMPMODE1_MASK));
        PeristalticPWM_CONTROL = ctrl | PeristalticPWM_DEFAULT_COMPARE2_MODE |
                                   PeristalticPWM_DEFAULT_COMPARE1_MODE;
    #endif /* (PeristalticPWM_UsingFixedFunction) */

    #if (!PeristalticPWM_UsingFixedFunction)
        #if (PeristalticPWM_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            PeristalticPWM_AUX_CONTROLDP0 |= (PeristalticPWM_AUX_CTRL_FIFO0_CLR);
        #else /* (PeristalticPWM_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            PeristalticPWM_AUX_CONTROLDP0 |= (PeristalticPWM_AUX_CTRL_FIFO0_CLR);
            PeristalticPWM_AUX_CONTROLDP1 |= (PeristalticPWM_AUX_CTRL_FIFO0_CLR);
        #endif /* (PeristalticPWM_Resolution == 8) */

        PeristalticPWM_WriteCounter(PeristalticPWM_INIT_PERIOD_VALUE);
    #endif /* (!PeristalticPWM_UsingFixedFunction) */

    PeristalticPWM_WritePeriod(PeristalticPWM_INIT_PERIOD_VALUE);

        #if (PeristalticPWM_UseOneCompareMode)
            PeristalticPWM_WriteCompare(PeristalticPWM_INIT_COMPARE_VALUE1);
        #else
            PeristalticPWM_WriteCompare1(PeristalticPWM_INIT_COMPARE_VALUE1);
            PeristalticPWM_WriteCompare2(PeristalticPWM_INIT_COMPARE_VALUE2);
        #endif /* (PeristalticPWM_UseOneCompareMode) */

        #if (PeristalticPWM_KillModeMinTime)
            PeristalticPWM_WriteKillTime(PeristalticPWM_MinimumKillTime);
        #endif /* (PeristalticPWM_KillModeMinTime) */

        #if (PeristalticPWM_DeadBandUsed)
            PeristalticPWM_WriteDeadTime(PeristalticPWM_INIT_DEAD_TIME);
        #endif /* (PeristalticPWM_DeadBandUsed) */

    #if (PeristalticPWM_UseStatus || PeristalticPWM_UsingFixedFunction)
        PeristalticPWM_SetInterruptMode(PeristalticPWM_INIT_INTERRUPTS_MODE);
    #endif /* (PeristalticPWM_UseStatus || PeristalticPWM_UsingFixedFunction) */

    #if (PeristalticPWM_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        PeristalticPWM_GLOBAL_ENABLE |= PeristalticPWM_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        PeristalticPWM_CONTROL2 |= PeristalticPWM_CTRL2_IRQ_SEL;
    #else
        #if(PeristalticPWM_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            PeristalticPWM_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            PeristalticPWM_STATUS_AUX_CTRL |= PeristalticPWM_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(PeristalticPWM_interruptState);

            /* Clear the FIFO to enable the PeristalticPWM_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            PeristalticPWM_ClearFIFO();
        #endif /* (PeristalticPWM_UseStatus) */
    #endif /* (PeristalticPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PeristalticPWM_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void PeristalticPWM_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (PeristalticPWM_UsingFixedFunction)
        PeristalticPWM_GLOBAL_ENABLE |= PeristalticPWM_BLOCK_EN_MASK;
        PeristalticPWM_GLOBAL_STBY_ENABLE |= PeristalticPWM_BLOCK_STBY_EN_MASK;
    #endif /* (PeristalticPWM_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (PeristalticPWM_UseControl || PeristalticPWM_UsingFixedFunction)
        PeristalticPWM_CONTROL |= PeristalticPWM_CTRL_ENABLE;
    #endif /* (PeristalticPWM_UseControl || PeristalticPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PeristalticPWM_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void PeristalticPWM_Stop(void) 
{
    #if (PeristalticPWM_UseControl || PeristalticPWM_UsingFixedFunction)
        PeristalticPWM_CONTROL &= ((uint8)(~PeristalticPWM_CTRL_ENABLE));
    #endif /* (PeristalticPWM_UseControl || PeristalticPWM_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (PeristalticPWM_UsingFixedFunction)
        PeristalticPWM_GLOBAL_ENABLE &= ((uint8)(~PeristalticPWM_BLOCK_EN_MASK));
        PeristalticPWM_GLOBAL_STBY_ENABLE &= ((uint8)(~PeristalticPWM_BLOCK_STBY_EN_MASK));
    #endif /* (PeristalticPWM_UsingFixedFunction) */
}

#if (PeristalticPWM_UseOneCompareMode)
    #if (PeristalticPWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: PeristalticPWM_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PeristalticPWM_SetCompareMode(uint8 comparemode) 
        {
            #if(PeristalticPWM_UsingFixedFunction)

                #if(0 != PeristalticPWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << PeristalticPWM_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != PeristalticPWM_CTRL_CMPMODE1_SHIFT) */

                PeristalticPWM_CONTROL3 &= ((uint8)(~PeristalticPWM_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                PeristalticPWM_CONTROL3 |= comparemodemasked;

            #elif (PeristalticPWM_UseControl)

                #if(0 != PeristalticPWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << PeristalticPWM_CTRL_CMPMODE1_SHIFT)) &
                                                PeristalticPWM_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & PeristalticPWM_CTRL_CMPMODE1_MASK;
                #endif /* (0 != PeristalticPWM_CTRL_CMPMODE1_SHIFT) */

                #if(0 != PeristalticPWM_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << PeristalticPWM_CTRL_CMPMODE2_SHIFT)) &
                                               PeristalticPWM_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & PeristalticPWM_CTRL_CMPMODE2_MASK;
                #endif /* (0 != PeristalticPWM_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                PeristalticPWM_CONTROL &= ((uint8)(~(PeristalticPWM_CTRL_CMPMODE1_MASK |
                                            PeristalticPWM_CTRL_CMPMODE2_MASK)));
                PeristalticPWM_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (PeristalticPWM_UsingFixedFunction) */
        }
    #endif /* PeristalticPWM_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (PeristalticPWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: PeristalticPWM_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PeristalticPWM_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != PeristalticPWM_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << PeristalticPWM_CTRL_CMPMODE1_SHIFT)) &
                                           PeristalticPWM_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & PeristalticPWM_CTRL_CMPMODE1_MASK;
            #endif /* (0 != PeristalticPWM_CTRL_CMPMODE1_SHIFT) */

            #if (PeristalticPWM_UseControl)
                PeristalticPWM_CONTROL &= ((uint8)(~PeristalticPWM_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                PeristalticPWM_CONTROL |= comparemodemasked;
            #endif /* (PeristalticPWM_UseControl) */
        }
    #endif /* PeristalticPWM_CompareMode1SW */

#if (PeristalticPWM_CompareMode2SW)


    /*******************************************************************************
    * Function Name: PeristalticPWM_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PeristalticPWM_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != PeristalticPWM_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << PeristalticPWM_CTRL_CMPMODE2_SHIFT)) &
                                                 PeristalticPWM_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & PeristalticPWM_CTRL_CMPMODE2_MASK;
        #endif /* (0 != PeristalticPWM_CTRL_CMPMODE2_SHIFT) */

        #if (PeristalticPWM_UseControl)
            PeristalticPWM_CONTROL &= ((uint8)(~PeristalticPWM_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            PeristalticPWM_CONTROL |= comparemodemasked;
        #endif /* (PeristalticPWM_UseControl) */
    }
    #endif /*PeristalticPWM_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!PeristalticPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PeristalticPWM_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void PeristalticPWM_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(PeristalticPWM_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: PeristalticPWM_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint8 PeristalticPWM_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(PeristalticPWM_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG8(PeristalticPWM_CAPTURE_LSB_PTR));
    }

    #if (PeristalticPWM_UseStatus)


        /*******************************************************************************
        * Function Name: PeristalticPWM_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PeristalticPWM_ClearFIFO(void) 
        {
            while(0u != (PeristalticPWM_ReadStatusRegister() & PeristalticPWM_STATUS_FIFONEMPTY))
            {
                (void)PeristalticPWM_ReadCapture();
            }
        }

    #endif /* PeristalticPWM_UseStatus */

#endif /* !PeristalticPWM_UsingFixedFunction */


/*******************************************************************************
* Function Name: PeristalticPWM_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void PeristalticPWM_WritePeriod(uint8 period) 
{
    #if(PeristalticPWM_UsingFixedFunction)
        CY_SET_REG16(PeristalticPWM_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(PeristalticPWM_PERIOD_LSB_PTR, period);
    #endif /* (PeristalticPWM_UsingFixedFunction) */
}

#if (PeristalticPWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: PeristalticPWM_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void PeristalticPWM_WriteCompare(uint8 compare) \
                                       
    {
        #if(PeristalticPWM_UsingFixedFunction)
            CY_SET_REG16(PeristalticPWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(PeristalticPWM_COMPARE1_LSB_PTR, compare);
        #endif /* (PeristalticPWM_UsingFixedFunction) */

        #if (PeristalticPWM_PWMMode == PeristalticPWM__B_PWM__DITHER)
            #if(PeristalticPWM_UsingFixedFunction)
                CY_SET_REG16(PeristalticPWM_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG8(PeristalticPWM_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (PeristalticPWM_UsingFixedFunction) */
        #endif /* (PeristalticPWM_PWMMode == PeristalticPWM__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: PeristalticPWM_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PeristalticPWM_WriteCompare1(uint8 compare) \
                                        
    {
        #if(PeristalticPWM_UsingFixedFunction)
            CY_SET_REG16(PeristalticPWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(PeristalticPWM_COMPARE1_LSB_PTR, compare);
        #endif /* (PeristalticPWM_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: PeristalticPWM_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PeristalticPWM_WriteCompare2(uint8 compare) \
                                        
    {
        #if(PeristalticPWM_UsingFixedFunction)
            CY_SET_REG16(PeristalticPWM_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(PeristalticPWM_COMPARE2_LSB_PTR, compare);
        #endif /* (PeristalticPWM_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (PeristalticPWM_DeadBandUsed)


    /*******************************************************************************
    * Function Name: PeristalticPWM_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PeristalticPWM_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!PeristalticPWM_DeadBand2_4)
            CY_SET_REG8(PeristalticPWM_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            PeristalticPWM_DEADBAND_COUNT &= ((uint8)(~PeristalticPWM_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(PeristalticPWM_DEADBAND_COUNT_SHIFT)
                PeristalticPWM_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << PeristalticPWM_DEADBAND_COUNT_SHIFT)) &
                                                    PeristalticPWM_DEADBAND_COUNT_MASK;
            #else
                PeristalticPWM_DEADBAND_COUNT |= deadtime & PeristalticPWM_DEADBAND_COUNT_MASK;
            #endif /* (PeristalticPWM_DEADBAND_COUNT_SHIFT) */

        #endif /* (!PeristalticPWM_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: PeristalticPWM_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 PeristalticPWM_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!PeristalticPWM_DeadBand2_4)
            return (CY_GET_REG8(PeristalticPWM_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(PeristalticPWM_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(PeristalticPWM_DEADBAND_COUNT & PeristalticPWM_DEADBAND_COUNT_MASK)) >>
                                                                           PeristalticPWM_DEADBAND_COUNT_SHIFT));
            #else
                return (PeristalticPWM_DEADBAND_COUNT & PeristalticPWM_DEADBAND_COUNT_MASK);
            #endif /* (PeristalticPWM_DEADBAND_COUNT_SHIFT) */
        #endif /* (!PeristalticPWM_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (PeristalticPWM_UseStatus || PeristalticPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PeristalticPWM_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PeristalticPWM_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(PeristalticPWM_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: PeristalticPWM_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 PeristalticPWM_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(PeristalticPWM_STATUS_PTR));
    }

#endif /* (PeristalticPWM_UseStatus || PeristalticPWM_UsingFixedFunction) */


#if (PeristalticPWM_UseControl)


    /*******************************************************************************
    * Function Name: PeristalticPWM_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 PeristalticPWM_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(PeristalticPWM_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: PeristalticPWM_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PeristalticPWM_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(PeristalticPWM_CONTROL_PTR, control);
    }

#endif /* (PeristalticPWM_UseControl) */


#if (!PeristalticPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PeristalticPWM_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint8 PeristalticPWM_ReadCapture(void) 
    {
        return (CY_GET_REG8(PeristalticPWM_CAPTURE_LSB_PTR));
    }

#endif /* (!PeristalticPWM_UsingFixedFunction) */


#if (PeristalticPWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: PeristalticPWM_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint8 PeristalticPWM_ReadCompare(void) 
    {
        #if(PeristalticPWM_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(PeristalticPWM_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(PeristalticPWM_COMPARE1_LSB_PTR));
        #endif /* (PeristalticPWM_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: PeristalticPWM_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 PeristalticPWM_ReadCompare1(void) 
    {
        return (CY_GET_REG8(PeristalticPWM_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: PeristalticPWM_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 PeristalticPWM_ReadCompare2(void) 
    {
        return (CY_GET_REG8(PeristalticPWM_COMPARE2_LSB_PTR));
    }

#endif /* (PeristalticPWM_UseOneCompareMode) */


/*******************************************************************************
* Function Name: PeristalticPWM_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint8 PeristalticPWM_ReadPeriod(void) 
{
    #if(PeristalticPWM_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PeristalticPWM_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(PeristalticPWM_PERIOD_LSB_PTR));
    #endif /* (PeristalticPWM_UsingFixedFunction) */
}

#if ( PeristalticPWM_KillModeMinTime)


    /*******************************************************************************
    * Function Name: PeristalticPWM_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PeristalticPWM_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(PeristalticPWM_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: PeristalticPWM_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 PeristalticPWM_ReadKillTime(void) 
    {
        return (CY_GET_REG8(PeristalticPWM_KILLMODEMINTIME_PTR));
    }

#endif /* ( PeristalticPWM_KillModeMinTime) */

/* [] END OF FILE */
