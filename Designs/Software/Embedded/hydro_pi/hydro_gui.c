#include "hydro_gui.h"
#include "hydro_gui_GuiElement.h"
#include "hydro_gui_Button.h"
#include "hydro_gui_IconButton.h"
#include "hydro_gui_Scene.h"
#include "hydro_gui_Boke.h"
#include "hydro_gui_Flipper.h"
#include "sensor_data.h"

#include "scene_dashboard.h"
#include "scene_targetSelect.h"
#include "scene_flowTarget.h"
#include "scene_phTarget.h"
#include "scene_ecTarget.h"
#include "scene_waterTarget.h"

 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <unistd.h> // usleep()
#include <math.h>
#include <sys/time.h> // for debounce clock
#include <pthread.h> // For automatically deselecting button

// Graphics
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>

// Interfaces
#include "QEI.h"
#include "Joy.h"
#include "vg_keyboard.h"
#include "vg_flipper.h"

enum gui_scenes {
  IP_DISPLAY
} gui_scene;



Scene *scene_mainMenu;
Scene *scene_tempTarget;
Scene *scene_ecTarget;
Scene *scene_phTarget;
Scene *scene_flowTarget;


// For displaying IP
char ipBuf[512];

// Joystick interrupts
void joy_up(void);
void joy_down(void);
void joy_left(void);
void joy_right(void);
void joy_click(void);

int xJoy = 0;
int yJoy = 0;
    

// Debouncing
struct timeval t_clickDebounceEvent;
double t_clickDebounceDuration = 1; // Minimum seconds between click events.
struct timeval t_joyMoveDebounceEvent;
double t_joyMoveDebounceDuration = 0.3; // Minimum seconds between movement events.

// Visual highlight inactivity delay
struct timeval t_lastActivity;
#define INACTIVITY_DELAY 3
void *inactivity_thread(void *foo);

#define TOUCH(tval) (gettimeofday(&tval,NULL))

// For some reason CLOCKS_PER_SEC seems to be twice the real value?
// Using clocks per sec just isn't working right
int debounce(struct timeval *t_lastEvent, double debounceDuration, void (*func)());

struct timeval t_lastFrame;
int framerate = 24;

// Infinite loop that draws the GUI
void *thread_draw(void *foo);










void click_dispIpCont(void *btn_) {
  printf("Continue.\n");
  currentScene = scene_mainMenu;
}
void click_dispIpClose(void *btn_) {
  printf("Closing.\n");
  exit(0);
}

void drawDisplayIP(void *scene_){
  Scene *scene = scene_;
  for(int i = 0; i < scene->numElements; i++) {
    scene->elements[i]->draw(scene->elements[i]);
  }
  TextMid((width/2), (height/2), ipBuf, SerifTypeface, height/20);   
  TextMid((width/2), (height/2)-(2*height/20), "Press Joystick to close.", SerifTypeface, height/20);   
}

/* ------- END OF SCENE DRAWING FUNCTIONS ------- */










void HYDRO_GUI_Init(int createThread, struct SensorData *sd) {
  gui_sd = sd;
  // Setup Graphics
  saveterm(); // Save current screen
  init(&width, &height); // Initialize display and get width and height
  Start(width, height);
  //rawterm(); // Needed to receive control characters from keyboard, such as ESC

  // Pins for the Y axis of the joystick (op-amp output). 
  // BCM 23, 22, 27, 17, 4, 3
  JOY_Init(3,2,7,0,9,joy_up,joy_down,joy_left,joy_right,joy_click);
  JOY_PreventNegativePositions();
  
  // VG_KB_Init();
  // VG_FLIPPER_Init(2,3,12.345);
  
  // // Setup Graphics
  // // Graphics
  // saveterm(); // Save current screen
  // init(&width, &height); // Initialize display and get width and height
  // Start(width, height);
  // //rawterm(); // Needed to receive control characters from keyboard, such as ESC
  
  // Background(0, 0, 0);          // Black background
  // Fill(255, 255, 255, 1);         // White text
  // TextMid((width/2), (height/2), "Testing network connection...", SerifTypeface, height/20);  // Greetings 
  // End();
  // int xMin, int xMax, int yMin, int yMax, double radius, double vX, double vY, double vZ, double vVariance, int R, int G, int B, int count
  

  scene_dashboard_init();
  currentScene = scene_dashboard;
  scene_targetSelect_init();
  scene_flowTarget_init();
  scene_phTarget_init();
  scene_ecTarget_init();
  scene_waterTarget_init();

  TOUCH(t_lastFrame);
  TOUCH(t_clickDebounceEvent);
  TOUCH(t_joyMoveDebounceEvent);
  TOUCH(t_lastActivity);

  // Thread for making selected button unselected after a period of time.
  pthread_t tid_inactivity;
  pthread_create(&tid_inactivity, NULL, inactivity_thread, NULL);

  if(createThread == 1) {
    pthread_t tid_draw;
    pthread_create(&tid_draw, NULL, thread_draw, NULL);
  }
}

void HYDRO_GUI_SetScene(enum gui_scenes newScene) {
  gui_scene = newScene;
}

void HYDRO_GUI_Draw() {
  Background(20,20,120);

  currentScene->draw(currentScene);
  if(backgroundScene){
    backgroundScene->draw(backgroundScene);
  }

  // waitForNextFrame();
  End();
  usleep(10000);
}

