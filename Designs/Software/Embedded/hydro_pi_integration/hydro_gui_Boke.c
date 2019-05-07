#include "hydro_gui_Boke.h"
#include "hydro_gui_GuiElement.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h> // usleep
 
// Graphics
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>

Boke *firstBoke = NULL;

// Overwrites old boke point with a new one based on Boke parameters
void newBokePoint(Boke *boke, BokePoint *bokePoint);

Boke *getLastBoke(Boke *first);
void *bokeThread(void *foo);

void drawBoke(void *boke);
void drawBoke2(void *parent);

int isBokeRunning = 1;
 
int bokeFrame = 0; 

Boke *newBoke(int xMin, int xMax, int yMin, int yMax, double radius, double vX, double vY, double vZ, double vVariance, int R, int G, int B, int count) {
  Boke *newObj = malloc(sizeof(Boke));
  GuiElement *baseObj = newGuiElement(xMin,yMin,newObj);
  newObj->gui_base = baseObj;
  newObj->xMin = xMin;
  newObj->xMax = xMax;
  newObj->yMin = yMin;
  newObj->yMax = yMax;
  newObj->radius = radius;
  newObj->vX = vX;
  newObj->vY = vY;
  newObj->vZ = vZ;
  newObj->vVariance = vVariance;
  newObj->R = R;
  newObj->G = G;
  newObj->B = B;
  newObj->isPaused = 0;
  newObj->next = NULL;
  newObj->count = count;

  newObj->draw = drawBoke;
  baseObj->draw = drawBoke2;

  if(firstBoke == NULL) {
    firstBoke = newObj;
  }else{
    Boke *lastBoke = getLastBoke(firstBoke);
    lastBoke->next = newObj;
  }

  newObj->points = malloc(count*sizeof(BokePoint));
  int i = 0;
  for(;i<count;i++){
    BokePoint *point = malloc(sizeof(BokePoint));
    newBokePoint(newObj,point);
    newObj->points[i] = point;
  }

  pthread_create(&(newObj->boke_tid), NULL, bokeThread, NULL);
  return newObj;
}

void newBokePoint(Boke *boke, BokePoint *bokePoint) {
  bokePoint->x = (((double)rand())/RAND_MAX)*(boke->xMax-boke->xMin)+boke->xMin;
  bokePoint->y = (((double)rand())/RAND_MAX)*(boke->yMax-boke->yMin)+boke->yMin;
  bokePoint->z = 0;
  bokePoint->vX = boke->vX + (((double)rand())/RAND_MAX-0.5)*boke->vVariance;
  bokePoint->vY = boke->vY + (((double)rand())/RAND_MAX-0.5)*boke->vVariance;
  bokePoint->vZ = boke->vZ + (((double)rand())/RAND_MAX-0.5)*boke->vVariance;
  bokePoint->r = boke->radius;
  bokePoint->opacity = 0;
  bokePoint->lifespan = ((double)rand()/RAND_MAX)*5+5;
  bokePoint->age = 0;
  gettimeofday(&bokePoint->birthday,NULL);
}

Boke *getLastBoke(Boke *first) {
  while(first->next != NULL) {
    first = first->next;
  }
  return first;
}

void *bokeThread(void *foo) {
  Boke *currBoke = firstBoke;
  struct timeval now;
  while(isBokeRunning) {
    gettimeofday(&now,NULL);
    currBoke = firstBoke;
    while(currBoke) {
      if(!currBoke->isPaused){
        for(int i = 0; i<currBoke->count; i++) {
          BokePoint *currPoint = currBoke->points[i];
          currPoint->x += currPoint->vX;
          currPoint->y += currPoint->vY;
          currPoint->z += currPoint->vZ;

          currPoint->age = (double)(now.tv_usec - currPoint->birthday.tv_usec) / 1000000 + (double)(now.tv_sec - currPoint->birthday.tv_sec);
          if(currPoint->age < currPoint->lifespan/3) {
            currPoint->opacity = currPoint->age/(currPoint->lifespan/3) * 0.3;
          }else if(currPoint->age>(2*currPoint->lifespan/3)){
            currPoint->opacity = (currPoint->lifespan-currPoint->age)/(currPoint->lifespan/3) * 0.3;
          }
          if(currPoint->age >= currPoint->lifespan) {
            newBokePoint(currBoke,currPoint);
          }

          if(bokeFrame%100==0) {
            // Modulo to reduce cpu load
            currPoint->vX += (((double)rand())/RAND_MAX-0.5)*currBoke->vVariance;
            currPoint->vY += (((double)rand())/RAND_MAX-0.5)*currBoke->vVariance;
            currPoint->vZ += (((double)rand())/RAND_MAX-0.5)*currBoke->vVariance;
          } 
        }
      }
      currBoke = currBoke->next;
    }   
    bokeFrame++;
    usleep(10000);
  }
  return NULL;
}

void stopAllBoke(Boke *boke) {
  isBokeRunning = 0;
}

void pauseBoke(Boke *boke) {
  boke->isPaused = 1;
}
void resumeBoke(Boke *boke) {
  boke->isPaused = 0;
}


void drawBoke2(void *parent) {
  GuiElement *gui_elem = parent;
  drawBoke(gui_elem->child);
}
void drawBoke(void *boke_) {
  Boke *boke = boke_;
  Stroke(0,0,0,0);
  for(int i = 0; i < boke->count; i++){ 
    BokePoint *p = boke->points[i];
    Fill(255,255,255,p->opacity);
    Circle(p->x,p->y,p->r);
  }
}
