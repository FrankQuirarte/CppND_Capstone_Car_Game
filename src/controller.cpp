#include "controller.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <unistd.h> //library for sleep()
#include "car.h"


void Controller::HandleInput(bool &running, Car &car)const{
  //Event handler
  SDL_Event e;
  //while there is an event
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
            case SDLK_UP: car.mVelY -= car.speed; break;
            case SDLK_DOWN: car.mVelY += car.speed; break;
            case SDLK_LEFT: car.mVelX -= car.speed; break;
            case SDLK_RIGHT: car.mVelX += car.speed; break;
        }
    }

    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: car.mVelY += car.speed; break;
            case SDLK_DOWN: car.mVelY -= car.speed; break;
            case SDLK_LEFT: car.mVelX += car.speed; break;
            case SDLK_RIGHT: car.mVelX -= car.speed; break;
        }
    }

  }
}

void Controller::WaitForEnterKey() {
  //Event handler
  SDL_Event e;
  bool continueB = true;
  while(continueB) {
    while (SDL_PollEvent(&e)) {
      //If a key was pressed
      if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ) { 
        if ( e.key.keysym.sym == SDLK_RETURN) { continueB = false; }
      }
      usleep(3000); //sleep for 3 milliseconds
    }
  }
}