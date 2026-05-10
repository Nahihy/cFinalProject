#include <2Dframework/player.h>

Player createPlayer(const char* image, int colorType, float maxVelocity, float accelaration, float modelSize[2],
                    TexColumn standAnim, TexColumn walkAnim, TexColumn jumpAnim, float xCoord, float yCoord, float width, float height) {
  Player player;
  player.maxVelocity = maxVelocity;
  player.accelaration = accelaration;
  player.animations[STAND_ANIM] = standAnim;
  player.animations[WALK_ANIM] = walkAnim;
  player.animations[JUMP_ANIM] = jumpAnim;
  player.entity.ignoreCollision = EN_USE_COLLISION;
  player.entity.model.modelsize[0] = modelSize[0];
  player.entity.model.modelsize[1] = modelSize[1];
  player.entity.model.modelColumns = player.animations;
  player.entity.model.modelColumnCount = TOTAL_ANIM_SIZE;
  player.entity.model.currModel = 1;
  player.entity.model.currModelColumn = STAND_ANIM;

  player.entity.obj = createGameObject(image, colorType, createEntityMesh(player.entity.model.modelsize),  xCoord, yCoord, width, height, 0.0f);
  entityUpdateTex(&player.entity);


  return player;
}

void playerDelete(Player* player) {
  entityDelete(&player->entity);
}
