#include "raylib.h"
#include "raymath.h"
#include "game.h"
#include "planet.h"
#include "world.h"
#include "camera.h"
#include "stdlib.h"
#include "ui.h"

Game game_create(void) {
    Game game = {
        .screenWidth = 1920,
        .screenHeight = 1080,
        .game_active = true,

        .camera = create_camera(),
   };

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(game.screenWidth, game.screenHeight, "Orbital Physics Simulator");

    SetTargetFPS(60);
    DisableCursor();

    game.camera = create_camera();
    Planet earth = planet_create("earth", "../assets/graphics/earth.jpg", 10.0f, (Vector3){200.0f, 0.0f, 0.0f}, 32, 32, 1, 0.0f, false);
    Planet sun = planet_create("sun", "../assets/graphics/sun.jpg", 30.0f, (Vector3){0.0f, 0.0f, 0.0f}, 48, 48, 1000, 0.5f, true);
    //game.samriddh = planet_create("../assets/graphics/samriddh.jpeg", 50.0f, (Vector3){0.0f, 200.0f, 0.0f}, 48, 48, 1.989e30f, 0.5f, true);
    //game.test = planet_create("../assets/graphics/samriddh.jpeg", 10.0f, (Vector3){-30.0f, 140.0f, 0.0f}, 48, 48, 1.989e30f, 0.5f, false);

    int capacity = 4;
    int count = 0;    

    Planet* planets = malloc(capacity * sizeof(Planet));

    planets[count++] = earth;
    planets[count++] = sun;
    //planets[count++] = samriddh;
    //planets[count++] = test;

    if(count >= capacity) {
        capacity *= 2;
        planets = realloc(planets, capacity * sizeof(Planet));
    }

    game.world = world_create(planets, count);

    return game;
}

static void enable_cursor(Cam *camera) {
    if (IsKeyPressed(KEY_ENTER)) {
        EnableCursor();
        camera->rotate_active = false;
    } 
    else if (IsKeyPressed(KEY_RIGHT_SHIFT)) {
        DisableCursor();
        camera->rotate_active = true;
    }
}

static void fullscreen() {
    if(IsKeyPressed(KEY_F11) && IsWindowFullscreen() == false) {
        SetWindowMinSize(GetMonitorWidth(0), GetMonitorHeight(0));
        SetWindowState(FLAG_FULLSCREEN_MODE);
    }
    else if(IsKeyPressed(KEY_F11) && IsWindowFullscreen() == true) {
        ClearWindowState(FLAG_FULLSCREEN_MODE);
    }
}

static void game_draw(Game *game) {
    BeginDrawing();
    BeginMode3D(game->camera.camera);
    ClearBackground(BLACK);

    enable_cursor(&game->camera);
    fullscreen();

    world_draw(&game->world);
    world_update(&game->world);

    DrawGrid(1000, 2.0f);
    update_camera(&game->camera);

    EndMode3D();


    DrawFPS(10, 10);
    DrawText(GetMonitorName(0), 10, 40, 20, DARKGREEN);

    ui_draw(&game->world);

    EndDrawing();
}

static void game_update(Game *game)
{
    if (IsKeyPressed(KEY_ESCAPE)) {
        game->game_active = false;
    }
}
void game_run(Game *game) {
    while (game->game_active == true && !WindowShouldClose())
    {
        game_update(game);
        game_draw(game);
    }
    
}
void game_destroy(Game *game) {
    CloseWindow();
    free(game->world.planets);
    game->world.planets = NULL;
}