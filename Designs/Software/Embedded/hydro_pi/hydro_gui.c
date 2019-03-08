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









// Button click functions
void btn1click(void *btn_) {
  printf("Heyyy\n");
}

void btn2click(void *btn_) {
  printf("Lenny\n");
}

void click_dispIpCont(void *btn_) {
  printf("Continue.\n");
  currentScene = scene_mainMenu;
}
void click_dispIpClose(void *btn_) {
  printf("Closing.\n");
  exit(0);
}
void click_mainMenu_temp(void *btn_){
  currentScene = sceneTransition(currentScene,scene_tempTarget,ST_EASE_LEFTRIGHT);
}
void click_mainMenu_ec(void *btn_){
  currentScene = sceneTransition(currentScene,scene_ecTarget,ST_EASE_LEFTRIGHT);
}
void click_mainMenu_ph(void *btn_){
  currentScene = sceneTransition(currentScene,scene_phTarget,ST_EASE_LEFTRIGHT);
}
void click_mainMenu_flow(void *btn_){
  currentScene = sceneTransition(currentScene,scene_flowTarget,ST_EASE_LEFTRIGHT);
}

void click_tempTarget_back(void *btn_) {
  currentScene = sceneTransition(currentScene,scene_mainMenu,ST_EASE_LEFTRIGHT);
}
void click_tempTarget_ok(void *btn_) {
  gui_sd->temp_target = ((Flipper *)currentScene->elements[3]->child)->value;
  printf("New temperature target: %f\n", gui_sd->temp_target);
}
void click_ecTarget_back(void *btn_) {
  currentScene = sceneTransition(currentScene,scene_mainMenu,ST_EASE_LEFTRIGHT);
}
void click_ecTarget_ok(void *btn_) {
  gui_sd->ec_target = ((Flipper *)currentScene->elements[3]->child)->value;
  printf("New ec target: %f\n", gui_sd->ec_target);
}
void click_phTarget_back(void *btn_) {
  currentScene = sceneTransition(currentScene,scene_mainMenu,ST_EASE_LEFTRIGHT);
}
void click_phTarget_ok(void *btn_) {
  gui_sd->ph_target = ((Flipper *)currentScene->elements[3]->child)->value;
  printf("New ph target: %f\n", gui_sd->ph_target);
}
void click_flowTarget_back(void *btn_) {
  currentScene = sceneTransition(currentScene,scene_mainMenu,ST_EASE_LEFTRIGHT);
}
void click_flowTarget_ok(void *btn_) {
  gui_sd->flow_target = ((Flipper *)currentScene->elements[3]->child)->value;
  printf("New flow target: %f\n", gui_sd->flow_target);
}











/* ------- SCENE OPENING FUNCTIONS ------- */
void open_tempTargetScene(void *scene_) {
  Scene *scene = scene_;
  ((Flipper *)scene->elements[3]->child)->value = gui_sd->temp_target;
}
void open_ecTargetScene(void *scene_) {
  Scene *scene = scene_;
  ((Flipper *)scene->elements[3]->child)->value = gui_sd->ec_target;
}
void open_phTargetScene(void *scene_) {
  Scene *scene = scene_;
  ((Flipper *)scene->elements[3]->child)->value = gui_sd->ph_target;
}
void open_flowTargetScene(void *scene_) {
  Scene *scene = scene_;
  ((Flipper *)scene->elements[3]->child)->value = gui_sd->flow_target;
}







