# CPPND: Capstone Car Game 

This is my Capstone project for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). 
The project option chosen was a 2D game. In this case, is a race game where the users controls a car and has to move it around the highway to avoid collitions with other vehicles on the road. Everytime a car was is successfully dodged the score increments by one. Every increment of five in the game score increments the game level, there is a maximum of 10 levels. So have fun and try to reach the maximum level and highest scores. :)

The code for this repo was inspired by the [snake game example](https://github.com/udacity/CppND-Capstone-Snake-Game) and this great online tutorial [Lazy Foo' Beginning Game Programming v2.0](https://lazyfoo.net/tutorials/SDL/index.php).


![Car game](/resources/CarGame.jpg "Car Game")

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./CarGame`

## Overview of code structure

The Car game code consists of five main classes: Car, Controller, Game, Renderer and Texture: 

### 1) main.cpp
To begin, main creates a Renderer, a Controller, and a Game object.
Main calls `Game::Run()` to starts the game loop. `Game::Run()` receives the controller and render objects to operate.

### 2) controller.h and controller.cpp 
These files define the Controller class. This class handles keyboard input using the SDL libary, and it sets the car's movement based on the input. 

### 3) car.h and car.cpp 
These files define the Car class which contains attributes to keep track of the car and enemies dimensionts, position and speed. Additionally, there are methods to move the car `Car::move()`, to move the enemies in a horizontal way with random start position `Car::enemyHorizontalMove()` and check for collitions in `Car::checkCollision()`.

### 4) game.h and game.cpp 
These files define the Game class and the game loop: `Game::run()`. The Game class stores the state of the game, including an instance of the player car object, the enemies car objects the game score, and the game level. 

Inside the game loop there is a call to `Game::Update()` in which the movement of the car and enemies takes place, as well as checks for collisions, an updates the score of the game. 

### 5) texture.h and texture.cpp
These files provide the APIs to cretate the Texture objects from the .bmp pictures inside the resources folder.

### 6) render.h and render.cpp
These files define the Renderer class which uses the SDL library to render the game to the screen. The Renderer class constructor creates the SDL window and an SDL renderer object that can draw in the window. 

With the help of the texture class the `Renderer::RenderCars()` function renders the car images representing the car objects in their current position during the game.
`Renderer::RenderBackGround()` method draws the background image with an horizontal animation. `Renderer::RenderGameOver()` method draws the game over picture when the game ends.


## Project Rubric

|  Criteria |   Comentaries   |
| --------- | --------------- |
| README file | A README.md file with all the requirements is included in the root of the project.                |
| Compiling and Testing | The project compiles and executes without errors. <br> `Cmake` and `make` are used as a build system.  |
| Understanding of C++ functions and control structures   | The project uses control structures and functions. <br>  The names of the functions are self-explained.|
| The project accepts user input and processes the input  | The game reads the keyboard arrow keys to update the car position.                                                |
| The project uses Object Oriented Programming techniques | The project is organized into five classes with attributes to hold the data, and methods to perform  actions. |
| Classes use appropriate access specifiers for class members.| E.g. The game object class defines the car objects as private. |
| Classes encapsulate behavior | E.g. The game score variable is accesed only by `game.GetScore()` outside the class. |
| The project makes use of references in function declarations. | E.g. The game score variable is acessed by `Car::enemyHorizontalMove()` as a reference. <br> Also the enemy_vel variable is acessed by refenrence in `Gamme::UpdateGameLevel()`. |
| The project uses destructors appropriately |  E.g. Texture class implements a desctructor. |





## License


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
