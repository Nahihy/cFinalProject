#ifndef SHADER_BACKGROUND_VERTEX_GLSL
#define SHADER_BACKGROUND_VERTEX_GLSL
static const char* background_vertex_glsl = "#version 330 core\n"
"\n"
"layout (location = 0) in vec2 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"\n"
"out vec2 texCoord;\n"
"\n"
"uniform vec2 texOffset;\n"
"\n"
"void main() {\n"
"  gl_Position = vec4(aPos.xy, 0.0f, 1.0f);\n"
"  texCoord = aTexCoord.xy + texOffset.xy;\n"
"}\n"
"";
#endif
