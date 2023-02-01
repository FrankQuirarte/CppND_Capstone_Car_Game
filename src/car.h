#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <SDL2/SDL.h>

class Car {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  // car constructor, puts the car in the middle botton of the screen
  Car(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        PosX(grid_width / 2),
        PosY(grid_height) {}

  void UpdateCarPosition();

  //not default direction during game start
  Direction direction;

  float CalbSpeed{0.1f};
  bool alive{true};
  float PosX;
  float PosY;
  float VelX;
  float VelY;
  
 private:
  int grid_width;
  int grid_height;
};

#endif