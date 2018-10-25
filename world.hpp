/*
  This is free software. Created by 0G9Z.
*/

#include "utility.hpp"
#include "render.hpp"
#include "input.hpp"
#include "camera.hpp"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

using namespace std;

class World {
  int screen_width, screen_height;
  string window_title, window_prefix;
  double current_time, prev_time;
  float delta_time;
  float frame_time;

  Render render;
  Input input;
  Camera camera;

public:
  World() {

  }
  ~World() {
    printf( "INFO: World De-Initialized \n" );
  }
  int init( string WindowPrefix, int ScreenWidth, int ScreenHeight ) {
    // Window Vars
    window_prefix = WindowPrefix;
    screen_width = ScreenWidth;
    screen_height = ScreenHeight;

    // Timer Vars
    current_time = 0, prev_time = 0;
    delta_time = 0;
    frame_time = 0.016;

    // Mark Program Begin
    printf( "INFO: World Initialized \n" );
                                     
    // Render Init
    InitGLFW( screen_width, screen_height );
    InitGL( screen_width, screen_height );
    render.Init( screen_width, screen_height );

    // Input Init
    input.setRender( &render );
    input.setScreenXY( screen_width, screen_height );

    // Camera Init
    camera.loadData();

    return 0;
  }

  int engage() {
    // Engage Main Loop
    printf( "\n########## Main Loop Begin ##########\n" );
    while( ! input.Escape() ) {
      // Timer
      prev_time = current_time;
      current_time = glfwGetTime();
      delta_time = current_time - prev_time;
      glfwSleep( frame_time - delta_time );

      // Input
      input.update( current_time);

      // Camera
      camera.adjustAngle( input.getMouseDeltaX(), input.getMouseDeltaY() );
      camera.move( input.getMove() );
      render.setViewMatrix( camera.getViewMat() );

      // Render
      render.draw( current_time );

      // Title Update
      ostringstream ss;
      ss << 1 / delta_time;
      window_title = window_prefix + ss.str();
      glfwSetWindowTitle( (char*)window_title.c_str() );
    }
    printf( "########### Main Loop End ###########\n\n" );

    return 0;
  }

};
