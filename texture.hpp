#ifndef _TEXTURE_HPP_INCLUDED_
#define _TEXTURE_HPP_INCLUDED_

#include "superheader.hpp"

class Texture {
  const char* filename;
  GLenum texture_target;
  GLuint texture_id;

  void load() {
    glGenTextures( 1, &texture_id );
    glBindTexture( texture_target, texture_id );
    glfwLoadTexture2D( filename, 0 );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
    glGenerateMipmap(GL_TEXTURE_2D);
  }

public:
  Texture( const char* FileName, GLenum TextureTarget = GL_TEXTURE_2D ) {
    filename = FileName;
    texture_target = TextureTarget;
    load();
  }
  void bind( GLenum TextureUnit ) {
    glActiveTexture( TextureUnit );
    glBindTexture( texture_target, texture_id );
  }
};

#endif
