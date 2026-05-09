#pragma once
#include <glad/glad.h>
#include <cglm/cglm.h>

typedef struct {
  unsigned int ID;
  ivec2 size;
  ivec2 bearing;
  unsigned int advance;
} Character;

typedef struct {
  char key;
  Character value;
} KeyCharacterPair;

typedef struct {
  KeyCharacterPair* list;
  int size;
  int capacity;
} CharacterMap;

CharacterMap createCharacterMap(int initCapacity);
void characterMapInsert(CharacterMap* map, char key, Character value);
void characterMapUpdate(CharacterMap* map, char key, Character value);
int characterMapFind(CharacterMap* map, char key, Character* outValue);
Character characterMapGet(CharacterMap* map, char key);
void characterMapDelete(CharacterMap* map);
