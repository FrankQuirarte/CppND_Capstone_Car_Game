#include "renderer.h"
#include "texture.h"
#include <iostream>
#include <string>
#include <unistd.h> //library for sleep()




//Scene textures
LTexture gCarTexture;
LTexture gEnemy1Texture;
LTexture gEnemy2Texture;
LTexture gBackGroundTexture;
LTexture gGOTexture;

int scrollingOffset = 0;

//constructor
Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height) : screen_width(screen_width), screen_height(screen_height)
{
  
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
  loadMedia();

}

//destructor
Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

bool Renderer::loadMedia() {
  //Loading success flag
  bool success = true;

  //Load car texture
  if( !gCarTexture.loadFromFile("../resources/red_car.bmp", sdl_renderer ) )
  {
    printf( "Failed to load car texture!\n" );
    success = false;
  }

  //Load enemy1 texture
  if( !gEnemy1Texture.loadFromFile( "../resources/blue_car.bmp", sdl_renderer ) )
  {
    printf( "Failed to load enemy1 image!\n" );
    success = false;
  }

  //Load enemy2 texture
  if( !gEnemy2Texture.loadFromFile( "../resources/purple_car.bmp", sdl_renderer ) )
  {
    printf( "Failed to load enemy2 image!\n" );
    success = false;
  }


  //Load background texture
  if( !gBackGroundTexture.loadFromFile( "../resources/background.bmp", sdl_renderer ) )
  {
    printf( "Failed to load background image!\n" );
    success = false;
  }


  //Load game over texture
  if( !gGOTexture.loadFromFile( "../resources/game_over.bmp", sdl_renderer ) )
  {
    printf( "Failed to load game_over image!\n" );
    success = false;
  }
  return success;
}


void Renderer::RenderGameOver() {

  int goX = 150, goY = 250, goWidth = 771, goHeight = 320;
  gGOTexture.render(goX, goY, sdl_renderer); //render image
  SDL_RenderPresent( sdl_renderer ); //update screen
  sleep(3); //sleep for two seconds
}


void Renderer::RenderBackGround() {
  
  //Scroll background
  --scrollingOffset;
  if( scrollingOffset < -gBackGroundTexture.getHeight() )
  {
    scrollingOffset = 0;
  }

  //Render moving background
  gBackGroundTexture.render(scrollingOffset, 0, sdl_renderer);
  gBackGroundTexture.render(scrollingOffset + gBackGroundTexture.getHeight(), 0, sdl_renderer);

}

void Renderer::RenderCars(Car const car, Car const enemy1, Car const enemy2) {
  //Show the car
  gCarTexture.render(car.mPosX, car.mPosY, sdl_renderer);
  //Show the enemy1
  gEnemy1Texture.render(enemy1.mPosX, enemy1.mPosY, sdl_renderer);
  //Show the enemy2
  gEnemy2Texture.render(enemy2.mPosX, enemy2.mPosY, sdl_renderer);
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int level, int fps) {
  std::string title{"Car Game     Score: " + std::to_string(score) + "     Level: " + std::to_string(level) + "     FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
