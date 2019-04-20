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
#include "Calibration.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define FULL_X_LENGTH_STEPS 8096
#define FULL_Z_LENGTH 4000
#define INITIAL_TO_DECON 1000
#define INITIAL_STEPS_MICROSTEP 6400 //one rev
#define INITIAL_STEPS_FULLSTEP 200  //one rev = 8mm for X-axis 5mm for Z-axis
#define TOP_TO_BOTTOM 3000 //15 rev on Z-axis 75mm
#define TOP_TO_CALIBRATE 1600 //8 rev on Z-axis 40mm
#define DECON_TO_TARGET1 1375 // 57.5mm one target to the next X-axis
#define TARGET1_TO_DECON 1375
#define PH4_TO_RINSE 2200
#define ERROR 0
#define LEFT X_Step_Control_Write(0b01)
#define RIGHT X_Step_Control_Write(0b11)
#define STOP X_Step_Control_Write(0b00)
#define UP Z_Step_Control_Write(0b01)
#define DOWN Z_Step_Control_Write(0b11)
#define EVER ;;
#define X_STOP  X_Step_ISR_Disable()
#define X_START X_Step_ISR_Enable()
#define Z_STOP Z_Step_ISR_Disable()
#define Z_START Z_Step_ISR_Enable()


static enum {
    ZERO,
    SPONGE,
    RINSE, 
    PH4,
    PH7,
    PH10,
    FINISHED,
}gantryState=ZERO;    

static enum {
    Z_AXIS_ZERO,
    X_AXIS_ZERO,
}zeroState=Z_AXIS_ZERO; 

static enum {
    X_AXIS_MOVE_SPONGE,
    Z_AXIS_MOVE_SPONGE,
    Z_AXIS_ZERO_SPONGE,
}spongeState=X_AXIS_MOVE_SPONGE; 


static enum {
    X_AXIS_MOVE_PH4,
    Z_AXIS_MOVE_PH4,
    Z_AXIS_ZERO_PH4,
}Ph4State=X_AXIS_MOVE_PH4; 

static enum {
    X_AXIS_MOVE_RINSE,
    Z_AXIS_MOVE_RINSE,
    Z_AXIS_ZERO_RINSE,
}rinseState=X_AXIS_MOVE_RINSE; 

static enum {
    X_AXIS_MOVE_PH7,
    Z_AXIS_MOVE_PH7,
    Z_AXIS_ZERO_PH7,
}Ph7State=X_AXIS_MOVE_PH7; 

static enum {
    X_AXIS_MOVE_PH10,
    Z_AXIS_MOVE_PH10,
    Z_AXIS_ZERO_PH10,
}Ph10State=X_AXIS_MOVE_PH10; 


int  X_AXIS_MOVE_FINISHED=1001;
int  AXIS_MOVE_FINISHED=1000;


int xStepsToMove=FULL_X_LENGTH_STEPS;
uint16_t xStepCount=0;
uint16_t X_pos;
uint16_t X_target;
uint16_t Z_pos;
uint16_t Z_target;
uint8_t xLimitflag=0;
uint8_t zLimitflag=0;
int zStepsToMove=FULL_X_LENGTH_STEPS;
uint16_t zStepCount=0;
uint8_t nextState; 
uint8_t prevState;
uint8_t xLimitInitFlag=0;
uint8_t zLimitInitFlag=0;
uint8_t measurementFlag;
uint8_t xMoveFlag=0;
uint8_t zMoveFlag=0;
uint8_t Ph4;
uint8_t Ph7;
uint8_t Ph10;

CY_ISR(X_Step_ISR){
        switch(gantryState){
            case ZERO:
                LEFT;  
                break;
            case SPONGE:
            case PH4:
            case RINSE:
            case PH7:
            case PH10:
            case FINISHED:
                if(X_pos>X_target){
                    LEFT;
                    X_pos--;
                }else{
                    RIGHT;
                    X_pos++;
                }
            break;    
            default:
                break;
        }  
}

