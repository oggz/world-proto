#ifndef MESH_HPP_INCLUDED
#define MESH_HPP_INCLUDED

#include "superheader.hpp"
#include "instance.hpp"

class Mesh {
private:
  vector<Vertex> mesh;
  GLuint vao, vbo;

  bool ReadOBJ( const char * path, std::vector<Vertex> & out_data ) {
    printf("INFO: Loading OBJ file %s...\n", path);
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices; 
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    FILE * file = fopen(path, "r");
    if( file == NULL ){
      printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
      return false;
    }

    while( 1 ){
      char lineHeader[128];
      int res = fscanf(file, "%s", lineHeader);
      if (res == EOF)
	break; // EOF = End Of File. Quit the loop.
      if ( strcmp( lineHeader, "v" ) == 0 ){
	glm::vec3 vertex;
	fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
	temp_vertices.push_back(vertex);
      }else if ( strcmp( lineHeader, "vt" ) == 0 ){
	glm::vec2 uv;
	fscanf(file, "%f %f\n", &uv.x, &uv.y );
	uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. 
	// Remove if you want to use TGA or BMP loaders.
	temp_uvs.push_back(uv);
      }else if ( strcmp( lineHeader, "vn" ) == 0 ){
	glm::vec3 normal;
	fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
	temp_normals.push_back(normal);
      }else if ( strcmp( lineHeader, "f" ) == 0 ){
	std::string vertex1, vertex2, vertex3;
	unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
	int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
			     &vertexIndex[0], &uvIndex[0], &normalIndex[0], 
			     &vertexIndex[1], &uvIndex[1], &normalIndex[1], 
			     &vertexIndex[2], &uvIndex[2], &normalIndex[2] 
			     );
	if (matches != 9){
	  printf("File can't be read by our simple parser :-( Try exporting with other options\n");
	  return false;
	}
	vertexIndices.push_back(vertexIndex[0]);
	vertexIndices.push_back(vertexIndex[1]);
	vertexIndices.push_back(vertexIndex[2]);
	uvIndices    .push_back(uvIndex[0]);
	uvIndices    .push_back(uvIndex[1]);
	uvIndices    .push_back(uvIndex[2]);
	normalIndices.push_back(normalIndex[0]);
	normalIndices.push_back(normalIndex[1]);
	normalIndices.push_back(normalIndex[2]);
      }else{
	char stupidBuffer[1000];
	fgets(stupidBuffer, 1000, file);
      }
    }

    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
      unsigned int vertexIndex = vertexIndices[i];
      unsigned int uvIndex = uvIndices[i];
      unsigned int normalIndex = normalIndices[i];
		
      glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
      glm::vec2 uv = temp_uvs[ uvIndex-1 ];
      glm::vec3 normal = temp_normals[ normalIndex-1 ];
		
      out_data.push_back( Vertex( vertex, normal, uv ) );
    }

    return true;
  }

  void loadMesh( const char* FileName ) {
    bool result = ReadOBJ( FileName, mesh );
    if ( result != 1 ) { printf( "ERROR: failed to load OBJ file. \n" ); }

    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, mesh.size() * sizeof( Vertex ), &mesh[0], GL_STATIC_DRAW );
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)0 );
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)12 );
    glEnableVertexAttribArray( 2 );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)24 );
    glBindVertexArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
  }

public:
  vector<Instance*> instances;

  Mesh( const char* FileName ) {
    loadMesh( FileName );
  }
  ~Mesh() {
    glDeleteBuffers( 1, &vao );
    glDeleteBuffers( 1, &vbo );
    for ( unsigned int i = 0; i < instances.size(); i++ ) {
      delete instances[i];
    }
  }
  GLuint getVao() { return vao; }
  GLuint getMeshSize() { return mesh.size(); }

  Instance* getInstance( unsigned int I ) { return instances[I]; }
  Instance* addInstance( Shader* S ) {
    instances.push_back( new Instance( S ) );
    return instances[instances.size() - 1];
  }
  void removeInstance( unsigned int I ) {
    instances.erase( instances.begin() + I );
  }

  // int draw() {
  // 	instances[0]->getTexture()->bind( GL_TEXTURE0 );
  // 	glUseProgram( instances[0]->getShader()->getProgram() );
  //   for ( unsigned int i = 0; i < instances.size(); i++ ) {
  //     if ( instances[i]->getRender() == 1 ) {
  // 	glUniformMatrix4fv( instances[i]->getShader()->getUniform( "M" ), 1, GL_FALSE, instances[i]->getModelMatP() );
  // 	glBindVertexArray( vao );
  // 	glDrawArrays( GL_TRIANGLES, 0, mesh.size() );
  //     }
  //   }
  // 	glBindVertexArray( 0 );
  // 	glUseProgram( 0 );

  //   return 0;
  // }
};

#endif
