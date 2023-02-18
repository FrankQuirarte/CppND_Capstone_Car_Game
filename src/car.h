#ifndef CAR_H
#define CAR_H

#include <vector>
#include <SDL2/SDL.h>

// game window limits
#define SCREEN_WIDTH 1043
#define SCREEN_HEIGHT 819

//Highway limits
#define HIGHWAY_UPPER_LIMIT 200
#define HIGHWAY_LOWER_LIMIT 600


class Car {
  public:

    // car constructor, 
    Car(int PosX, int PosY, int carWidth, int carHeight) : 
    mPosX(PosX), 
    mPosY(PosY), 
    width(carWidth), 
    height(carHeight),
    mVelX(0),
    mVelY(0)
    { 
      mCollider.x = mPosX;
      mCollider.y = mPosY;
      mCollider.w = width;
      mCollider.h = height;
    }

    //check if there is a collision between car objects
    bool checkCollision( SDL_Rect carColliderBox, SDL_Rect enemyColliderBox);

    //Moves the car and checks collisions agains the enemies
    void move(SDL_Rect& collisionRect1, SDL_Rect& collisionRect2);
    //bool move(SDL_Rect& collisionRect1, SDL_Rect& collisionRect2);
    
    //Generates a random start position for the enemies and moves them from right to left
    void enemyHorizontalMove(int &gameScore);

    //Car's collision box
    SDL_Rect mCollider;

    //Maximum axis velocity of the car and enemy
    int speed = 5;
    int enemy_vel = 2;
    
    //dimmensions of the car picture
    int width;
    int height;
    
    //The velocity of the car
    int mVelX, mVelY;
      
    //The X and Y offsets of the car
    int mPosX, mPosY;

    //Collision status
    bool collision = false;

  private:

};

#endif