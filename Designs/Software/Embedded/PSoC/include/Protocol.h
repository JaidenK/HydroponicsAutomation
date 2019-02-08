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
#ifndef Protocol_h
#define Protocol_h

typedef enum Keys_t{
    //Client Side incoming
    flow_target,
    ph_target,
    ec_target,
    h20_level_target,
    
    //Client Side outgoing
    h20_level,
    h20_stored,
    ph_measured,
    ph_up_stored,
    ph_down_stored,
    ec_measured,
    ec_stored,
    temp_measured,
    flow_measured,
}Keys_t;
    
#endif
/* [] END OF FILE */
