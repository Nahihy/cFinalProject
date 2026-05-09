#pragma once
#include <glad/glad.h>
#include <cglm/cglm.h>
#include <randerer/shader.h>
#include <randerer/charmap.h>

#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct {
  CharacterMap glyphs;
  unsigned int VAO, VBO;
  unsigned int shaderID;
  unsigned int fontSize;
} Font;

Font createFont(const char* path, unsigned int fontSize, int windowWidth, int windowHeight);
void fontRenderText(Font* font, const char* text, float x, float y, float scale, vec3 color);
void fontDelete(Font* font);
