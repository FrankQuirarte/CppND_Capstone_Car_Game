#include "renderer.h"
#include "texture.h"
#include <iostream>
#include <string>

LTexture gCarTexture;
LTexture gBackGroundTexture;

//constructor
Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height, const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Windows
  sdl_window = SDL_CreateWindow("Car Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  //Initialize PNG loading image 
  int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) )
  {
    std::cout << "SDL_image could not initialize! SDL_image Error: %s" << IMG_GetError() << "\n";
  }

}

//destructor
Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::RenderBackGround() {
  // Render highway background
  if( !gBackGroundTexture.loadFromFile("../resources/background.bmp", sdl_renderer ) )
  {
    std::cout << "Failed to load background image!" << "\n";
  }
  //Show the background
  gBackGroundTexture.render( 0, 0, sdl_renderer);
}


void Renderer::Render(Car const car) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen and set black color to the background
  //                                     R    G      B   Alpha: opacity
  //SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x0, 0x00, 0xFF);
  //SDL_RenderClear(sdl_renderer); // draw the color

  Renderer::RenderBackGround();


  // Render a rectangle as car's body
  /*
  block.x = static_cast<int>(car.PosX) * block.w;
  block.y = static_cast<int>(car.PosY) * block.h;
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF); // set red color
  SDL_RenderFillRect(sdl_renderer, &block); //draws a rectangle
  */

  // Render car's picture
  if( !gCarTexture.loadFromFile("../resources/carPicture.bmp", sdl_renderer ) )
  {
    std::cout << "Failed to load car image!" << "\n";
  }
  //Show the car
	gCarTexture.render( car.PosX, car.PosY, sdl_renderer);


  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Car Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
