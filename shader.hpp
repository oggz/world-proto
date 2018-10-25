#ifndef SHADER_HPP_INCLUDED
#define SHADER_HPP_INCLUDED

#include "superheader.hpp"

class Shader {
  GLuint LoadShader(const char* vertex_file_path,const char * fragment_file_path) {
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
      std::string Line = "";
      while(getline(VertexShaderStream, Line))
	VertexShaderCode += "\n" + Line;
      VertexShaderStream.close();
    }else{
      printf("ERROR: Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !", vertex_file_path);
      return 0;
    }
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
      std::string Line = "";
      while(getline(FragmentShaderStream, Line))
	FragmentShaderCode += "\n" + Line;
      FragmentShaderStream.close();
    }
    GLint Result = GL_FALSE;
    int InfoLogLength;

    printf("INFO: Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 1 ){
      std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
      glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
      printf("\n%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    printf("INFO: Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);
    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 1 ){
      std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
      glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
      printf("\n%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    printf("INFO: Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 1 ){
      std::vector<char> ProgramErrorMessage(InfoLogLength+1);
      glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
      printf("\n%s\n", &ProgramErrorMessage[0]);
    }

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
  }

public:
  GLuint program;
  // vector<GLuint> uniforms;
  map<string,GLuint> uniforms;

  Shader( const char* VS, const char* FS ) {
    program = LoadShader( VS, FS );
    printf( "INFO: Shader Uniforms: \n" );
    int total = -1;
    glGetProgramiv( program, GL_ACTIVE_UNIFORMS, &total ); 
    for(int i=0; i<total; ++i)  {
      int name_len=-1, num=-1;
      GLenum type = GL_ZERO;
      char name[100];
      glGetActiveUniform( program, GLuint(i), sizeof(name)-1,
			  &name_len, &num, &type, name );
      name[name_len] = 0;
      uniforms[name] = glGetUniformLocation( program, name );
      printf( "INFO:   Uniform Index: %d, Uniform type: %d, Uniform Name: %s \n", i, type, name );
    }
  }
  ~Shader() {
  }

  GLuint getProgram() { return program; }

  GLuint getUniform( string Name ) { return uniforms["Name"]; }

};

#endif
