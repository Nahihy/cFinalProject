#include <2Dframework/player.h>

Player createPlayer(const char* image, int colorType, int animationDelay, float maxVelocity, float accelaration, float modelSize[2],
                    TexColumn standAnim, TexColumn walkAnim, TexColumn jumpAnim, float xCoord, float yCoord, float width, float height) {
  Player player;
  player.animations[STAND_ANIM] = standAnim;
  player.animations[WALK_ANIM] = walkAnim;
  player.animations[JUMP_ANIM] = jumpAnim;
  player.animationDelay = animationDelay;
  player.delayToNextTex = animationDelay;
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

void playerGetUserMovement(Player* player, Randerer* randerer, Ground* ground) {
  int wPressed = glfwGetKey(randerer->window.GLFWwindow, GLFW_KEY_W) == GLFW_PRESS;
  int sPressed = glfwGetKey(randerer->window.GLFWwindow, GLFW_KEY_S) == GLFW_PRESS;
  int dPressed = glfwGetKey(randerer->window.GLFWwindow, GLFW_KEY_D) == GLFW_PRESS;
  int aPressed = glfwGetKey(randerer->window.GLFWwindow, GLFW_KEY_A) == GLFW_PRESS;
  
  entityUpdateMovement(&player->entity, 0.0f, 0.0f, ground);

  if(!wPressed && !sPressed && !dPressed && !aPressed) {
    entityChangeTexColumn(&player->entity, STAND_ANIM);
    player->delayToNextTex = player->animationDelay;
    return;
  }
  entityChangeTexColumn(&player->entity, WALK_ANIM);
  if(player->delayToNextTex <= 0) entityNextTex(&player->entity);
  else player->delayToNextTex--;

  if(wPressed) {
    entityUpdateMovement(&player->entity, 0.0f, 1.0f, ground);
    if(groundCheckCollision(ground, &player->entity.obj)) entityUpdateMovement(&player->entity, 0.0f, -1.0f, ground);
  }
  if(sPressed) {
    entityUpdateMovement(&player->entity, 0.0f, -1.0f, ground);
    if(groundCheckCollision(ground, &player->entity.obj)) entityUpdateMovement(&player->entity, 0.0f, 1.0f, ground);
  }
  if(dPressed) {
    entityUpdateMovement(&player->entity, 1.0f, 0.0f, ground);
    if(groundCheckCollision(ground, &player->entity.obj)) entityUpdateMovement(&player->entity, -1.0f, 0.0f, ground);
  }
  if(aPressed) {
    entityUpdateMovement(&player->entity, -1.0f, 0.0f, ground);
    if(groundCheckCollision(ground, &player->entity.obj)) entityUpdateMovement(&player->entity, 1.0f, 0.0f, ground);
  }
}
