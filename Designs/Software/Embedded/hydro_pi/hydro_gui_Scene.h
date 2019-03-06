#ifndef _HYDRO_GUI_SCENE_H
#define _HYDRO_GUI_SCENE_H

#include "hydro_gui_GuiElement.h"

/**
 * @file hydro_gui_Scene.h
 * A collection of buttons and other GuiElements for easy drawing.
 */

enum SceneTransitionType {
   ST_EASE_LEFTRIGHT
};

typedef struct {
  GuiElement **elements;
  GuiElement *selectedElement;
  int numElements;
  void (*draw)(void *self);
  void (*open)(void *self);
  void (*close)(void *self);
} Scene;

Scene *newScene(GuiElement **elements, int numElements, GuiElement *initialSelection);

/**
 * Closes one scene and opens another.
 * @return Returns the pointer to nextScene;
 */
Scene *sceneTransition(Scene *prevScene, Scene *nextScene, enum SceneTransitionType st_type);

/**
 * Selects the next GuiElement
 * @return The newly selected element.
 */
GuiElement *moveUp(Scene *scene);
GuiElement *moveDown(Scene *scene);
GuiElement *moveLeft(Scene *scene);
GuiElement *moveRight(Scene *scene);

#endif
