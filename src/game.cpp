#include "game.h"
#include <iostream>
#include <SDL2/SDL.h>

//constructor
Game::Game(std::size_t grid_width, std::size_t grid_height)
    : car(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) 
{
  //PlaceEnemy();
}


void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, car);
    Update();
    renderer.Render(car);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If game is moving to fast (the time for the frame is too small)
    // i.e. frame_duration is smaller than the target ms_per_frame, 
    // delay the loop to achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}


void Game::Update() {
  //if the car has crashed do not update the screen
  if (!car.alive) return;
  car.UpdateCarPosition();
}

int Game::GetScore() const { 
  return score; 
}

//int Game::GetSize() const { return car.size; }