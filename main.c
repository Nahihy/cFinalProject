#include "2Dframework/entity.h"
#include <2Dframework/2Dframework.h>

int main() {

  Randerer randerer = randererInit("2DframeworkTest", (int[]){800, 600});
  randererSetAutoFrameResizingKeepRatio(&randerer);


  Background bg = createBackground("purpleMountsBackground.jpg", GL_RGB, 0.0f, 1.0f, 1.0f, 0.0f, BG_REPEAT);

  Ground ground = createGround(1);

  groundAdd(&ground, "container.jpg", GL_RGB, GO_SQUARE, 1.0f, 0.0f, 0.5f, 0.5f, 0.0f);
  groundAdd(&ground, "awesomeface.png", GL_RGBA, GO_SQUARE, -1.0f, 0.0f, 0.5f, 0.5f, 45.0f);


  Player player = createPlayer("mario.png", GL_RGBA, 20, 0.01f, 0.01f, (float[2]){0.3333f, 0.3333f}, (TexColumn){0, 1, EN_REPEAT},
                               (TexColumn){1, 3, EN_REPEAT}, (TexColumn){2, 1, EN_REPEAT}, 0.0f, 0.0f, 0.5f, 0.5f);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  while(!randererShouldClose(&randerer)) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    backgroundDraw(&bg);

    groundDraw(&ground);
    playerDraw(&player);
    playerGetUserMovement(&player, &randerer, &ground);
    randererSwapBuffers(&randerer);
  }
  groundDelete(&ground);
  backgroundDelete(&bg);
  playerDelete(&player);
  randererClose(&randerer);

}
