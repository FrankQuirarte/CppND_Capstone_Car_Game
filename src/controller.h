#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "car.h"

class Controller {
 public:
  void HandleInput(bool &running, Car &car) const;
  void WaitForEnterKey();

 private:
};

#endif