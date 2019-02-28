#include "hydro_gui_GuiElement.h"

#include <stdlib.h>

GuiElement *newGuiElement(int x, int y, void *child) {
  GuiElement *newObj = malloc(sizeof(GuiElement));
  newObj->xPos = x;
  newObj->yPos = y;
  newObj->child = child;
  newObj->isSelected = 0;
  return newObj;
}

void setGuiNeighbors(GuiElement *parent, GuiElement *up, GuiElement *down, GuiElement *left,  GuiElement *right) {
  parent->up = up;
  parent->down = down;
  parent->left = left;
  parent->right = right;
}
