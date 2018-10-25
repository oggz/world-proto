/*
  This is free software. Created by 0G9Z.
*/

#include "world.hpp"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main( int argc, char* argv[] ) {
  World world;

  world.init( "GL Test - ", SCREEN_WIDTH, SCREEN_HEIGHT );

  world.engage();

  return 0;
}
