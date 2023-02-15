/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, vectors, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <unistd.h> //library for sleep()
#include <cstdlib> //library for rand()
#include "texture.h"

//Screen dimension constants
//const int SCREEN_WIDTH = 1043;
//const int SCREEN_HEIGHT = 819;

//Highway limits
const int HIGHWAY_UPPER_LIMIT = 200;
const int HIGHWAY_LOWER_LIMIT = 600;

//The dimensions and start position of the car
static const int CAR_X_START_POS = 0;
static const int CAR_Y_START_POS = 400;
static const int CAR_WIDTH = 173;
static const int CAR_HEIGHT = 60;

//The dimensions and start position of the blue enemy 1 car
static const int ENEMY1_X_START_POS = 1200;
static const int ENEMY1_Y_START_POS = 250;
static const int ENEMY1_WIDTH = 191;
static const int ENEMY1_HEIGHT = 59;

//The dimensions and start position of the purple enemy 2 car
static const int ENEMY2_X_START_POS = 1800;
static const int ENEMY2_Y_START_POS = 500;
static const int ENEMY2_WIDTH = 181; 
static const int ENEMY2_HEIGHT = 58;


//Scene textures
LTexture gCarTexture;
LTexture gEnemy1Texture;
LTexture gEnemy2Texture;
LTexture gBGTexture;
LTexture gGOTexture;

//Main loop flag
bool running = true;

//Game score
int GameScore = 0;

//Game score
int GameLevel = 0;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Box set collision detector
//bool checkCollision( SDL_Rect carColliderBox, SDL_Rect enemyColliderBox );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Car game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load car texture
	if( !gCarTexture.loadFromFile("../resources/red_car.bmp", gRenderer ) )
	{
		printf( "Failed to load car texture!\n" );
		success = false;
	}

	//Load enemy1 texture
	if( !gEnemy1Texture.loadFromFile( "../resources/blue_car.bmp", gRenderer ) )
	{
		printf( "Failed to load enemy1 image!\n" );
		success = false;
	}

	//Load enemy2 texture
	if( !gEnemy2Texture.loadFromFile( "../resources/purple_car.bmp", gRenderer ) )
	{
		printf( "Failed to load enemy2 image!\n" );
		success = false;
	}

	//Load background texture
	if( !gBGTexture.loadFromFile( "../resources/background.bmp", gRenderer ) )
	{
		printf( "Failed to load background image!\n" );
		success = false;
	}

	//Load game over texture
	if( !gGOTexture.loadFromFile( "../resources/game_over.bmp", gRenderer ) )
	{
		printf( "Failed to load game_over image!\n" );
		success = false;
	}
	return success;
}

