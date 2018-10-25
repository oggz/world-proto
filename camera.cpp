#include "camera.hpp"

Camera::Camera() {
  initData();
}

Camera::~Camera() {
  saveData();
}



void Camera::initData() {
  position = glm::vec3( 0.0f, 3.0f, 10.0f );
  v_angle = -PI/12, h_angle = PI;
  delta_move = 0.5f;
}

void Camera::move( glm::vec3* Move ) {
  if ( Move->z != 0.0f )
    position -= vector * Move->z;
  if ( Move->x != 0.0f )
    position += right_vector * Move->x;
  if ( Move->y != 0.0f )
    position -= up_vector * Move->y;
}

void Camera::setViewAngle() {
  vector = glm::vec3( cos( v_angle ) * sin( h_angle ),
		      sin( v_angle ),
		      cos( v_angle ) * cos( h_angle ) );
  right_vector = glm::vec3( sin( h_angle - 3.14159f / 2.0f ),
			 0,
			 cos( h_angle - 3.14159f / 2.0f ) );
  up_vector = glm::cross( right_vector, vector );
  view_mat = glm::lookAt( position,
			  position + vector,
			  up_vector );
}

void Camera::update() {
  setViewAngle();
}

void Camera::saveData() {
  string filename = "data/camera-data.txt";
  ofstream out_file( filename.c_str() );
  if ( ! out_file.is_open() )
    cout << "ERROR: Could not open file: " << filename << endl;
  else {
    out_file << position.x << endl;
    out_file << position.y << endl;
    out_file << position.z << endl;
    out_file << v_angle << endl;
    out_file << h_angle << endl;
    out_file.close();
    printf( "INFO: Camera Data Saved. \n" );
  }
}

void Camera::loadData() {
  string filename = "data/camera-data.txt";
  ifstream in_file( filename.c_str() );
  char char_buffer[256];
  string data;
  int line = 0;
  float var[5];
  if ( ! in_file.is_open() )
    cout << "ERROR: Could not open file: " << filename << endl;
  else {
    while ( ! in_file.eof() ) {
      in_file.getline( char_buffer, 255 );
      data = char_buffer;
      stringstream ss( data );
      ss >> var[line];
      line++;
    }
    position.x = var[0];
    position.y = var[1];
    position.z = var[2];
    v_angle = var[3];
    h_angle = var[4];

    //printf( " Camera data successfully loaded. \n" );
  }
}
