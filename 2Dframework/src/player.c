#include <2Dframework/player.h>

Player createPlayer(const char* image, int colorType, float maxVelocity, float accelaration, float modelSize[2],
                    TexColumn standAnim, TexColumn walkAnim, TexColumn jumpAnim, float xCoord, float yCoord, float width, float height) {
  Player player;
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
  player.entity.maxVelocity = maxVelocity;
  player.entity.accelaration = accelaration;
  player.entity.currHoriVelocity = 0.0f;
  player.entity.currVertVelocity = 0.0f;

  player.entity.obj = createGameObject(image, colorType, createEntityMesh(player.entity.model.modelsize),  xCoord, yCoord, width, height, 0.0f);
  entityUpdateTex(&player.entity);


  return player;
}

void playerDelete(Player* player) {
  entityDelete(&player->entity);
}

void playerDraw(Player* player) {
  entityDraw(&player->entity);
}

void playerGetUserMovement(Player* player, Randerer* randerer) {
  if(glfwGetKey(randerer->window.GLFWwindow, GLFW_KEY_W) == GLFW_PRESS)
    entityUpdateMovement(&player->entity, 0.0f, 1.0f);
  if(glfwGetKey(randerer->window.GLFWwindow, GLFW_KEY_S) == GLFW_PRESS)
    entityUpdateMovement(&player->entity, 0.0f, -1.0f);
  if(glfwGetKey(randerer->window.GLFWwindow, GLFW_KEY_D) == GLFW_PRESS)
    entityUpdateMovement(&player->entity, 1.0f, 0.0f);
  if(glfwGetKey(randerer->window.GLFWwindow, GLFW_KEY_A) == GLFW_PRESS)
    entityUpdateMovement(&player->entity, -1.0f, 0.0f);
}
