#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <SDL2/SDL.h>

class Car {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  // car constructor, 
  Car(int startPosX, int startPosY) : PosX(startPosX), PosY(startPosY) {}

  void UpdateCarPosition();

  //not default direction during game start
  Direction direction;

  float CalbSpeed = 10.5;
  bool alive{true};
  float PosX;
  float PosY;
  float VelX;
  float VelY;
  
 private:
  //int grid_width;
  //int grid_height;
};

#endif