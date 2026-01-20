#include <stdio.h>
#include "raylib.h"
#include "game.h"

int main(void) {
    Game game = game_create();
    game_run(&game);
    game_destroy(&game);
    return 0;
}