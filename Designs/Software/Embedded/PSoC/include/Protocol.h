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

#define PROTOCOL_TEST
#define MODULE_TEST

#ifndef Protocol_h
#define Protocol_h

typedef enum pkey_t{
    //Client Side incoming
    invalid_key,
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
}pkey_t;

typedef struct target_t{
    pkey_t key;
    float value;
}target_t;

/**
 * @function Protocol_DecodeInput(char * input)
 * @param None
 * @return Takes an incoming data transmission and decodes it
 * @brief Converts the current frequency and returns flow rate
 * @author Barron Wong 02/08/19
*/
target_t Protocol_DecodeInput(char * input);

/**
 * @function Protocol_EncodeOutput(char * input)
 * @param key, value, and buffer
 * @return String pointer ready for output
 * @brief Takes a key and a parameter and get it read for output
 * @author Barron Wong 02/08/19
*/
char * Protocol_EncodeOutput(pkey_t key, float value, char * buffer);

#endif
/* [] END OF FILE */
