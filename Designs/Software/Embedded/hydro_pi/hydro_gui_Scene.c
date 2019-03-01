#include "hydro_gui_Scene.h"
#include "hydro_gui_GuiElement.h"

#include <stdlib.h>
#include <stdio.h>

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

Scene *sceneTransition(Scene *prevScene, Scene *nextScene) {
  prevScene->close(prevScene);
  nextScene->open(nextScene);
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
