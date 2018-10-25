#ifndef INPUT_HPP_INCLUDED
#define INPUT_HPP_INCLUDED

#include "superheader.hpp"
#include "render.hpp"

class Input {
  Render* render;
  int screen_width, screen_height;
  double time;

  char current_key;
  bool keys[256];

  int mouse_x, mouse_y;
  float mouse_delta_x, mouse_delta_y;
  float mouse_accel;

  glm::vec3 move;
  bool move_forward, move_backward;

  bool wireframe;

public:
  Input() {
    move = glm::vec3( 0.0f );
  }
  ~Input() {  }

  void setRender( Render* Render ) { render = Render; }

  void setScreenXY( int X, int Y ) { screen_width = X; screen_height = Y; }

  float getMouseDeltaX() { return mouse_delta_x; }
  float getMouseDeltaY() { return mouse_delta_y; }

  glm::vec3* getMove() { return &move; }

  bool getMoveForward() { return move_forward; }
  bool getMoveBackward() { return move_backward; }

  int Escape() {
    if ( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS )
      return true;
    else
      return false;
  }

  void keyboard() {
    // Toggle Template
    current_key = 'T';
    if ( glfwGetKey( current_key ) == GLFW_PRESS && keys[(int)current_key] == 0 ) {
      keys[(int)current_key] = 1;
    }
    else if ( glfwGetKey( current_key ) == GLFW_RELEASE && keys[(int)current_key] == 1 ) {
      keys[(int)current_key] = 0;
    }

    current_key = 'L';
    if ( glfwGetKey( current_key ) == GLFW_PRESS && keys[(int)current_key] == 0 ) {
      keys[(int)current_key] = 1;
      wireframe = ! wireframe;
      if ( wireframe ) {
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      }
      else {
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
      }
    }
    else if ( glfwGetKey( current_key ) == GLFW_RELEASE && keys[(int)current_key] == 1 ) {
      keys[(int)current_key] = 0;
    }

    // Every Frame
    move = glm::vec3( 0.0f );

    if ( glfwGetKey( 'W' ) == GLFW_PRESS ) {
      move.z += -1.0f;
    }
    if ( glfwGetKey( 'S' ) == GLFW_PRESS ) {
      move.z += 1.0f;
    }
    if ( glfwGetKey( 'W' ) == GLFW_RELEASE && glfwGetKey( 'S' ) == GLFW_RELEASE ) {
      move.z = 0.0f;
    }

    if ( glfwGetKey( 'A' ) == GLFW_PRESS ) {
      move.x += -1.0f;
    }
    if ( glfwGetKey( 'D' ) == GLFW_PRESS ) {
      move.x += 1.0f;
    }
    if ( glfwGetKey( 'A' ) == GLFW_RELEASE && glfwGetKey( 'D' ) == GLFW_RELEASE ) {
      move.x = 0.0f;
    }

    if ( glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS ) {
      move.y = 1.0f;
    }
    if ( glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS ) {
      move.y = -1.0f;
    }
    if ( glfwGetKey( GLFW_KEY_UP ) == GLFW_RELEASE && glfwGetKey( GLFW_KEY_DOWN ) == GLFW_RELEASE ) {
      move.y = 0.0f;
    }

  }

  void mouse() {
    mouse_accel = 0.003f;
    glfwGetMousePos( &mouse_x, &mouse_y );
    glfwSetMousePos( screen_width / 2, screen_height / 2 );
    // printf( "Mouse position. X: '%d', Y: '%d' \n", mX, mY );

    if ( mouse_y < screen_height / 2 + 2 && mouse_y > screen_height / 2 - 2 )
      mouse_y = screen_height / 2;
    mouse_delta_x = mouse_accel * (float)( screen_width / 2 - mouse_x );
    mouse_delta_y = mouse_accel * (float)( screen_height / 2 - mouse_y );
  }

  void update( double Time ) {
    time = Time;
    keyboard();
    mouse();
  }

};

#endif
