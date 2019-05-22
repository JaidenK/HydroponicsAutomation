/*******************************************************************************
* File Name: pHSampleTimer.c
* Version 2.80
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
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "pHSampleTimer.h"

uint8 pHSampleTimer_initVar = 0u;


/*******************************************************************************
* Function Name: pHSampleTimer_Init
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
void pHSampleTimer_Init(void) 
{
    #if(!pHSampleTimer_UsingFixedFunction)
            /* Interrupt State Backup for Critical Region*/
            uint8 pHSampleTimer_interruptState;
    #endif /* Interrupt state back up for Fixed Function only */

    #if (pHSampleTimer_UsingFixedFunction)
        /* Clear all bits but the enable bit (if it's already set) for Timer operation */
        pHSampleTimer_CONTROL &= pHSampleTimer_CTRL_ENABLE;

        /* Clear the mode bits for continuous run mode */
        #if (CY_PSOC5A)
            pHSampleTimer_CONTROL2 &= ((uint8)(~pHSampleTimer_CTRL_MODE_MASK));
        #endif /* Clear bits in CONTROL2 only in PSOC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            pHSampleTimer_CONTROL3 &= ((uint8)(~pHSampleTimer_CTRL_MODE_MASK));
        #endif /* CONTROL3 register exists only in PSoC3 OR PSoC5LP */

        /* Check if One Shot mode is enabled i.e. RunMode !=0*/
        #if (pHSampleTimer_RunModeUsed != 0x0u)
            /* Set 3rd bit of Control register to enable one shot mode */
            pHSampleTimer_CONTROL |= 0x04u;
        #endif /* One Shot enabled only when RunModeUsed is not Continuous*/

        #if (pHSampleTimer_RunModeUsed == 2)
            #if (CY_PSOC5A)
                /* Set last 2 bits of control2 register if one shot(halt on
                interrupt) is enabled*/
                pHSampleTimer_CONTROL2 |= 0x03u;
            #endif /* Set One-Shot Halt on Interrupt bit in CONTROL2 for PSoC5A */

            #if (CY_PSOC3 || CY_PSOC5LP)
                /* Set last 2 bits of control3 register if one shot(halt on
                interrupt) is enabled*/
                pHSampleTimer_CONTROL3 |= 0x03u;
            #endif /* Set One-Shot Halt on Interrupt bit in CONTROL3 for PSoC3 or PSoC5LP */

        #endif /* Remove section if One Shot Halt on Interrupt is not enabled */

        #if (pHSampleTimer_UsingHWEnable != 0)
            #if (CY_PSOC5A)
                /* Set the default Run Mode of the Timer to Continuous */
                pHSampleTimer_CONTROL2 |= pHSampleTimer_CTRL_MODE_PULSEWIDTH;
            #endif /* Set Continuous Run Mode in CONTROL2 for PSoC5A */

            #if (CY_PSOC3 || CY_PSOC5LP)
                /* Clear and Set ROD and COD bits of CFG2 register */
                pHSampleTimer_CONTROL3 &= ((uint8)(~pHSampleTimer_CTRL_RCOD_MASK));
                pHSampleTimer_CONTROL3 |= pHSampleTimer_CTRL_RCOD;

                /* Clear and Enable the HW enable bit in CFG2 register */
                pHSampleTimer_CONTROL3 &= ((uint8)(~pHSampleTimer_CTRL_ENBL_MASK));
                pHSampleTimer_CONTROL3 |= pHSampleTimer_CTRL_ENBL;

                /* Set the default Run Mode of the Timer to Continuous */
                pHSampleTimer_CONTROL3 |= pHSampleTimer_CTRL_MODE_CONTINUOUS;
            #endif /* Set Continuous Run Mode in CONTROL3 for PSoC3ES3 or PSoC5A */

        #endif /* Configure Run Mode with hardware enable */

        /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        pHSampleTimer_RT1 &= ((uint8)(~pHSampleTimer_RT1_MASK));
        pHSampleTimer_RT1 |= pHSampleTimer_SYNC;

        /*Enable DSI Sync all all inputs of the Timer*/
        pHSampleTimer_RT1 &= ((uint8)(~pHSampleTimer_SYNCDSI_MASK));
        pHSampleTimer_RT1 |= pHSampleTimer_SYNCDSI_EN;

        /* Set the IRQ to use the status register interrupts */
        pHSampleTimer_CONTROL2 |= pHSampleTimer_CTRL2_IRQ_SEL;
    #endif /* Configuring registers of fixed function implementation */

    /* Set Initial values from Configuration */
    pHSampleTimer_WritePeriod(pHSampleTimer_INIT_PERIOD);
    pHSampleTimer_WriteCounter(pHSampleTimer_INIT_PERIOD);

    #if (pHSampleTimer_UsingHWCaptureCounter)/* Capture counter is enabled */
        pHSampleTimer_CAPTURE_COUNT_CTRL |= pHSampleTimer_CNTR_ENABLE;
        pHSampleTimer_SetCaptureCount(pHSampleTimer_INIT_CAPTURE_COUNT);
    #endif /* Configure capture counter value */

    #if (!pHSampleTimer_UsingFixedFunction)
        #if (pHSampleTimer_SoftwareCaptureMode)
            pHSampleTimer_SetCaptureMode(pHSampleTimer_INIT_CAPTURE_MODE);
        #endif /* Set Capture Mode for UDB implementation if capture mode is software controlled */

        #if (pHSampleTimer_SoftwareTriggerMode)
            #if (!pHSampleTimer_UDB_CONTROL_REG_REMOVED)
                if (0u == (pHSampleTimer_CONTROL & pHSampleTimer__B_TIMER__TM_SOFTWARE))
                {
                    pHSampleTimer_SetTriggerMode(pHSampleTimer_INIT_TRIGGER_MODE);
                }
            #endif /* (!pHSampleTimer_UDB_CONTROL_REG_REMOVED) */
        #endif /* Set trigger mode for UDB Implementation if trigger mode is software controlled */

        /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
        /* Enter Critical Region*/
        pHSampleTimer_interruptState = CyEnterCriticalSection();

        /* Use the interrupt output of the status register for IRQ output */
        pHSampleTimer_STATUS_AUX_CTRL |= pHSampleTimer_STATUS_ACTL_INT_EN_MASK;

        /* Exit Critical Region*/
        CyExitCriticalSection(pHSampleTimer_interruptState);

        #if (pHSampleTimer_EnableTriggerMode)
            pHSampleTimer_EnableTrigger();
        #endif /* Set Trigger enable bit for UDB implementation in the control register*/
		
		
        #if (pHSampleTimer_InterruptOnCaptureCount && !pHSampleTimer_UDB_CONTROL_REG_REMOVED)
            pHSampleTimer_SetInterruptCount(pHSampleTimer_INIT_INT_CAPTURE_COUNT);
        #endif /* Set interrupt count in UDB implementation if interrupt count feature is checked.*/

        pHSampleTimer_ClearFIFO();
    #endif /* Configure additional features of UDB implementation */

    pHSampleTimer_SetInterruptMode(pHSampleTimer_INIT_INTERRUPT_MODE);
}


