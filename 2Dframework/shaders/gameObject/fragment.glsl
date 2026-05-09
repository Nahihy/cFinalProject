#version 330 core

in vec2 texCoord;

uniform sampler2D tex;
uniform vec2 texOffset;

void main() {
  gl_FragColor = texture(tex, texOffset + texCoord);
}
