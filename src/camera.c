#include "camera.h"
#include "raylib.h"
#include "raymath.h"

Cam create_camera(void)
{
    Cam cam = {
        .camera = {
            .position = (Vector3){ 20.0f, 20.0f, 20.0f },
            .target = (Vector3){ 0.0f, 0.0f, 0.0f },
            .up = (Vector3){ 0.0f, 1.0f, 0.0f },
            .fovy = 90.0f,
            .projection = CAMERA_PERSPECTIVE,
        },
        .pitch = 0.0f,
        .yaw = 0.0f,
        .sensitivity = 0.1f,
        .velocity = 2.0f,
        .rotate_active = true,
    };

    cam.forward = (Vector3){0.0f, 0.0f, 0.0f};

    return cam;
}

static void move_camera(Cam *camera)
{

    Vector3 right = Vector3Normalize(Vector3CrossProduct(camera->forward, camera->camera.up));
    Vector3 up = {0.0f, 1.0f, 0.0f};

    if(IsKeyDown(KEY_Q)) {
        camera->velocity += 0.2f;
    }
    if(IsKeyDown(KEY_E)) {
        camera->velocity -= 0.2f;
    }

    if(IsKeyDown(KEY_W)) {
        camera->camera.position = Vector3Add(camera->camera.position, Vector3Scale(camera->forward, camera->velocity));
    }
    if(IsKeyDown(KEY_S)) {
        camera->camera.position = Vector3Subtract(camera->camera.position, Vector3Scale(camera->forward, camera->velocity));
    }
    if(IsKeyDown(KEY_A)) {
        camera->camera.position = Vector3Subtract(camera->camera.position, Vector3Scale(right, camera->velocity));
    }
    if(IsKeyDown(KEY_D)) {
        camera->camera.position = Vector3Add(camera->camera.position, Vector3Scale(right, camera->velocity));
    }
    if(IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_SPACE)) {
        camera->camera.position = Vector3Subtract(camera->camera.position, Vector3Scale(up, camera->velocity));
    }
    else if(IsKeyDown(KEY_SPACE)) {
        camera->camera.position = Vector3Add(camera->camera.position, Vector3Scale(up, camera->velocity));
    }
}

static void rotate_camera(Cam *camera)
{
    Vector2 mouseDelta = GetMouseDelta();

    float sensitivity = 0.001f;
    camera->pitch -=  mouseDelta.y * sensitivity;
    camera->yaw += mouseDelta.x * sensitivity;

    if (camera->pitch >  1.5f) camera->pitch =  1.5f; // Limit pitch to avoid gimbal lock
    if (camera->pitch < -1.5f) camera->pitch = -1.5f; // Limit pitch to avoid gimbal lock

    camera->forward = (Vector3){
        cos(camera->pitch) * cos(camera->yaw),
        sin(camera->pitch),
        cos(camera->pitch) * sin(camera->yaw)
    };

    camera->camera.target = Vector3Add(camera->camera.position, camera->forward);

}

void update_camera(Cam *camera)
{   
    move_camera(camera);
    if(camera->rotate_active) {
        rotate_camera(camera);
    }
}