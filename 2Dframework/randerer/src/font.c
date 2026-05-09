#include <randerer/font.h>
#include <stdio.h>
#include <string.h>

#ifdef EMBED_FONTS
#include "font_lookup.h"
#endif

static const char* fontVertSrc =
  "#version 330 core\n"
  "layout (location = 0) in vec4 vertex;\n"
  "out vec2 texCoord;\n"
  "uniform mat4 projection;\n"
  "void main() {\n"
  "  gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
  "  texCoord = vertex.zw;\n"
  "}\0";

static const char* fontFragSrc =
  "#version 330 core\n"
  "in vec2 texCoord;\n"
  "out vec4 fragColor;\n"
  "uniform sampler2D text;\n"
  "uniform vec3 textColor;\n"
  "void main() {\n"
  "  float alpha = texture(text, texCoord).r;\n"
  "  fragColor = vec4(textColor, alpha);\n"
  "}\0";

static unsigned int compileShader() {
  int success;
  char infoLog[512];

  unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert, 1, &fontVertSrc, NULL);
  glCompileShader(vert);
  glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vert, 512, NULL, infoLog);
    printf("FONT::VERT: %s\n", infoLog);
  }

  unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag, 1, &fontFragSrc, NULL);
  glCompileShader(frag);
  glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(frag, 512, NULL, infoLog);
    printf("FONT::FRAG: %s\n", infoLog);
  }

  unsigned int program = glCreateProgram();
  glAttachShader(program, vert);
  glAttachShader(program, frag);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    printf("FONT::LINK: %s\n", infoLog);
  }

  glDeleteShader(vert);
  glDeleteShader(frag);
  return program;
}

static FT_Face loadFace(FT_Library ft, const char* path) {
  FT_Face face;
#ifdef EMBED_FONTS
  FontData fd = lookupFont(path);
  if (!fd.data) {
    printf("ERROR::FONT::NOT_FOUND_IN_EMBEDDED: %s\n", path);
    return NULL;
  }
  if (FT_New_Memory_Face(ft, fd.data, fd.len, 0, &face)) {
    printf("ERROR::FREETYPE: Failed to load embedded font: %s\n", path);
    return NULL;
  }
#else
  char* fullPath = malloc(strlen(FONT_DIR) + 1 + strlen(path) + 1);
  sprintf(fullPath, "%s/%s", FONT_DIR, path);
  int result = FT_New_Face(ft, fullPath, 0, &face);
  free(fullPath);
  if (result) {
    printf("ERROR::FREETYPE: Failed to load font: %s\n", path);
    return NULL;
  }
#endif
  return face;
}

Font createFont(const char* path, unsigned int fontSize, int windowWidth, int windowHeight) {
  Font font;
  font.fontSize = fontSize;
  font.glyphs   = createCharacterMap(64);
  font.shaderID = compileShader();

  mat4 projection;
  glm_ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -1.0f, 1.0f, projection);
  glUseProgram(font.shaderID);
  glUniformMatrix4fv(glGetUniformLocation(font.shaderID, "projection"), 1, GL_FALSE, (float*)projection);
  glUniform1i(glGetUniformLocation(font.shaderID, "text"), 0);

  FT_Library ft;
  if (FT_Init_FreeType(&ft)) {
    printf("ERROR::FREETYPE: Could not init FreeType\n");
    return font;
  }

  FT_Face face = loadFace(ft, path);
  if (!face) {
    FT_Done_FreeType(ft);
    return font;
  }

  FT_Set_Pixel_Sizes(face, 0, fontSize);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  FT_UInt glyphIndex;
  FT_ULong charCode = FT_Get_First_Char(face, &glyphIndex);
  while (glyphIndex != 0) {
    if (FT_Load_Char(face, charCode, FT_LOAD_RENDER)) {
      printf("ERROR::FREETYPE: Failed to load glyph %lu\n", charCode);
      charCode = FT_Get_Next_Char(face, charCode, &glyphIndex);
      continue;
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
      GL_TEXTURE_2D, 0, GL_RED,
      face->glyph->bitmap.width,
      face->glyph->bitmap.rows,
      0, GL_RED, GL_UNSIGNED_BYTE,
      face->glyph->bitmap.buffer
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Character glyph;
    glyph.ID         = texture;
    glyph.size[0]    = face->glyph->bitmap.width;
    glyph.size[1]    = face->glyph->bitmap.rows;
    glyph.bearing[0] = face->glyph->bitmap_left;
    glyph.bearing[1] = face->glyph->bitmap_top;
    glyph.advance    = face->glyph->advance.x;

    characterMapInsert(&font.glyphs, (char)charCode, glyph);

    charCode = FT_Get_Next_Char(face, charCode, &glyphIndex);
  }

  glBindTexture(GL_TEXTURE_2D, 0);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
  FT_Done_Face(face);
  FT_Done_FreeType(ft);

  glGenVertexArrays(1, &font.VAO);
  glGenBuffers(1, &font.VBO);
  glBindVertexArray(font.VAO);
  glBindBuffer(GL_ARRAY_BUFFER, font.VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return font;
}

void fontRenderText(Font* font, const char* text, float x, float y, float scale, vec3 color) {
  glUseProgram(font->shaderID);
  glUniform3f(glGetUniformLocation(font->shaderID, "textColor"), color[0], color[1], color[2]);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(font->VAO);

  for (int i = 0; text[i] != '\0'; i++) {
    Character g = characterMapGet(&font->glyphs, text[i]);

    float xpos = x + g.bearing[0] * scale;
    float ypos = y - (g.size[1] - g.bearing[1]) * scale;
    float w    = g.size[0] * scale;
    float h    = g.size[1] * scale;

    float vertices[6][4] = {
      { xpos,     ypos + h,   0.0f, 0.0f },
      { xpos,     ypos,       0.0f, 1.0f },
      { xpos + w, ypos,       1.0f, 1.0f },
      { xpos,     ypos + h,   0.0f, 0.0f },
      { xpos + w, ypos,       1.0f, 1.0f },
      { xpos + w, ypos + h,   1.0f, 0.0f }
    };

    glBindTexture(GL_TEXTURE_2D, g.ID);
    glBindBuffer(GL_ARRAY_BUFFER, font->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    x += (g.advance >> 6) * scale;
  }

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void fontDelete(Font* font) {
  for (int i = 0; i < font->glyphs.size; i++)
    glDeleteTextures(1, &font->glyphs.list[i].value.ID);
  characterMapDelete(&font->glyphs);
  glDeleteVertexArrays(1, &font->VAO);
  glDeleteBuffers(1, &font->VBO);
  glDeleteProgram(font->shaderID);
}
