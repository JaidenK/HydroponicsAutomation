/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
/* Add an explicit reference to the floating point printf library to allow
the usage of floating point conversion specifier */

#ifndef SerialCom_H
#define SerialCom_H
    
#include <project.h>
#include <stdio.h>

#if defined (__GNUC__)
    asm (".global _printf_float");
#endif
    



CY_ISR_PROTO(RxIsr);

/**
 * @function SerialCom_Init(void)
 * @param None
 * @return None
 * @brief Initializes hardware components necessary Serial Communication
 *        through UART and KitProg
 * @author Barron Wong 01/25/19
*/
void SerialCom_Init();

/**
 * @function _write(void)
 * @param None
 * @return None
 * @brief Overriding _write function for printf redirection to UART
 * @author Barron Wong 01/25/19
*/
/* For GCC compiler revise _write() function for printf functionality */
int _write(int file, char *ptr, int len);

#endif

/* [] END OF FILE */