/*******************************************************************************
* Function Name: pHSampleTimer_Enable
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
void pHSampleTimer_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (pHSampleTimer_UsingFixedFunction)
        pHSampleTimer_GLOBAL_ENABLE |= pHSampleTimer_BLOCK_EN_MASK;
        pHSampleTimer_GLOBAL_STBY_ENABLE |= pHSampleTimer_BLOCK_STBY_EN_MASK;
    #endif /* Set Enable bit for enabling Fixed function timer*/

    /* Remove assignment if control register is removed */
    #if (!pHSampleTimer_UDB_CONTROL_REG_REMOVED || pHSampleTimer_UsingFixedFunction)
        pHSampleTimer_CONTROL |= pHSampleTimer_CTRL_ENABLE;
    #endif /* Remove assignment if control register is removed */
}


/*******************************************************************************
* Function Name: pHSampleTimer_Start
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
*  pHSampleTimer_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void pHSampleTimer_Start(void) 
{
    if(pHSampleTimer_initVar == 0u)
    {
        pHSampleTimer_Init();

        pHSampleTimer_initVar = 1u;   /* Clear this bit for Initialization */
    }

    /* Enable the Timer */
    pHSampleTimer_Enable();
}


/*******************************************************************************
* Function Name: pHSampleTimer_Stop
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
void pHSampleTimer_Stop(void) 
{
    /* Disable Timer */
    #if(!pHSampleTimer_UDB_CONTROL_REG_REMOVED || pHSampleTimer_UsingFixedFunction)
        pHSampleTimer_CONTROL &= ((uint8)(~pHSampleTimer_CTRL_ENABLE));
    #endif /* Remove assignment if control register is removed */

    /* Globally disable the Fixed Function Block chosen */
    #if (pHSampleTimer_UsingFixedFunction)
        pHSampleTimer_GLOBAL_ENABLE &= ((uint8)(~pHSampleTimer_BLOCK_EN_MASK));
        pHSampleTimer_GLOBAL_STBY_ENABLE &= ((uint8)(~pHSampleTimer_BLOCK_STBY_EN_MASK));
    #endif /* Disable global enable for the Timer Fixed function block to stop the Timer*/
}


