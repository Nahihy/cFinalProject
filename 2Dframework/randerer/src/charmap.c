#include <randerer/charmap.h>
#include <stdlib.h>
#include <stdio.h>

CharacterMap createCharacterMap(int initCapacity) {
  CharacterMap map;
  map.capacity = initCapacity;
  map.size = 0;
  map.list = malloc(map.capacity * sizeof(KeyCharacterPair));
  return map;
}

void characterMapDelete(CharacterMap* map) {
  free(map->list);
  map->list = NULL;
  map->size = 0;
  map->capacity = 0;
}

static int findIndex(CharacterMap* map, char key) {
  for (int i = 0; i < map->size; i++)
    if (map->list[i].key == key)
      return i;
  return -1;
}

void characterMapInsert(CharacterMap* map, char key, Character value) {
  if (map->size >= map->capacity) {
    map->capacity = (map->capacity * 3) / 2;
    map->list = realloc(map->list, map->capacity * sizeof(KeyCharacterPair));
  }
  map->list[map->size].key   = key;
  map->list[map->size].value = value;
  map->size++;
}

void characterMapUpdate(CharacterMap* map, char key, Character value) {
  int i = findIndex(map, key);
  if (i != -1)
    map->list[i].value = value;
  else
    printf("CharacterMap: key '%c' not found for update\n", key);
}

int characterMapFind(CharacterMap* map, char key, Character* outValue) {
  int i = findIndex(map, key);
  if (i == -1) return 0;
  *outValue = map->list[i].value;
  return 1;
}

Character characterMapGet(CharacterMap* map, char key) {
  int i = findIndex(map, key);
  if (i == -1) {
    printf("CharacterMap: key '%c' not found\n", key);
    Character empty = {0};
    return empty;
  }
  return map->list[i].value;
}
