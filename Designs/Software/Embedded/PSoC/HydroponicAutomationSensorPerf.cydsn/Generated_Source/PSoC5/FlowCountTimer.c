/*******************************************************************************
* File Name: FlowCountTimer.c
* Version 2.70
*
* Description:
*  The Timer component consists of a 8, 16, 24 or 32-bit timer with
*  a selectable period between 2 and 2^Width - 1.  The timer may free run
*  or be used as a capture timer as well.  The capture can be initiated
*  by a positive or negative edge signal as well as via software.
*  A trigger input can be programmed to enable the timer on rising edge
*  falling edge, either edge or continous run.
*  Interrupts may be generated due to a terminal count condition
*  or a capture event.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "FlowCountTimer.h"

uint8 FlowCountTimer_initVar = 0u;


/*******************************************************************************
* Function Name: FlowCountTimer_Init
********************************************************************************
*
* Summary:
*  Initialize to the schematic state
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void FlowCountTimer_Init(void) 
{
    #if(!FlowCountTimer_UsingFixedFunction)
            /* Interrupt State Backup for Critical Region*/
            uint8 FlowCountTimer_interruptState;
    #endif /* Interrupt state back up for Fixed Function only */

    #if (FlowCountTimer_UsingFixedFunction)
        /* Clear all bits but the enable bit (if it's already set) for Timer operation */
        FlowCountTimer_CONTROL &= FlowCountTimer_CTRL_ENABLE;

        /* Clear the mode bits for continuous run mode */
        #if (CY_PSOC5A)
            FlowCountTimer_CONTROL2 &= ((uint8)(~FlowCountTimer_CTRL_MODE_MASK));
        #endif /* Clear bits in CONTROL2 only in PSOC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            FlowCountTimer_CONTROL3 &= ((uint8)(~FlowCountTimer_CTRL_MODE_MASK));
        #endif /* CONTROL3 register exists only in PSoC3 OR PSoC5LP */

        /* Check if One Shot mode is enabled i.e. RunMode !=0*/
        #if (FlowCountTimer_RunModeUsed != 0x0u)
            /* Set 3rd bit of Control register to enable one shot mode */
            FlowCountTimer_CONTROL |= 0x04u;
        #endif /* One Shot enabled only when RunModeUsed is not Continuous*/

        #if (FlowCountTimer_RunModeUsed == 2)
            #if (CY_PSOC5A)
                /* Set last 2 bits of control2 register if one shot(halt on
                interrupt) is enabled*/
                FlowCountTimer_CONTROL2 |= 0x03u;
            #endif /* Set One-Shot Halt on Interrupt bit in CONTROL2 for PSoC5A */

            #if (CY_PSOC3 || CY_PSOC5LP)
                /* Set last 2 bits of control3 register if one shot(halt on
                interrupt) is enabled*/
                FlowCountTimer_CONTROL3 |= 0x03u;
            #endif /* Set One-Shot Halt on Interrupt bit in CONTROL3 for PSoC3 or PSoC5LP */

        #endif /* Remove section if One Shot Halt on Interrupt is not enabled */

        #if (FlowCountTimer_UsingHWEnable != 0)
            #if (CY_PSOC5A)
                /* Set the default Run Mode of the Timer to Continuous */
                FlowCountTimer_CONTROL2 |= FlowCountTimer_CTRL_MODE_PULSEWIDTH;
            #endif /* Set Continuous Run Mode in CONTROL2 for PSoC5A */

            #if (CY_PSOC3 || CY_PSOC5LP)
                /* Clear and Set ROD and COD bits of CFG2 register */
                FlowCountTimer_CONTROL3 &= ((uint8)(~FlowCountTimer_CTRL_RCOD_MASK));
                FlowCountTimer_CONTROL3 |= FlowCountTimer_CTRL_RCOD;

                /* Clear and Enable the HW enable bit in CFG2 register */
                FlowCountTimer_CONTROL3 &= ((uint8)(~FlowCountTimer_CTRL_ENBL_MASK));
                FlowCountTimer_CONTROL3 |= FlowCountTimer_CTRL_ENBL;

                /* Set the default Run Mode of the Timer to Continuous */
                FlowCountTimer_CONTROL3 |= FlowCountTimer_CTRL_MODE_CONTINUOUS;
            #endif /* Set Continuous Run Mode in CONTROL3 for PSoC3ES3 or PSoC5A */

        #endif /* Configure Run Mode with hardware enable */

        /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        FlowCountTimer_RT1 &= ((uint8)(~FlowCountTimer_RT1_MASK));
        FlowCountTimer_RT1 |= FlowCountTimer_SYNC;

        /*Enable DSI Sync all all inputs of the Timer*/
        FlowCountTimer_RT1 &= ((uint8)(~FlowCountTimer_SYNCDSI_MASK));
        FlowCountTimer_RT1 |= FlowCountTimer_SYNCDSI_EN;

        /* Set the IRQ to use the status register interrupts */
        FlowCountTimer_CONTROL2 |= FlowCountTimer_CTRL2_IRQ_SEL;
    #endif /* Configuring registers of fixed function implementation */

    /* Set Initial values from Configuration */
    FlowCountTimer_WritePeriod(FlowCountTimer_INIT_PERIOD);
    FlowCountTimer_WriteCounter(FlowCountTimer_INIT_PERIOD);

    #if (FlowCountTimer_UsingHWCaptureCounter)/* Capture counter is enabled */
        FlowCountTimer_CAPTURE_COUNT_CTRL |= FlowCountTimer_CNTR_ENABLE;
        FlowCountTimer_SetCaptureCount(FlowCountTimer_INIT_CAPTURE_COUNT);
    #endif /* Configure capture counter value */

    #if (!FlowCountTimer_UsingFixedFunction)
        #if (FlowCountTimer_SoftwareCaptureMode)
            FlowCountTimer_SetCaptureMode(FlowCountTimer_INIT_CAPTURE_MODE);
        #endif /* Set Capture Mode for UDB implementation if capture mode is software controlled */

        #if (FlowCountTimer_SoftwareTriggerMode)
            #if (!FlowCountTimer_UDB_CONTROL_REG_REMOVED)
                if (0u == (FlowCountTimer_CONTROL & FlowCountTimer__B_TIMER__TM_SOFTWARE))
                {
                    FlowCountTimer_SetTriggerMode(FlowCountTimer_INIT_TRIGGER_MODE);
                }
            #endif /* (!FlowCountTimer_UDB_CONTROL_REG_REMOVED) */
        #endif /* Set trigger mode for UDB Implementation if trigger mode is software controlled */

        /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
        /* Enter Critical Region*/
        FlowCountTimer_interruptState = CyEnterCriticalSection();

        /* Use the interrupt output of the status register for IRQ output */
        FlowCountTimer_STATUS_AUX_CTRL |= FlowCountTimer_STATUS_ACTL_INT_EN_MASK;

        /* Exit Critical Region*/
        CyExitCriticalSection(FlowCountTimer_interruptState);

        #if (FlowCountTimer_EnableTriggerMode)
            FlowCountTimer_EnableTrigger();
        #endif /* Set Trigger enable bit for UDB implementation in the control register*/
		
		
        #if (FlowCountTimer_InterruptOnCaptureCount && !FlowCountTimer_UDB_CONTROL_REG_REMOVED)
            FlowCountTimer_SetInterruptCount(FlowCountTimer_INIT_INT_CAPTURE_COUNT);
        #endif /* Set interrupt count in UDB implementation if interrupt count feature is checked.*/

        FlowCountTimer_ClearFIFO();
    #endif /* Configure additional features of UDB implementation */

    FlowCountTimer_SetInterruptMode(FlowCountTimer_INIT_INTERRUPT_MODE);
}


