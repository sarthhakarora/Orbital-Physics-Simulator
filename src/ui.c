#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "raylib.h"

#include "ui.h"
#include "world.h"
#include "planet.h"

static void styling() {
    // Global
    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, 0x1E1E1ECC);
    GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, 0x25252FF);
    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, 0x25252FF);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0xDADADAFF);
    GuiSetStyle(DEFAULT, TEXT_COLOR_DISABLED, 0x7A7A7AFF);

    // Window / status bar
    GuiSetStyle(STATUSBAR, BACKGROUND_COLOR, 0x2A2A2AFF);
    GuiSetStyle(STATUSBAR, TEXT_COLOR_NORMAL, 0xFFFFFFFF);
    GuiSetStyle(STATUSBAR, BORDER_WIDTH, 1);

    // Buttons
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x313131FF);
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0x3E3E3EFF);
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0x4A4A4AFF);
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x5A5A5AFF);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xFFFFFFFF);

    // Sliders
    GuiSetStyle(SLIDER, BASE_COLOR_NORMAL, 0x313131FF);
    GuiSetStyle(SLIDER, BASE_COLOR_FOCUSED, 0x3E3E3EFF);
    GuiSetStyle(SLIDER, BORDER_COLOR_NORMAL, 0x5A5A5AFF);

    // Textboxes
    GuiSetStyle(TEXTBOX, BASE_COLOR_NORMAL, 0x1E1E1EFF);
    GuiSetStyle(TEXTBOX, BORDER_COLOR_NORMAL, 0x5A5A5AFF);
    GuiSetStyle(TEXTBOX, TEXT_COLOR_NORMAL, 0xFFFFFFFF);

    // Checkboxes
    GuiSetStyle(CHECKBOX, BASE_COLOR_NORMAL, 0x313131FF);
    GuiSetStyle(CHECKBOX, BORDER_COLOR_NORMAL, 0x5A5A5AFF);

    // General spacing
    GuiSetStyle(DEFAULT, BORDER_WIDTH, 1);
    GuiSetStyle(DEFAULT, TEXT_PADDING, 6);

}

static void slider(float *val, float min, float max, char text[], char righttext[], int row, Rectangle content, bool percentage_mode) {
    char label[128];
    if(percentage_mode) {
        snprintf(label, sizeof(label),"%s = %.2f%%", text, (*val) * 100);
    }
    if(!percentage_mode) {
        snprintf(label, sizeof(label),"%s = %.2f", text, (*val));
    }
    char right_label[128];
    snprintf(right_label, sizeof(right_label),"%s ", righttext);

    float y = content.y + row * 60;
    
    GuiLabel((Rectangle){content.x, y, 300, 20}, label);
    GuiSlider((Rectangle){content.x, y + 25, content.width, 20}, right_label, NULL, val, min, max);

}

void ui_draw(World *world){
    styling();

    Rectangle window = {
        GetScreenWidth() - 300,
        0, 
        300, 
        GetScreenHeight()
    };
    static bool windowOpen = true;

    if(!windowOpen) return;

    windowOpen = !GuiWindowBox(window, "Simulation Contorls");

    Rectangle content = {
        window.x + 10,
        window.y + 30,
        window.width - 20,
        window.height - 40
    };


    slider(&world->gravity_strength, 30.0f, 100.0f, "Gravity", NULL, 1, content, false);
    slider(&world->deltaTime, 0.0f, 2.0f, "Time Speed", NULL, 2, content, true);

    world->count_g = 0;
    world->count_ng = 0;

    for (int i = 0; i < world->planet_count; i++) {
        planet_update(&world->planets[i]); // This is visual only
        if(world->planets[i].has_gravity == true) {
            world->gravity_planet_indexs[world->count_g++] = i;
        }

        if(world->planets[i].has_gravity == false) {
            world->non_gravity_planet_indexs[world->count_ng++] = i;
        }
    }

    for(int j = 0; j < world->count_g; j++) {
        int g = world->gravity_planet_indexs[j];

        float last_radius = world->planets[g].radius;

        slider(&world->planets[g].mass, 0.0f, 10000.0f, world->planets[g].name, "mass", j + 3, content, false);
        slider(&world->planets[g].radius, 0.0f, 1000.0f, world->planets[g].name, "radius", j + 4, content, false);

        if(last_radius != world->planets[g].radius) {
            remake_model(&world->planets[g]);
        }
    }
    for(int i = 0; i < world->count_ng; i++) {
    }
}
void ui_update(void) {
}