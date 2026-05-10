#include <2Dframework/entity.h>

#define STAND_ANIM 0
#define WALK_ANIM 1
#define JUMP_ANIM 2
#define TOTAL_ANIM_SIZE 3


typedef struct {
  Entity entity;
  float maxVelocity;
  float accelaration;
  TexColumn animations[TOTAL_ANIM_SIZE];
} Player;


Player createPlayer(const char* image, int colorType, float maxVelocity, float accelaration, float modelSize[2],
                    TexColumn standAnim, TexColumn walkAnim, TexColumn jumpAnim, float xCoord, float yCoord, float width, float height);
void playerDelete(Player* player);
void playerDraw(Player* player);