/*******************************************************************************
* Function Name: FlowCountTimer_Enable
********************************************************************************
*
* Summary:
*  Enable the Timer
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void FlowCountTimer_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (FlowCountTimer_UsingFixedFunction)
        FlowCountTimer_GLOBAL_ENABLE |= FlowCountTimer_BLOCK_EN_MASK;
        FlowCountTimer_GLOBAL_STBY_ENABLE |= FlowCountTimer_BLOCK_STBY_EN_MASK;
    #endif /* Set Enable bit for enabling Fixed function timer*/

    /* Remove assignment if control register is removed */
    #if (!FlowCountTimer_UDB_CONTROL_REG_REMOVED || FlowCountTimer_UsingFixedFunction)
        FlowCountTimer_CONTROL |= FlowCountTimer_CTRL_ENABLE;
    #endif /* Remove assignment if control register is removed */
}


/*******************************************************************************
* Function Name: FlowCountTimer_Start
********************************************************************************
*
* Summary:
*  The start function initializes the timer with the default values, the
*  enables the timerto begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  FlowCountTimer_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void FlowCountTimer_Start(void) 
{
    if(FlowCountTimer_initVar == 0u)
    {
        FlowCountTimer_Init();

        FlowCountTimer_initVar = 1u;   /* Clear this bit for Initialization */
    }

    /* Enable the Timer */
    FlowCountTimer_Enable();
}


