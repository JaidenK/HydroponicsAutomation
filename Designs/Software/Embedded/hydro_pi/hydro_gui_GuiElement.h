#ifndef _GUI_ELEMENT_H
#define _GUI_ELEMENT_H

/**
 * @file hydro_gui_GuiElement.h
 * The base object of a GUI element, like a button.
 */

typedef struct GuiElement GuiElement;
struct GuiElement{
  int xPos;
  int yPos;
  GuiElement *up;
  GuiElement *down;
  GuiElement *left;
  GuiElement *right;
  int isSelected;
  void *child; // Pointer to the object which inherits from this struct
  void (*draw)(void *self); // These functions make it so that you can 
                            // call the draw function on any GUI object 
                            // and let it do what it wants, rather than 
                            // manually calling the correct draw function
                            // for each.
  void (*click)(void *self);
};

/**
 * Allocates memory for the element and initializes the variables.
 * @param x Horizontal position
 * @param y Vertical position
 * @param child A pointer to the object which is inheriting this base element.
 * @return Pointer to the instantiated object.
 */
GuiElement *newGuiElement(int x, int y, void *child);

/**
 * Assigns which objects will be selected when the user navigates up/down/left/right
 * @param parent The object to which you're assigning neighbors.
 */ 
void setGuiNeighbors(GuiElement *parent, GuiElement *up, GuiElement *down, GuiElement *left,  GuiElement *right);

#endif
