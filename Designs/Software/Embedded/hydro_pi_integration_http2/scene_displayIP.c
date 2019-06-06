#include "hydro_gui.h"
#include "hydro_gui_Boke.h"
#include "hydro_gui_Button.h"
#include "hydro_gui_Scene.h"
#include "scene_targetSelect.h"
#include "scene_displayIP.h"
#include "scene_dashboard.h"

// Graphics
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h> // usleep()

// For displaying IP
char ipBuf[512];

pthread_t tid_updateIPstr;
int exitIpUpdateThread = 0;
void *ipUpdateStrThread(void *foo);

void click_displayIP_continue(void *btn_);
void click_displayIP_close(void *btn_);
void draw_displayIP(void *scene_);

void scene_displayIP_init() {
  Button *b1 = newButton(width/2-210,20,200,60,"Continue");
  b1->click = click_displayIP_continue;
  Button *b2 = newButton(width/2+10,20,200,60,"Close");
  b2->click = click_displayIP_close;

  setGuiNeighbors(b1->gui_base, NULL, NULL, NULL, b2->gui_base);
  setGuiNeighbors(b2->gui_base, NULL, NULL, b1->gui_base, NULL);
  GuiElement **elems = malloc(3*sizeof(GuiElement));
  elems[0] = boke->gui_base;
  elems[1] = b1->gui_base;
  elems[2] = b2->gui_base;
  scene_displayIP = newScene(elems, 3, b1->gui_base);
  scene_displayIP->draw = draw_displayIP; 

  pthread_create(&tid_updateIPstr, NULL, ipUpdateStrThread, NULL);
}

void click_displayIP_continue(void *btn_) {
  printf("Continue.\n");
  exitIpUpdateThread = 1;
  currentScene = scene_dashboard;
}
void click_displayIP_close(void *btn_) {
  printf("Closing.\n");
  exit(0);
}

void draw_displayIP(void *scene_){
  Scene *scene = scene_;
  for(int i = 0; i < scene->numElements; i++) {
    scene->elements[i]->draw(scene->elements[i]);
  }
  TextMid((width/2), (height/2), ipBuf, SerifTypeface, height/20);   
  TextMid((width/2), (height/2)-(2*height/20), "Press Joystick to close.", SerifTypeface, height/20);   
}

void *ipUpdateStrThread(void *foo) {
  usleep(500000); // Give it 0.5 sec on startup
  char ipStr[256]; // Surely we wont need 256 chars for the ip string?
  char line[512]; // line for reading output
  while(!exitIpUpdateThread) {
    // printf("Test ip\n");
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
    sprintf(ipBuf, "IP: %s",ipStr);
    usleep(2500000);
  }
  return NULL;
}
