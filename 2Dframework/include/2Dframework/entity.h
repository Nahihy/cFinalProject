#pragma once
#include <2Dframework/gameObject.h>

#define EN_USE_COLLISION 0
#define EN_IGNORE_COLLISION 1
#define EN_REPEAT 2
#define EN_MIRROR 3

typedef struct {
  int column;
  int count;
  int actionAtEnd;
} TexColumn;

typedef struct {
  float modelsize[2];
  TexColumn* modelColumns;
  int modelColumnCount;
  int currModelColumn;
  int currModel;
} ModelAttrib;

typedef struct {
  GameObject obj;
  int ignoreCollision;
  ModelAttrib model;
} Entity;



Entity createEntity(const char* image, int colorType, ModelAttrib* model, int ignoreCollision, float xCoord, float yCoord, float width, float height);
void entityDelete(Entity* entity);
void entityDraw(Entity* entity);
void entityMove(Entity* entity, float horizontal, float vertical);
void entityResize(Entity* entity, float horizontal, float vertical);
void entityChangeTexColumn(Entity* entity, int column);
void entityNextTex(Entity* entity);
void entityUpdateTex(Entity* entity);
Mesh createEntityMesh(float texCoord[2]);
