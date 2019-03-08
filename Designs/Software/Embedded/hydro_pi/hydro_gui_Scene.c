#include "hydro_gui.h"
#include "hydro_gui_Scene.h"
#include "hydro_gui_GuiElement.h"

#include <stdlib.h>
#include <stdio.h>

#include <sys/time.h>
#include <unistd.h> // usleep
#include <pthread.h>

struct SceneTransition {
  Scene *prevScene;
  Scene *nextScene;
  double duration; // seconds
  int direction;
};

//scene transition thread
pthread_t tid_st;

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
  // Do not use 
}

void *st_ease_leftOrRight(void *vargp) {
  struct SceneTransition *st = (struct SceneTransition *)vargp;

  int easeDurationFrames = 60;
  int oldX[st->prevScene->numElements];
  // int oldY[st->prevScene->numElements];
  int oldX2[st->nextScene->numElements];
  // int oldY2[st->nextScene->numElements];

  for(int i = 0; i < st->prevScene->numElements; i++) {
    oldX[i] = st->prevScene->elements[i]->xPos;
    // oldY[i] = st->prevScene->elements[i]->yPos;
  }
  for(int i = 0; i < st->nextScene->numElements; i++) {
    oldX2[i] = st->nextScene->elements[i]->xPos;
    st->nextScene->elements[i]->xPos += -width * st->direction;
    // oldY2[i] = st->nextScene->elements[i]->yPos;
  }

  currentScene = st->nextScene;
  backgroundScene = st->prevScene;

  for(int i = 0; i < easeDurationFrames; i++) {
    for(int n = 0; n < st->prevScene->numElements; n++) {
        st->prevScene->elements[n]->xPos += ((st->direction)*width/easeDurationFrames);
    }
    for(int n = 0; n < st->nextScene->numElements; n++) {
        st->nextScene->elements[n]->xPos += ((st->direction)*width/easeDurationFrames);
    }
    usleep(FRAME_PERIOD * 100000);
  }
  backgroundScene = NULL;

  for(int i = 0; i < st->prevScene->numElements; i++) {
    st->prevScene->elements[i]->xPos = oldX[i];
  }
  for(int i = 0; i < st->nextScene->numElements; i++) {
    st->nextScene->elements[i]->xPos = oldX2[i];
  }

  return NULL;
}

Scene *sceneTransition(Scene *prevScene, Scene *nextScene, enum SceneTransitionType st_type) {
  prevScene->close(prevScene);
  nextScene->open(nextScene);

  // pthread_create(&tid_st, NULL, thread_draw, NULL);
  // I feel like there's a memory leak ready to happen here 
  struct SceneTransition st;
  st.prevScene = prevScene;
  st.nextScene = nextScene;
  st.duration = 0.5;
  st.direction = 0;
  switch(st_type) {
    case ST_EASE_LEFTRIGHT:
      st_ease_leftright(prevScene, nextScene);
      break;
    case ST_EASE_LEFT:
      st.direction = -1;
      pthread_create(&tid_st, NULL, st_ease_leftOrRight, (void *)&st);
      break;
    case ST_EASE_RIGHT:
      st.direction = 1;
      pthread_create(&tid_st, NULL, st_ease_leftOrRight, (void *)&st);
      break;
  }
  // This defeats the purpose of the threads, but it's segfaulting 
  // if I let it run on its own.
  pthread_join(tid_st, NULL);
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
