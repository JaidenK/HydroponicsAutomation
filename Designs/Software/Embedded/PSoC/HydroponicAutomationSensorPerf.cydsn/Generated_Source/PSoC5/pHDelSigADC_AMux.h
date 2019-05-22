/*******************************************************************************
* File Name: pHDelSigADC_AMux.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_pHDelSigADC_AMux_H)
#define CY_AMUX_pHDelSigADC_AMux_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*        Function Prototypes
***************************************/

void pHDelSigADC_AMux_Start(void) ;
#define pHDelSigADC_AMux_Init() pHDelSigADC_AMux_Start()
void pHDelSigADC_AMux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void pHDelSigADC_AMux_Stop(void); */
/* void pHDelSigADC_AMux_Select(uint8 channel); */
/* void pHDelSigADC_AMux_Connect(uint8 channel); */
/* void pHDelSigADC_AMux_Disconnect(uint8 channel); */
/* void pHDelSigADC_AMux_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define pHDelSigADC_AMux_CHANNELS  2u
#define pHDelSigADC_AMux_MUXTYPE   1
#define pHDelSigADC_AMux_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define pHDelSigADC_AMux_NULL_CHANNEL 0xFFu
#define pHDelSigADC_AMux_MUX_SINGLE   1
#define pHDelSigADC_AMux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if pHDelSigADC_AMux_MUXTYPE == pHDelSigADC_AMux_MUX_SINGLE
# if !pHDelSigADC_AMux_ATMOSTONE
#  define pHDelSigADC_AMux_Connect(channel) pHDelSigADC_AMux_Set(channel)
# endif
# define pHDelSigADC_AMux_Disconnect(channel) pHDelSigADC_AMux_Unset(channel)
#else
# if !pHDelSigADC_AMux_ATMOSTONE
void pHDelSigADC_AMux_Connect(uint8 channel) ;
# endif
void pHDelSigADC_AMux_Disconnect(uint8 channel) ;
#endif

#if pHDelSigADC_AMux_ATMOSTONE
# define pHDelSigADC_AMux_Stop() pHDelSigADC_AMux_DisconnectAll()
# define pHDelSigADC_AMux_Select(channel) pHDelSigADC_AMux_FastSelect(channel)
void pHDelSigADC_AMux_DisconnectAll(void) ;
#else
# define pHDelSigADC_AMux_Stop() pHDelSigADC_AMux_Start()
void pHDelSigADC_AMux_Select(uint8 channel) ;
# define pHDelSigADC_AMux_DisconnectAll() pHDelSigADC_AMux_Start()
#endif

#endif /* CY_AMUX_pHDelSigADC_AMux_H */


/* [] END OF FILE */