void close()
{
	//Free loaded images
	gCarTexture.free();
	gEnemy1Texture.free();
	gEnemy2Texture.free();
	gBGTexture.free();
	gGOTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


void updateGameLevel(int &enemy1_vel, int &enemy2_vel)
{
	if (GameScore < 5 )                   { enemy1_vel = 2;   enemy2_vel = 2;   GameLevel = 1;}
	if (GameScore >= 5 && GameScore < 10) { enemy1_vel = 3;   enemy2_vel = 3;   GameLevel = 2;}
	if (GameScore >= 10 && GameScore < 15){ enemy1_vel = 4;   enemy2_vel = 4;   GameLevel = 3;}
	if (GameScore >= 15 && GameScore < 20){ enemy1_vel = 5;   enemy2_vel = 5;   GameLevel = 4;}
	if (GameScore >= 20 && GameScore < 25){ enemy1_vel = 6;   enemy2_vel = 6;   GameLevel = 5;}
	if (GameScore >= 25 && GameScore < 30){ enemy1_vel = 7;   enemy2_vel = 7;   GameLevel = 6;}
	if (GameScore >= 30 && GameScore < 35){ enemy1_vel = 8;   enemy2_vel = 8;   GameLevel = 7;}
	if (GameScore >= 35 && GameScore < 40){ enemy1_vel = 9;   enemy2_vel = 9;   GameLevel = 8;}
	if (GameScore >= 40 && GameScore < 45){ enemy1_vel = 10;  enemy2_vel = 10;  GameLevel = 9;}
	if (GameScore >= 45 && GameScore < 50){ enemy1_vel = 11;  enemy2_vel = 11;  GameLevel = 10;}
	

}


void drawGameOver()
{
	Car gameOver(150,250,771,320); //create gameOver car object
	gGOTexture.render(gameOver.mPosX, gameOver.mPosY, gRenderer);  //gameOver.render(gGOTexture); //render image
	SDL_RenderPresent( gRenderer ); //Update screen
	sleep(2); //sleep for two seconds
}


void UpdateScoreWindowTitle(int fps, int level) 
{
	std::string title{"Car Game     Score: " + std::to_string(GameScore) + "     Level: " + std::to_string(level) + "     FPS: " + std::to_string(fps)};
	SDL_SetWindowTitle(gWindow, title.c_str());
}

int main( int argc, char* args[] )
{
	int title_timestamp = SDL_GetTicks();
	int frame_start, frame_end, frame_duration, frame_count = 0;
	bool collision;

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Event handler
			SDL_Event e;

			//Creates the players car to and place it in the middle of the highway
			Car car(CAR_X_START_POS, CAR_Y_START_POS, CAR_WIDTH, CAR_HEIGHT);
			//Creates enemies that the car needs to dodge
			Car enemy1(ENEMY1_X_START_POS, ENEMY1_Y_START_POS, ENEMY1_WIDTH, ENEMY1_HEIGHT);
			Car enemy2(ENEMY2_X_START_POS, ENEMY2_Y_START_POS, ENEMY2_WIDTH, ENEMY2_HEIGHT);

			//The background scrolling offset
			int scrollingOffset = 0;

			//While application is running
			while(running)
			{
				
				frame_start = SDL_GetTicks();
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests to quit
					if( e.type == SDL_QUIT )
					{
						running = false;
					}

					//Handle input for the car
					car.handleEvent( e );
				}

				//Move the car
				collision = car.move(enemy1.mCollider , enemy2.mCollider);
				
				//if the car has crashed the game ends
				if (collision == true) { running = false; }

				//moves the enemies
				enemy1.enemyHorizontalMove();
				enemy2.enemyHorizontalMove();

				//Scroll background
				--scrollingOffset;
				if( scrollingOffset < -gBGTexture.getHeight() )
				{
					scrollingOffset = 0;
				}
				
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				//Render moving background
				gBGTexture.render(scrollingOffset, 0, gRenderer);
				gBGTexture.render(scrollingOffset + gBGTexture.getHeight(), 0, gRenderer);
				
				//Render car objects
				gCarTexture.render(car.mPosX, car.mPosY, gRenderer); //car.render(gCarTexture);
				gEnemy1Texture.render(enemy1.mPosX, enemy1.mPosY, gRenderer); //enemy1.render(gEnemy1Texture);
				gEnemy2Texture.render(enemy2.mPosX, enemy2.mPosY, gRenderer); //enemy2.render(gEnemy2Texture);
				
				//Render enemies collieder boxes
				//SDL_SetRenderDrawColor( gRenderer, 0xC0, 0xC0, 0xC0, 0xFF ); //gray
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF); // red
				SDL_RenderDrawRect(gRenderer, &enemy1.mCollider);
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF); // red
				SDL_RenderDrawRect(gRenderer, &enemy2.mCollider);
				
				//Update screen
				SDL_RenderPresent(gRenderer);
				
				frame_end = SDL_GetTicks();

				// Keep track of how long each loop through the input/update/render cycle takes.
				frame_count++;
				frame_duration = frame_end - frame_start;

				// After every second, update the window title.
				if (frame_end - title_timestamp >= 1000) {
					UpdateScoreWindowTitle(frame_count, GameLevel);
					frame_count = 0;
					title_timestamp = frame_end;
				}
				
				updateGameLevel(enemy1.enemy_vel, enemy2.enemy_vel);
			}
			//if the game has ended, render game over image
			drawGameOver();
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}