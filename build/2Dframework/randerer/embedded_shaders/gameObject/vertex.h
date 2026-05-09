#ifndef SHADER_GAMEOBJECT_VERTEX_GLSL
#define SHADER_GAMEOBJECT_VERTEX_GLSL
static const char* gameObject_vertex_glsl = "#version 330 core\n"
"\n"
"layout (location = 0) in vec2 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"\n"
"out vec2 texCoord;\n"
"\n"
"uniform mat4 transform;\n"
"\n"
"void main() {\n"
"\n"
"  gl_Position = transform * vec4(aPos.xy , 0.0f, 1.0f);\n"
"  texCoord = aTexCoord.xy;\n"
"\n"
"}\n"
"";
#endif