/*******************************************************************************
* Function Name: FlowCountTimer_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the timer, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the timer.
*
*******************************************************************************/
void FlowCountTimer_Stop(void) 
{
    /* Disable Timer */
    #if(!FlowCountTimer_UDB_CONTROL_REG_REMOVED || FlowCountTimer_UsingFixedFunction)
        FlowCountTimer_CONTROL &= ((uint8)(~FlowCountTimer_CTRL_ENABLE));
    #endif /* Remove assignment if control register is removed */

    /* Globally disable the Fixed Function Block chosen */
    #if (FlowCountTimer_UsingFixedFunction)
        FlowCountTimer_GLOBAL_ENABLE &= ((uint8)(~FlowCountTimer_BLOCK_EN_MASK));
        FlowCountTimer_GLOBAL_STBY_ENABLE &= ((uint8)(~FlowCountTimer_BLOCK_STBY_EN_MASK));
    #endif /* Disable global enable for the Timer Fixed function block to stop the Timer*/
}


/*******************************************************************************
* Function Name: FlowCountTimer_SetInterruptMode
********************************************************************************
*
* Summary:
*  This function selects which of the interrupt inputs may cause an interrupt.
*  The twosources are caputure and terminal.  One, both or neither may
*  be selected.
*
* Parameters:
*  interruptMode:   This parameter is used to enable interrups on either/or
*                   terminal count or capture.
*
* Return:
*  void
*
*******************************************************************************/
void FlowCountTimer_SetInterruptMode(uint8 interruptMode) 
{
    FlowCountTimer_STATUS_MASK = interruptMode;
}


/*******************************************************************************
* Function Name: FlowCountTimer_SoftwareCapture
********************************************************************************
*
* Summary:
*  This function forces a capture independent of the capture signal.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Side Effects:
*  An existing hardware capture could be overwritten.
*
*******************************************************************************/
void FlowCountTimer_SoftwareCapture(void) 
{
    /* Generate a software capture by reading the counter register */
    #if(FlowCountTimer_UsingFixedFunction)
        (void)CY_GET_REG16(FlowCountTimer_COUNTER_LSB_PTR);
    #else
        (void)CY_GET_REG8(FlowCountTimer_COUNTER_LSB_PTR_8BIT);
    #endif/* (FlowCountTimer_UsingFixedFunction) */
    /* Capture Data is now in the FIFO */
}


/*******************************************************************************
* Function Name: FlowCountTimer_ReadStatusRegister
********************************************************************************
*
* Summary:
*  Reads the status register and returns it's state. This function should use
*  defined types for the bit-field information as the bits in this register may
*  be permuteable.
*
* Parameters:
*  void
*
* Return:
*  The contents of the status register
*
* Side Effects:
*  Status register bits may be clear on read.
*
*******************************************************************************/
uint8   FlowCountTimer_ReadStatusRegister(void) 
{
    return (FlowCountTimer_STATUS);
}


#if (!FlowCountTimer_UDB_CONTROL_REG_REMOVED) /* Remove API if control register is unused */


