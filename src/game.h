#ifndef GAME_H
#define GAME_H

#include <random>
#include <SDL2/SDL.h>
#include "controller.h"
#include "renderer.h"
#include "car.h"
#define CAR_X_START_POSITION 220
#define CAR_Y_START_POSITION 450

class Game {
 public:
  Game();
  void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;

 private:
  Car car;
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;


  int score{0};
  void Update();
};

#endif