/*******************************************************************************
* File Name: ECADC_INT.c
* Version 3.30
*
* Description:
*  This file contains the code that operates during the ADC_DelSig interrupt
*  service routine.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ECADC.h"
#include "cyapicallbacks.h"


/*******************************************************************************
* Custom Declarations and Variables
* - add user include files, prototypes and variables between the following
*   #START and #END tags
*******************************************************************************/
/* `#START ADC_SYS_VAR`  */

/* `#END`  */

#if(ECADC_IRQ_REMOVE == 0u)


    /*****************************************************************************
    * Function Name: ECADC_ISR1
    ******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *****************************************************************************/
    CY_ISR( ECADC_ISR1)
    {
        #ifdef ECADC_ISR1_ENTRY_CALLBACK
            ECADC_ISR1_EntryCallback();
        #endif /* ECADC_ISR1_ENTRY_CALLBACK */
        

        /**************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        **************************************************************************/
        /* `#START MAIN_ADC_ISR1`  */

        /* `#END`  */
        
        /* Stop the conversion if conversion mode is single sample and resolution
        *  is above 16 bits.
        */
        #if(ECADC_CFG1_RESOLUTION > 16 && \
            ECADC_CFG1_CONV_MODE == ECADC_MODE_SINGLE_SAMPLE)
            ECADC_StopConvert();
            /* Software flag for checking conversion complete or not. Will be used when
            *  resolution is above 16 bits and conversion mode is single sample 
			*/
            ECADC_convDone = ECADC_DEC_CONV_DONE;
        #endif /* Single sample conversion mode with resolution above 16 bits */

        #ifdef ECADC_ISR1_EXIT_CALLBACK
            ECADC_ISR1_ExitCallback();
        #endif /* ECADC_ISR1_EXIT_CALLBACK */
    }


    /*****************************************************************************
    * Function Name: ECADC_ISR2
    ******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *****************************************************************************/
    CY_ISR( ECADC_ISR2)
    {
        #ifdef ECADC_ISR2_ENTRY_CALLBACK
            ECADC_ISR2_EntryCallback();
        #endif /* ECADC_ISR2_ENTRY_CALLBACK */
        
        
        /***************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        **************************************************************************/
        /* `#START MAIN_ADC_ISR2`  */

        /* `#END`  */

        /* Stop the conversion conversion mode is single sample and resolution
        *  is above 16 bits.
        */
        #if(ECADC_CFG2_RESOLUTION > 16 && \
            ECADC_CFG2_CONVMODE == ECADC_MODE_SINGLE_SAMPLE)
            ECADC_StopConvert();
            /* Software flag for checking conversion complete or not. Will be used when
            *   resolution is above 16 bits and conversion mode is single sample 
			*/
            ECADC_convDone = ECADC_DEC_CONV_DONE;
        #endif /* Single sample conversion mode with resolution above 16 bits */

        #ifdef ECADC_ISR2_EXIT_CALLBACK
            ECADC_ISR2_ExitCallback();
        #endif /* ECADC_ISR2_EXIT_CALLBACK */
    }


    /*****************************************************************************
    * Function Name: ECADC_ISR3
    ******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *****************************************************************************/
    CY_ISR( ECADC_ISR3)
    {
        #ifdef ECADC_ISR3_ENTRY_CALLBACK
            ECADC_ISR3_EntryCallback();
        #endif /* ECADC_ISR3_ENTRY_CALLBACK */        

        
        /***************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        **************************************************************************/
        /* `#START MAIN_ADC_ISR3`  */

        /* `#END`  */
        
        /* Stop the conversion if conversion mode is set to single sample and
        *  resolution is above 16 bits.
        */
        #if(ECADC_CFG3_RESOLUTION > 16 && \
            ECADC_CFG3_CONVMODE == ECADC_MODE_SINGLE_SAMPLE)
            ECADC_StopConvert();
            /* Software flag for checking conversion complete or not. Will be used when
            *  resolution is above 16 bits and conversion mode is single sample 
			*/
            ECADC_convDone = ECADC_DEC_CONV_DONE;
        #endif /* Single sample conversion mode with resolution above 16 bits */

        #ifdef ECADC_ISR3_EXIT_CALLBACK
            ECADC_ISR3_ExitCallback();
        #endif /* ECADC_ISR3_EXIT_CALLBACK */        
    }


    /*****************************************************************************
    * Function Name: ECADC_ISR4
    ******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *****************************************************************************/
    CY_ISR( ECADC_ISR4)
    {
        #ifdef ECADC_ISR4_ENTRY_CALLBACK
            ECADC_ISR4_EntryCallback();
        #endif /* ECADC_ISR4_ENTRY_CALLBACK */            

        
        /***************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        **************************************************************************/
        /* `#START MAIN_ADC_ISR4`  */

        /* `#END`  */

        /* Stop the conversion if conversion mode is set to single sample and
        *  resolution is above 16 bits.
        */
        #if(ECADC_CFG4_RESOLUTION > 16 && \
            ECADC_CFG4_CONVMODE == ECADC_MODE_SINGLE_SAMPLE)
            ECADC_StopConvert();
            /* Software flag for checking conversion complete or not. Will be used when
            *  resolution is above 16 bits and conversion mode is single sample 
			*/
            ECADC_convDone = ECADC_DEC_CONV_DONE;
        #endif /* Single sample conversion mode with resolution above 16 bits */
        
        #ifdef ECADC_ISR4_EXIT_CALLBACK
            ECADC_ISR4_ExitCallback();
        #endif /* ECADC_ISR4_EXIT_CALLBACK */            
    }

#endif   /* End ECADC_IRQ_REMOVE */


/* [] END OF FILE */