/*******************************************************************************
* Function Name: FlowCountTimer_ReadControlRegister
********************************************************************************
*
* Summary:
*  Reads the control register and returns it's value.
*
* Parameters:
*  void
*
* Return:
*  The contents of the control register
*
*******************************************************************************/
uint8 FlowCountTimer_ReadControlRegister(void) 
{
    #if (!FlowCountTimer_UDB_CONTROL_REG_REMOVED) 
        return ((uint8)FlowCountTimer_CONTROL);
    #else
        return (0);
    #endif /* (!FlowCountTimer_UDB_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: FlowCountTimer_WriteControlRegister
********************************************************************************
*
* Summary:
*  Sets the bit-field of the control register.
*
* Parameters:
*  control: The contents of the control register
*
* Return:
*
*******************************************************************************/
void FlowCountTimer_WriteControlRegister(uint8 control) 
{
    #if (!FlowCountTimer_UDB_CONTROL_REG_REMOVED) 
        FlowCountTimer_CONTROL = control;
    #else
        control = 0u;
    #endif /* (!FlowCountTimer_UDB_CONTROL_REG_REMOVED) */
}

#endif /* Remove API if control register is unused */


/*******************************************************************************
* Function Name: FlowCountTimer_ReadPeriod
********************************************************************************
*
* Summary:
*  This function returns the current value of the Period.
*
* Parameters:
*  void
*
* Return:
*  The present value of the counter.
*
*******************************************************************************/
uint32 FlowCountTimer_ReadPeriod(void) 
{
   #if(FlowCountTimer_UsingFixedFunction)
       return ((uint32)CY_GET_REG16(FlowCountTimer_PERIOD_LSB_PTR));
   #else
       return (CY_GET_REG24(FlowCountTimer_PERIOD_LSB_PTR));
   #endif /* (FlowCountTimer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FlowCountTimer_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period: This value may be between 1 and (2^Resolution)-1.  A value of 0 will
*          result in the counter remaining at zero.
*
* Return:
*  void
*
*******************************************************************************/
void FlowCountTimer_WritePeriod(uint32 period) 
{
    #if(FlowCountTimer_UsingFixedFunction)
        uint16 period_temp = (uint16)period;
        CY_SET_REG16(FlowCountTimer_PERIOD_LSB_PTR, period_temp);
    #else
        CY_SET_REG24(FlowCountTimer_PERIOD_LSB_PTR, period);
    #endif /*Write Period value with appropriate resolution suffix depending on UDB or fixed function implementation */
}


/*******************************************************************************
* Function Name: FlowCountTimer_ReadCapture
********************************************************************************
*
* Summary:
*  This function returns the last value captured.
*
* Parameters:
*  void
*
* Return:
*  Present Capture value.
*
*******************************************************************************/
uint32 FlowCountTimer_ReadCapture(void) 
{
   #if(FlowCountTimer_UsingFixedFunction)
       return ((uint32)CY_GET_REG16(FlowCountTimer_CAPTURE_LSB_PTR));
   #else
       return (CY_GET_REG24(FlowCountTimer_CAPTURE_LSB_PTR));
   #endif /* (FlowCountTimer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FlowCountTimer_WriteCounter
********************************************************************************
*
* Summary:
*  This funtion is used to set the counter to a specific value
*
* Parameters:
*  counter:  New counter value.
*
* Return:
*  void
*
*******************************************************************************/
void FlowCountTimer_WriteCounter(uint32 counter) 
{
   #if(FlowCountTimer_UsingFixedFunction)
        /* This functionality is removed until a FixedFunction HW update to
         * allow this register to be written
         */
        CY_SET_REG16(FlowCountTimer_COUNTER_LSB_PTR, (uint16)counter);
        
    #else
        CY_SET_REG24(FlowCountTimer_COUNTER_LSB_PTR, counter);
    #endif /* Set Write Counter only for the UDB implementation (Write Counter not available in fixed function Timer */
}


/*******************************************************************************
* Function Name: FlowCountTimer_ReadCounter
********************************************************************************
*
* Summary:
*  This function returns the current counter value.
*
* Parameters:
*  void
*
* Return:
*  Present compare value.
*
*******************************************************************************/
uint32 FlowCountTimer_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(FlowCountTimer_UsingFixedFunction)
        (void)CY_GET_REG16(FlowCountTimer_COUNTER_LSB_PTR);
    #else
        (void)CY_GET_REG8(FlowCountTimer_COUNTER_LSB_PTR_8BIT);
    #endif/* (FlowCountTimer_UsingFixedFunction) */

    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(FlowCountTimer_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(FlowCountTimer_CAPTURE_LSB_PTR));
    #else
        return (CY_GET_REG24(FlowCountTimer_CAPTURE_LSB_PTR));
    #endif /* (FlowCountTimer_UsingFixedFunction) */
}


#if(!FlowCountTimer_UsingFixedFunction) /* UDB Specific Functions */

    
/*******************************************************************************
 * The functions below this point are only available using the UDB
 * implementation.  If a feature is selected, then the API is enabled.
 ******************************************************************************/


#if (FlowCountTimer_SoftwareCaptureMode)


/*******************************************************************************
* Function Name: FlowCountTimer_SetCaptureMode
********************************************************************************
*
* Summary:
*  This function sets the capture mode to either rising or falling edge.
*
* Parameters:
*  captureMode: This parameter sets the capture mode of the UDB capture feature
*  The parameter values are defined using the
*  #define FlowCountTimer__B_TIMER__CM_NONE 0
#define FlowCountTimer__B_TIMER__CM_RISINGEDGE 1
#define FlowCountTimer__B_TIMER__CM_FALLINGEDGE 2
#define FlowCountTimer__B_TIMER__CM_EITHEREDGE 3
#define FlowCountTimer__B_TIMER__CM_SOFTWARE 4
 identifiers
*  The following are the possible values of the parameter
*  FlowCountTimer__B_TIMER__CM_NONE        - Set Capture mode to None
*  FlowCountTimer__B_TIMER__CM_RISINGEDGE  - Rising edge of Capture input
*  FlowCountTimer__B_TIMER__CM_FALLINGEDGE - Falling edge of Capture input
*  FlowCountTimer__B_TIMER__CM_EITHEREDGE  - Either edge of Capture input
*
* Return:
*  void
*
*******************************************************************************/
void FlowCountTimer_SetCaptureMode(uint8 captureMode) 
{
    /* This must only set to two bits of the control register associated */
    captureMode = ((uint8)((uint8)captureMode << FlowCountTimer_CTRL_CAP_MODE_SHIFT));
    captureMode &= (FlowCountTimer_CTRL_CAP_MODE_MASK);

    #if (!FlowCountTimer_UDB_CONTROL_REG_REMOVED)
        /* Clear the Current Setting */
        FlowCountTimer_CONTROL &= ((uint8)(~FlowCountTimer_CTRL_CAP_MODE_MASK));

        /* Write The New Setting */
        FlowCountTimer_CONTROL |= captureMode;
    #endif /* (!FlowCountTimer_UDB_CONTROL_REG_REMOVED) */
}
#endif /* Remove API if Capture Mode is not Software Controlled */


#if (FlowCountTimer_SoftwareTriggerMode)


/*******************************************************************************
* Function Name: FlowCountTimer_SetTriggerMode
********************************************************************************
*
* Summary:
*  This function sets the trigger input mode
*
* Parameters:
*  triggerMode: Pass one of the pre-defined Trigger Modes (except Software)
    #define FlowCountTimer__B_TIMER__TM_NONE 0x00u
    #define FlowCountTimer__B_TIMER__TM_RISINGEDGE 0x04u
    #define FlowCountTimer__B_TIMER__TM_FALLINGEDGE 0x08u
    #define FlowCountTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
    #define FlowCountTimer__B_TIMER__TM_SOFTWARE 0x10u
*
* Return:
*  void
*
*******************************************************************************/
void FlowCountTimer_SetTriggerMode(uint8 triggerMode) 
{
    /* This must only set to two bits of the control register associated */
    triggerMode &= FlowCountTimer_CTRL_TRIG_MODE_MASK;

    #if (!FlowCountTimer_UDB_CONTROL_REG_REMOVED)   /* Remove assignment if control register is removed */
    
        /* Clear the Current Setting */
        FlowCountTimer_CONTROL &= ((uint8)(~FlowCountTimer_CTRL_TRIG_MODE_MASK));

        /* Write The New Setting */
        FlowCountTimer_CONTROL |= (triggerMode | FlowCountTimer__B_TIMER__TM_SOFTWARE);
    #endif /* Remove code section if control register is not used */
}
#endif /* Remove API if Trigger Mode is not Software Controlled */

#if (FlowCountTimer_EnableTriggerMode)


/*******************************************************************************
* Function Name: FlowCountTimer_EnableTrigger
********************************************************************************
*
* Summary:
*  Sets the control bit enabling Hardware Trigger mode
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void FlowCountTimer_EnableTrigger(void) 
{
    #if (!FlowCountTimer_UDB_CONTROL_REG_REMOVED)   /* Remove assignment if control register is removed */
        FlowCountTimer_CONTROL |= FlowCountTimer_CTRL_TRIG_EN;
    #endif /* Remove code section if control register is not used */
}


/*******************************************************************************
* Function Name: FlowCountTimer_DisableTrigger
********************************************************************************
*
* Summary:
*  Clears the control bit enabling Hardware Trigger mode
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void FlowCountTimer_DisableTrigger(void) 
{
    #if (!FlowCountTimer_UDB_CONTROL_REG_REMOVED )   /* Remove assignment if control register is removed */
        FlowCountTimer_CONTROL &= ((uint8)(~FlowCountTimer_CTRL_TRIG_EN));
    #endif /* Remove code section if control register is not used */
}
#endif /* Remove API is Trigger Mode is set to None */

