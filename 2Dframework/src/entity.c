#include <2Dframework/entity.h>
#include <stdio.h>

Mesh createEntityMesh(float texCoord[2]) {
  float vertices[16] = {
   -1.0f, 1.0f,   0.0f,        texCoord[1],
    1.0f, 1.0f,   texCoord[0], texCoord[1],
   -1.0f,-1.0f,   0.0f,        0.0f,
    1.0f,-1.0f,   texCoord[0], 0.0f
  };
  unsigned int indices[6] = {
    0, 1, 2,
    1, 2, 3
  };

  VertexAttrib attrib[2] = {
    {0, 2, 4 * sizeof(float), 0},
    {1, 2, 4 * sizeof(float), 2 * sizeof(float)}
  };

  return createMesh(vertices, 16, indices, 6, attrib, 2);
}

Entity createEntity(const char* image, int colorType, ModelAttrib* model, int ignoreCollision,
                    float accelaration, float maxVelocity, float xCoord, float yCoord, float width, float height) {
  if(ignoreCollision != EN_IGNORE_COLLISION && ignoreCollision != EN_USE_COLLISION) {
    printf("Warning: invalid collision value in %s entity. only set to \"EN_USE_COLLISION\" or \"EN_IGNORE_COLLISION\", it has been set to ignore", image);
    ignoreCollision = EN_IGNORE_COLLISION;
  }
  Entity entity;
  entity.ignoreCollision = ignoreCollision;
  entity.model = *model;
  entity.accelaration = accelaration;
  entity.maxVelocity = maxVelocity;
  entity.currHoriVelocity = 0.0f;
  entity.currVertVelocity = 0.0f;
  entity.obj = createGameObject(image, colorType, createEntityMesh(entity.model.modelsize),  xCoord, yCoord, width, height, 0.0f);
  entityUpdateTex(&entity);
  return entity;
}

void entityUpdateMovement(Entity* entity, float horiMovement, float vertMovement) {
  entity->currHoriVelocity += entity->accelaration * horiMovement;
  if(!horiMovement && entity->currHoriVelocity < 0.0f) entity->currHoriVelocity += entity->accelaration / 2.0f;
  else if(!horiMovement && entity->currHoriVelocity > 0.0f) entity->currHoriVelocity -= entity->accelaration / 2.0f;
  if(entity->currHoriVelocity > entity->maxVelocity) entity->currHoriVelocity -= entity->currHoriVelocity;
  else if(entity->currHoriVelocity < -entity->maxVelocity) entity->currHoriVelocity += entity->currHoriVelocity;
  gameObjectMove(&entity->obj, entity->currHoriVelocity, 0);
}

void entityDelete(Entity* entity) {
  gameObjectDelete(&entity->obj);
}

void entityDraw(Entity* entity) {
  gameObjectDraw(&entity->obj);
}

void entityMove(Entity* entity, float horizontal, float vertical) {
  gameObjectMove(&entity->obj, horizontal, vertical);
}

void entityResize(Entity* entity, float horizontal, float vertical) {
  gameObjectResize(&entity->obj, horizontal, vertical);
}

void entityNextTex(Entity* entity) {
  entity->model.currModel++;
  TexColumn* currColumn = &(entity->model.modelColumns[entity->model.currModelColumn]);
  if(currColumn->count <= entity->model.currModel)
    if(currColumn->actionAtEnd == EN_REPEAT) entity->model.currModel = 1;
    else if(currColumn->actionAtEnd == EN_MIRROR) entity->model.currModel -= 2;
  entityUpdateTex(entity);
}

void entityChangeTexColumn(Entity* entity, int column) {
  entity->model.currModel = 1;
  entity->model.currModelColumn = column;
  entityUpdateTex(entity);
}

void entityUpdateTex(Entity* entity) {
  entity->obj.horiTexOffset = entity->model.currModelColumn * entity->model.modelsize[0];
  entity->obj.vertTexOffset = 1.0f - (entity->model.currModel * entity->model.modelsize[1]);
  gameObjectUpdateTex(&entity->obj);
}
