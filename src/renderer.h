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

  //loads all necesary images for the game
  bool LoadMedia();
  
  //renders the car and enemies
  void RenderCars(Car const car, Car const enemy1, Car const enemy2);

  void RenderInstructions();

  void RenderGameOver();

  void RenderBackGround();
  //updates the upper bar in the game window
  void UpdateWindowTitle(int score, int level, int fps);
  SDL_Renderer *sdl_renderer;

 private:
  SDL_Window *sdl_window;
  //SDL_Renderer *sdl_renderer;
  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif