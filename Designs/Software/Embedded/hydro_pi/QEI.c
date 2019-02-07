#include "QEI.h"

#include <stdint.h>
#include <stdio.h>

// Peripheral libraries
#include <wiringPi.h>

// Pin assignments
int chA = 0;
int chB = 0;

// Accumulated position. 4 per click
int position = 0;

// States based on the direction you're turning
enum enc_states {
  ENC_IDLE, ENC_CW_A, ENC_CW_AB, ENC_CW_B, ENC_CCW_B, ENC_CCW_BA, ENC_CCW_A
} state;

void CHANGE_ISR(void);

void QEI_Init(int chA_, int chB_) {
  chA = chA_;
  chB = chB_;
  // Configure the pins for input
  pinMode(chA,INPUT);
  pinMode(chB,INPUT);
  // Specify the pull down resistors.
  // (Not sure if necessary)
  pullUpDnControl(chA, PUD_DOWN); 
  pullUpDnControl(chB, PUD_DOWN); 
  // Assign the ISRs
  wiringPiISR(chA,INT_EDGE_BOTH,CHANGE_ISR);
  wiringPiISR(chB,INT_EDGE_BOTH,CHANGE_ISR);
  // Make sure the state starts at idle.
  state = ENC_IDLE;
}

int QEI_GetPosition() {
  return position;
  //return (digitalRead(chA) << 1) | digitalRead(chB);
}



void CHANGE_ISR() {
  int a = digitalRead(chA);
  int b = digitalRead(chB);
  uint8_t AB = (a<<1) | b;
  
  
  // Switch through each state and do the appropriate action based on 
  // the states of AB
  switch(state) {
    case ENC_IDLE:
      switch(AB) {
        case 0b00:
          // Do nothing
          break;
        case 0b01:
          // CCW start
          position--;
          state = ENC_CCW_B;
          break;
        case 0b10:
          // CW start
          position++;
          state = ENC_CW_A;
          break;
        case 0b11:
          // Error
          printf("QEI ERROR 1\n");
          break;
      }
      break;
    case ENC_CW_A:
      switch(AB) {
        case 0b00:
          // Backwards
          position--;
          state = ENC_IDLE;
          break;
        case 0b01:
          // Error
          printf("QEI ERROR 2\n");
          state = ENC_IDLE;
          break;
        case 0b10:
          // Do nothing
          break;
        case 0b11:
          // continue turn
          position++;
          state = ENC_CW_AB;
          break;
      }
      break;
    case ENC_CW_AB:
      switch(AB) {
        case 0b00:
          // Error
          printf("QEI ERROR 3\n");
          state = ENC_IDLE;
          break;
        case 0b01:
          // continue turn
          position++;
          state = ENC_CW_B;
          break;
        case 0b10:
          // Backwards
          position--;
          state = ENC_CW_A;
          break;
        case 0b11:
          // Do nothing
          break;
      }
      break;
    case ENC_CW_B:
      switch(AB) {
        case 0b00:
          // continue turn
          position++;
          state = ENC_IDLE;
          break;
        case 0b01:
          // Do nothing
          break;
        case 0b10:
          // Error
          printf("QEI ERROR 4\n");
          state = ENC_IDLE;
          break;
        case 0b11:
          // Backwards
          position--;
          state = ENC_CW_AB;
          break;
      }
      break;
    case ENC_CCW_B:
      switch(AB) {
        case 0b00:
          // Backwards
          position++;
          state = ENC_IDLE;
          break;
        case 0b01:
          // Do nothing
          break;
        case 0b10:
          // Error
          printf("QEI ERROR 5\n");
          state = ENC_IDLE;
          break;
        case 0b11:
          // continue turn
          position--;
          state = ENC_CCW_BA;
          break;
      }
      break;
    case ENC_CCW_BA:
      switch(AB) {
        case 0b00:
          // Error
          printf("QEI ERROR 6\n");
          state = ENC_IDLE;
          break;
        case 0b01:
          // Backwards
          position++;
          state = ENC_CCW_B;
          break;
        case 0b10:
          // continue turn
          position--;
          state = ENC_CCW_A;
          break;
        case 0b11:
          // Do nothing
          break;
      }
      break;
    case ENC_CCW_A:
      switch(AB) {
        case 0b00:
          // continue turn
          position--;
          state = ENC_IDLE;
          break;
        case 0b01:
          // Error
          printf("QEI ERROR 7\n");
          state = ENC_IDLE;
          break;
        case 0b10:
          // Do nothing
          break;
        case 0b11:
          // Backwards
          position++;
          state = ENC_CCW_BA;
          break;
      }
      break;
  }
}
