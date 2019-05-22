/*******************************************************************************
* File Name: FlowSensorCounter.c  
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

#include "FlowSensorCounter.h"

uint8 FlowSensorCounter_initVar = 0u;


/*******************************************************************************
* Function Name: FlowSensorCounter_Init
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
void FlowSensorCounter_Init(void) 
{
        #if (!FlowSensorCounter_UsingFixedFunction && !FlowSensorCounter_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!FlowSensorCounter_UsingFixedFunction && !FlowSensorCounter_ControlRegRemoved) */
        
        #if(!FlowSensorCounter_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 FlowSensorCounter_interruptState;
        #endif /* (!FlowSensorCounter_UsingFixedFunction) */
        
        #if (FlowSensorCounter_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            FlowSensorCounter_CONTROL &= FlowSensorCounter_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                FlowSensorCounter_CONTROL2 &= ((uint8)(~FlowSensorCounter_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                FlowSensorCounter_CONTROL3 &= ((uint8)(~FlowSensorCounter_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (FlowSensorCounter_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                FlowSensorCounter_CONTROL |= FlowSensorCounter_ONESHOT;
            #endif /* (FlowSensorCounter_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            FlowSensorCounter_CONTROL2 |= FlowSensorCounter_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            FlowSensorCounter_RT1 &= ((uint8)(~FlowSensorCounter_RT1_MASK));
            FlowSensorCounter_RT1 |= FlowSensorCounter_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            FlowSensorCounter_RT1 &= ((uint8)(~FlowSensorCounter_SYNCDSI_MASK));
            FlowSensorCounter_RT1 |= FlowSensorCounter_SYNCDSI_EN;

        #else
            #if(!FlowSensorCounter_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = FlowSensorCounter_CONTROL & ((uint8)(~FlowSensorCounter_CTRL_CMPMODE_MASK));
            FlowSensorCounter_CONTROL = ctrl | FlowSensorCounter_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = FlowSensorCounter_CONTROL & ((uint8)(~FlowSensorCounter_CTRL_CAPMODE_MASK));
            
            #if( 0 != FlowSensorCounter_CAPTURE_MODE_CONF)
                FlowSensorCounter_CONTROL = ctrl | FlowSensorCounter_DEFAULT_CAPTURE_MODE;
            #else
                FlowSensorCounter_CONTROL = ctrl;
            #endif /* 0 != FlowSensorCounter_CAPTURE_MODE */ 
            
            #endif /* (!FlowSensorCounter_ControlRegRemoved) */
        #endif /* (FlowSensorCounter_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!FlowSensorCounter_UsingFixedFunction)
            FlowSensorCounter_ClearFIFO();
        #endif /* (!FlowSensorCounter_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        FlowSensorCounter_WritePeriod(FlowSensorCounter_INIT_PERIOD_VALUE);
        #if (!(FlowSensorCounter_UsingFixedFunction && (CY_PSOC5A)))
            FlowSensorCounter_WriteCounter(FlowSensorCounter_INIT_COUNTER_VALUE);
        #endif /* (!(FlowSensorCounter_UsingFixedFunction && (CY_PSOC5A))) */
        FlowSensorCounter_SetInterruptMode(FlowSensorCounter_INIT_INTERRUPTS_MASK);
        
        #if (!FlowSensorCounter_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)FlowSensorCounter_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            FlowSensorCounter_WriteCompare(FlowSensorCounter_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            FlowSensorCounter_interruptState = CyEnterCriticalSection();
            
            FlowSensorCounter_STATUS_AUX_CTRL |= FlowSensorCounter_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(FlowSensorCounter_interruptState);
            
        #endif /* (!FlowSensorCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FlowSensorCounter_Enable
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
void FlowSensorCounter_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (FlowSensorCounter_UsingFixedFunction)
        FlowSensorCounter_GLOBAL_ENABLE |= FlowSensorCounter_BLOCK_EN_MASK;
        FlowSensorCounter_GLOBAL_STBY_ENABLE |= FlowSensorCounter_BLOCK_STBY_EN_MASK;
    #endif /* (FlowSensorCounter_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!FlowSensorCounter_ControlRegRemoved || FlowSensorCounter_UsingFixedFunction)
        FlowSensorCounter_CONTROL |= FlowSensorCounter_CTRL_ENABLE;                
    #endif /* (!FlowSensorCounter_ControlRegRemoved || FlowSensorCounter_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: FlowSensorCounter_Start
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
*  FlowSensorCounter_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void FlowSensorCounter_Start(void) 
{
    if(FlowSensorCounter_initVar == 0u)
    {
        FlowSensorCounter_Init();
        
        FlowSensorCounter_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    FlowSensorCounter_Enable();        
}


/*******************************************************************************
* Function Name: FlowSensorCounter_Stop
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
void FlowSensorCounter_Stop(void) 
{
    /* Disable Counter */
    #if(!FlowSensorCounter_ControlRegRemoved || FlowSensorCounter_UsingFixedFunction)
        FlowSensorCounter_CONTROL &= ((uint8)(~FlowSensorCounter_CTRL_ENABLE));        
    #endif /* (!FlowSensorCounter_ControlRegRemoved || FlowSensorCounter_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (FlowSensorCounter_UsingFixedFunction)
        FlowSensorCounter_GLOBAL_ENABLE &= ((uint8)(~FlowSensorCounter_BLOCK_EN_MASK));
        FlowSensorCounter_GLOBAL_STBY_ENABLE &= ((uint8)(~FlowSensorCounter_BLOCK_STBY_EN_MASK));
    #endif /* (FlowSensorCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FlowSensorCounter_SetInterruptMode
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
void FlowSensorCounter_SetInterruptMode(uint8 interruptsMask) 
{
    FlowSensorCounter_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: FlowSensorCounter_ReadStatusRegister
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
uint8   FlowSensorCounter_ReadStatusRegister(void) 
{
    return FlowSensorCounter_STATUS;
}


#if(!FlowSensorCounter_ControlRegRemoved)
/*******************************************************************************
* Function Name: FlowSensorCounter_ReadControlRegister
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
uint8   FlowSensorCounter_ReadControlRegister(void) 
{
    return FlowSensorCounter_CONTROL;
}


/*******************************************************************************
* Function Name: FlowSensorCounter_WriteControlRegister
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
void    FlowSensorCounter_WriteControlRegister(uint8 control) 
{
    FlowSensorCounter_CONTROL = control;
}

#endif  /* (!FlowSensorCounter_ControlRegRemoved) */


#if (!(FlowSensorCounter_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: FlowSensorCounter_WriteCounter
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
void FlowSensorCounter_WriteCounter(uint16 counter) \
                                   
{
    #if(FlowSensorCounter_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (FlowSensorCounter_GLOBAL_ENABLE & FlowSensorCounter_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        FlowSensorCounter_GLOBAL_ENABLE |= FlowSensorCounter_BLOCK_EN_MASK;
        CY_SET_REG16(FlowSensorCounter_COUNTER_LSB_PTR, (uint16)counter);
        FlowSensorCounter_GLOBAL_ENABLE &= ((uint8)(~FlowSensorCounter_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(FlowSensorCounter_COUNTER_LSB_PTR, counter);
    #endif /* (FlowSensorCounter_UsingFixedFunction) */
}
#endif /* (!(FlowSensorCounter_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: FlowSensorCounter_ReadCounter
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
uint16 FlowSensorCounter_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(FlowSensorCounter_UsingFixedFunction)
		(void)CY_GET_REG16(FlowSensorCounter_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(FlowSensorCounter_COUNTER_LSB_PTR_8BIT);
	#endif/* (FlowSensorCounter_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(FlowSensorCounter_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(FlowSensorCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(FlowSensorCounter_STATICCOUNT_LSB_PTR));
    #endif /* (FlowSensorCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FlowSensorCounter_ReadCapture
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
uint16 FlowSensorCounter_ReadCapture(void) 
{
    #if(FlowSensorCounter_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(FlowSensorCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(FlowSensorCounter_STATICCOUNT_LSB_PTR));
    #endif /* (FlowSensorCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FlowSensorCounter_WritePeriod
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
void FlowSensorCounter_WritePeriod(uint16 period) 
{
    #if(FlowSensorCounter_UsingFixedFunction)
        CY_SET_REG16(FlowSensorCounter_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(FlowSensorCounter_PERIOD_LSB_PTR, period);
    #endif /* (FlowSensorCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FlowSensorCounter_ReadPeriod
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
uint16 FlowSensorCounter_ReadPeriod(void) 
{
    #if(FlowSensorCounter_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(FlowSensorCounter_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(FlowSensorCounter_PERIOD_LSB_PTR));
    #endif /* (FlowSensorCounter_UsingFixedFunction) */
}


#if (!FlowSensorCounter_UsingFixedFunction)
/*******************************************************************************
* Function Name: FlowSensorCounter_WriteCompare
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
void FlowSensorCounter_WriteCompare(uint16 compare) \
                                   
{
    #if(FlowSensorCounter_UsingFixedFunction)
        CY_SET_REG16(FlowSensorCounter_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(FlowSensorCounter_COMPARE_LSB_PTR, compare);
    #endif /* (FlowSensorCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FlowSensorCounter_ReadCompare
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
uint16 FlowSensorCounter_ReadCompare(void) 
{
    return (CY_GET_REG16(FlowSensorCounter_COMPARE_LSB_PTR));
}


#if (FlowSensorCounter_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: FlowSensorCounter_SetCompareMode
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
void FlowSensorCounter_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    FlowSensorCounter_CONTROL &= ((uint8)(~FlowSensorCounter_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    FlowSensorCounter_CONTROL |= compareMode;
}
#endif  /* (FlowSensorCounter_COMPARE_MODE_SOFTWARE) */


#if (FlowSensorCounter_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: FlowSensorCounter_SetCaptureMode
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
void FlowSensorCounter_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    FlowSensorCounter_CONTROL &= ((uint8)(~FlowSensorCounter_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    FlowSensorCounter_CONTROL |= ((uint8)((uint8)captureMode << FlowSensorCounter_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (FlowSensorCounter_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: FlowSensorCounter_ClearFIFO
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
void FlowSensorCounter_ClearFIFO(void) 
{

    while(0u != (FlowSensorCounter_ReadStatusRegister() & FlowSensorCounter_STATUS_FIFONEMP))
    {
        (void)FlowSensorCounter_ReadCapture();
    }

}
#endif  /* (!FlowSensorCounter_UsingFixedFunction) */


/* [] END OF FILE */

