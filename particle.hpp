#ifndef PARTICLE_HPP_INCLUDED
#define PARTICLE_HPP_INCLUDED

#include "superheader.hpp"

class ParticleSystem {
  Particle {
    glm::vec3 position;

    Particle( float X, float Y, float Z ) :
      position.x( X ), position.y( Y ), position.z( Z ) {}
  };

  vector<Particle> particles;
  GLuint vao, vbo;

public:
  ParticleSystem() {  }
  ~ParticleSystem() {  }

  GenerateParticles( int NumParticles ) {
    glm::vec3 tParticle;
    for ( int i = 0; i < NumParticles; i++ ) {
      tParticle.x = rand() % 100;
      tParticle.y = rand() % 100;
      tParticle.z = rand() % 100;

      particles.push_back( Particle( tParticle.x, tParticle.y, tParticle.z ) );
    }

    
  }
  Render() {  }
};

#endif
