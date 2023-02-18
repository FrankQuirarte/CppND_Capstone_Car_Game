#ifndef GAME_H
#define GAME_H

#include <random>
#include <SDL2/SDL.h>
#include "controller.h"
#include "renderer.h"
#include "car.h"

//The dimensions and start position of the car
const int CAR_X_START_POS = 0;
const int CAR_Y_START_POS = 400;
const int CAR_WIDTH = 173;
const int CAR_HEIGHT = 60;

//The dimensions and start position of the blue enemy 1 car
const int ENEMY1_X_START_POS = 1200;
const int ENEMY1_Y_START_POS = 250;
const int ENEMY1_WIDTH = 191;
const int ENEMY1_HEIGHT = 59;

//The dimensions and start position of the purple enemy 2 car
const int ENEMY2_X_START_POS = 1800;
const int ENEMY2_Y_START_POS = 500;
const int ENEMY2_WIDTH = 181; 
const int ENEMY2_HEIGHT = 58;


class Game {
 public:
  Game();
  void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;
  void updateGameLevel(int &enemy1_vel, int &enemy2_vel);
  void over(Renderer &renderer);
  int score = 0;
  int level = 0;

 private:
  Car car;
  Car enemy1;
  Car enemy2;

  void Update();
};

#endif