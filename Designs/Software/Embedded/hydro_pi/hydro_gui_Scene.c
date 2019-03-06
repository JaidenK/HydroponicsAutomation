#include "hydro_gui.h"
#include "hydro_gui_Scene.h"
#include "hydro_gui_GuiElement.h"

#include <stdlib.h>
#include <stdio.h>

#include <sys/time.h>
#include <unistd.h> // usleep

void drawScene(void *scene);
void openScene(void *scene);
void closeScene(void *scene);

Scene *newScene(GuiElement **elements, int numElements, GuiElement *initialSelection) {
  Scene *newScene = malloc(sizeof(Scene));
  newScene->elements = elements;
  newScene->numElements = numElements;
  newScene->draw = drawScene;
  newScene->selectedElement = initialSelection;
  newScene->open = openScene;
  newScene->close = closeScene;
  return newScene;
}

void st_ease_leftright(Scene *prevScene, Scene *nextScene) {
  /*
  int easeDurationFrames = 6;
  int oldX[prevScene->numElements];
  int oldY[prevScene->numElements];
  for(int i = 0; i < prevScene->numElements; i++) {
    oldX[i] = prevScene->elements[i]->xPos;
    oldY[i] = prevScene->elements[i]->yPos;
  }
  for(int i = 0; i < easeDurationFrames; i++) {
    for(int n = 0; n < prevScene->numElements; n++) {
      if(oldX[n] < width/2) {
        prevScene->elements[n]->xPos -= (width/easeDurationFrames);
      }else{
        prevScene->elements[n]->xPos += (width/easeDurationFrames);
      }
    }
    usleep(FRAME_PERIOD * 1000000);
  }
  for(int i = 0; i < prevScene->numElements; i++) {
    prevScene->elements[i]->xPos = oldX[i];
  }
  */
  prevScene->close(prevScene);
  nextScene->open(nextScene);
}

Scene *sceneTransition(Scene *prevScene, Scene *nextScene, enum SceneTransitionType st_type) {
  switch(st_type) {
    case ST_EASE_LEFTRIGHT:
      st_ease_leftright(prevScene, nextScene);
      break;
  }
  return nextScene;
}

void drawScene(void *scene_) {
  Scene *scene = scene_;
  for(int i = 0; i < scene->numElements; i++) {
    scene->elements[i]->draw(scene->elements[i]);
  }
}

void openScene(void *scene) {
  printf("This scene has no open function.\n");
}

void closeScene(void *scene) {
  printf("This scene has no close function.\n");
}

GuiElement *moveUp(Scene *scene) {
  scene->selectedElement->isSelected = 0;
  scene->selectedElement = scene->selectedElement->moveUp(scene->selectedElement);
  scene->selectedElement->isSelected = 1;
  return scene->selectedElement;
}
GuiElement *moveDown(Scene *scene) {
  scene->selectedElement->isSelected = 0;
  scene->selectedElement = scene->selectedElement->moveDown(scene->selectedElement);
  scene->selectedElement->isSelected = 1;
  return scene->selectedElement;
}
GuiElement *moveLeft(Scene *scene) {
  scene->selectedElement->isSelected = 0;
  scene->selectedElement = scene->selectedElement->moveLeft(scene->selectedElement);
  scene->selectedElement->isSelected = 1;
  return scene->selectedElement;
}
GuiElement *moveRight(Scene *scene) {
  scene->selectedElement->isSelected = 0;
  scene->selectedElement = scene->selectedElement->moveRight(scene->selectedElement);
  scene->selectedElement->isSelected = 1;
  return scene->selectedElement;
}
