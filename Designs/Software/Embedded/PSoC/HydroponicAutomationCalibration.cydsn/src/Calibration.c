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
#define ERROR 0
#define LEFT X_Step_Control_Write(0b01);
#define RIGHT X_Step_Control_Write(0b11);
#define STOP X_Step_Control_Write(0b00);
#define UP Z_Step_Control_Write(0b01);
#define DOWN Z_Step_Control_Write(0b11);
#define EVER ;;
    
static enum {
    ZEROPOSITION,
    MEASUREMENT,
    DECONTAMINATE,
    TARGET_1, 
    TARGET_2,
    TARGET_3,
}gantryState=ZEROPOSITION;    
    
static uint16_t xStepsToMove=FULL_X_LENGTH_STEPS;
static uint16_t xStepCount=0;
static uint16_t X_pos;
static uint16_t Z_pos;
static uint8_t xLimitflag=0;
static uint8_t zLimitflag=0;
static uint16_t zStepsToMove=FULL_X_LENGTH_STEPS;
static uint16_t zStepCount=0;
static uint8_t nextState; 
static uint8_t prevState;
static uint8_t xLimitInitFlag=0;
static uint8_t zLimitInitFlag=0;
static uint8_t measurementFlag;
static uint8_t xMoveFlag=0;
static uint8_t zMoveFlag=0;

CY_ISR(X_Step_ISR){
    if(xStepCount<=xStepsToMove){
        switch(gantryState){
            case ZEROPOSITION:
                if(!xLimitflag){
                    LEFT;
                    xStepCount++;
                }
                break;
            case MEASUREMENT:
                break;
            case DECONTAMINATE:
                switch(prevState){
                    case ZEROPOSITION:
                        RIGHT;
                        xStepCount++;
                        break;
                    default:
                        break;
                }
            case TARGET_1:
                if(zMoveFlag){
                    break;
                }else{
                    RIGHT;
                    xStepCount++;    
                }
                break;
            default:
                break;
        }
    }else{
        X_Step_Timer_Stop();
        X_Step_ISR_Stop();
        xStepCount=0;
        xMoveFlag=0;
    }
    
}

CY_ISR(Z_Step_ISR){
    if(zStepCount<=zStepsToMove){
        switch(gantryState){
            case ZEROPOSITION:
                if(!zLimitflag){
                    UP;//UP normaly for entry into ZEROPOSITON
                    zStepCount++;
                }
                break;
            case MEASUREMENT:
                DOWN;
                zStepCount++;
                break;
            case DECONTAMINATE:
                switch(prevState){
                    case ZEROPOSITION:
                        if(xMoveFlag){
                            break;
                        }else{
                            DOWN;
                            zStepCount++;
                        }
                    case TARGET_1:
                        break;
                    default:
                        break;
                }
                break;
            case TARGET_1:
                UP;
                zStepCount++;
                break;
            default:
                break;
        }
    }else{
        Z_Step_Timer_Stop();
        Z_Step_ISR_Stop();
        zStepCount=0;
        zMoveFlag=0;
    }
    
}

CY_ISR(X_Limit_ISR){
    if(xLimitInitFlag==0){
        xLimitInitFlag=1;
    }else{
        printf("X limit ISR\r\n");
        X_Step_Timer_Stop();
        X_Step_ISR_Stop();
        xStepCount=0;
        X_pos=0;
        xLimitflag=1;
    }
}

CY_ISR(Z_Limit_ISR){
    if(zLimitInitFlag==0){
        zLimitInitFlag=1;
    }else{
        printf("Z limit ISR\r\n");
        Z_Step_Timer_Stop();
        Z_Step_ISR_Stop();
        zStepCount=0;
        Z_pos=0;
        zLimitflag=1;
    }
}


uint8_t xStepperInit(){
    
    if (gantryState != ZEROPOSITION) {
        return ERROR;
    }else{
        printf("xStepperInit\r\n");
        X_Step_Timer_Start();
        X_Step_ISR_StartEx(X_Step_ISR);
        X_Limit_ISR_StartEx(X_Limit_ISR);
    }    
    return TRUE;

}

uint8_t zStepperInit(){
    
    if (gantryState != ZEROPOSITION) {
        return ERROR;
    }else{
        printf("zStepperInit\r\n");
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
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    SerialCom_Init();
    xStepperInit();
    zStepperInit();
    
    printf("Hydroponic Automation\r\n");

    
    for(EVER)
    {   
        switch(gantryState){
            case ZEROPOSITION:
                if(!xLimitflag){
                    xStepsToMove = FULL_X_LENGTH_STEPS;
                }else{
                    xStepsToMove=0;
                }
                if(!zLimitflag){
                    zStepsToMove= FULL_Z_LENGTH; //INITIAL_STEPS_FULLSTEP                 
                }else{
                    zStepsToMove=0;
                }
                if(xLimitflag && zLimitflag){
                    gantryState=DECONTAMINATE;
                    prevState=ZEROPOSITION;
                    xStepsToMove = INITIAL_TO_DECON;                       
                    zStepsToMove = TOP_TO_CALIBRATE;
                    xMoveFlag=1;
                    zMoveFlag=1;
                    Z_Step_Timer_Start();
                    Z_Step_ISR_StartEx(Z_Step_ISR);
                    Z_Limit_ISR_Stop();
                    X_Step_Timer_Start();
                    X_Step_ISR_StartEx(X_Step_ISR);
                    X_Limit_ISR_Stop();
                }
                break;
            case MEASUREMENT:
                zStepsToMove=TOP_TO_BOTTOM;
                break;
            case DECONTAMINATE:
                switch(prevState){
                    case ZEROPOSITION:
                        if((xMoveFlag && zMoveFlag)==0){
                            gantryState=TARGET_1;
                            prevState=DECONTAMINATE;
                            xMoveFlag=1;
                            zMoveFlag=1;
                            xStepsToMove = DECON_TO_TARGET1;                       
                            zStepsToMove = TOP_TO_CALIBRATE;
                            X_Step_Timer_Start();
                            X_Step_ISR_StartEx(X_Step_ISR);
                            Z_Limit_ISR_Start();
                            Z_Step_Timer_Start();
                            Z_Step_ISR_StartEx(Z_Step_ISR);
                        }    
                        break;
                    case TARGET_1:    
                    default:
                        break;
                }
            case TARGET_1:
                if((xMoveFlag && zMoveFlag)==0){
                    gantryState=DECONTAMINATE;
                    prevState=TARGET_1;
                    xMoveFlag=1;
                    zMoveFlag=1;
                    xStepsToMove = TARGET1_TO_DECON;                       
                    zStepsToMove = FULL_Z_LENGTH;
                    X_Step_Timer_Start();
                    X_Step_ISR_StartEx(X_Step_ISR);
                    Z_Limit_ISR_Start();
                    Z_Step_Timer_Start();
                    Z_Step_ISR_StartEx(Z_Step_ISR);
                }  
            default:
                break;
        }
     }
}
#endif

/* [] END OF FILE */