#if(FlowCountTimer_InterruptOnCaptureCount)


/*******************************************************************************
* Function Name: FlowCountTimer_SetInterruptCount
********************************************************************************
*
* Summary:
*  This function sets the capture count before an interrupt is triggered.
*
* Parameters:
*  interruptCount:  A value between 0 and 3 is valid.  If the value is 0, then
*                   an interrupt will occur each time a capture occurs.
*                   A value of 1 to 3 will cause the interrupt
*                   to delay by the same number of captures.
*
* Return:
*  void
*
*******************************************************************************/
void FlowCountTimer_SetInterruptCount(uint8 interruptCount) 
{
    /* This must only set to two bits of the control register associated */
    interruptCount &= FlowCountTimer_CTRL_INTCNT_MASK;

    #if (!FlowCountTimer_UDB_CONTROL_REG_REMOVED)
        /* Clear the Current Setting */
        FlowCountTimer_CONTROL &= ((uint8)(~FlowCountTimer_CTRL_INTCNT_MASK));
        /* Write The New Setting */
        FlowCountTimer_CONTROL |= interruptCount;
    #endif /* (!FlowCountTimer_UDB_CONTROL_REG_REMOVED) */
}
#endif /* FlowCountTimer_InterruptOnCaptureCount */


#if (FlowCountTimer_UsingHWCaptureCounter)


