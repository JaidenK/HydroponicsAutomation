/*******************************************************************************
* File Name: PingSensorTrigCounter.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "PingSensorTrigCounter.h"

uint8 PingSensorTrigCounter_initVar = 0u;


/*******************************************************************************
* Function Name: PingSensorTrigCounter_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void PingSensorTrigCounter_Init(void) 
{
        #if (!PingSensorTrigCounter_UsingFixedFunction && !PingSensorTrigCounter_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!PingSensorTrigCounter_UsingFixedFunction && !PingSensorTrigCounter_ControlRegRemoved) */
        
        #if(!PingSensorTrigCounter_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 PingSensorTrigCounter_interruptState;
        #endif /* (!PingSensorTrigCounter_UsingFixedFunction) */
        
        #if (PingSensorTrigCounter_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            PingSensorTrigCounter_CONTROL &= PingSensorTrigCounter_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                PingSensorTrigCounter_CONTROL2 &= ((uint8)(~PingSensorTrigCounter_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                PingSensorTrigCounter_CONTROL3 &= ((uint8)(~PingSensorTrigCounter_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (PingSensorTrigCounter_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                PingSensorTrigCounter_CONTROL |= PingSensorTrigCounter_ONESHOT;
            #endif /* (PingSensorTrigCounter_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            PingSensorTrigCounter_CONTROL2 |= PingSensorTrigCounter_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            PingSensorTrigCounter_RT1 &= ((uint8)(~PingSensorTrigCounter_RT1_MASK));
            PingSensorTrigCounter_RT1 |= PingSensorTrigCounter_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            PingSensorTrigCounter_RT1 &= ((uint8)(~PingSensorTrigCounter_SYNCDSI_MASK));
            PingSensorTrigCounter_RT1 |= PingSensorTrigCounter_SYNCDSI_EN;

        #else
            #if(!PingSensorTrigCounter_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = PingSensorTrigCounter_CONTROL & ((uint8)(~PingSensorTrigCounter_CTRL_CMPMODE_MASK));
            PingSensorTrigCounter_CONTROL = ctrl | PingSensorTrigCounter_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = PingSensorTrigCounter_CONTROL & ((uint8)(~PingSensorTrigCounter_CTRL_CAPMODE_MASK));
            
            #if( 0 != PingSensorTrigCounter_CAPTURE_MODE_CONF)
                PingSensorTrigCounter_CONTROL = ctrl | PingSensorTrigCounter_DEFAULT_CAPTURE_MODE;
            #else
                PingSensorTrigCounter_CONTROL = ctrl;
            #endif /* 0 != PingSensorTrigCounter_CAPTURE_MODE */ 
            
            #endif /* (!PingSensorTrigCounter_ControlRegRemoved) */
        #endif /* (PingSensorTrigCounter_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!PingSensorTrigCounter_UsingFixedFunction)
            PingSensorTrigCounter_ClearFIFO();
        #endif /* (!PingSensorTrigCounter_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        PingSensorTrigCounter_WritePeriod(PingSensorTrigCounter_INIT_PERIOD_VALUE);
        #if (!(PingSensorTrigCounter_UsingFixedFunction && (CY_PSOC5A)))
            PingSensorTrigCounter_WriteCounter(PingSensorTrigCounter_INIT_COUNTER_VALUE);
        #endif /* (!(PingSensorTrigCounter_UsingFixedFunction && (CY_PSOC5A))) */
        PingSensorTrigCounter_SetInterruptMode(PingSensorTrigCounter_INIT_INTERRUPTS_MASK);
        
        #if (!PingSensorTrigCounter_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)PingSensorTrigCounter_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            PingSensorTrigCounter_WriteCompare(PingSensorTrigCounter_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            PingSensorTrigCounter_interruptState = CyEnterCriticalSection();
            
            PingSensorTrigCounter_STATUS_AUX_CTRL |= PingSensorTrigCounter_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(PingSensorTrigCounter_interruptState);
            
        #endif /* (!PingSensorTrigCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PingSensorTrigCounter_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void PingSensorTrigCounter_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (PingSensorTrigCounter_UsingFixedFunction)
        PingSensorTrigCounter_GLOBAL_ENABLE |= PingSensorTrigCounter_BLOCK_EN_MASK;
        PingSensorTrigCounter_GLOBAL_STBY_ENABLE |= PingSensorTrigCounter_BLOCK_STBY_EN_MASK;
    #endif /* (PingSensorTrigCounter_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!PingSensorTrigCounter_ControlRegRemoved || PingSensorTrigCounter_UsingFixedFunction)
        PingSensorTrigCounter_CONTROL |= PingSensorTrigCounter_CTRL_ENABLE;                
    #endif /* (!PingSensorTrigCounter_ControlRegRemoved || PingSensorTrigCounter_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: PingSensorTrigCounter_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  PingSensorTrigCounter_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void PingSensorTrigCounter_Start(void) 
{
    if(PingSensorTrigCounter_initVar == 0u)
    {
        PingSensorTrigCounter_Init();
        
        PingSensorTrigCounter_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    PingSensorTrigCounter_Enable();        
}


/*******************************************************************************
* Function Name: PingSensorTrigCounter_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void PingSensorTrigCounter_Stop(void) 
{
    /* Disable Counter */
    #if(!PingSensorTrigCounter_ControlRegRemoved || PingSensorTrigCounter_UsingFixedFunction)
        PingSensorTrigCounter_CONTROL &= ((uint8)(~PingSensorTrigCounter_CTRL_ENABLE));        
    #endif /* (!PingSensorTrigCounter_ControlRegRemoved || PingSensorTrigCounter_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (PingSensorTrigCounter_UsingFixedFunction)
        PingSensorTrigCounter_GLOBAL_ENABLE &= ((uint8)(~PingSensorTrigCounter_BLOCK_EN_MASK));
        PingSensorTrigCounter_GLOBAL_STBY_ENABLE &= ((uint8)(~PingSensorTrigCounter_BLOCK_STBY_EN_MASK));
    #endif /* (PingSensorTrigCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PingSensorTrigCounter_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void PingSensorTrigCounter_SetInterruptMode(uint8 interruptsMask) 
{
    PingSensorTrigCounter_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: PingSensorTrigCounter_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   PingSensorTrigCounter_ReadStatusRegister(void) 
{
    return PingSensorTrigCounter_STATUS;
}


#if(!PingSensorTrigCounter_ControlRegRemoved)
/*******************************************************************************
* Function Name: PingSensorTrigCounter_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   PingSensorTrigCounter_ReadControlRegister(void) 
{
    return PingSensorTrigCounter_CONTROL;
}


/*******************************************************************************
* Function Name: PingSensorTrigCounter_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    PingSensorTrigCounter_WriteControlRegister(uint8 control) 
{
    PingSensorTrigCounter_CONTROL = control;
}

#endif  /* (!PingSensorTrigCounter_ControlRegRemoved) */


#if (!(PingSensorTrigCounter_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: PingSensorTrigCounter_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void PingSensorTrigCounter_WriteCounter(uint8 counter) \
                                   
{
    #if(PingSensorTrigCounter_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (PingSensorTrigCounter_GLOBAL_ENABLE & PingSensorTrigCounter_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        PingSensorTrigCounter_GLOBAL_ENABLE |= PingSensorTrigCounter_BLOCK_EN_MASK;
        CY_SET_REG16(PingSensorTrigCounter_COUNTER_LSB_PTR, (uint16)counter);
        PingSensorTrigCounter_GLOBAL_ENABLE &= ((uint8)(~PingSensorTrigCounter_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(PingSensorTrigCounter_COUNTER_LSB_PTR, counter);
    #endif /* (PingSensorTrigCounter_UsingFixedFunction) */
}
#endif /* (!(PingSensorTrigCounter_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: PingSensorTrigCounter_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) The present value of the counter.
*
*******************************************************************************/
uint8 PingSensorTrigCounter_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(PingSensorTrigCounter_UsingFixedFunction)
		(void)CY_GET_REG16(PingSensorTrigCounter_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(PingSensorTrigCounter_COUNTER_LSB_PTR_8BIT);
	#endif/* (PingSensorTrigCounter_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(PingSensorTrigCounter_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PingSensorTrigCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(PingSensorTrigCounter_STATICCOUNT_LSB_PTR));
    #endif /* (PingSensorTrigCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PingSensorTrigCounter_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) Present Capture value.
*
*******************************************************************************/
uint8 PingSensorTrigCounter_ReadCapture(void) 
{
    #if(PingSensorTrigCounter_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PingSensorTrigCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(PingSensorTrigCounter_STATICCOUNT_LSB_PTR));
    #endif /* (PingSensorTrigCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PingSensorTrigCounter_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint8) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void PingSensorTrigCounter_WritePeriod(uint8 period) 
{
    #if(PingSensorTrigCounter_UsingFixedFunction)
        CY_SET_REG16(PingSensorTrigCounter_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(PingSensorTrigCounter_PERIOD_LSB_PTR, period);
    #endif /* (PingSensorTrigCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PingSensorTrigCounter_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) Present period value.
*
*******************************************************************************/
uint8 PingSensorTrigCounter_ReadPeriod(void) 
{
    #if(PingSensorTrigCounter_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PingSensorTrigCounter_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(PingSensorTrigCounter_PERIOD_LSB_PTR));
    #endif /* (PingSensorTrigCounter_UsingFixedFunction) */
}


#if (!PingSensorTrigCounter_UsingFixedFunction)
/*******************************************************************************
* Function Name: PingSensorTrigCounter_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void PingSensorTrigCounter_WriteCompare(uint8 compare) \
                                   
{
    #if(PingSensorTrigCounter_UsingFixedFunction)
        CY_SET_REG16(PingSensorTrigCounter_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(PingSensorTrigCounter_COMPARE_LSB_PTR, compare);
    #endif /* (PingSensorTrigCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PingSensorTrigCounter_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint8) Present compare value.
*
*******************************************************************************/
uint8 PingSensorTrigCounter_ReadCompare(void) 
{
    return (CY_GET_REG8(PingSensorTrigCounter_COMPARE_LSB_PTR));
}


#if (PingSensorTrigCounter_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: PingSensorTrigCounter_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void PingSensorTrigCounter_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    PingSensorTrigCounter_CONTROL &= ((uint8)(~PingSensorTrigCounter_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    PingSensorTrigCounter_CONTROL |= compareMode;
}
#endif  /* (PingSensorTrigCounter_COMPARE_MODE_SOFTWARE) */


#if (PingSensorTrigCounter_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: PingSensorTrigCounter_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void PingSensorTrigCounter_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    PingSensorTrigCounter_CONTROL &= ((uint8)(~PingSensorTrigCounter_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    PingSensorTrigCounter_CONTROL |= ((uint8)((uint8)captureMode << PingSensorTrigCounter_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (PingSensorTrigCounter_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: PingSensorTrigCounter_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void PingSensorTrigCounter_ClearFIFO(void) 
{

    while(0u != (PingSensorTrigCounter_ReadStatusRegister() & PingSensorTrigCounter_STATUS_FIFONEMP))
    {
        (void)PingSensorTrigCounter_ReadCapture();
    }

}
#endif  /* (!PingSensorTrigCounter_UsingFixedFunction) */


/* [] END OF FILE */

