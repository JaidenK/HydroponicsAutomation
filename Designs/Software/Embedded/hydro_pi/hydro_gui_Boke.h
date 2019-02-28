#ifndef _HYDRO_GUI_BOKE_H
#define _HYDRO_GUI_BOKE_H

/**
 * @file hydro_gui_Boke.h
 * Creates a threaded boke.
 */

#include "hydro_gui_GuiElement.h"
 
#include <pthread.h>
#include <sys/time.h>

typedef struct {
   double x;
   double y;
   double z;
   double vX;
   double vY;
   double vZ;
   double r;
   double opacity;
   double lifespan;
   struct timeval birthday;
   double age;
} BokePoint;

typedef struct Boke Boke;
struct Boke {
  GuiElement *gui_base;
  BokePoint **points;
  int count;
  int xMin;
  int xMax;
  int yMin;
  int yMax;
  double radius;
  double vX;
  double vY;
  double vZ;
  int R;
  int G;
  int B;
  double vVariance;
  int isPaused;
  void (*draw)(void *self); 
  pthread_t boke_tid;
  Boke *next;
};

/**
 * Creates boke that wander across the screen and a thread to wiggle them.
 * @param xMin Minimum x value to generate new boke
 * @param xMax Maximum x value to generate new boke
 * @param yMin Minimum y value to generate new boke
 * @param yMax Maximum y value to generate new boke
 * @param vX Horizontal velocity offset
 * @param vY Vertical velocity offset
 * @param vVariance Random velocity change scaling factor
 * @param count The number of boke to draw.
 * @param R Red value
 * @param G Green value
 * @param B Blue value
 */
Boke *newBoke(int xMin, int xMax, int yMin, int yMax, double radius, double vX, double vY, double vZ, double vVariance, int R, int G, int B, int count);

/**
 * Terminates the thread that's calculating the Boke positions.
 */
void stopAllBoke(Boke *boke);

/**
 * Skips calculations of the specific Boke.
 */
void pauseBoke(Boke *boke);
void resumeBoke(Boke *boke);



#endif