CY_ISR(Z_Step_ISR){
        switch(gantryState){
            case ZERO:
                UP;
                break;
            case SPONGE:
                if(Z_pos>Z_target){
                   UP;
                   Z_pos--;
                }else if(spongeState==Z_AXIS_ZERO_SPONGE){
                   UP;
                }else{
                   DOWN;
                   Z_pos++;
                }
                 break;
            case PH4:
                if(Z_pos>Z_target){
                   UP;
                   Z_pos--;
                }else if(Ph4State==Z_AXIS_ZERO_PH4){
                   UP;
                }else{
                   DOWN;
                   Z_pos++;
                }
                break;
            case RINSE:
                if(Z_pos>Z_target){
                   UP;
                   Z_pos--;
                }else if(rinseState==Z_AXIS_ZERO_RINSE){
                   UP;
                }else{
                   DOWN;
                   Z_pos++;
                }
                break;
            case PH7:
                if(Z_pos>Z_target){
                   UP;
                   Z_pos--;
                }else if(Ph7State==Z_AXIS_ZERO_PH7){
                   UP;
                }else{
                   DOWN;
                   Z_pos++;
                }
                break; 
            case PH10:
                if(Z_pos>Z_target){
                   UP;
                   Z_pos--;
                }else if(Ph10State==Z_AXIS_ZERO_PH10){
                   UP;
                }else{
                   DOWN;
                   Z_pos++;
                }
                break;
            case FINISHED:
                if(Z_pos>Z_target){
                    LEFT;
                    Z_pos--;
                }else{
                    RIGHT;
                    Z_pos++;
                }
                break;
            default:
                break;
        }
}

CY_ISR(X_Limit_ISR){
    if(xLimitInitFlag==0){
        xLimitInitFlag=1;
    }else{
       // printf("X limit ISR\r\n");
        xLimitflag=1;
        X_pos=0;
        X_Limit_ISR_Disable();
    }
    X_Limit_ISR_ClearPending();
}

CY_ISR(Z_Limit_ISR){
    if(zLimitInitFlag==0){
        zLimitInitFlag=1;
    }else {
       // printf("Z limit ISR\r\n");
        zLimitflag=1;
        Z_pos=0;
        Z_Limit_ISR_Disable();
    }
    Z_Limit_ISR_ClearPending();
}

uint8_t xStepperInit(){
    
    if (gantryState != ZERO) {
        return ERROR;
    }else{
       // printf("xStepperInit\r\n");
        X_Step_Timer_Start();
        X_Step_ISR_StartEx(X_Step_ISR);
        X_Limit_ISR_StartEx(X_Limit_ISR);
        
    }    
    return TRUE;
}

uint8_t zStepperInit(){
    
    if (gantryState != ZERO) {
        return ERROR;
    }else{
       // printf("zStepperInit\r\n");
        Z_Step_Timer_Start();
        Z_Step_ISR_StartEx(Z_Step_ISR);
        Z_Limit_ISR_StartEx(Z_Limit_ISR);
        
    }    
    return TRUE;
} 

