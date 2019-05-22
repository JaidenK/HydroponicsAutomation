/*******************************************************************************
* File Name: FlowSpeedDAC.h  
* Version 1.90
*
*  Description:
*    This file contains the function prototypes and constants used in
*    the 8-bit Voltage DAC (vDAC8) User Module.
*
*   Note:
*     
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_VDAC8_FlowSpeedDAC_H) 
#define CY_VDAC8_FlowSpeedDAC_H

#include "cytypes.h"
#include "cyfitter.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component VDAC8_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/***************************************
*       Type defines
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState; 
    uint8 data_value;
}FlowSpeedDAC_backupStruct;

/* component init state */
extern uint8 FlowSpeedDAC_initVar;


/***************************************
*        Function Prototypes 
***************************************/

void FlowSpeedDAC_Start(void)           ;
void FlowSpeedDAC_Stop(void)            ;
void FlowSpeedDAC_SetSpeed(uint8 speed) ;
void FlowSpeedDAC_SetRange(uint8 range) ;
void FlowSpeedDAC_SetValue(uint8 value) ;
void FlowSpeedDAC_DacTrim(void)         ;
void FlowSpeedDAC_Init(void)            ;
void FlowSpeedDAC_Enable(void)          ;
void FlowSpeedDAC_SaveConfig(void)      ;
void FlowSpeedDAC_RestoreConfig(void)   ;
void FlowSpeedDAC_Sleep(void)           ;
void FlowSpeedDAC_Wakeup(void)          ;


/***************************************
*            API Constants
***************************************/

/* SetRange constants */

#define FlowSpeedDAC_RANGE_1V       0x00u
#define FlowSpeedDAC_RANGE_4V       0x04u


/* Power setting for Start API  */
#define FlowSpeedDAC_LOWSPEED       0x00u
#define FlowSpeedDAC_HIGHSPEED      0x02u


/***************************************
*  Initialization Parameter Constants
***************************************/

 /* Default DAC range */
#define FlowSpeedDAC_DEFAULT_RANGE    4u
 /* Default DAC speed */
#define FlowSpeedDAC_DEFAULT_SPEED    0u
 /* Default Control */
#define FlowSpeedDAC_DEFAULT_CNTL      0x00u
/* Default Strobe mode */
#define FlowSpeedDAC_DEFAULT_STRB     0u
 /* Initial DAC value */
#define FlowSpeedDAC_DEFAULT_DATA     100u
 /* Default Data Source */
#define FlowSpeedDAC_DEFAULT_DATA_SRC 0u


/***************************************
*              Registers        
***************************************/
#define FlowSpeedDAC_CR0_REG            (* (reg8 *) FlowSpeedDAC_viDAC8__CR0 )
#define FlowSpeedDAC_CR0_PTR            (  (reg8 *) FlowSpeedDAC_viDAC8__CR0 )
#define FlowSpeedDAC_CR1_REG            (* (reg8 *) FlowSpeedDAC_viDAC8__CR1 )
#define FlowSpeedDAC_CR1_PTR            (  (reg8 *) FlowSpeedDAC_viDAC8__CR1 )
#define FlowSpeedDAC_Data_REG           (* (reg8 *) FlowSpeedDAC_viDAC8__D )
#define FlowSpeedDAC_Data_PTR           (  (reg8 *) FlowSpeedDAC_viDAC8__D )
#define FlowSpeedDAC_Strobe_REG         (* (reg8 *) FlowSpeedDAC_viDAC8__STROBE )
#define FlowSpeedDAC_Strobe_PTR         (  (reg8 *) FlowSpeedDAC_viDAC8__STROBE )
#define FlowSpeedDAC_SW0_REG            (* (reg8 *) FlowSpeedDAC_viDAC8__SW0 )
#define FlowSpeedDAC_SW0_PTR            (  (reg8 *) FlowSpeedDAC_viDAC8__SW0 )
#define FlowSpeedDAC_SW2_REG            (* (reg8 *) FlowSpeedDAC_viDAC8__SW2 )
#define FlowSpeedDAC_SW2_PTR            (  (reg8 *) FlowSpeedDAC_viDAC8__SW2 )
#define FlowSpeedDAC_SW3_REG            (* (reg8 *) FlowSpeedDAC_viDAC8__SW3 )
#define FlowSpeedDAC_SW3_PTR            (  (reg8 *) FlowSpeedDAC_viDAC8__SW3 )
#define FlowSpeedDAC_SW4_REG            (* (reg8 *) FlowSpeedDAC_viDAC8__SW4 )
#define FlowSpeedDAC_SW4_PTR            (  (reg8 *) FlowSpeedDAC_viDAC8__SW4 )
#define FlowSpeedDAC_TR_REG             (* (reg8 *) FlowSpeedDAC_viDAC8__TR )
#define FlowSpeedDAC_TR_PTR             (  (reg8 *) FlowSpeedDAC_viDAC8__TR )
/* Power manager */
#define FlowSpeedDAC_PWRMGR_REG         (* (reg8 *) FlowSpeedDAC_viDAC8__PM_ACT_CFG )
#define FlowSpeedDAC_PWRMGR_PTR         (  (reg8 *) FlowSpeedDAC_viDAC8__PM_ACT_CFG )
  /* Standby Power manager */
#define FlowSpeedDAC_STBY_PWRMGR_REG    (* (reg8 *) FlowSpeedDAC_viDAC8__PM_STBY_CFG )
#define FlowSpeedDAC_STBY_PWRMGR_PTR    (  (reg8 *) FlowSpeedDAC_viDAC8__PM_STBY_CFG )

