#include "hydro_gui_GuiElement.h"

#include <stdlib.h>
#include <stdio.h>

void GuiElement_click(void *self);
GuiElement *GuiElement_moveUp(void *self_);
GuiElement *GuiElement_moveDown(void *self_);
GuiElement *GuiElement_moveLeft(void *self_);
GuiElement *GuiElement_moveRight(void *self_);

GuiElement *newGuiElement(int x, int y, void *child) {
  GuiElement *newObj = malloc(sizeof(GuiElement));
  newObj->xPos = x;
  newObj->yPos = y;
  newObj->child = child;
  newObj->isSelected = 0;
  newObj->click = GuiElement_click;
  newObj->moveUp = GuiElement_moveUp;
  newObj->moveDown = GuiElement_moveDown;
  newObj->moveLeft = GuiElement_moveLeft;
  newObj->moveRight = GuiElement_moveRight;
  return newObj;
}

void setGuiNeighbors(GuiElement *parent, GuiElement *up, GuiElement *down, GuiElement *left,  GuiElement *right) {
  parent->up = up;
  parent->down = down;
  parent->left = left;
  parent->right = right;
}

void GuiElement_click(void *self_) {
  printf("This GUI Element has no click function.\n");
}

GuiElement *GuiElement_moveUp(void *self_) {
  GuiElement *self = self_;
  return (self->up != NULL)?self->up:self;
}
GuiElement *GuiElement_moveDown(void *self_) {
  GuiElement *self = self_;
  return (self->down != NULL)?self->down:self;
}
GuiElement *GuiElement_moveLeft(void *self_) {
  GuiElement *self = self_;
  return (self->left != NULL)?self->left:self;
}
GuiElement *GuiElement_moveRight(void *self_) {
  GuiElement *self = self_;
  return (self->right != NULL)?self->right:self;
}
