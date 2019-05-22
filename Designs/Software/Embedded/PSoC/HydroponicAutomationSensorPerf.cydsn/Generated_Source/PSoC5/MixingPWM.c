/*******************************************************************************
* File Name: MixingPWM.c
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

#include "MixingPWM.h"

/* Error message for removed <resource> through optimization */
#ifdef MixingPWM_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* MixingPWM_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 MixingPWM_initVar = 0u;


/*******************************************************************************
* Function Name: MixingPWM_Start
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
*  MixingPWM_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void MixingPWM_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(MixingPWM_initVar == 0u)
    {
        MixingPWM_Init();
        MixingPWM_initVar = 1u;
    }
    MixingPWM_Enable();

}


/*******************************************************************************
* Function Name: MixingPWM_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  MixingPWM_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MixingPWM_Init(void) 
{
    #if (MixingPWM_UsingFixedFunction || MixingPWM_UseControl)
        uint8 ctrl;
    #endif /* (MixingPWM_UsingFixedFunction || MixingPWM_UseControl) */

    #if(!MixingPWM_UsingFixedFunction)
        #if(MixingPWM_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 MixingPWM_interruptState;
        #endif /* (MixingPWM_UseStatus) */
    #endif /* (!MixingPWM_UsingFixedFunction) */

    #if (MixingPWM_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        MixingPWM_CONTROL |= MixingPWM_CFG0_MODE;
        #if (MixingPWM_DeadBand2_4)
            MixingPWM_CONTROL |= MixingPWM_CFG0_DB;
        #endif /* (MixingPWM_DeadBand2_4) */

        ctrl = MixingPWM_CONTROL3 & ((uint8 )(~MixingPWM_CTRL_CMPMODE1_MASK));
        MixingPWM_CONTROL3 = ctrl | MixingPWM_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        MixingPWM_RT1 &= ((uint8)(~MixingPWM_RT1_MASK));
        MixingPWM_RT1 |= MixingPWM_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        MixingPWM_RT1 &= ((uint8)(~MixingPWM_SYNCDSI_MASK));
        MixingPWM_RT1 |= MixingPWM_SYNCDSI_EN;

    #elif (MixingPWM_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = MixingPWM_CONTROL & ((uint8)(~MixingPWM_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~MixingPWM_CTRL_CMPMODE1_MASK));
        MixingPWM_CONTROL = ctrl | MixingPWM_DEFAULT_COMPARE2_MODE |
                                   MixingPWM_DEFAULT_COMPARE1_MODE;
    #endif /* (MixingPWM_UsingFixedFunction) */

    #if (!MixingPWM_UsingFixedFunction)
        #if (MixingPWM_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            MixingPWM_AUX_CONTROLDP0 |= (MixingPWM_AUX_CTRL_FIFO0_CLR);
        #else /* (MixingPWM_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            MixingPWM_AUX_CONTROLDP0 |= (MixingPWM_AUX_CTRL_FIFO0_CLR);
            MixingPWM_AUX_CONTROLDP1 |= (MixingPWM_AUX_CTRL_FIFO0_CLR);
        #endif /* (MixingPWM_Resolution == 8) */

        MixingPWM_WriteCounter(MixingPWM_INIT_PERIOD_VALUE);
    #endif /* (!MixingPWM_UsingFixedFunction) */

    MixingPWM_WritePeriod(MixingPWM_INIT_PERIOD_VALUE);

        #if (MixingPWM_UseOneCompareMode)
            MixingPWM_WriteCompare(MixingPWM_INIT_COMPARE_VALUE1);
        #else
            MixingPWM_WriteCompare1(MixingPWM_INIT_COMPARE_VALUE1);
            MixingPWM_WriteCompare2(MixingPWM_INIT_COMPARE_VALUE2);
        #endif /* (MixingPWM_UseOneCompareMode) */

        #if (MixingPWM_KillModeMinTime)
            MixingPWM_WriteKillTime(MixingPWM_MinimumKillTime);
        #endif /* (MixingPWM_KillModeMinTime) */

        #if (MixingPWM_DeadBandUsed)
            MixingPWM_WriteDeadTime(MixingPWM_INIT_DEAD_TIME);
        #endif /* (MixingPWM_DeadBandUsed) */

    #if (MixingPWM_UseStatus || MixingPWM_UsingFixedFunction)
        MixingPWM_SetInterruptMode(MixingPWM_INIT_INTERRUPTS_MODE);
    #endif /* (MixingPWM_UseStatus || MixingPWM_UsingFixedFunction) */

    #if (MixingPWM_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        MixingPWM_GLOBAL_ENABLE |= MixingPWM_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        MixingPWM_CONTROL2 |= MixingPWM_CTRL2_IRQ_SEL;
    #else
        #if(MixingPWM_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            MixingPWM_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            MixingPWM_STATUS_AUX_CTRL |= MixingPWM_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(MixingPWM_interruptState);

            /* Clear the FIFO to enable the MixingPWM_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            MixingPWM_ClearFIFO();
        #endif /* (MixingPWM_UseStatus) */
    #endif /* (MixingPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MixingPWM_Enable
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
void MixingPWM_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (MixingPWM_UsingFixedFunction)
        MixingPWM_GLOBAL_ENABLE |= MixingPWM_BLOCK_EN_MASK;
        MixingPWM_GLOBAL_STBY_ENABLE |= MixingPWM_BLOCK_STBY_EN_MASK;
    #endif /* (MixingPWM_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (MixingPWM_UseControl || MixingPWM_UsingFixedFunction)
        MixingPWM_CONTROL |= MixingPWM_CTRL_ENABLE;
    #endif /* (MixingPWM_UseControl || MixingPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MixingPWM_Stop
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
void MixingPWM_Stop(void) 
{
    #if (MixingPWM_UseControl || MixingPWM_UsingFixedFunction)
        MixingPWM_CONTROL &= ((uint8)(~MixingPWM_CTRL_ENABLE));
    #endif /* (MixingPWM_UseControl || MixingPWM_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (MixingPWM_UsingFixedFunction)
        MixingPWM_GLOBAL_ENABLE &= ((uint8)(~MixingPWM_BLOCK_EN_MASK));
        MixingPWM_GLOBAL_STBY_ENABLE &= ((uint8)(~MixingPWM_BLOCK_STBY_EN_MASK));
    #endif /* (MixingPWM_UsingFixedFunction) */
}

