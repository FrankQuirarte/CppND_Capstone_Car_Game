#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "car.h"

class Controller {
 public:
  void HandleInput(bool &running, Car &car) const;

 private:
  void ChangeDirection(Car &car, Car::Direction input,
                       Car::Direction opposite) const;
};

#endif