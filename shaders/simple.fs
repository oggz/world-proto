#version 330 core // Fragment Shader

in vec2 uv_coord;
in vec3 position;
in vec3 position_worldspace;
in vec3 normal_cameraspace;
out vec4 color;
uniform mat4 M;
uniform mat4 V;
uniform sampler2D tx0;
uniform vec3 l_pos[2];
uniform float time;

vec3 light( int i ) {
  vec3 light_color = vec3( abs( sin( time ) ), 1.0f * i, 1.0f * i );
  float light_power = 40000.0f;
  // vec3 material_diffuse_color = vec3( 1.0f, 1.0f, 1.0f ) * texture( tx0, uv_coord ).rgb ;
  vec3 material_diffuse_color = vec3( texture( tx0, uv_coord ).rgb );
  vec3 material_ambient_color = vec3( 0.1, 0.1f, 0.1f ) * material_diffuse_color;
  vec3 material_specular_color = vec3( 0.3f, 0.3f, 0.3f );

  vec3 eye_dir_cameraspace = vec3( 0, 0, 0 ) - ( V * M * vec4( position, 1 ) ).xyz;
  vec3 light_dir_cameraspace = normalize( ( V * vec4( l_pos[i], 1) ).xyz - position );

  float distance = length( l_pos[i] - position_worldspace );

  vec3 n = normalize( normal_cameraspace );
  vec3 l = normalize( light_dir_cameraspace );
  float cos_theta = clamp( dot( n, l ), 0, 1 );

  vec3 E = normalize( eye_dir_cameraspace );
  vec3 R = reflect( -l, n );
  float cos_alpha = clamp( dot( E, R ), 0, 1 );
  vec3 light_conrib = 
    material_ambient_color + 
    material_diffuse_color * light_color * light_power * cos_theta / ( distance * distance ) +
    material_specular_color * light_color * light_power * pow( cos_alpha, 10 ) / ( distance * distance ) ;

  return light_conrib;
}

void main()
{
  color = vec4( light( 0 ) + light ( 1 ), 1 );
  // color = texture( tx0, uv_coord );
  // color = vec4( 0.5f + 0.5f * normalize( normal_cameraspace ), 1.0f );
  // color = texture( texture_sampler, uv_coord ).rgb;
}
