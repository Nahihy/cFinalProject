#ifndef SHADER_GAMEOBJECT_FRAGMENT_GLSL
#define SHADER_GAMEOBJECT_FRAGMENT_GLSL
static const char* gameObject_fragment_glsl = "#version 330 core\n"
"\n"
"in vec2 texCoord;\n"
"\n"
"uniform sampler2D tex;\n"
"uniform vec2 texOffset;\n"
"\n"
"void main() {\n"
"  gl_FragColor = texture(tex, texOffset + texCoord);\n"
"}\n"
"";
#endif