#ifdef CALIBRATION_TEST
#include "SerialCom.h"
int main(void)
{
    CyGlobalIntEnable;
    
    SerialCom_Init();
    xStepperInit();
    zStepperInit();
    X_STOP;
    Z_STOP;
    
    printf("Hydroponic Automation\r\n");

    for(EVER)
    {   
        switch(gantryState){
            case ZERO:
                switch(zeroState){
                    case Z_AXIS_ZERO:
                        if(!zLimitflag){
                            Z_START;
                        }else{
                            Z_STOP;
                            zeroState=X_AXIS_ZERO;
                        }
                        break;
                    case X_AXIS_ZERO:
                         if(!xLimitflag){
                            X_START;
                        }else{
                            X_STOP;
                            zeroState=Z_AXIS_ZERO;
                            gantryState=SPONGE; 
                            X_target=INITIAL_TO_DECON;
                            Ph4=0;
                            Ph7=0;
                            Ph10=0;
                            X_pos=0;
                            Z_pos=0;
                        }
                        break;
                }        
                break;
            case SPONGE:
                switch(spongeState){
                    case X_AXIS_MOVE_SPONGE:
                        if(X_pos != X_target){
                            X_START;
                        }else{
                            X_STOP;
                            spongeState=Z_AXIS_MOVE_SPONGE;
                            Z_target=TOP_TO_CALIBRATE;
                        }    
                        break;
                    case Z_AXIS_MOVE_SPONGE:
                        if(Z_pos != Z_target){
                            Z_START;
                        }else{
                            Z_STOP;
                            spongeState=Z_AXIS_ZERO_SPONGE;
                            zLimitflag=0;
                            //printf("before ISR ENABLE\r\n");
                            zLimitInitFlag=0;
                            Z_Limit_ISR_Enable();
                            
                        }
                        break;
                    case Z_AXIS_ZERO_SPONGE:
                        if(!zLimitflag){
                            Z_START;
                        }else{
                            Z_STOP;
                            if(!Ph4){
                                gantryState=PH4;
                                X_target=DECON_TO_TARGET1;
                            }else if(Ph4&&!Ph7){
                                gantryState=PH7;
                                X_target=DECON_TO_TARGET1*2; 
                            }else if(Ph4&&Ph7){
                                gantryState=PH10;
                                X_target=DECON_TO_TARGET1*3;
                            }
                        }  
                        break;
                }   
                break;
            case PH4:
                switch(Ph4State){
                    case X_AXIS_MOVE_PH4:
                        if(X_pos!=X_target){
                            X_START;
                        }else{
                            X_STOP;
                            Ph4State=Z_AXIS_MOVE_PH4;
                            Z_target=TOP_TO_CALIBRATE;
                        }
                        break;
                    case Z_AXIS_MOVE_PH4:
                        if(Z_pos != Z_target){
                            Z_START;
                        }else{
                            Z_STOP;
                            Ph4State=Z_AXIS_ZERO_PH4;
                            zLimitflag=0;
                            zLimitInitFlag=0;
                            Z_Limit_ISR_Enable();                          
                        }
                        break;
                    case Z_AXIS_ZERO_PH4:
                        if(!zLimitflag){
                            Z_START;
                        }else{
                            Z_STOP;
                            Ph4=1;
                            gantryState=RINSE;
                            X_target=PH4_TO_RINSE;
                        }  
                        break;
                }    
                break;
            case RINSE:
                switch(rinseState){
                    case X_AXIS_MOVE_RINSE:
                        if(X_pos!=X_target){
                            X_START;
                        }else{
                            X_STOP;
                            rinseState=Z_AXIS_MOVE_RINSE;
                            Z_target=TOP_TO_BOTTOM;
                        }
                        break;
                    case Z_AXIS_MOVE_RINSE:
                        if(Z_pos != Z_target){
                            Z_START;
                        }else{
                            Z_STOP;
                            rinseState=Z_AXIS_ZERO_RINSE;
                            zLimitflag=0;
                            zLimitInitFlag=0;
                            Z_Limit_ISR_Enable();                          
                        }
                        break;
                    case Z_AXIS_ZERO_RINSE:
                         if(!zLimitflag){
                            Z_START;
                        }else{
                            Z_STOP;
                            gantryState=SPONGE;
                            rinseState=X_AXIS_MOVE_RINSE;
                            X_target=INITIAL_TO_DECON-100;
                        }  
                        break;
                }
                break;
            case PH7:
                switch(Ph7State){
                    case X_AXIS_MOVE_PH7:
                        if(X_pos!=X_target){
                            X_START;
                        }else{
                            X_STOP;
                            Ph7State=Z_AXIS_MOVE_PH7;
                            Z_target=TOP_TO_CALIBRATE;
                        }
                        break;
                    case Z_AXIS_MOVE_PH7:
                         if(Z_pos != Z_target){
                            Z_START;
                        }else{
                            Z_STOP;
                            Ph7State=Z_AXIS_ZERO_PH7;
                            zLimitflag=0;
                            zLimitInitFlag=0;
                            Z_Limit_ISR_Enable();                          
                        }
                        break;
                    case Z_AXIS_ZERO_PH7:
                        if(!zLimitflag){
                            Z_START;
                        }else{
                            Z_STOP;
                            gantryState=RINSE;
                            X_target=DECON_TO_TARGET1*3;
                            Ph7=1;
                        }  
                        break;
                }
                break;
            case PH10:
                switch(Ph10State){
                    case X_AXIS_MOVE_PH10:
                        if(X_pos!=X_target){
                            X_START;
                        }else{
                            X_STOP;
                            Ph7State=Z_AXIS_MOVE_PH10;
                            Z_target=TOP_TO_CALIBRATE;
                        }
                        break;
                    case Z_AXIS_MOVE_PH10:
                         if(Z_pos != Z_target){
                            Z_START;
                        }else{
                            Z_STOP;
                            Ph7State=Z_AXIS_ZERO_PH10;
                            zLimitflag=0;
                            zLimitInitFlag=0;
                            Z_Limit_ISR_Enable();                          
                        }
                        break;
                    case Z_AXIS_ZERO_PH10:
                        if(!zLimitflag){
                            Z_START;
                        }else{
                            Z_STOP;
                            gantryState=FINISHED;
                            X_target=DECON_TO_TARGET1*4;
                        }  
                        break;
                }
                break;
            case FINISHED:
                case X_AXIS_MOVE_FINISHED:
                    if(X_pos!=X_target){
                            X_START;
                        }else{
                            X_STOP;
                            Ph7State=Z_AXIS_MOVE_PH10;
                            Z_target=TOP_TO_CALIBRATE;
                        }
                break;
            default:
                break;
        }
    }
        
}
#endif

/* [] END OF FILE */
