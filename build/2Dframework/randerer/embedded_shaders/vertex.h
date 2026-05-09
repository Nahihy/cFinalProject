#ifndef SHADER_VERTEX_GLSL
#define SHADER_VERTEX_GLSL
static const char* vertex_glsl = "#version 330 core\n"
"\n"
"layout (location = 0) in vec2 aPos;\n"
"\n"
"uniform mat4 transform;\n"
"\n"
"void main() {\n"
"  gl_Position = transform * vec4(aPos.xy, 1.0f, 1.0f); \n"
"}\n"
"";
#endif
