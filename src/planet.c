#include "planet.h"
#include "raymath.h"
#include <stdio.h>
#include "raylib.h"

Planet planet_create(char* name, char* texture_path, float radius, Vector3 position, int rings, int slices, float mass, float speed, bool has_gravity) 
{
    Image img = LoadImage(texture_path);
    Planet planet = {
        .texture = LoadTextureFromImage(img),
        .texture_path = texture_path,
        .radius = radius,
        .position = position,
        .rings = rings,
        .slices = slices,
        .mass = mass,
        .has_gravity = has_gravity,
        .perpendicular_direction = (Vector3){0.0f, 0.0f, 0.0f},
        .speed = speed,
        .acceleration = (Vector3){0.0f, 0.0f, 0.0f},
        .velocity = {0.0f, 0.0f, 0.0f},
        .name = name,
    };


    UnloadImage(img);
    SetTextureWrap(planet.texture, TEXTURE_WRAP_CLAMP);
    SetTextureFilter(planet.texture, TEXTURE_FILTER_TRILINEAR);
    
    Mesh mesh = GenMeshSphere(planet.radius, planet.rings, planet.slices);

    planet.model = LoadModelFromMesh(mesh); 
    planet.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = planet.texture;
    planet.model.transform = MatrixRotateY(PI);

    return planet;
}

void remake_model(Planet *planet) {
    UnloadModel(planet->model);
    Image img = LoadImage(planet->texture_path);
    UnloadImage(img);
    SetTextureWrap(planet->texture, TEXTURE_WRAP_CLAMP);
    SetTextureFilter(planet->texture, TEXTURE_FILTER_TRILINEAR);
    
    Mesh mesh = GenMeshSphere(planet->radius, planet->rings, planet->slices);

    planet->model = LoadModelFromMesh(mesh); 
    planet->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = planet->texture;
    planet->model.transform = MatrixRotateY(PI);

}

void planet_draw(Planet *planet)
{
    DrawModel(planet->model, planet->position, 1.0f, WHITE);
}

void planet_update(Planet *planet)
{
    planet->model.transform = MatrixRotateY(GetTime() * 0.1f);
    planet->model.transform = MatrixRotateX(GetTime() * 0.1f);
}