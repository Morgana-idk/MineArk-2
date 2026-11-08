#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "../sharedLibs/World/world.h"
#include "../sharedLibs/Memoria/memoria.h"

#define screenH 450
#define screenW 800

int main() {q
    const World world = GenerateWorld();
    int blocos = 0;
    
    for (int i = 0; i < world->Size; i++) blocos += world->Chunks[i].Size;

    printf("Worlds: 1\nChunks: %d\nBlocks: %d", world->Size, blocos);

    InitWindow(screenW, screenH, "MineArk 2");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Olá, raylib!", 280, 200, 30, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();

    limparMemoria(&world);

    return 0;
}