#include "2Dframework/entity.h"
#include <2Dframework/2Dframework.h>

int main() {

  Randerer randerer = randererInit("2DframeworkTest", (int[]){800, 600});
  randererSetAutoFrameResizingKeepRatio(&randerer);


  Background bg = createBackground("purpleMountsBackground.jpg", GL_RGB, 0.0f, 1.0f, 1.0f, 0.0f, BG_REPEAT);


  Player player = createPlayer("mario.png", GL_RGBA, 0.005f, 0.0001f, (float[2]){0.3333f, 0.3333f},
                               (TexColumn){0, 1, EN_REPEAT}, (TexColumn){1, 3, EN_REPEAT}, (TexColumn){2, 1, EN_REPEAT}, 0.0f, 0.0f, 0.5f, 0.5f);
  entityChangeTexColumn(&player.entity, 1);
  entityNextTex(&player.entity);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  while(!randererShouldClose(&randerer)) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    backgroundDraw(&bg);

    float deltaTime = randererGetDeltaTime(&randerer);

    playerDraw(&player);
    entityUpdateMovement(&player.entity, 0.0000001f * deltaTime, 0.0f);
    entityNextTex(&player.entity);
    randererSwapBuffers(&randerer);
  }

    playerDelete(&player);
  randererClose(&randerer);

}
