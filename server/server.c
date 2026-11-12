#include <stdbool.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include "../sharedLibs/World/world.h"
#include "../sharedLibs/Memoria/memoria.h"
#include "../sharedLibs/Raycast/raycast.h"

#define screenH 450
#define screenW 800

int main() {
    const World world = GenerateWorld();
    world.Chunks[0].Blocks[world.Chunks[0].Size] = GenerateBlock(1, (Vector3){0, 2, 0}, 0);
    world.Chunks[0].Size++;
    world.Chunks[0].Blocks[world.Chunks[0].Size] = GenerateBlock(1, (Vector3){0, 4, 0}, 0);
    world.Chunks[0].Size++;

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

    AtlasInfo TextureAtlas = LoadResources();

    Shader lighthing = LoadShader("shaders/glsl330/lighting.vs", "shaders/glsl330/lighting.fs");

    for (int i = 0; i < ACTUAL_TEXTURES; i++) {
        TextureAtlas.Models[i].materials[0].shader = lighthing;
    }

    Vector3 lightDir = (Vector3){0, 1, 0};

    int lightDirLoc = GetShaderLocation(lighthing, "lightDir");

    SetShaderValue(lighthing, lightDirLoc, &lightDir, SHADER_UNIFORM_VEC3);


    IsBlocksShadowed(&world, lightDir);

    Raycast((Vector3){7, 4, 0}, (Vector3){-1, 0, 0}, 7, &world, true);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground((Color){120, 167, 255, 255});

        BeginMode3D(camera);
            UpdateCamera(&camera, CAMERA_FREE);
    
            DrawWorld(&world, &lighthing, &TextureAtlas);

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