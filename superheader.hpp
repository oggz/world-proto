#ifndef SUPERHEADER_HPP_INCLUDED
#define SUPERHEADER_HPP_INCLUDED

#include <stdio.h>
#include <cstring>
#include <map>
#include <vector>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fstream>

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


#define PI 3.14159265

using namespace std;

struct Entity {
  glm::mat4 model_mat;
  unsigned int mesh_index, shader_index;
  Entity() {
    model_mat = glm::mat4( 1.0f );
    mesh_index = 0, shader_index = 0;
  }
  ~Entity() {
  }
};

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 uv;
  Vertex( glm::vec3 pos, glm::vec3 norm, glm::vec2 tex ) : 
    position( pos ), normal( norm ), uv( tex ) {}
};

#endif