/*******************************************************************************
* Function Name: pHSampleTimer_SetInterruptMode
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
void pHSampleTimer_SetInterruptMode(uint8 interruptMode) 
{
    pHSampleTimer_STATUS_MASK = interruptMode;
}


/*******************************************************************************
* Function Name: pHSampleTimer_SoftwareCapture
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
void pHSampleTimer_SoftwareCapture(void) 
{
    /* Generate a software capture by reading the counter register */
    #if(pHSampleTimer_UsingFixedFunction)
        (void)CY_GET_REG16(pHSampleTimer_COUNTER_LSB_PTR);
    #else
        (void)CY_GET_REG8(pHSampleTimer_COUNTER_LSB_PTR_8BIT);
    #endif/* (pHSampleTimer_UsingFixedFunction) */
    /* Capture Data is now in the FIFO */
}


/*******************************************************************************
* Function Name: pHSampleTimer_ReadStatusRegister
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
uint8   pHSampleTimer_ReadStatusRegister(void) 
{
    return (pHSampleTimer_STATUS);
}


#if (!pHSampleTimer_UDB_CONTROL_REG_REMOVED) /* Remove API if control register is unused */


/*******************************************************************************
* Function Name: pHSampleTimer_ReadControlRegister
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
uint8 pHSampleTimer_ReadControlRegister(void) 
{
    #if (!pHSampleTimer_UDB_CONTROL_REG_REMOVED) 
        return ((uint8)pHSampleTimer_CONTROL);
    #else
        return (0);
    #endif /* (!pHSampleTimer_UDB_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: pHSampleTimer_WriteControlRegister
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
void pHSampleTimer_WriteControlRegister(uint8 control) 
{
    #if (!pHSampleTimer_UDB_CONTROL_REG_REMOVED) 
        pHSampleTimer_CONTROL = control;
    #else
        control = 0u;
    #endif /* (!pHSampleTimer_UDB_CONTROL_REG_REMOVED) */
}

#endif /* Remove API if control register is unused */


/*******************************************************************************
* Function Name: pHSampleTimer_ReadPeriod
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
uint16 pHSampleTimer_ReadPeriod(void) 
{
   #if(pHSampleTimer_UsingFixedFunction)
       return ((uint16)CY_GET_REG16(pHSampleTimer_PERIOD_LSB_PTR));
   #else
       return (CY_GET_REG16(pHSampleTimer_PERIOD_LSB_PTR));
   #endif /* (pHSampleTimer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pHSampleTimer_WritePeriod
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
void pHSampleTimer_WritePeriod(uint16 period) 
{
    #if(pHSampleTimer_UsingFixedFunction)
        uint16 period_temp = (uint16)period;
        CY_SET_REG16(pHSampleTimer_PERIOD_LSB_PTR, period_temp);
    #else
        CY_SET_REG16(pHSampleTimer_PERIOD_LSB_PTR, period);
    #endif /*Write Period value with appropriate resolution suffix depending on UDB or fixed function implementation */
}


