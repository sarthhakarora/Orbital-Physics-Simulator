#pragma once

#include "camera.h"
#include "raylib.h"
#include "world.h"
#include "planet.h"

typedef struct {
    const int screenWidth;
    const int screenHeight;   
    bool game_active;

    Cam camera;
    World world;

    
} Game;


Game game_create(void);
void game_run(Game *game);
void game_destroy(Game *game);