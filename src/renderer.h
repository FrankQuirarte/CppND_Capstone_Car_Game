#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "car.h"


class Renderer {
 public:
  //constructor
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  //destructor
  ~Renderer();

  //methods:
  //renders the car and enemies
  void Render(Car const car);
  void RenderBackGround();
  //updates the upper bar in the game window
  void UpdateWindowTitle(int score, int fps);
  SDL_Renderer *sdl_renderer;

 private:
  SDL_Window *sdl_window;
  //SDL_Renderer *sdl_renderer;
  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif