#ifndef CAR_H
#define CAR_H

#include <vector>
#include <SDL2/SDL.h>
#include "texture.h"
#include "game.h"

#define SCREEN_WIDTH 1043
#define SCREEN_HEIGHT 819

class Car {
  
  public:
    // car constructor, 
    Car(int PosX, int PosY, int carWidth, int carHeight);

    //Takes key presses and adjusts the car's velocity
    void handleEvent( SDL_Event& e );

    //check if there is a collision between car objects
    bool checkCollision( SDL_Rect carColliderBox, SDL_Rect enemyColliderBox);
    
    //Moves the car and checks collisions agains the enemies
    bool move(SDL_Rect& collisionRect1, SDL_Rect& collisionRect2);

    //Generates a random start position for the enemies and moves them from right to left
    void enemyHorizontalMove();

    //Shows the car on the screend
    //void render(LTexture &gTexture);
    
    //Car's collision box
    SDL_Rect mCollider;

    //Maximum axis velocity of the car and enemy
    int speed = 5;
    int enemy_vel = 2;
    int width;
    int height;

    //The velocity of the car
    int mVelX, mVelY;
    
    //The X and Y offsets of the car
    int mPosX, mPosY;
  
 private:


};

#endif