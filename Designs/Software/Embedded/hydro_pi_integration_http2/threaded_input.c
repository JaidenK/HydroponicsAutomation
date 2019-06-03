#include "threaded_input.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>

#define THREADED_INPUT_BUF_SIZE 256
char threaded_input_buf[THREADED_INPUT_BUF_SIZE];
uint8_t hasNewLine = 0;


void *thread_readinput(void *foo) {
  while(1) {
   fgets(threaded_input_buf, THREADED_INPUT_BUF_SIZE, stdin);
   hasNewLine = 1;
  }
}

void ThreadedInput_Init() {
  pthread_t tid_input;
  pthread_create(&tid_input, NULL, thread_readinput, NULL);
}

char *getstr_nonblocking(char *str) {
   if(hasNewLine) {
      hasNewLine = 0;
      strcpy(str, threaded_input_buf);
      return str;
   }
   return NULL;
}
