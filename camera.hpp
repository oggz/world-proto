#ifndef _CAMERA_HPP_INCLUDED_
#define _CAMERA_HPP_INCLUDED_

#include "superheader.hpp"
#include <sstream>

using namespace std;

class Camera {
private:
  glm::vec3 position, vector, right_vector, up_vector;
  float v_angle, h_angle;
  float delta_move;
  glm::mat4 view_mat;
  
public:
  Camera();
  ~Camera();

  void adjustAngle( float X, float Y ) { h_angle += X; v_angle += Y; }

  glm::vec3 getPosition() { return position; };
  void setPosition( glm::vec3 pos ) { position = pos; };

  glm::vec3 getVector() { return vector; };
  void setVector( glm::vec3 vec ) { vector = vec; };

  glm::mat4 getViewMat() { setViewAngle(); return view_mat; };
  void setViewMat( glm::mat4 view ) { view_mat = view; };

  void initData();
  void move( glm::vec3* );
  void setViewAngle();
  void update();
  void saveData();
  void loadData();
  void setLoad( bool Load );
};

#endif
