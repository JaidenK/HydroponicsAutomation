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

//new and improved position macros
//X positions
#define RINSE_POSITION 75 //Check
#define SPONGE_POSITION 1100 //Check
#define PH4_POSITION 2325 //Check
#define PH7_POSITION 3600 //Check   
#define PH10_POSITION 4800 //Check

//Z positions
#define BOTTOM_POSITION 3000
#define CALIBRATION_POSITION 2100

//Timekeeping
#define FIVE_SECONDS 1000000
#define TWO_MINUITES 24000000

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

static enum {
    X_AXIS_MOVE_FINISHED,
    Z_AXIS_MOVE_FINISHED,
}finishedState=X_AXIS_MOVE_FINISHED; 

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
uint32_t startTime;
uint32_t finishTime;


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
                    UP;
                    Z_pos--;
                }else{
                    DOWN;
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

/**
 * @function Calibration_Init()
 * @param None
 * @return None
 * @brief Initialize calibration
 * @author Barron Wong 05/22/19
 */
void Calibration_Init(){
    gantryState=ZERO;
    zeroState=Z_AXIS_ZERO;
    spongeState=X_AXIS_MOVE_SPONGE; 
    Ph4State=X_AXIS_MOVE_PH4; 
    rinseState=X_AXIS_MOVE_RINSE; 
    Ph7State=X_AXIS_MOVE_PH7; 
    Ph10State=X_AXIS_MOVE_PH10; 
    finishedState=X_AXIS_MOVE_FINISHED;
    xStepsToMove=FULL_X_LENGTH_STEPS;
    xStepCount=0;
    xLimitflag=0;
    zLimitflag=0;
    zStepsToMove=FULL_X_LENGTH_STEPS;
    zStepCount=0;
    xLimitInitFlag=0;
    zLimitInitFlag=0;
    xMoveFlag=0;
    zMoveFlag=0;
    
    FreeRunningTimer_Init();
    FreeRunningTimer_Start();
    xStepperInit();
    zStepperInit();
    CalibrationEnable_Write(0);
    X_STOP;
    Z_STOP;
}

/**
 * @function Calibration_RunCalibration()
 * @param None
 * @return CALIBRATION_FINISHED if calibration is finished
 *         CALIBRATION_RUNNING if calibration is still running
 * @brief Runs Calibration
 * @author Barron Wong 05/22/19
 */
uint8_t Calibration_RunCalibration(){
    uint8_t return_val = CALIBRATION_RUNNING;
    switch (gantryState) {
    case ZERO:
        //printf("ZERO\r\n");
        switch (zeroState) {
            case Z_AXIS_ZERO:
                if (!zLimitflag) {
                    Z_START;
                } else {
                    Z_STOP;
                    zeroState = X_AXIS_ZERO;
                }
                break;
            case X_AXIS_ZERO:
                if (!xLimitflag) {
                    X_START;
                } else {
                    X_STOP;
                    zeroState = Z_AXIS_ZERO;
                    gantryState = SPONGE;
                    X_target = SPONGE_POSITION;
                    Ph4 = 0;
                    Ph7 = 0;
                    Ph10 = 0;
                    X_pos = 0;
                    Z_pos = 0;
                }
                break;
        }
        break;
    case SPONGE:
        //printf("SPONGE\r\n");
        switch (spongeState) {
            case X_AXIS_MOVE_SPONGE:
                if (X_pos != X_target) {
                    X_START;
                } else {
                    X_STOP;
                    spongeState = Z_AXIS_MOVE_SPONGE;
                    Z_target = CALIBRATION_POSITION; //TOP_TO_CALIBRATE
                }
                break;
            case Z_AXIS_MOVE_SPONGE:
                if (Z_pos != Z_target) {
                    Z_START;
                } else {
                    Z_STOP;
                    spongeState = Z_AXIS_ZERO_SPONGE;
                    zLimitflag = 0;
                    //printf("before ISR ENABLE\r\n");
                    zLimitInitFlag = 0;
                    Z_Limit_ISR_Enable();
                }
                break;
            case Z_AXIS_ZERO_SPONGE:
                if (!zLimitflag) {
                    Z_START;
                } else {
                    Z_STOP;
                    spongeState = X_AXIS_MOVE_SPONGE; //reset to initial sponge state
                    if (!Ph4) {
                        gantryState = PH4;
                        X_target = PH4_POSITION;
                    } else if (Ph4&&!Ph7) {
                        gantryState = PH7;
                        X_target = PH7_POSITION;
                    } else if (Ph4 && Ph7) {
                        gantryState = PH10;
                        X_target = PH10_POSITION;
                    }
                }
                break;
        }
        break;
    case PH4:
        //printf("PH4\r\n");
        switch (Ph4State) {
            case X_AXIS_MOVE_PH4:
                if (X_pos != X_target) {
                    X_START;
                } else {
                    X_STOP;
                    Ph4State = Z_AXIS_MOVE_PH4;
                    Z_target = CALIBRATION_POSITION;
                }
                break;
            case Z_AXIS_MOVE_PH4:
                if (Z_pos != Z_target) {
                    Z_START;
                    startTime = FreeRunningTimer_ReadCounter();
                } else {
                    Z_STOP;
                    if (startTime - FreeRunningTimer_ReadCounter() > FIVE_SECONDS) {
                        Ph4State = Z_AXIS_ZERO_PH4;
                        zLimitflag = 0;
                        zLimitInitFlag = 0;
                        Z_Limit_ISR_Enable();
                    }
                }
                break;
            case Z_AXIS_ZERO_PH4:
                if (!zLimitflag) {
                    Z_START;
                } else {
                    Z_STOP;
                    Ph4 = 1;
                    gantryState = RINSE;
                    X_target = RINSE_POSITION;
                }
                break;
        }
        break;
    case RINSE:
        //printf("RINSE\r\n");
        switch (rinseState) {
            case X_AXIS_MOVE_RINSE:
                if (X_pos != X_target) {
                    X_START;
                } else {
                    X_STOP;
                    rinseState = Z_AXIS_MOVE_RINSE;
                    Z_target = BOTTOM_POSITION;
                }
                break;
            case Z_AXIS_MOVE_RINSE:
                if (Z_pos != Z_target) {
                    Z_START;
                } else {
                    Z_STOP;
                    rinseState = Z_AXIS_ZERO_RINSE;
                    zLimitflag = 0;
                    zLimitInitFlag = 0;
                    Z_Limit_ISR_Enable();
                }
                break;
            case Z_AXIS_ZERO_RINSE:
                if (!zLimitflag) {
                    Z_START;
                } else {
                    Z_STOP;
                    gantryState = SPONGE;
                    rinseState = X_AXIS_MOVE_RINSE;
                    X_target = SPONGE_POSITION;
                }
                break;
        }
        break;
    case PH7:
        //printf("PH7\r\n");
        switch (Ph7State) {
            case X_AXIS_MOVE_PH7:
                if (X_pos != X_target) {
                    X_START;
                } else {
                    X_STOP;
                    Ph7State = Z_AXIS_MOVE_PH7;
                    Z_target = CALIBRATION_POSITION;
                }
                break;
            case Z_AXIS_MOVE_PH7:
                if (Z_pos != Z_target) {
                    Z_START;
                    startTime = FreeRunningTimer_ReadCounter();
                } else {
                    Z_STOP;
                    if (startTime - FreeRunningTimer_ReadCounter() > FIVE_SECONDS) {
                        Ph7State = Z_AXIS_ZERO_PH7;
                        zLimitflag = 0;
                        zLimitInitFlag = 0;
                        Z_Limit_ISR_Enable();
                    }
                }
                break;
            case Z_AXIS_ZERO_PH7:
                if (!zLimitflag) {
                    Z_START;
                } else {
                    Z_STOP;
                    gantryState = RINSE;
                    X_target = RINSE_POSITION;
                    Ph7 = 1;
                }
                break;
        }
        break;
    case PH10:
        //printf("PH10\r\n");
        switch (Ph10State) {
            case X_AXIS_MOVE_PH10:
                if (X_pos != X_target) {
                    X_START;
                } else {
                    X_STOP;
                    Ph10State = Z_AXIS_MOVE_PH10;
                    Z_target = CALIBRATION_POSITION;
                }
                break;
            case Z_AXIS_MOVE_PH10:
                if (Z_pos != Z_target) {
                    Z_START;
                    startTime = FreeRunningTimer_ReadCounter();
                } else {
                    Z_STOP;
                    if (startTime - FreeRunningTimer_ReadCounter() > FIVE_SECONDS) {
                        Ph10State = Z_AXIS_ZERO_PH10;
                        zLimitflag = 0;
                        zLimitInitFlag = 0;
                        Z_Limit_ISR_Enable();
                    }
                }
                break;
            case Z_AXIS_ZERO_PH10:
                if (!zLimitflag) {
                    Z_START;
                } else {
                    Z_STOP;
                    gantryState = FINISHED;
                    X_target = RINSE_POSITION;
                }
                break;
        }
        break;
    case FINISHED:
        //printf("FINISHED\r\n");
        switch (finishedState) {
            case X_AXIS_MOVE_FINISHED:
                if (X_pos != X_target) {
                    X_START;
                } else {
                    X_STOP;
                    // finishedState=X_AXIS_MOVE_FINISHED;
                    finishedState = Z_AXIS_MOVE_FINISHED;
                    Z_target = TOP_TO_BOTTOM;
                }
                break;
            case Z_AXIS_MOVE_FINISHED:
                if (Z_pos != Z_target) {
                    Z_START;
                } else {
                    Z_STOP;
                    return_val = CALIBRATION_FINISHED;
                    
                    //Reinitialize for next calibration
                    Calibration_Init();
                    
                }
                break;
            default:
                break;


        }
        break;
    default:
        break;
    }
    return return_val;
}

#ifdef CALIBRATION_TEST
#include "SerialCom.h"
int main(void)
{
    CyGlobalIntEnable;
    
    SerialCom_Init();
    Calibration_Init();
    
    printf("Hydroponic Automation\r\n");

    for(EVER){
        if(CalibrationTrigger_Read()){
            printf("Triggered\r\n");
            while(Calibration_RunCalibration()){
                printf("Running\r\n");
            }
            printf("Finished\r\n");
        }
        

    }
}
#endif

/* [] END OF FILE */
