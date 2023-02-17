#include "game.h"
#include <iostream>
#include <SDL2/SDL.h>



//Game score
int GameScore = 0;


//constructor
Game::Game( )
  :car(CAR_X_START_POS, CAR_Y_START_POS, CAR_WIDTH, CAR_HEIGHT),
  enemy1(ENEMY1_X_START_POS, ENEMY1_Y_START_POS, ENEMY1_WIDTH, ENEMY1_HEIGHT),
  enemy2(ENEMY2_X_START_POS, ENEMY2_Y_START_POS, ENEMY2_WIDTH, ENEMY2_HEIGHT)

{
  //place enemy (enemy1)
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
  //if (!car.alive) return;
  car.move();
}

void Game::updateScore() { 
  score = GameScore;
}

int Game::GetScore() const { 
  return score; 
}

void Game::updateGameLevel(int &enemy1_vel, int &enemy2_vel) {
	if (score < 5 )                { enemy1_vel = 2;   enemy2_vel = 2;   level = 1;}
	if (score >= 5 && score < 10)  { enemy1_vel = 3;   enemy2_vel = 3;   level = 2;}
	if (score >= 10 && score < 15) { enemy1_vel = 4;   enemy2_vel = 4;   level = 3;}
	if (score >= 15 && score < 20) { enemy1_vel = 5;   enemy2_vel = 5;   level = 4;}
	if (score >= 20 && score < 25) { enemy1_vel = 6;   enemy2_vel = 6;   level = 5;}
	if (score >= 25 && score < 30) { enemy1_vel = 7;   enemy2_vel = 7;   level = 6;}
	if (score >= 30 && score < 35) { enemy1_vel = 8;   enemy2_vel = 8;   level = 7;}
	if (score >= 35 && score < 40) { enemy1_vel = 9;   enemy2_vel = 9;   level = 8;}
	if (score >= 40 && score < 45) { enemy1_vel = 10;  enemy2_vel = 10;  level = 9;}
	if (score >= 45 && score < 50) { enemy1_vel = 11;  enemy2_vel = 11;  level = 10;}
  if (score >= 50)               { enemy1_vel = 12;  enemy2_vel = 12;  level = 10;}
	

}






//int Game::GetSize() const { return car.size; }