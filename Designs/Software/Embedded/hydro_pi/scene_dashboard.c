#include "hydro_gui.h"
#include "hydro_gui_Boke.h"
#include "hydro_gui_Button.h"
#include "hydro_gui_Scene.h"
#include "scene_dashboard.h"
#include "scene_targetSelect.h"

// Graphics
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>

#include <stdio.h>
#include <stdlib.h>

void click_dashboard_targets(void *btn_);
void draw_dashboard(void *scene_);

void scene_dashboard_init() {
  boke = newBoke(-width/2, width/2, height/3, height, 20, 0.9, 0, 0, 0.1, 255, 255, 255, 15);
  
  Button *b1 = newButton(30,20,200,60,"Targets");
  b1->click = click_dashboard_targets;

  GuiElement **elems = malloc(2*sizeof(GuiElement*));
  elems[0] = boke->gui_base;
  elems[1] = b1->gui_base;

  scene_dashboard = newScene(elems, 2, b1->gui_base);
  scene_dashboard->draw = draw_dashboard;
}

void click_dashboard_targets(void *btn_) {
  printf("Targets\n");
  sceneTransition(currentScene,scene_targetSelect,ST_EASE_LEFT);
}

void draw_dashboard(void *scene_) {
  Scene *scene = scene_;
  for(int i = 0; i < scene->numElements; i++) {
    scene->elements[i]->draw(scene->elements[i]);
  }
  Fill(255, 255, 255, 1);         // White text
  TextMid((width/2), height - 40, "Main Menu", SerifTypeface, 30);  // Greetings 
}
