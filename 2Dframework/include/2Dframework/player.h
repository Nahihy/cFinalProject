#include <2Dframework/entity.h>

#define WALK_ANIM 0
#define JUMP_ANIM 1
#define TOTAL_ANIM_SIZE 2

typedef struct {
  Entity entity;
  float maxVelocity;
  float accelaration;
  TexColumn animations[TOTAL_ANIM_SIZE];
} Player;


Player createPlayer(const char* image, int colorType, float maxVelocity, float accelaration, float modelSize[2], TexColumn walkAnim, TexColumn jumpAnim, float xCoord, float yCoord, float width, float height);