/*******************************************************************************
* Function Name: FlowCountTimer_SetCaptureCount
********************************************************************************
*
* Summary:
*  This function sets the capture count
*
* Parameters:
*  captureCount: A value between 2 and 127 inclusive is valid.  A value of 1
*                to 127 will cause the interrupt to delay by the same number of
*                captures.
*
* Return:
*  void
*
*******************************************************************************/
void FlowCountTimer_SetCaptureCount(uint8 captureCount) 
{
    FlowCountTimer_CAP_COUNT = captureCount;
}


/*******************************************************************************
* Function Name: FlowCountTimer_ReadCaptureCount
********************************************************************************
*
* Summary:
*  This function reads the capture count setting
*
* Parameters:
*  void
*
* Return:
*  Returns the Capture Count Setting
*
*******************************************************************************/
uint8 FlowCountTimer_ReadCaptureCount(void) 
{
    return ((uint8)FlowCountTimer_CAP_COUNT);
}
#endif /* FlowCountTimer_UsingHWCaptureCounter */


/*******************************************************************************
* Function Name: FlowCountTimer_ClearFIFO
********************************************************************************
*
* Summary:
*  This function clears all capture data from the capture FIFO
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void FlowCountTimer_ClearFIFO(void) 
{
    while(0u != (FlowCountTimer_ReadStatusRegister() & FlowCountTimer_STATUS_FIFONEMP))
    {
        (void)FlowCountTimer_ReadCapture();
    }
}

#endif /* UDB Specific Functions */


/* [] END OF FILE */
