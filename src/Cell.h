#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "Link.h"

class Cell : public Observer {
  std::vector<Observer*> observers;
  Point p;
  Link * link;

  // Add other private members if necessary

 public:
  Cell();  // Default constructor
  ~Cell(); // Destructor

  int getX() const; // Returns the value of x.
  int getY() const; // Returns the value of y.
  Link* getLink() const; // Returns the pointer to the link in this cell
  void setCoords(int x, int y);  // Tells me my row and column number.

  void detachLink();
  virtual void attachLink(Link *l);

  void notify(); // needed? not sure
};
#endif
