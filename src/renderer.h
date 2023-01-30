#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "car.h"

class Renderer {
 public:
  //constructor
  Renderer(const std::size_t screen_width, const std::size_t screen_height, const std::size_t grid_width, const std::size_t grid_height);
  //destructor
  ~Renderer();

  //methods:
  //renders the car and enemies
  void Render(Car const car);
  //updates the upper bar in the game window
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif