#ifndef SHADER_LOOKUP_H
#define SHADER_LOOKUP_H
#include "all_shaders.h"
#include <string.h>

static inline const char* lookupShader(const char* path) {
  if (strcmp(path, "background/fragment.glsl") == 0) return background_fragment_glsl;
  if (strcmp(path, "background/vertex.glsl") == 0) return background_vertex_glsl;
  if (strcmp(path, "fragment.glsl") == 0) return fragment_glsl;
  if (strcmp(path, "gameObject/fragment.glsl") == 0) return gameObject_fragment_glsl;
  if (strcmp(path, "gameObject/vertex.glsl") == 0) return gameObject_vertex_glsl;
  if (strcmp(path, "vertex.glsl") == 0) return vertex_glsl;
  return 0;
}
#endif
