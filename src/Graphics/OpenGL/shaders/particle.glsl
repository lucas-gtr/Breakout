#shader vertex
#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 model;
uniform mat4 projection;

uniform vec4 color;

void main()
{
  float scale = 0.01f;
  TexCoords = vertex.zw;
  ParticleColor = color;
  gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}

#shader fragment
#version 330 core
in vec2 TexCoords;
in vec4 ParticleColor;

out vec4 color;

uniform sampler2D sprite;

void main()
{
  color = (texture(sprite, TexCoords) * ParticleColor);
}
