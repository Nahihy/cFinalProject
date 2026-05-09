#ifndef SHADER_BACKGROUND_FRAGMENT_GLSL
#define SHADER_BACKGROUND_FRAGMENT_GLSL
static const char* background_fragment_glsl = "#version 330 core\n"
"\n"
"in vec2 texCoord;\n"
"\n"
"out vec4 fragColor;\n"
"\n"
"uniform sampler2D tex;\n"
"\n"
"void main() {\n"
"  fragColor = texture(tex, texCoord);\n"
"}\n"
"";
#endif