/*******************************************************************************
* Function Name: pHSampleTimer_ReadCapture
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
uint16 pHSampleTimer_ReadCapture(void) 
{
   #if(pHSampleTimer_UsingFixedFunction)
       return ((uint16)CY_GET_REG16(pHSampleTimer_CAPTURE_LSB_PTR));
   #else
       return (CY_GET_REG16(pHSampleTimer_CAPTURE_LSB_PTR));
   #endif /* (pHSampleTimer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pHSampleTimer_WriteCounter
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
void pHSampleTimer_WriteCounter(uint16 counter) 
{
   #if(pHSampleTimer_UsingFixedFunction)
        /* This functionality is removed until a FixedFunction HW update to
         * allow this register to be written
         */
        CY_SET_REG16(pHSampleTimer_COUNTER_LSB_PTR, (uint16)counter);
        
    #else
        CY_SET_REG16(pHSampleTimer_COUNTER_LSB_PTR, counter);
    #endif /* Set Write Counter only for the UDB implementation (Write Counter not available in fixed function Timer */
}


/*******************************************************************************
* Function Name: pHSampleTimer_ReadCounter
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
uint16 pHSampleTimer_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(pHSampleTimer_UsingFixedFunction)
        (void)CY_GET_REG16(pHSampleTimer_COUNTER_LSB_PTR);
    #else
        (void)CY_GET_REG8(pHSampleTimer_COUNTER_LSB_PTR_8BIT);
    #endif/* (pHSampleTimer_UsingFixedFunction) */

    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(pHSampleTimer_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(pHSampleTimer_CAPTURE_LSB_PTR));
    #else
        return (CY_GET_REG16(pHSampleTimer_CAPTURE_LSB_PTR));
    #endif /* (pHSampleTimer_UsingFixedFunction) */
}


#if(!pHSampleTimer_UsingFixedFunction) /* UDB Specific Functions */

    
/*******************************************************************************
 * The functions below this point are only available using the UDB
 * implementation.  If a feature is selected, then the API is enabled.
 ******************************************************************************/


#if (pHSampleTimer_SoftwareCaptureMode)


/*******************************************************************************
* Function Name: pHSampleTimer_SetCaptureMode
********************************************************************************
*
* Summary:
*  This function sets the capture mode to either rising or falling edge.
*
* Parameters:
*  captureMode: This parameter sets the capture mode of the UDB capture feature
*  The parameter values are defined using the
*  #define pHSampleTimer__B_TIMER__CM_NONE 0
#define pHSampleTimer__B_TIMER__CM_RISINGEDGE 1
#define pHSampleTimer__B_TIMER__CM_FALLINGEDGE 2
#define pHSampleTimer__B_TIMER__CM_EITHEREDGE 3
#define pHSampleTimer__B_TIMER__CM_SOFTWARE 4
 identifiers
*  The following are the possible values of the parameter
*  pHSampleTimer__B_TIMER__CM_NONE        - Set Capture mode to None
*  pHSampleTimer__B_TIMER__CM_RISINGEDGE  - Rising edge of Capture input
*  pHSampleTimer__B_TIMER__CM_FALLINGEDGE - Falling edge of Capture input
*  pHSampleTimer__B_TIMER__CM_EITHEREDGE  - Either edge of Capture input
*
* Return:
*  void
*
*******************************************************************************/
void pHSampleTimer_SetCaptureMode(uint8 captureMode) 
{
    /* This must only set to two bits of the control register associated */
    captureMode = ((uint8)((uint8)captureMode << pHSampleTimer_CTRL_CAP_MODE_SHIFT));
    captureMode &= (pHSampleTimer_CTRL_CAP_MODE_MASK);

    #if (!pHSampleTimer_UDB_CONTROL_REG_REMOVED)
        /* Clear the Current Setting */
        pHSampleTimer_CONTROL &= ((uint8)(~pHSampleTimer_CTRL_CAP_MODE_MASK));

        /* Write The New Setting */
        pHSampleTimer_CONTROL |= captureMode;
    #endif /* (!pHSampleTimer_UDB_CONTROL_REG_REMOVED) */
}
#endif /* Remove API if Capture Mode is not Software Controlled */


#if (pHSampleTimer_SoftwareTriggerMode)


