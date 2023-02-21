#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "texture.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  
  constexpr std::size_t kScreenWidth{1043};
  constexpr std::size_t kScreenHeight{819};
  

  Renderer renderer(kScreenWidth, kScreenHeight);
  Controller controller;
  Game game;
  game.Instructions(controller, renderer);
  game.Run(controller, renderer, kMsPerFrame);
  game.Over(controller, renderer);
  
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  return 0;
}