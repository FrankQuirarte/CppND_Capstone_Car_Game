#include "car.h"
#include "texture.h"
#include <cmath>
#include <iostream>
#include <cstdlib> //library for rand()


//Highway limits
#define HIGHWAY_UPPER_LIMIT 200
#define HIGHWAY_LOWER_LIMIT 600

extern int GameScore;


Car::Car(int PosX, int PosY, int carWidth, int carHeight)
{
	//Initialize the offsets
	mPosX = PosX;
	mPosY = PosY;

  //car dimensions
  width = carWidth;
  height = carHeight;

	//Set collision box dimension
	mCollider.x = PosX;
	mCollider.y = PosY;
	mCollider.w = carWidth;
	mCollider.h = carHeight;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Car::handleEvent( SDL_Event& e )
{
	//If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{
		//Adjust the velocity
		switch( e.key.keysym.sym )
		{
		case SDLK_UP: mVelY -= speed; break;
		case SDLK_DOWN: mVelY += speed; break;
		case SDLK_LEFT: mVelX -= speed; break;
		case SDLK_RIGHT: mVelX += speed; break;
		}
	}
	//If a key was released
	else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
	{
		//Adjust the velocity
		switch( e.key.keysym.sym )
		{
		case SDLK_UP: mVelY += speed; break;
		case SDLK_DOWN: mVelY -= speed; break;
		case SDLK_LEFT: mVelX += speed; break;
		case SDLK_RIGHT: mVelX -= speed; break;
		}
	}
}


bool Car::checkCollision( SDL_Rect carColliderBox, SDL_Rect enemyColliderBox )
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = carColliderBox.x;
	rightA = carColliderBox.x + carColliderBox.w;
	topA = carColliderBox.y;
	bottomA = carColliderBox.y + carColliderBox.h;

	//Calculate the sides of rect B
	leftB = enemyColliderBox.x;
	rightB = enemyColliderBox.x + enemyColliderBox.w;
	topB = enemyColliderBox.y;
	bottomB = enemyColliderBox.y + enemyColliderBox.h;

	//If any of the sides from A are outside of B
	if( bottomA <= topB )
	{
		return false;
	}

	if( topA >= bottomB )
	{
		return false;
	}

	if( rightA <= leftB )
	{
		return false;
	}

	if( leftA >= rightB )
	{
		return false;
	}

	//If we cannot find any separation, then there is a collision
	return true;
}



bool Car::move(SDL_Rect& collisionRect1, SDL_Rect& collisionRect2)
{
    bool collision = false;
    
    //Move the car left or right
    mPosX += mVelX;
    mCollider.x = mPosX;
    

    //If the car went too far to the left or right
    if( (mPosX < 0) || (mPosX + height > SCREEN_WIDTH)  )
    {
        //Move back the object, so it doest surpass the screen width limits
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }

    //Move the car up or down
    mPosY += mVelY;
    mCollider.y = mPosY;

    //If the car went too far up or down (reached the highway limts)
    if( ( mPosY < HIGHWAY_UPPER_LIMIT) || ( mPosY + height > HIGHWAY_LOWER_LIMIT) )
    {
        //Move the object back, so it doest surpass the highway limts
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }
    
    //check if the car has chrased against the enemies
    if(checkCollision(mCollider, collisionRect1) || checkCollision(mCollider, collisionRect2)){
      collision = true;
    }
    return collision;
}

void Car::enemyHorizontalMove()
{

	// variables for the upper and lower boundaries for the random number generator
	int lbx = SCREEN_WIDTH + width; 
	int ubx = 3000; //magic number

	int lby = HIGHWAY_UPPER_LIMIT; 
	int uby = HIGHWAY_LOWER_LIMIT;

	//Move the car fromthe right to left until it desapears from screen
	mPosX -= enemy_vel;
	mCollider.x = mPosX;

	// here we could check if the enemy doesnt crash agains the player instead of the other way around

	//if the car is out of the screen, generate a new random position in the left outside part
	if(mPosX < -width) 
	{
		//mPosX = ENEMY1_X_START_POS;
		mPosX = rand() % (ubx - lbx + 1) + lbx;
		mCollider.x = mPosX;
		mPosY = rand() % (uby - lby + 1) + lby;
		mCollider.y = mPosY;
		//if the enemy is out of the screen and there was not collision, increment the score
		GameScore++;
		enemy_vel++;
	}
}

/*
void Car::render(LTexture &gTexture)
{
	//Show the car
	gTexture.render( mPosX, mPosY, gRenderer);
}
*/


