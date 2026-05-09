#include <2Dframework/2Dframework.h>
#include <stdio.h>

int main() {

  Randerer randerer = randererInit("2DframeworkTest", (int[]){800, 600});
  randererSetAutoFrameResizingKeepRatio(&randerer);


  Background bg = createBackground("purpleMountsBackground.jpg", GL_RGB, 0.0f, 1.0f, 1.0f, 0.0f, BG_REPEAT);

  TexColumn columns[3] = {
    {0, 1, EN_MIRROR},
    {1, 3, EN_MIRROR},
    {2, 1, EN_MIRROR}
  };

  ModelAttrib model = {
    {0.3333f, 0.3333f},
    columns,
    3,
    0,
    1
  };

  Entity entity = createEntity("mario.png", GL_RGBA, &model, EN_USE_COLLISION, 0.0f, 0.0f, 0.5f, 0.5f);
  entityChangeTexColumn(&entity, 1);
  entityNextTex(&entity);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  while(!randererShouldClose(&randerer)) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    backgroundDraw(&bg);

    entityDraw(&entity);

    randererSwapBuffers(&randerer);
  }

  entityDelete(&entity);
  randererClose(&randerer);

}
