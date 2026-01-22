#pragma once

#include "raylib.h"

#include "camera.h"
#include "world.h"
#include "skybox.h"
#include "planet.h"

typedef struct {
    const int screenWidth;
    const int screenHeight;   
    bool game_active;

    Cam camera;
    World world;

    Skybox skybox;
    
} Game;


Game game_create(void);
void game_run(Game *game);
void game_destroy(Game *game);