void *thread_draw(void *foo) {
  // Setup Graphics
  // Graphics
  saveterm(); // Save current screen
  init(&width, &height); // Initialize display and get width and height
  Start(width, height);
  //rawterm(); // Needed to receive control characters from keyboard, such as ESC

  while(1) {
    HYDRO_GUI_Draw();
  }
}

int displayIP() {
  char ipStr[256]; // Surely we wont need 256 chars for the ip string?
  char line[512]; // line for reading output
  FILE *console = popen("ifconfig | grep wlan0 -A1","r");
  if(console==NULL) {
    printf("Could not make ifconfig system call.\n%s\n",strerror(errno));
  }
  // Loop through each line of file
  while(fgets(line,512,console)!=NULL){
    char *word = strstr(line,"inet");
    if(word != NULL) {
      word += 5; // Move pointer past inet
      sscanf(word,"%s",ipStr);
      break;
    }
  }
  pclose(console);
  printf("%s\n",ipStr);

  Background(0, 0, 0);          // Black background
  Fill(255, 255, 255, 1);         // White text
  sprintf(ipBuf, "IP: %s",ipStr);
  End();

  Button *b1 = newButton(width/2-210,20,200,60,"Continue");
  b1->click = click_dispIpCont;
  Button *b2 = newButton(width/2+10,20,200,60,"Close");
  b2->click = click_dispIpClose;

  setGuiNeighbors(b1->gui_base, NULL, NULL, NULL, b2->gui_base);
  setGuiNeighbors(b2->gui_base, NULL, NULL, b1->gui_base, NULL);

  GuiElement **elems = malloc(2*sizeof(GuiElement));
  elems[0] = b1->gui_base;
  elems[1] = b2->gui_base;
  Scene *scene_displayIP = newScene(elems, 2, b1->gui_base);
  scene_displayIP->draw = drawDisplayIP;
  currentScene = scene_displayIP;
  
  // clock_t now = clock();
  // while(clock() - now < CLOCKS_PER_SEC) {
  //   // if(isRunning == 0) {
  //   //   return 1;
  //   // }
  // }
  return 2;
}

void joy_up(void) {
  TOUCH(t_lastActivity);
  // VG_KB_Up();
  // VG_FLIPPER_Up();
  debounce(&t_joyMoveDebounceEvent,t_joyMoveDebounceDuration,({
    void __fn__ () {
      moveUp(currentScene);
    } __fn__;
  }));
}
void joy_down(void){
  TOUCH(t_lastActivity);
  // VG_KB_Down();
  // VG_FLIPPER_Down();
  debounce(&t_joyMoveDebounceEvent,t_joyMoveDebounceDuration,({
    void __fn__ () {
      moveDown(currentScene);
    } __fn__;
  }));
}
void joy_left(void){
  TOUCH(t_lastActivity);
  // VG_KB_Left();
  // VG_FLIPPER_Left();
  debounce(&t_joyMoveDebounceEvent,t_joyMoveDebounceDuration,({
    void __fn__ () {
      moveLeft(currentScene);
    } __fn__;
  }));
}
void joy_right(void){
  TOUCH(t_lastActivity);
  // VG_KB_Right();
  // VG_FLIPPER_Right();
  debounce(&t_joyMoveDebounceEvent,t_joyMoveDebounceDuration,({
    void __fn__ () {
      moveRight(currentScene);
    } __fn__;
  }));
}


void joy_click(void) {
  TOUCH(t_lastActivity);
  // clicked = !clicked;
  // switch(hydro_state) {
  //   case HYDRO_IDLE:
      // isRunning = 0;
      // exit(0);
  //     break;
  //   case WIFI_SELECTING_NETWORK:
  //     selectedNetwork = yJoy;
  //     break;
  //   case STARTUP_DISP_IP:
  //     isRunning = 0;
  //     break;
  // }
  //debounce(&t_joyDebounceEvent,t_joyDebounceDuration,addKeyToPassword);
  debounce(&t_clickDebounceEvent,t_clickDebounceDuration,({
    void __fn__ () {
      printf("click\n");
      currentScene->selectedElement->click(currentScene->selectedElement);
    } __fn__;
  }));//void(){
    //currentScene->selectedElement->click(currentScene->selectedElement
  //});
}

int debounce(struct timeval *t_lastEvent, double debounceDuration, void (*func)()) {
  // clock_t now = clock();
  struct timeval now;
  gettimeofday(&now, NULL);
  double secs = (double)(now.tv_usec - t_lastEvent->tv_usec) / 1000000 + (double)(now.tv_sec - t_lastEvent->tv_sec);
  if(secs > debounceDuration) {
    gettimeofday(t_lastEvent, NULL);
    func();
    return 0;
  }else{
    //printf("Debounced. (%.2f/%.2f)\n", secs, debounceDuration);
  }
  return 1;
}

int waitForNextFrame() {
  struct timeval now;
  double secs = 0;
  int cycles = -1;
  do {
    TOUCH(now);
    secs = (double)(now.tv_usec - t_lastFrame.tv_usec) / 1000000 + (double)(now.tv_sec - t_lastFrame.tv_sec);
    cycles++;
  }while(secs < FRAME_PERIOD);
  if(cycles < 1){ 
    //printf("Dropped frame.\n");
  }
  return cycles < 1;
}

void *inactivity_thread(void *foo) {
  struct timeval inactivityThreadNow;
  while(1) {
    TOUCH(inactivityThreadNow);
    if(inactivityThreadNow.tv_sec - t_lastActivity.tv_sec > INACTIVITY_DELAY) {
      currentScene->selectedElement->isSelected = 0;
    }
    sleep(1);
  }
}
