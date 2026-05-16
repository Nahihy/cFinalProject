#pragma once
#include <2Dframework/ground.h>
#include <2Dframework/background.h>

typedef struct {
  Background bg;
  Ground ground;
  int gravityLevel[2];
  float playerSpawn[2];
} World;

World createWorld(Background bg, int initGroundCount, int gravityLevel[2], float playerSpawn[2]);
void worldDelete(World* world);
void worldDraw(World* world);
