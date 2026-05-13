#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

void main() {
  gl_Position = vec4(aPos.xy, 1.0f, 1.0f);
  texCoord = aTexCoord.xy;
}
