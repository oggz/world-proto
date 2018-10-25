#ifndef UTILITY_HPP_INCLUDED
#define UTILITY_HPP_INCLUDED

#include "superheader.hpp"

void windowSizeCallback( int x, int y ) {
  glViewport( 0, 0, x, y );
}

int InitGLFW( int ScreenWidth, int ScreenHeight ) {
  if ( ! glfwInit() ) {
    printf( "ERROR: GLFW failed to initialize! \n" );
    return -1;
  }
  glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 4 );
  glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
  glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 3 );
  glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
  glfwOpenWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, 1 );
  if ( ! glfwOpenWindow( ScreenWidth, ScreenHeight, 0,0,0,0, 32,0, GLFW_WINDOW ) ) {
    printf( "ERROR: GLFW failed to open a window! \n" );
    glfwTerminate();
    return -1;
  }
  glfwSetWindowTitle( "world-proto1 - null" );
  glfwEnable( GLFW_STICKY_KEYS );
  glfwSetWindowSizeCallback( &windowSizeCallback );
  glfwSwapInterval(1);
  glfwSetMousePos( ScreenWidth / 2, ScreenHeight / 2 );
  // glfwDisable( GLFW_MOUSE_CURSOR );

  return 0;
}

int InitGL( int ScreenWidth, int ScreenHeight ) {
  glewExperimental = true;
  if ( glewInit() != GLEW_OK ) {
    printf( "ERROR: GLEW failed to initialize! \n" );
    return -1;
  }
  unsigned err = glGetError();
  if ( err != GL_NO_ERROR ) {
    printf( "INFO: Absorbing wonky init error: '%s' \n", glewGetErrorString( err ) );
  }
  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
  glViewport( 0, 0, ScreenWidth, ScreenHeight  );
  glEnable( GL_DEPTH_TEST );
  glDepthMask( GL_TRUE );
  glDepthFunc( GL_LEQUAL );
  glDepthRange( 0.0f, 1.0f );
  glEnable( GL_CULL_FACE );
  glCullFace( GL_BACK );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  return 0;
}

#endif