/* ------- SCENE DRAWING FUNCTION ------- */
void drawMainMenu(void *scene_) {
  Scene *scene = scene_;
  for(int i = 0; i < scene->numElements; i++) {
    scene->elements[i]->draw(scene->elements[i]);
  }
  Fill(255, 255, 255, 1);         // White text
  TextMid((width/2), (height/2), "Main Menu", SerifTypeface, height/20);  // Greetings 

}
void draw_tempTarget(void *scene_) {
  Scene *scene = scene_;
  for(int i = 0; i < scene->numElements; i++) {
    scene->elements[i]->draw(scene->elements[i]);
  }
  Fill(255, 255, 255, 1);         // White text
  char buf[64];
  sprintf(buf,"Temp Target: %2.3f", gui_sd->temp_target);
  Text(20, height-40, buf, SerifTypeface, 20);  // Greetings 
}
void draw_ecTarget(void *scene_) {
  Scene *scene = scene_;
  for(int i = 0; i < scene->numElements; i++) {
    scene->elements[i]->draw(scene->elements[i]);
  }
  Fill(255, 255, 255, 1);         // White text
  char buf[64];
  sprintf(buf,"EC Target: %2.3f", gui_sd->ec_target);
  Text(20, height-40, buf, SerifTypeface, 20);  // Greetings 
}
void draw_phTarget(void *scene_) {
  Scene *scene = scene_;
  for(int i = 0; i < scene->numElements; i++) {
    scene->elements[i]->draw(scene->elements[i]);
  }
  Fill(255, 255, 255, 1);         // White text
  char buf[64];
  sprintf(buf,"pH Target: %2.3f", gui_sd->ph_target);
  Text(20, height-40, buf, SerifTypeface, 20);  // Greetings 
}
void draw_flowTarget(void *scene_) {
  Scene *scene = scene_;
  for(int i = 0; i < scene->numElements; i++) {
    scene->elements[i]->draw(scene->elements[i]);
  }
  Fill(255, 255, 255, 1);         // White text
  char buf[64];
  sprintf(buf,"Flow Target: %2.3f", gui_sd->flow_target);
  Text(20, height-40, buf, SerifTypeface, 20);  // Greetings 
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

  // Setup Graphics
  saveterm(); // Save current screen
  init(&width, &height); // Initialize display and get width and height
  Start(width, height);
  //rawterm(); // Needed to receive control characters from keyboard, such as ESC

  // Pins for the Y axis of the joystick (op-amp output). 
  // BCM 23, 22, 27, 17, 4, 3
  JOY_Init(3,2,7,0,9,joy_up,joy_down,joy_left,joy_right,joy_click);
  JOY_PreventNegativePositions();
  
  VG_KB_Init();
  VG_FLIPPER_Init(2,3,12.345);
  
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

  /* -------- BEGIN MAIN MENU SCENE -------- */

  Button *b1 = newButton(30,20,200,60,"Flow");
  Button *b2 = newButton(30,100,200,60,"pH");
  Button *b3 = newButton(30,180,200,60,"EC");
  Button *b4 = newButton(30,260,200,60,"Temp");
  IconButton *b5 = newIconButton(width-70, height-70, 60, 60, IB_GEAR);
  b4->click = click_mainMenu_temp;
  b3->click = click_mainMenu_ec;
  b2->click = click_mainMenu_ph;
  b1->click = click_mainMenu_flow;

  setGuiNeighbors(b1->gui_base, b2->gui_base,         NULL, NULL, NULL);
  setGuiNeighbors(b2->gui_base, b3->gui_base, b1->gui_base, NULL, NULL);
  setGuiNeighbors(b3->gui_base, b4->gui_base, b2->gui_base, NULL, NULL);
  setGuiNeighbors(b4->gui_base, NULL        , b3->gui_base, NULL, NULL);

  GuiElement **elems = malloc(6*sizeof(GuiElement*));
  elems[0] = boke->gui_base;
  elems[1] = b1->gui_base;
  elems[2] = b2->gui_base;
  elems[3] = b3->gui_base;
  elems[4] = b4->gui_base;
  elems[5] = b5->gui_base;

  scene_mainMenu = newScene(elems, 6, b1->gui_base);
  scene_mainMenu->draw = drawMainMenu;

  /* -------- BEGIN TEMP TARGET SCENE -------- */
  Button *button_tempTarget_back = newButton(width-210,height-70,200,60,"Back");
  button_tempTarget_back->click = click_tempTarget_back;
  Button *button_tempTarget_ok = newButton(width/2-100,100,200,60,"Apply");
  button_tempTarget_ok->click = click_tempTarget_ok;
  Flipper *flipper_tempTarget = newFlipper(width/2-300,height/2-40,600,80,2,3,12.345);

  setGuiNeighbors(button_tempTarget_back->gui_base, NULL, flipper_tempTarget->gui_base, NULL, flipper_tempTarget->gui_base);
  setGuiNeighbors(flipper_tempTarget->gui_base, NULL, NULL, button_tempTarget_back->gui_base, button_tempTarget_ok->gui_base);
  setGuiNeighbors(button_tempTarget_ok->gui_base, flipper_tempTarget->gui_base, NULL, flipper_tempTarget->gui_base, NULL);

  GuiElement **elems_tempTarget = malloc(4*sizeof(GuiElement*));
  elems_tempTarget[0] = boke->gui_base;
  elems_tempTarget[1] = button_tempTarget_back->gui_base;
  elems_tempTarget[2] = button_tempTarget_ok->gui_base;
  elems_tempTarget[3] = flipper_tempTarget->gui_base;

  scene_tempTarget = newScene(elems_tempTarget, 4, flipper_tempTarget->gui_base);
  scene_tempTarget->draw = draw_tempTarget;
  scene_tempTarget->open = open_tempTargetScene;

  /* -------- BEGIN EC TARGET SCENE -------- */
  Button *button_ecTarget_back = newButton(width-210,height-70,200,60,"Back");
  button_ecTarget_back->click = click_ecTarget_back;
  Button *button_ecTarget_ok = newButton(width/2-100,100,200,60,"Apply");
  button_ecTarget_ok->click = click_ecTarget_ok;
  Flipper *flipper_ecTarget = newFlipper(width/2-300,height/2-40,600,80,2,3,12.345);

  setGuiNeighbors(button_ecTarget_back->gui_base, NULL, flipper_ecTarget->gui_base, NULL, flipper_ecTarget->gui_base);
  setGuiNeighbors(flipper_ecTarget->gui_base, NULL, NULL, button_ecTarget_back->gui_base, button_ecTarget_ok->gui_base);
  setGuiNeighbors(button_ecTarget_ok->gui_base, flipper_ecTarget->gui_base, NULL, flipper_ecTarget->gui_base, NULL);

  GuiElement **elems_ecTarget = malloc(4*sizeof(GuiElement*));
  elems_ecTarget[0] = boke->gui_base;
  elems_ecTarget[1] = button_ecTarget_back->gui_base;
  elems_ecTarget[2] = button_ecTarget_ok->gui_base;
  elems_ecTarget[3] = flipper_ecTarget->gui_base;

  scene_ecTarget = newScene(elems_ecTarget, 4, flipper_ecTarget->gui_base);
  scene_ecTarget->draw = draw_ecTarget;
  scene_ecTarget->open = open_ecTargetScene;

  /* -------- BEGIN PH TARGET SCENE -------- */
  Button *button_phTarget_back = newButton(width-210,height-70,200,60,"Back");
  button_phTarget_back->click = click_phTarget_back;
  Button *button_phTarget_ok = newButton(width/2-100,100,200,60,"Apply");
  button_phTarget_ok->click = click_phTarget_ok;
  Flipper *flipper_phTarget = newFlipper(width/2-300,height/2-40,600,80,2,3,12.345);

  setGuiNeighbors(button_phTarget_back->gui_base, NULL, flipper_phTarget->gui_base, NULL, flipper_phTarget->gui_base);
  setGuiNeighbors(flipper_phTarget->gui_base, NULL, NULL, button_phTarget_back->gui_base, button_phTarget_ok->gui_base);
  setGuiNeighbors(button_phTarget_ok->gui_base, flipper_phTarget->gui_base, NULL, flipper_phTarget->gui_base, NULL);

  GuiElement **elems_phTarget = malloc(4*sizeof(GuiElement*));
  elems_phTarget[0] = boke->gui_base;
  elems_phTarget[1] = button_phTarget_back->gui_base;
  elems_phTarget[2] = button_phTarget_ok->gui_base;
  elems_phTarget[3] = flipper_phTarget->gui_base;

  scene_phTarget = newScene(elems_phTarget, 4, flipper_phTarget->gui_base);
  scene_phTarget->draw = draw_phTarget;
  scene_phTarget->open = open_phTargetScene;


  /* -------- BEGIN FLOW TARGET SCENE -------- */
  Button *button_flowTarget_back = newButton(width-210,height-70,200,60,"Back");
  button_flowTarget_back->click = click_flowTarget_back;
  Button *button_flowTarget_ok = newButton(width/2-100,100,200,60,"Apply");
  button_flowTarget_ok->click = click_flowTarget_ok;
  Flipper *flipper_flowTarget = newFlipper(width/2-300,height/2-40,600,80,2,3,12.345);

  setGuiNeighbors(button_flowTarget_back->gui_base, NULL, flipper_flowTarget->gui_base, NULL, flipper_flowTarget->gui_base);
  setGuiNeighbors(flipper_flowTarget->gui_base, NULL, NULL, button_flowTarget_back->gui_base, button_flowTarget_ok->gui_base);
  setGuiNeighbors(button_flowTarget_ok->gui_base, flipper_flowTarget->gui_base, NULL, flipper_flowTarget->gui_base, NULL);

  GuiElement **elems_flowTarget = malloc(4*sizeof(GuiElement*));
  elems_flowTarget[0] = boke->gui_base;
  elems_flowTarget[1] = button_flowTarget_back->gui_base;
  elems_flowTarget[2] = button_flowTarget_ok->gui_base;
  elems_flowTarget[3] = flipper_flowTarget->gui_base;

  scene_flowTarget = newScene(elems_flowTarget, 4, flipper_flowTarget->gui_base);
  scene_flowTarget->draw = draw_flowTarget;
  scene_flowTarget->open = open_flowTargetScene;





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