/*******************************************************************************
* Function Name: pHSampleTimer_SetTriggerMode
********************************************************************************
*
* Summary:
*  This function sets the trigger input mode
*
* Parameters:
*  triggerMode: Pass one of the pre-defined Trigger Modes (except Software)
    #define pHSampleTimer__B_TIMER__TM_NONE 0x00u
    #define pHSampleTimer__B_TIMER__TM_RISINGEDGE 0x04u
    #define pHSampleTimer__B_TIMER__TM_FALLINGEDGE 0x08u
    #define pHSampleTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
    #define pHSampleTimer__B_TIMER__TM_SOFTWARE 0x10u
*
* Return:
*  void
*
*******************************************************************************/
void pHSampleTimer_SetTriggerMode(uint8 triggerMode) 
{
    /* This must only set to two bits of the control register associated */
    triggerMode &= pHSampleTimer_CTRL_TRIG_MODE_MASK;

    #if (!pHSampleTimer_UDB_CONTROL_REG_REMOVED)   /* Remove assignment if control register is removed */
    
        /* Clear the Current Setting */
        pHSampleTimer_CONTROL &= ((uint8)(~pHSampleTimer_CTRL_TRIG_MODE_MASK));

        /* Write The New Setting */
        pHSampleTimer_CONTROL |= (triggerMode | pHSampleTimer__B_TIMER__TM_SOFTWARE);
    #endif /* Remove code section if control register is not used */
}
#endif /* Remove API if Trigger Mode is not Software Controlled */

#if (pHSampleTimer_EnableTriggerMode)


/*******************************************************************************
* Function Name: pHSampleTimer_EnableTrigger
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
void pHSampleTimer_EnableTrigger(void) 
{
    #if (!pHSampleTimer_UDB_CONTROL_REG_REMOVED)   /* Remove assignment if control register is removed */
        pHSampleTimer_CONTROL |= pHSampleTimer_CTRL_TRIG_EN;
    #endif /* Remove code section if control register is not used */
}


/*******************************************************************************
* Function Name: pHSampleTimer_DisableTrigger
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
void pHSampleTimer_DisableTrigger(void) 
{
    #if (!pHSampleTimer_UDB_CONTROL_REG_REMOVED )   /* Remove assignment if control register is removed */
        pHSampleTimer_CONTROL &= ((uint8)(~pHSampleTimer_CTRL_TRIG_EN));
    #endif /* Remove code section if control register is not used */
}
#endif /* Remove API is Trigger Mode is set to None */

#if(pHSampleTimer_InterruptOnCaptureCount)


/*******************************************************************************
* Function Name: pHSampleTimer_SetInterruptCount
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
void pHSampleTimer_SetInterruptCount(uint8 interruptCount) 
{
    /* This must only set to two bits of the control register associated */
    interruptCount &= pHSampleTimer_CTRL_INTCNT_MASK;

    #if (!pHSampleTimer_UDB_CONTROL_REG_REMOVED)
        /* Clear the Current Setting */
        pHSampleTimer_CONTROL &= ((uint8)(~pHSampleTimer_CTRL_INTCNT_MASK));
        /* Write The New Setting */
        pHSampleTimer_CONTROL |= interruptCount;
    #endif /* (!pHSampleTimer_UDB_CONTROL_REG_REMOVED) */
}
#endif /* pHSampleTimer_InterruptOnCaptureCount */


#if (pHSampleTimer_UsingHWCaptureCounter)


/*******************************************************************************
* Function Name: pHSampleTimer_SetCaptureCount
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
void pHSampleTimer_SetCaptureCount(uint8 captureCount) 
{
    pHSampleTimer_CAP_COUNT = captureCount;
}


/*******************************************************************************
* Function Name: pHSampleTimer_ReadCaptureCount
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
uint8 pHSampleTimer_ReadCaptureCount(void) 
{
    return ((uint8)pHSampleTimer_CAP_COUNT);
}
#endif /* pHSampleTimer_UsingHWCaptureCounter */


/*******************************************************************************
* Function Name: pHSampleTimer_ClearFIFO
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
void pHSampleTimer_ClearFIFO(void) 
{
    while(0u != (pHSampleTimer_ReadStatusRegister() & pHSampleTimer_STATUS_FIFONEMP))
    {
        (void)pHSampleTimer_ReadCapture();
    }
}

#endif /* UDB Specific Functions */


/* [] END OF FILE */