/***************************************
*  Registers definitions
* for backward capability        
***************************************/
#define FlowSpeedDAC_CR0         (* (reg8 *) FlowSpeedDAC_viDAC8__CR0 )
#define FlowSpeedDAC_CR1         (* (reg8 *) FlowSpeedDAC_viDAC8__CR1 )
#define FlowSpeedDAC_Data        (* (reg8 *) FlowSpeedDAC_viDAC8__D )
#define FlowSpeedDAC_Data_PTR    (  (reg8 *) FlowSpeedDAC_viDAC8__D )
#define FlowSpeedDAC_Strobe      (* (reg8 *) FlowSpeedDAC_viDAC8__STROBE )
#define FlowSpeedDAC_SW0         (* (reg8 *) FlowSpeedDAC_viDAC8__SW0 )
#define FlowSpeedDAC_SW2         (* (reg8 *) FlowSpeedDAC_viDAC8__SW2 )
#define FlowSpeedDAC_SW3         (* (reg8 *) FlowSpeedDAC_viDAC8__SW3 )
#define FlowSpeedDAC_SW4         (* (reg8 *) FlowSpeedDAC_viDAC8__SW4 )
#define FlowSpeedDAC_TR          (* (reg8 *) FlowSpeedDAC_viDAC8__TR )
/* Power manager */
#define FlowSpeedDAC_PWRMGR      (* (reg8 *) FlowSpeedDAC_viDAC8__PM_ACT_CFG )
  /* Standby Power manager */
#define FlowSpeedDAC_STBY_PWRMGR (* (reg8 *) FlowSpeedDAC_viDAC8__PM_STBY_CFG )


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE                  */
#define FlowSpeedDAC_HS_MASK        0x02u
#define FlowSpeedDAC_HS_LOWPOWER    0x00u
#define FlowSpeedDAC_HS_HIGHSPEED   0x02u

/* Bit Field  DAC_MODE                  */
#define FlowSpeedDAC_MODE_MASK      0x10u
#define FlowSpeedDAC_MODE_V         0x00u
#define FlowSpeedDAC_MODE_I         0x10u

/* Bit Field  DAC_RANGE                  */
#define FlowSpeedDAC_RANGE_MASK     0x0Cu
#define FlowSpeedDAC_RANGE_0        0x00u
#define FlowSpeedDAC_RANGE_1        0x04u

/* CR1 iDac Control Register 1 definitions */

/* Bit Field  DAC_MX_DATA                  */
#define FlowSpeedDAC_SRC_MASK       0x20u
#define FlowSpeedDAC_SRC_REG        0x00u
#define FlowSpeedDAC_SRC_UDB        0x20u

/* This bit enable reset from UDB array      */
#define FlowSpeedDAC_RESET_MASK     0x10u
#define FlowSpeedDAC_RESET_ENABLE   0x10u
#define FlowSpeedDAC_RESET_DISABLE  0x00u

/* This bit enables data from DAC bus      */
#define FlowSpeedDAC_DACBUS_MASK     0x20u
#define FlowSpeedDAC_DACBUS_ENABLE   0x20u
#define FlowSpeedDAC_DACBUS_DISABLE  0x00u

/* DAC STROBE Strobe Control Register definitions */

/* Bit Field  DAC_MX_STROBE                  */
#define FlowSpeedDAC_STRB_MASK     0x08u
#define FlowSpeedDAC_STRB_EN       0x08u
#define FlowSpeedDAC_STRB_DIS      0x00u

/* PM_ACT_CFG (Active Power Mode CFG Register)     */ 
#define FlowSpeedDAC_ACT_PWR_EN   FlowSpeedDAC_viDAC8__PM_ACT_MSK
  /* Standby Power enable mask */
#define FlowSpeedDAC_STBY_PWR_EN  FlowSpeedDAC_viDAC8__PM_STBY_MSK


/*******************************************************************************
*              Trim    
* Note - VDAC trim values are stored in the "Customer Table" area in * Row 1 of
*the Hidden Flash.  There are 8 bytes of trim data for each VDAC block.
* The values are:
*       I Gain offset, min range, Sourcing
*       I Gain offset, min range, Sinking
*       I Gain offset, med range, Sourcing
*       I Gain offset, med range, Sinking
*       I Gain offset, max range, Sourcing
*       I Gain offset, max range, Sinking
*       V Gain offset, 1V range
*       V Gain offset, 4V range
*
* The data set for the 4 VDACs are arranged using a left side/right side
* approach:
*   Left 0, Left 1, Right 0, Right 1.
* When mapped to the VDAC0 thru VDAC3 as:
*   VDAC 0, VDAC 2, VDAC 1, VDAC 3
*******************************************************************************/
#define FlowSpeedDAC_TRIM_M7_1V_RNG_OFFSET  0x06u
#define FlowSpeedDAC_TRIM_M8_4V_RNG_OFFSET  0x07u
/*Constatnt to set DAC in current mode and turnoff output */
#define FlowSpeedDAC_CUR_MODE_OUT_OFF       0x1Eu 
#define FlowSpeedDAC_DAC_TRIM_BASE          (FlowSpeedDAC_viDAC8__TRIM__M1)

#endif /* CY_VDAC8_FlowSpeedDAC_H  */


/* [] END OF FILE */


