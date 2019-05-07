#include "hydro_gui.h"
#include "hydro_gui_Button.h"
#include "hydro_gui_Flipper.h"
#include "hydro_gui_Scene.h"
#include "scene_targetSelect.h"
#include "scene_phTarget.h"

// Graphics
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>

#include <stdio.h>
#include <stdlib.h>

void click_phTarget_back(void *btn_);
void click_phTarget_ok(void *btn_);
void open_phTarget(void *scene_);
void draw_phTarget(void *scene_);

void scene_phTarget_init() {
 
  Button *btnBack = newButton(width/2+10,height/2-70,200,60,"Back");
  Button *btnOk = newButton(width/2-210,height/2-70,200,60,"Apply");

  btnBack->click = click_phTarget_back;
  btnOk->click = click_phTarget_ok;

  Flipper *flipper = newFlipper(220,height/2,600,80,2,3,12.345);

  setGuiNeighbors(btnOk->gui_base,flipper->gui_base,NULL,NULL,btnBack->gui_base);
  setGuiNeighbors(flipper->gui_base,NULL,NULL,btnOk->gui_base,btnBack->gui_base);
  setGuiNeighbors(btnBack->gui_base,flipper->gui_base,NULL,btnOk->gui_base,NULL);


  GuiElement **elems = malloc(4*sizeof(GuiElement*));
  elems[0] = boke->gui_base;
  elems[1] = btnOk->gui_base;
  elems[2] = flipper->gui_base;
  elems[3] = btnBack->gui_base;

  scene_phTarget = newScene(elems, 4, btnBack->gui_base);
  scene_phTarget->open = open_phTarget;
  scene_phTarget->draw = draw_phTarget;
}

void click_phTarget_back(void *btn_) {
  sceneTransition(currentScene,scene_targetSelect,ST_EASE_RIGHT);
}
void click_phTarget_ok(void *btn_) {
  gui_sd->ph_target = ((Flipper *)currentScene->elements[2]->child)->value;
  printf("New pH target: %f\n", gui_sd->ph_target);
}

void open_phTarget(void *scene_) {
  Scene *scene = scene_;
  ((Flipper *)scene->elements[2]->child)->value = gui_sd->ph_target;
}

void draw_phTarget(void *scene_) {
  Scene *scene = scene_;
  for(int i = 0; i < scene->numElements; i++) {
    scene->elements[i]->draw(scene->elements[i]);
  }
  Fill(255, 255, 255, 1);         // White text
  char buf[64];
  sprintf(buf,"pH Target: %2.3f", gui_sd->ph_target);
  Text(20, height-50, buf, SerifTypeface, 30);  // Greetings 
}


