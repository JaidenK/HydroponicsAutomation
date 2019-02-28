#include "hydro_gui_Scene.h"
#include "hydro_gui_GuiElement.h"

#include <stdlib.h>

void drawScene(void *scene);

Scene *newScene(GuiElement **elements, int numElements, GuiElement *initialSelection) {
  Scene *newScene = malloc(sizeof(Scene));
  newScene->elements = elements;
  newScene->numElements = numElements;
  newScene->draw = drawScene;
  newScene->selectedElement = initialSelection;
  return newScene;
}

void drawScene(void *scene_) {
  Scene *scene = scene_;
  for(int i = 0; i < scene->numElements; i++) {
    scene->elements[i]->draw(scene->elements[i]);
  }
}

GuiElement *moveUp(Scene *scene) {
   if(scene->selectedElement->up) {
      scene->selectedElement->isSelected = 0;
      scene->selectedElement = scene->selectedElement->up;
   }
   scene->selectedElement->isSelected = 1;
   return scene->selectedElement;
}
GuiElement *moveDown(Scene *scene) {
   if(scene->selectedElement->down) {
      scene->selectedElement->isSelected = 0;
      scene->selectedElement = scene->selectedElement->down;
   }
   scene->selectedElement->isSelected = 1;
   return scene->selectedElement;
}
GuiElement *moveLeft(Scene *scene) {
   if(scene->selectedElement->left) {
      scene->selectedElement->isSelected = 0;
      scene->selectedElement = scene->selectedElement->left;
   }
   scene->selectedElement->isSelected = 1;
   return scene->selectedElement;
}
GuiElement *moveRight(Scene *scene) {
   if(scene->selectedElement->right) {
      scene->selectedElement->isSelected = 0;
      scene->selectedElement = scene->selectedElement->right;
   }
   scene->selectedElement->isSelected = 1;
   return scene->selectedElement;
}
