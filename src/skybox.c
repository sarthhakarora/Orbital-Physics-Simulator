#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include "skybox.h"

Skybox create_skybox()
{
    Skybox skybox = {
        .shader = LoadShader(
            "../assets/shaders/star_skybox.vs",
            "../assets/shaders/star_skybox.fs"
        ),
        .cube = GenMeshCube(1.0f, 1.0f, 1.0f),
    };
    
    skybox.skybox = LoadModelFromMesh(skybox.cube);

    skybox.skybox.materials[0].shader = skybox.shader;

    return skybox;
}


void draw_skybox(Skybox *skybox, Camera3D camera)
{
    Matrix view = GetCameraMatrix(camera);
    Matrix proj = MatrixPerspective(
        camera.fovy * DEG2RAD,
        (float)GetScreenWidth() / GetScreenHeight(),
        0.1f,
        1000.0f
    );

    SetShaderValueMatrix(skybox->shader,
        GetShaderLocation(skybox->shader, "matView"),
        view);

    SetShaderValueMatrix(skybox->shader,
        GetShaderLocation(skybox->shader, "matProjection"),
        proj);
    
    rlDisableBackfaceCulling();
    rlDisableDepthMask();
    DrawModel(skybox->skybox, (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
    rlEnableDepthMask();
    rlEnableBackfaceCulling();
}