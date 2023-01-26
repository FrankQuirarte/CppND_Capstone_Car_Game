#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "car.h"

void Controller::ChangeDirection(Car &car, Car::Direction input,
                                 Car::Direction opposite) const {
  if (car.direction != opposite || car.size == 1) car.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Car &car) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } 
    else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(car, Car::Direction::kUp,
                          Car::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(car, Car::Direction::kDown,
                          Car::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(car, Car::Direction::kLeft,
                          Car::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(car, Car::Direction::kRight,
                          Car::Direction::kLeft);
          break;
      }
    }
  }
}