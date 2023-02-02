#include "car.h"
#include <cmath>
#include <iostream>


void Car::UpdateCarPosition() {
  SDL_Point prev_cell{ static_cast<int>(PosX), static_cast<int>(PosY)};  // We first capture the car's cell before updating.
  
    //Move the car left or right
    PosX += VelX;

    //If the car went too far to the left or right stop the movement
    if( ( PosX < 0 ) || ( PosX > 400 ) )
    {
        //Move back
        PosX -= VelX;
    }
  
  SDL_Point current_cell{ static_cast<int>(PosX), static_cast<int>(PosY)};  // Capture the car's cell after updating.

}
