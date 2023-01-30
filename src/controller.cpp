#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "car.h"

void Controller::ChangeDirection(Car &car, Car::Direction input, Car::Direction opposite) const {
  if (car.direction != opposite) car.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Car &car) const {
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0 ) {
    
    //if users press "e" key quits the game
    if (e.type == SDL_QUIT) {
      running = false;
    } 
    
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: /*mVelY -= DOT_VEL;*/ break;
            case SDLK_DOWN: /*mVelY += DOT_VEL;*/ break;
            case SDLK_LEFT: car.VelX -= car.CalbSpeed; break;
            case SDLK_RIGHT: car.VelX += car.CalbSpeed; break;
        }
    }

    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: /*mVelY += DOT_VEL;*/ break;
            case SDLK_DOWN: /*mVelY -= DOT_VEL;*/ break;
            case SDLK_LEFT: car.VelX += car.CalbSpeed; break;
            case SDLK_RIGHT: car.VelX -= car.CalbSpeed; break;
        }
    }

  }
}