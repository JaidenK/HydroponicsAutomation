#include "hydro_gui.h"
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

void click_targetSelect_back(void *btn_);
void draw_targetSelect(void *scene_);

void scene_targetSelect_init() {
 
  Button *b1 = newButton(width/2-210,height/2+10,200,60,"Flow");
  Button *b2 = newButton(width/2+10 ,height/2+10,200,60,"pH");
  Button *b3 = newButton(width/2-210,height/2-70,200,60,"EC");
  Button *b4 = newButton(width/2+10 ,height/2-70,200,60,"Water");
  Button *b5 = newButton(width/2-210,70,420,60,"Back");
  
  b5->click = click_targetSelect_back;

  setGuiNeighbors(b1->gui_base, NULL, b3->gui_base, NULL, b2->gui_base);
  setGuiNeighbors(b2->gui_base, NULL, b4->gui_base, b1->gui_base, NULL);
  setGuiNeighbors(b3->gui_base, b1->gui_base, b5->gui_base, NULL, b4->gui_base);
  setGuiNeighbors(b4->gui_base, b2->gui_base, b5->gui_base, b3->gui_base, NULL);
  setGuiNeighbors(b5->gui_base, b3->gui_base, NULL, NULL, NULL);

  GuiElement **elems = malloc(6*sizeof(GuiElement*));
  elems[0] = boke->gui_base;
  elems[1] = b1->gui_base;
  elems[2] = b2->gui_base;
  elems[3] = b3->gui_base;
  elems[4] = b4->gui_base;
  elems[5] = b5->gui_base;

  scene_targetSelect = newScene(elems, 6, b5->gui_base);
}

void click_targetSelect_back(void *btn_) {
  printf("Back\n");
  sceneTransition(currentScene,scene_dashboard,ST_EASE_RIGHT);
}



