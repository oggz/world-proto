#ifndef RENDER_HPP_INCLUDED
#define RENDER_HPP_INCLUDED

#include "superheader.hpp"
#include "mesh.hpp"
#include "shader.hpp"

class Render {
  int screen_width, screen_height;

  vector<Entity*> entities;
  vector<Mesh*> meshes;
  vector<Shader*> shaders;
  vector<Texture*> textures;

  glm::mat4 model_mat;
  glm::mat4 view_mat;
  glm::mat4 projection_mat;
  float light_pos[6];

  static const int cubes = 100;

  void InitMatrices() {
    projection_mat = glm::perspective( 45.0f, (float)screen_width / (float)screen_height, 0.1f, 1000.0f );
    view_mat = glm::lookAt( glm::vec3( 0.0f, 0.0f, 10.0f ),
			    glm::vec3( 0.0f, 0.0f, 0.0f ),
			    glm::vec3( 0.0f, 1.0f, 0.0f ) );
    model_mat = glm::mat4( 1.0f );
  }

  void InitLights() {
    light_pos[0] = 300.0f; light_pos[1] = 300.0f; light_pos[2] = 10.0f;
    light_pos[3] = -300.0f; light_pos[4] = 300.0f; light_pos[5] = 10.0f;
  }

public:
  Render() {
  }
  ~Render() {
    for ( unsigned int i = 0; i < entities.size(); i++ ) {
      delete entities[i];
    }
    for ( unsigned int i = 0; i < meshes.size(); i++ ) {
      delete meshes[i];
    }
    for ( unsigned int i = 0; i < shaders.size(); i++ ) {
      delete shaders[i];
    }
    for ( unsigned int i = 0; i < textures.size(); i++ ) {
      delete textures[i];
    }
  }

  Mesh* getMesh( unsigned int I ) { return meshes[I]; }
  Mesh* addMesh( const char* FileName ) { meshes.push_back( new Mesh( FileName ) ); return meshes[meshes.size() - 1]; }

  Shader* getShader( unsigned int I ) { return shaders[I]; }

  Texture* getTexture( unsigned int I ) { return textures[I]; }

  void setViewMatrix( glm::mat4 ViewMat ) { view_mat = ViewMat; }
  glm::mat4* getViewMatrix() { return &view_mat; }


  int Init( int ScreenWidth, int ScreenHeight ) {
    screen_width = ScreenWidth;
    screen_height = ScreenHeight;

    InitMatrices();
    InitLights();

    shaders.push_back( new Shader( "shaders/simple.vs", "shaders/simple.fs" ) );
    shaders.push_back( new Shader( "shaders/post_proc-water.vs", "shaders/simple.fs" ) );

    textures.push_back( new Texture( "textures/metal.tga" ) );
    textures.push_back( new Texture( "textures/gold-2.tga" ) );

    meshes.push_back( new Mesh( "models/terrain.obj" ) );
    meshes[0]->addInstance( shaders[1] );
    meshes[0]->getInstance( 0 )->setRender( 1 );
    meshes[0]->getInstance( 0 )->setTexture( textures[0] );
    meshes[0]->getInstance( 0 )->setTranslation( 0.0f, 0.0f, 200.0f );
    meshes[0]->getInstance( 0 )->setScale( 2.0f, 2.0f, 2.0f );

    meshes.push_back( new Mesh( "models/cube.obj" ) );
    meshes[1]->addInstance( shaders[0] );
    meshes[1]->getInstance( 0 )->setTexture( textures[1] );

    return 0;
  }

  int draw( double Time ) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    for ( unsigned int i = 0; i < shaders.size(); i++ ) {
      glUseProgram ( shaders[i]->program );
      glUniformMatrix4fv( shaders[i]->uniforms["M"], 1, GL_FALSE, &model_mat[0][0] );
      glUniformMatrix4fv( shaders[i]->uniforms["P"], 1, GL_FALSE, &projection_mat[0][0] );
      glUniformMatrix4fv( shaders[i]->uniforms["V"], 1, GL_FALSE, &view_mat[0][0] );
      glUniform1i( shaders[i]->uniforms["tx0"], 0 );
      glUniform3fv( shaders[i]->uniforms["l_pos[0]"], 2, light_pos );
      glUniform1f( shaders[i]->uniforms["time"], (float)Time );
      glUseProgram( 0 );
    }

    for ( unsigned int i = 0; i < meshes.size(); i++ ) {
      meshes[i]->instances[0]->getTexture()->bind( GL_TEXTURE0 );
      glUseProgram( meshes[i]->instances[0]->getShader()->getProgram() );
      for ( unsigned int j = 0; j < meshes[i]->instances.size(); j++ ) {
	glUniformMatrix4fv( meshes[i]->instances[j]->getShader()->getUniform( "M" ),
			    1,
			    GL_FALSE,
			    meshes[i]->instances[j]->getModelMatP() );
	glBindVertexArray( meshes[i]->getVao() );
	glDrawArrays( GL_TRIANGLES, 0, meshes[i]->getMeshSize() );
      }
      glBindVertexArray( 0 );
      glUseProgram( 0 );
    }

    glfwSwapBuffers();
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR ) {
      printf( "ERROR: Opengl error = '%d' \n",  err );
    }

    return 0;
  }

};

#endif