#if (MixingPWM_UseOneCompareMode)
    #if (MixingPWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: MixingPWM_SetCompareMode
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
        void MixingPWM_SetCompareMode(uint8 comparemode) 
        {
            #if(MixingPWM_UsingFixedFunction)

                #if(0 != MixingPWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << MixingPWM_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != MixingPWM_CTRL_CMPMODE1_SHIFT) */

                MixingPWM_CONTROL3 &= ((uint8)(~MixingPWM_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                MixingPWM_CONTROL3 |= comparemodemasked;

            #elif (MixingPWM_UseControl)

                #if(0 != MixingPWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << MixingPWM_CTRL_CMPMODE1_SHIFT)) &
                                                MixingPWM_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & MixingPWM_CTRL_CMPMODE1_MASK;
                #endif /* (0 != MixingPWM_CTRL_CMPMODE1_SHIFT) */

                #if(0 != MixingPWM_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << MixingPWM_CTRL_CMPMODE2_SHIFT)) &
                                               MixingPWM_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & MixingPWM_CTRL_CMPMODE2_MASK;
                #endif /* (0 != MixingPWM_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                MixingPWM_CONTROL &= ((uint8)(~(MixingPWM_CTRL_CMPMODE1_MASK |
                                            MixingPWM_CTRL_CMPMODE2_MASK)));
                MixingPWM_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (MixingPWM_UsingFixedFunction) */
        }
    #endif /* MixingPWM_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (MixingPWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: MixingPWM_SetCompareMode1
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
        void MixingPWM_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != MixingPWM_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << MixingPWM_CTRL_CMPMODE1_SHIFT)) &
                                           MixingPWM_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & MixingPWM_CTRL_CMPMODE1_MASK;
            #endif /* (0 != MixingPWM_CTRL_CMPMODE1_SHIFT) */

            #if (MixingPWM_UseControl)
                MixingPWM_CONTROL &= ((uint8)(~MixingPWM_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                MixingPWM_CONTROL |= comparemodemasked;
            #endif /* (MixingPWM_UseControl) */
        }
    #endif /* MixingPWM_CompareMode1SW */

#if (MixingPWM_CompareMode2SW)


    /*******************************************************************************
    * Function Name: MixingPWM_SetCompareMode2
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
    void MixingPWM_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != MixingPWM_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << MixingPWM_CTRL_CMPMODE2_SHIFT)) &
                                                 MixingPWM_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & MixingPWM_CTRL_CMPMODE2_MASK;
        #endif /* (0 != MixingPWM_CTRL_CMPMODE2_SHIFT) */

        #if (MixingPWM_UseControl)
            MixingPWM_CONTROL &= ((uint8)(~MixingPWM_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            MixingPWM_CONTROL |= comparemodemasked;
        #endif /* (MixingPWM_UseControl) */
    }
    #endif /*MixingPWM_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!MixingPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: MixingPWM_WriteCounter
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
    void MixingPWM_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(MixingPWM_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: MixingPWM_ReadCounter
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
    uint16 MixingPWM_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(MixingPWM_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(MixingPWM_CAPTURE_LSB_PTR));
    }

    #if (MixingPWM_UseStatus)


        /*******************************************************************************
        * Function Name: MixingPWM_ClearFIFO
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
        void MixingPWM_ClearFIFO(void) 
        {
            while(0u != (MixingPWM_ReadStatusRegister() & MixingPWM_STATUS_FIFONEMPTY))
            {
                (void)MixingPWM_ReadCapture();
            }
        }

    #endif /* MixingPWM_UseStatus */

#endif /* !MixingPWM_UsingFixedFunction */


/*******************************************************************************
* Function Name: MixingPWM_WritePeriod
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
void MixingPWM_WritePeriod(uint16 period) 
{
    #if(MixingPWM_UsingFixedFunction)
        CY_SET_REG16(MixingPWM_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(MixingPWM_PERIOD_LSB_PTR, period);
    #endif /* (MixingPWM_UsingFixedFunction) */
}

#if (MixingPWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: MixingPWM_WriteCompare
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
    void MixingPWM_WriteCompare(uint16 compare) \
                                       
    {
        #if(MixingPWM_UsingFixedFunction)
            CY_SET_REG16(MixingPWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(MixingPWM_COMPARE1_LSB_PTR, compare);
        #endif /* (MixingPWM_UsingFixedFunction) */

        #if (MixingPWM_PWMMode == MixingPWM__B_PWM__DITHER)
            #if(MixingPWM_UsingFixedFunction)
                CY_SET_REG16(MixingPWM_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(MixingPWM_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (MixingPWM_UsingFixedFunction) */
        #endif /* (MixingPWM_PWMMode == MixingPWM__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: MixingPWM_WriteCompare1
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
    void MixingPWM_WriteCompare1(uint16 compare) \
                                        
    {
        #if(MixingPWM_UsingFixedFunction)
            CY_SET_REG16(MixingPWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(MixingPWM_COMPARE1_LSB_PTR, compare);
        #endif /* (MixingPWM_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: MixingPWM_WriteCompare2
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
    void MixingPWM_WriteCompare2(uint16 compare) \
                                        
    {
        #if(MixingPWM_UsingFixedFunction)
            CY_SET_REG16(MixingPWM_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(MixingPWM_COMPARE2_LSB_PTR, compare);
        #endif /* (MixingPWM_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (MixingPWM_DeadBandUsed)


    /*******************************************************************************
    * Function Name: MixingPWM_WriteDeadTime
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
    void MixingPWM_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!MixingPWM_DeadBand2_4)
            CY_SET_REG8(MixingPWM_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            MixingPWM_DEADBAND_COUNT &= ((uint8)(~MixingPWM_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(MixingPWM_DEADBAND_COUNT_SHIFT)
                MixingPWM_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << MixingPWM_DEADBAND_COUNT_SHIFT)) &
                                                    MixingPWM_DEADBAND_COUNT_MASK;
            #else
                MixingPWM_DEADBAND_COUNT |= deadtime & MixingPWM_DEADBAND_COUNT_MASK;
            #endif /* (MixingPWM_DEADBAND_COUNT_SHIFT) */

        #endif /* (!MixingPWM_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: MixingPWM_ReadDeadTime
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
    uint8 MixingPWM_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!MixingPWM_DeadBand2_4)
            return (CY_GET_REG8(MixingPWM_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(MixingPWM_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(MixingPWM_DEADBAND_COUNT & MixingPWM_DEADBAND_COUNT_MASK)) >>
                                                                           MixingPWM_DEADBAND_COUNT_SHIFT));
            #else
                return (MixingPWM_DEADBAND_COUNT & MixingPWM_DEADBAND_COUNT_MASK);
            #endif /* (MixingPWM_DEADBAND_COUNT_SHIFT) */
        #endif /* (!MixingPWM_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (MixingPWM_UseStatus || MixingPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: MixingPWM_SetInterruptMode
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
    void MixingPWM_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(MixingPWM_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: MixingPWM_ReadStatusRegister
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
    uint8 MixingPWM_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(MixingPWM_STATUS_PTR));
    }

#endif /* (MixingPWM_UseStatus || MixingPWM_UsingFixedFunction) */


#if (MixingPWM_UseControl)


    /*******************************************************************************
    * Function Name: MixingPWM_ReadControlRegister
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
    uint8 MixingPWM_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(MixingPWM_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: MixingPWM_WriteControlRegister
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
    void MixingPWM_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(MixingPWM_CONTROL_PTR, control);
    }

#endif /* (MixingPWM_UseControl) */


#if (!MixingPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: MixingPWM_ReadCapture
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
    uint16 MixingPWM_ReadCapture(void) 
    {
        return (CY_GET_REG16(MixingPWM_CAPTURE_LSB_PTR));
    }

#endif /* (!MixingPWM_UsingFixedFunction) */


#if (MixingPWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: MixingPWM_ReadCompare
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
    uint16 MixingPWM_ReadCompare(void) 
    {
        #if(MixingPWM_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(MixingPWM_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(MixingPWM_COMPARE1_LSB_PTR));
        #endif /* (MixingPWM_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: MixingPWM_ReadCompare1
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
    uint16 MixingPWM_ReadCompare1(void) 
    {
        return (CY_GET_REG16(MixingPWM_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: MixingPWM_ReadCompare2
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
    uint16 MixingPWM_ReadCompare2(void) 
    {
        return (CY_GET_REG16(MixingPWM_COMPARE2_LSB_PTR));
    }

#endif /* (MixingPWM_UseOneCompareMode) */


/*******************************************************************************
* Function Name: MixingPWM_ReadPeriod
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
uint16 MixingPWM_ReadPeriod(void) 
{
    #if(MixingPWM_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(MixingPWM_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(MixingPWM_PERIOD_LSB_PTR));
    #endif /* (MixingPWM_UsingFixedFunction) */
}

#if ( MixingPWM_KillModeMinTime)


    /*******************************************************************************
    * Function Name: MixingPWM_WriteKillTime
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
    void MixingPWM_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(MixingPWM_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: MixingPWM_ReadKillTime
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
    uint8 MixingPWM_ReadKillTime(void) 
    {
        return (CY_GET_REG8(MixingPWM_KILLMODEMINTIME_PTR));
    }

#endif /* ( MixingPWM_KillModeMinTime) */

/* [] END OF FILE */
