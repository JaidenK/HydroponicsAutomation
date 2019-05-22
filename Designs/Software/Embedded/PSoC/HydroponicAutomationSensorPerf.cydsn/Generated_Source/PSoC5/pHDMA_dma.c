/***************************************************************************
* File Name: pHDMA_dma.c  
* Version 1.70
*
*  Description:
*   Provides an API for the DMAC component. The API includes functions
*   for the DMA controller, DMA channels and Transfer Descriptors.
*
*
*   Note:
*     This module requires the developer to finish or fill in the auto
*     generated funcions and setup the dma channel and TD's.
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#include <CYLIB.H>
#include <CYDMAC.H>
#include <pHDMA_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* pHDMA__DRQ_CTL_REG
* 
* 
* pHDMA__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* pHDMA__NUMBEROF_TDS
* 
* Priority of this channel.
* pHDMA__PRIORITY
* 
* True if pHDMA_TERMIN_SEL is used.
* pHDMA__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* pHDMA__TERMIN_SEL
* 
* 
* True if pHDMA_TERMOUT0_SEL is used.
* pHDMA__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* pHDMA__TERMOUT0_SEL
* 
* 
* True if pHDMA_TERMOUT1_SEL is used.
* pHDMA__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* pHDMA__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of pHDMA dma channel */
uint8 pHDMA_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 pHDMA_DmaInitalize
**********************************************************************
* Summary:
*   Allocates and initialises a channel of the DMAC to be used by the
*   caller.
*
* Parameters:
*   BurstCount.
*       
*       
*   ReqestPerBurst.
*       
*       
*   UpperSrcAddress.
*       
*       
*   UpperDestAddress.
*       
*
* Return:
*   The channel that can be used by the caller for DMA activity.
*   DMA_INVALID_CHANNEL (0xFF) if there are no channels left. 
*
*
*******************************************************************/
uint8 pHDMA_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    pHDMA_DmaHandle = (uint8)pHDMA__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(pHDMA_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)pHDMA__TERMOUT0_SEL,
                                  (uint8)pHDMA__TERMOUT1_SEL,
                                  (uint8)pHDMA__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(pHDMA_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(pHDMA_DmaHandle, (uint8)pHDMA__PRIORITY);
    
    return pHDMA_DmaHandle;
}

/*********************************************************************
* Function Name: void pHDMA_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with pHDMA.
*
*
* Parameters:
*   void.
*
*
*
* Return:
*   void.
*
*******************************************************************/
void pHDMA_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(pHDMA_DmaHandle);
}

