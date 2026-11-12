#include <stdio.h>
#include <raymath.h>
#include <raylib.h>
#include "../sharedLibs/World/world.h"
#include "../sharedLibs/Memoria/memoria.h"

#define screenH 450
#define screenW 800

int main() {
    const World world = GenerateWorld();
    int blocos = 0;

    for (int i = 0; i < world.Size; i++) blocos += world.Chunks[i].Size;
    char worldInfo[50];

    snprintf(worldInfo, sizeof(worldInfo), "Worlds: 1\nChunks: %d\nBlocks: %d", world.Size, blocos);

    Camera3D camera = {0};
    camera.position = (Vector3){0, 0, 0};
    camera.target = (Vector3){0, 0, 1};
    camera.up = (Vector3){0, 1, 0};

    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    InitWindow(screenW, screenH, "MineArk 2");
    SetTargetFPS(60);

    Shader lighthing = LoadShader("shaders/glsl330/lighting.vs", "shaders/glsl330/lighting.fs");
    Vector3 lightDir = (Vector3){0.5f, 1.0f, 0.3f};

    int lightDirLoc = GetShaderLocation(lighthing, "lightDir");

    SetShaderValue(lighthing, lightDirLoc, &lightDir, SHADER_UNIFORM_VEC3);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
            UpdateCamera(&camera, CAMERA_FREE);

            BeginShaderMode(lighthing);
                DrawWorld(&world);

            EndShaderMode();

            DrawGrid(30, 1);

        EndMode3D();

        DrawText(worldInfo, 50 / 2, 50 / 2, 24, WHITE);

        EndDrawing();
    }

    CloseWindow();

    UnloadShader(lighthing);
    limparMemoria(&world);

    return 0;
}