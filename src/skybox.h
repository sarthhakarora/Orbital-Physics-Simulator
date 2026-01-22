#pragma once

#include "raylib.h"

typedef struct {
    Shader shader;
    Mesh cube;
    Model skybox;
} Skybox;

Skybox create_skybox();
void draw_skybox(Skybox *skybox, Camera3D camera);