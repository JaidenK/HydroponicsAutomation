/*******************************************************************************
* File Name: PeristalticCounter.c  
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

#include "PeristalticCounter.h"

uint8 PeristalticCounter_initVar = 0u;


/*******************************************************************************
* Function Name: PeristalticCounter_Init
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
void PeristalticCounter_Init(void) 
{
        #if (!PeristalticCounter_UsingFixedFunction && !PeristalticCounter_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!PeristalticCounter_UsingFixedFunction && !PeristalticCounter_ControlRegRemoved) */
        
        #if(!PeristalticCounter_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 PeristalticCounter_interruptState;
        #endif /* (!PeristalticCounter_UsingFixedFunction) */
        
        #if (PeristalticCounter_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            PeristalticCounter_CONTROL &= PeristalticCounter_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                PeristalticCounter_CONTROL2 &= ((uint8)(~PeristalticCounter_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                PeristalticCounter_CONTROL3 &= ((uint8)(~PeristalticCounter_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (PeristalticCounter_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                PeristalticCounter_CONTROL |= PeristalticCounter_ONESHOT;
            #endif /* (PeristalticCounter_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            PeristalticCounter_CONTROL2 |= PeristalticCounter_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            PeristalticCounter_RT1 &= ((uint8)(~PeristalticCounter_RT1_MASK));
            PeristalticCounter_RT1 |= PeristalticCounter_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            PeristalticCounter_RT1 &= ((uint8)(~PeristalticCounter_SYNCDSI_MASK));
            PeristalticCounter_RT1 |= PeristalticCounter_SYNCDSI_EN;

        #else
            #if(!PeristalticCounter_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = PeristalticCounter_CONTROL & ((uint8)(~PeristalticCounter_CTRL_CMPMODE_MASK));
            PeristalticCounter_CONTROL = ctrl | PeristalticCounter_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = PeristalticCounter_CONTROL & ((uint8)(~PeristalticCounter_CTRL_CAPMODE_MASK));
            
            #if( 0 != PeristalticCounter_CAPTURE_MODE_CONF)
                PeristalticCounter_CONTROL = ctrl | PeristalticCounter_DEFAULT_CAPTURE_MODE;
            #else
                PeristalticCounter_CONTROL = ctrl;
            #endif /* 0 != PeristalticCounter_CAPTURE_MODE */ 
            
            #endif /* (!PeristalticCounter_ControlRegRemoved) */
        #endif /* (PeristalticCounter_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!PeristalticCounter_UsingFixedFunction)
            PeristalticCounter_ClearFIFO();
        #endif /* (!PeristalticCounter_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        PeristalticCounter_WritePeriod(PeristalticCounter_INIT_PERIOD_VALUE);
        #if (!(PeristalticCounter_UsingFixedFunction && (CY_PSOC5A)))
            PeristalticCounter_WriteCounter(PeristalticCounter_INIT_COUNTER_VALUE);
        #endif /* (!(PeristalticCounter_UsingFixedFunction && (CY_PSOC5A))) */
        PeristalticCounter_SetInterruptMode(PeristalticCounter_INIT_INTERRUPTS_MASK);
        
        #if (!PeristalticCounter_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)PeristalticCounter_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            PeristalticCounter_WriteCompare(PeristalticCounter_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            PeristalticCounter_interruptState = CyEnterCriticalSection();
            
            PeristalticCounter_STATUS_AUX_CTRL |= PeristalticCounter_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(PeristalticCounter_interruptState);
            
        #endif /* (!PeristalticCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PeristalticCounter_Enable
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
void PeristalticCounter_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (PeristalticCounter_UsingFixedFunction)
        PeristalticCounter_GLOBAL_ENABLE |= PeristalticCounter_BLOCK_EN_MASK;
        PeristalticCounter_GLOBAL_STBY_ENABLE |= PeristalticCounter_BLOCK_STBY_EN_MASK;
    #endif /* (PeristalticCounter_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!PeristalticCounter_ControlRegRemoved || PeristalticCounter_UsingFixedFunction)
        PeristalticCounter_CONTROL |= PeristalticCounter_CTRL_ENABLE;                
    #endif /* (!PeristalticCounter_ControlRegRemoved || PeristalticCounter_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: PeristalticCounter_Start
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
*  PeristalticCounter_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void PeristalticCounter_Start(void) 
{
    if(PeristalticCounter_initVar == 0u)
    {
        PeristalticCounter_Init();
        
        PeristalticCounter_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    PeristalticCounter_Enable();        
}


/*******************************************************************************
* Function Name: PeristalticCounter_Stop
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
void PeristalticCounter_Stop(void) 
{
    /* Disable Counter */
    #if(!PeristalticCounter_ControlRegRemoved || PeristalticCounter_UsingFixedFunction)
        PeristalticCounter_CONTROL &= ((uint8)(~PeristalticCounter_CTRL_ENABLE));        
    #endif /* (!PeristalticCounter_ControlRegRemoved || PeristalticCounter_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (PeristalticCounter_UsingFixedFunction)
        PeristalticCounter_GLOBAL_ENABLE &= ((uint8)(~PeristalticCounter_BLOCK_EN_MASK));
        PeristalticCounter_GLOBAL_STBY_ENABLE &= ((uint8)(~PeristalticCounter_BLOCK_STBY_EN_MASK));
    #endif /* (PeristalticCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PeristalticCounter_SetInterruptMode
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
void PeristalticCounter_SetInterruptMode(uint8 interruptsMask) 
{
    PeristalticCounter_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: PeristalticCounter_ReadStatusRegister
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
uint8   PeristalticCounter_ReadStatusRegister(void) 
{
    return PeristalticCounter_STATUS;
}


#if(!PeristalticCounter_ControlRegRemoved)
/*******************************************************************************
* Function Name: PeristalticCounter_ReadControlRegister
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
uint8   PeristalticCounter_ReadControlRegister(void) 
{
    return PeristalticCounter_CONTROL;
}


/*******************************************************************************
* Function Name: PeristalticCounter_WriteControlRegister
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
void    PeristalticCounter_WriteControlRegister(uint8 control) 
{
    PeristalticCounter_CONTROL = control;
}

#endif  /* (!PeristalticCounter_ControlRegRemoved) */


#if (!(PeristalticCounter_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: PeristalticCounter_WriteCounter
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
void PeristalticCounter_WriteCounter(uint16 counter) \
                                   
{
    #if(PeristalticCounter_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (PeristalticCounter_GLOBAL_ENABLE & PeristalticCounter_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        PeristalticCounter_GLOBAL_ENABLE |= PeristalticCounter_BLOCK_EN_MASK;
        CY_SET_REG16(PeristalticCounter_COUNTER_LSB_PTR, (uint16)counter);
        PeristalticCounter_GLOBAL_ENABLE &= ((uint8)(~PeristalticCounter_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(PeristalticCounter_COUNTER_LSB_PTR, counter);
    #endif /* (PeristalticCounter_UsingFixedFunction) */
}
#endif /* (!(PeristalticCounter_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: PeristalticCounter_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) The present value of the counter.
*
*******************************************************************************/
uint16 PeristalticCounter_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(PeristalticCounter_UsingFixedFunction)
		(void)CY_GET_REG16(PeristalticCounter_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(PeristalticCounter_COUNTER_LSB_PTR_8BIT);
	#endif/* (PeristalticCounter_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(PeristalticCounter_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(PeristalticCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(PeristalticCounter_STATICCOUNT_LSB_PTR));
    #endif /* (PeristalticCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PeristalticCounter_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint16) Present Capture value.
*
*******************************************************************************/
uint16 PeristalticCounter_ReadCapture(void) 
{
    #if(PeristalticCounter_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(PeristalticCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(PeristalticCounter_STATICCOUNT_LSB_PTR));
    #endif /* (PeristalticCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PeristalticCounter_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint16) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void PeristalticCounter_WritePeriod(uint16 period) 
{
    #if(PeristalticCounter_UsingFixedFunction)
        CY_SET_REG16(PeristalticCounter_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(PeristalticCounter_PERIOD_LSB_PTR, period);
    #endif /* (PeristalticCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PeristalticCounter_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) Present period value.
*
*******************************************************************************/
uint16 PeristalticCounter_ReadPeriod(void) 
{
    #if(PeristalticCounter_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(PeristalticCounter_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(PeristalticCounter_PERIOD_LSB_PTR));
    #endif /* (PeristalticCounter_UsingFixedFunction) */
}


#if (!PeristalticCounter_UsingFixedFunction)
/*******************************************************************************
* Function Name: PeristalticCounter_WriteCompare
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
void PeristalticCounter_WriteCompare(uint16 compare) \
                                   
{
    #if(PeristalticCounter_UsingFixedFunction)
        CY_SET_REG16(PeristalticCounter_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(PeristalticCounter_COMPARE_LSB_PTR, compare);
    #endif /* (PeristalticCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PeristalticCounter_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint16) Present compare value.
*
*******************************************************************************/
uint16 PeristalticCounter_ReadCompare(void) 
{
    return (CY_GET_REG16(PeristalticCounter_COMPARE_LSB_PTR));
}


#if (PeristalticCounter_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: PeristalticCounter_SetCompareMode
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
void PeristalticCounter_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    PeristalticCounter_CONTROL &= ((uint8)(~PeristalticCounter_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    PeristalticCounter_CONTROL |= compareMode;
}
#endif  /* (PeristalticCounter_COMPARE_MODE_SOFTWARE) */


#if (PeristalticCounter_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: PeristalticCounter_SetCaptureMode
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
void PeristalticCounter_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    PeristalticCounter_CONTROL &= ((uint8)(~PeristalticCounter_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    PeristalticCounter_CONTROL |= ((uint8)((uint8)captureMode << PeristalticCounter_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (PeristalticCounter_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: PeristalticCounter_ClearFIFO
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
void PeristalticCounter_ClearFIFO(void) 
{

    while(0u != (PeristalticCounter_ReadStatusRegister() & PeristalticCounter_STATUS_FIFONEMP))
    {
        (void)PeristalticCounter_ReadCapture();
    }

}
#endif  /* (!PeristalticCounter_UsingFixedFunction) */


/* [] END OF FILE */

