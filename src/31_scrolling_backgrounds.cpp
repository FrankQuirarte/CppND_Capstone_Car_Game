/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, vectors, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <unistd.h> //library for sleep()
#include <cstdlib> //library for rand()

//Screen dimension constants
const int SCREEN_WIDTH = 1043;
const int SCREEN_HEIGHT = 819;

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


//Main loop flag
bool quit = false;

//Game score
int GameScore = 0;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};


class Car
{
  public:

		//Maximum axis velocity of the car
		int CAR_VEL = 5;
    int ENEMY_VEL = 2;

		//Initializes the variables
		Car(int PosX, int PosY, int carWidth, int carHeight);

		//Takes key presses and adjusts the car's velocity
		void handleEvent( SDL_Event& e );

		//Moves the car and checks collisions agains the enemies
		void move(SDL_Rect& collisionRect1, SDL_Rect& collisionRect2);

    void enemyHorizontalMove();

		//Shows the car on the screen
		void render(LTexture &gTexture);
		
    //Car's collision box
		SDL_Rect mCollider;

  private:
		//The X and Y offsets of the car
		int mPosX, mPosY;

		//The velocity of the car
		int mVelX, mVelY;

};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Box set collision detector
bool checkCollision( SDL_Rect carColliderBox, SDL_Rect enemyColliderBox );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gCarTexture;
LTexture gEnemy1Texture;
LTexture gEnemy2Texture;
LTexture gBGTexture;
LTexture gGOTexture;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

Car::Car(int PosX, int PosY, int carWidth, int carHeight)
{
  //Initialize the offsets
  mPosX = PosX;
  mPosY = PosY;

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
            case SDLK_UP: mVelY -= CAR_VEL; break;
            case SDLK_DOWN: mVelY += CAR_VEL; break;
            case SDLK_LEFT: mVelX -= CAR_VEL; break;
            case SDLK_RIGHT: mVelX += CAR_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += CAR_VEL; break;
            case SDLK_DOWN: mVelY -= CAR_VEL; break;
            case SDLK_LEFT: mVelX += CAR_VEL; break;
            case SDLK_RIGHT: mVelX -= CAR_VEL; break;
        }
    }
}

void Car::move(SDL_Rect& collisionRect1, SDL_Rect& collisionRect2)
{
    //Move the car left or right
    mPosX += mVelX;
    mCollider.x = mPosX;
    

    //If the car went too far to the left or right
    if( (mPosX < 0) || (mPosX + CAR_WIDTH > SCREEN_WIDTH)  )
    {
        //Move back the object, so it doest surpass the screen width limits
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }

    //Move the car up or down
    mPosY += mVelY;
    mCollider.y = mPosY;

    //If the car went too far up or down (reached the highway limts)
    if( ( mPosY < HIGHWAY_UPPER_LIMIT) || ( mPosY + CAR_HEIGHT > HIGHWAY_LOWER_LIMIT) )
    {
        //Move the object back, so it doest surpass the highway limts
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }

    if(checkCollision(mCollider, collisionRect1) || checkCollision(mCollider, collisionRect2)){
      quit = true;
    }
}

void Car::enemyHorizontalMove()
{
    
    // variables for the upper and lower boundaries for the random number generator
    int lbx = SCREEN_WIDTH + ENEMY1_WIDTH; 
    int ubx = 3000; //magic number
    
    int lby = HIGHWAY_UPPER_LIMIT; 
    int uby = HIGHWAY_LOWER_LIMIT;
    
    //Move the car from  the right to left until it desapears from screen
    mPosX -= ENEMY_VEL;
    mCollider.x = mPosX;
    
    // here we could check if the enemy doesnt crash agains the player instead of the other way around

    //if the car is out of the screen, generate a new random position in the left outside part
    if(mPosX < -ENEMY1_WIDTH) 
    {
      //mPosX = ENEMY1_X_START_POS;
      mPosX = rand() % (ubx - lbx + 1) + lbx;
      mCollider.x = mPosX;
      mPosY = rand() % (uby - lby + 1) + lby;
      mCollider.y = mPosY;
      //if the enemy is out of the screen and there was not collision, increment the score
      GameScore++;
      ENEMY_VEL++;
    }
}


void Car::render(LTexture &gTexture)
{
    //Show the car
	gTexture.render( mPosX, mPosY );
}

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
	if( !gCarTexture.loadFromFile( "red_car.bmp" ) )
	{
		printf( "Failed to load car texture!\n" );
		success = false;
	}

	//Load enemy1 texture
	if( !gEnemy1Texture.loadFromFile( "blue_car.bmp" ) )
	{
		printf( "Failed to load enemy1 image!\n" );
		success = false;
	}

	//Load enemy2 texture
	if( !gEnemy2Texture.loadFromFile( "purple_car.bmp" ) )
	{
		printf( "Failed to load enemy2 image!\n" );
		success = false;
	}

	//Load background texture
	if( !gBGTexture.loadFromFile( "background.bmp" ) )
	{
		printf( "Failed to load background image!\n" );
		success = false;
	}

  //Load game over texture
	if( !gGOTexture.loadFromFile( "game_over.bmp" ) )
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


bool checkCollision( SDL_Rect carColliderBox, SDL_Rect enemyColliderBox )
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


void drawGameOver()
{
  Car gameOver(150,250,771,320); //crate gameover object
  gameOver.render(gGOTexture); //render image
  SDL_RenderPresent( gRenderer ); //Update screen
  sleep(2); //sleep for two seconds
}


void UpdateScoreWindowTitle(int fps, int level) 
{
  std::string title{"Car Game  Score:" + std::to_string(GameScore) + "   Level:" + std::to_string(level) + "   FPS:" + std::to_string(fps)};
  SDL_SetWindowTitle(gWindow, title.c_str());
}

int main( int argc, char* args[] )
{
  int title_timestamp = SDL_GetTicks();
  int frame_start, frame_end, frame_duration, frame_count = 0;
  
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
			while( !quit )
			{
				
        frame_start = SDL_GetTicks();

        //Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the car
					car.handleEvent( e );
				}

        //Move the car
				car.move(enemy1.mCollider , enemy2.mCollider);

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
				gBGTexture.render(scrollingOffset, 0);
				gBGTexture.render(scrollingOffset + gBGTexture.getHeight(), 0);

				//Render car objects
				car.render(gCarTexture);
				enemy1.render(gEnemy1Texture);
				enemy2.render(gEnemy2Texture);

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
          UpdateScoreWindowTitle(frame_count, enemy1.ENEMY_VEL);
          frame_count = 0;
          title_timestamp = frame_end;
        }
        //updateGameLevel();
			}
      //if the game has ended, render game over image
      drawGameOver();
		}
	}
	//Free resources and close SDL
  close();
	return 0;
}