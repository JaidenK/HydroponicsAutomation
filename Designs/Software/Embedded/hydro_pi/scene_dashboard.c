#include "hydro_gui.h"
#include "hydro_gui_Boke.h"
#include "hydro_gui_Button.h"
#include "hydro_gui_Scene.h"
// #include "hydro_gui_Graph.h"
#include "scene_dashboard.h"
#include "scene_targetSelect.h"

// Graphics
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buf_dashboard[32];

void click_dashboard_targets(void *btn_);
void click_dashboard_reboot(void *btn_);
void draw_dashboard(void *scene_);

void scene_dashboard_init() {
  boke = newBoke(-width/2, width/2, height/3, height, 20, 0.9, 0, 0, 0.1, 255, 255, 255, 15);
  
  Button *b1 = newButton(30,20,200,60,"Targets");
  b1->click = click_dashboard_targets;

  Button *b2 = newButton(width-230,20,200,60,"Reboot");
  b2->click = click_dashboard_reboot;

  // Graph *graph = newGraph(10, 10, 200, 100);

  setGuiNeighbors(b1->gui_base, NULL, NULL, NULL, b2->gui_base);
  setGuiNeighbors(b2->gui_base, NULL, NULL, b1->gui_base, NULL);

  GuiElement **elems = malloc(3*sizeof(GuiElement*));
  elems[0] = boke->gui_base;
  elems[1] = b1->gui_base;
  elems[2] = b2->gui_base;

  scene_dashboard = newScene(elems, 3, b1->gui_base);
  scene_dashboard->draw = draw_dashboard;
}

void click_dashboard_targets(void *btn_) {
  sceneTransition(currentScene,scene_targetSelect,ST_EASE_LEFT);
}

void click_dashboard_reboot(void *btn_) {
  popen("reboot now","r");
}

void draw_dashboard(void *scene_) {
  Scene *scene = scene_;
  for(int i = 0; i < scene->numElements; i++) {
    scene->elements[i]->draw(scene->elements[i]);
  }
  Fill(255, 255, 255, 1);         // White text
  TextMid((width/2), height - 40, "Main Menu", SerifTypeface, 30);  
  sprintf(buf_dashboard,"Flow: %.2f",gui_sd->flow_measured);
  Text(20, height - 100, buf_dashboard, SerifTypeface, 30);  
  sprintf(buf_dashboard,"pH: %.2f",gui_sd->ph_level);
  Text(width/2, height - 100, buf_dashboard, SerifTypeface, 30);  
  sprintf(buf_dashboard,"EC: %.2f",gui_sd->ec_level);
  Text(20, height - 200, buf_dashboard, SerifTypeface, 30);   
  sprintf(buf_dashboard,"H2O: %.2f",gui_sd->h2o_level);
  Text(width/2, height - 200, buf_dashboard, SerifTypeface, 30);  
  sprintf(buf_dashboard,"Temp: %.2f",gui_sd->temp_measured);
  Text(20, height - 300, buf_dashboard, SerifTypeface, 30);  
  
}
