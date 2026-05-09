#include <2Dframework/player.h>

Player createPlayer(const char* image, int colorType, float maxVelocity, float accelaration, float modelSize[2], TexColumn walkAnim, TexColumn jumpAnim, float xCoord, float yCoord, float width, float height) {
  Player player;
  player.maxVelocity = maxVelocity;
  player.accelaration = accelaration;
  player.animations[WALK_ANIM] = walkAnim;
  player.animations[JUMP_ANIM] = jumpAnim;
  player.entity.ignoreCollision = EN_USE_COLLISION;
  player.entity.model = {
    modelSize,
    player,
    2,
    0,
    1
  }
  player.entity.obj = createGameObject(image, colorType, createEntityMesh(player.entity.model.modelsize),  xCoord, yCoord, width, height, 0.0f);
  entityUpdateTex(&player.entity);


  return player;
}
