#ifndef INSTANCE_HPP_INCLUDED
#define INSTANCE_HPP_INCLUDED

#include "superheader.hpp"
#include "shader.hpp"
#include "texture.hpp"

class Instance {
private:
  bool render;
  Shader* shader;
  Texture* texture;
  glm::mat4 model_mat, rotate_mat, 
    translate_mat, scale_mat;

  void initMatrices() {
    scale_mat = glm::mat4( 1.0f );
    rotate_mat = glm::mat4( 1.0f );
    translate_mat = glm::mat4( 1.0f );
  }

  void multMatrices() {
    model_mat = translate_mat * rotate_mat * scale_mat;
  }

public:

  Instance( Shader* S ) {
    shader = S;
    render = true;
    multMatrices();
  }
  ~Instance() {
  }

  void setRender( bool Render ) { render = Render; }
  bool getRender() { return render; }
  void toggleRender() { render = ! render; }

  void setShader( Shader* S ) { shader = S; }
  Shader* getShader() { return shader; }

  void setTexture( Texture* T ) { texture = T; }
  Texture* getTexture() { return texture; }

  GLfloat* getModelMatP() { multMatrices(); return &model_mat[0][0]; }

  Instance* setRotation( float D, float X, float Y, float Z ) {
    rotate_mat = glm::rotate( model_mat, D, glm::vec3( X, Y, Z ) );
    return this;
  }
  glm::mat4* getRotation() { return &rotate_mat; }

  Instance* setTranslation( float X, float Y, float Z ) {
    translate_mat = glm::translate( glm::mat4( 1.0f ), X, Y, Z );
    return this;
  }
  glm::mat4* getTranslation() { return &translate_mat; }

  void setScale( float X, float Y, float Z ) {
    scale_mat = glm::scale( X, Y, Z );
  }
  glm::mat4* getScale() { return &scale_mat; }

};

#endif
