#include <stdio.h>
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include "../sharedLibs/World/world.h"
#include "../sharedLibs/Memoria/memoria.h"

#define screenH 450
#define screenW 800

#define SHADOWMAP_RESOLUTION 1024

RenderTexture2D LoadShadowmapRenderTexture(int width, int height) {
    RenderTexture2D target = {0};

    target.id = rlLoadFramebuffer();

    target.texture.width = width;
    target.texture.height = height;

    if (target.id > 0) {
        rlEnableFramebuffer(target.id);

        target.depth.id = rlLoadTextureDepth(width, height, false);
        target.depth.width = width;
        target.depth.height = height;
        target.depth.format = 19;
        target.depth.mipmaps = 1;

        rlFramebufferAttach(
            target.id,
            target.depth.id,
            RL_ATTACHMENT_DEPTH,
            RL_ATTACHMENT_TEXTURE2D,
            0
        );

        rlDisableFramebuffer();
    }

    return target;
}

void UnloadShadowmapRenderTexture(RenderTexture2D target) {
    if (target.id > 0) {
        rlUnloadFramebuffer(target.id);
    }
}


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

       // ---------------------------SOMBRAS -- (CHATGPT) -----------------------------------------------------------

    Shader shadowShader = LoadShader("shaders/glsl330/shadowmap.vs", "shaders/glsl330/shadowmap.fs");
    Vector3 lightDir = Vector3Normalize((Vector3){0.35f, -1.0f, -0.35f});
    Vector4 lightColor = (Vector4){1, 1, 1, 1};
    Vector4 ambient = (Vector4){0.25f, 0.25f, 0.25f, 1};

    int lightDirLoc = GetShaderLocation(shadowShader, "lightDir");
    int lightColorLoc = GetShaderLocation(shadowShader, "lightColor");
    int ambientLoc = GetShaderLocation(shadowShader, "ambient");

    SetShaderValue(shadowShader, lightDirLoc, &lightDir, SHADER_UNIFORM_VEC3);
    SetShaderValue(shadowShader, lightColorLoc, &lightColor, SHADER_UNIFORM_VEC4);
    SetShaderValue(shadowShader, ambientLoc, &ambient, SHADER_UNIFORM_VEC4);

    Camera3D lightCamera = {0};

    lightCamera.position = Vector3Scale(lightDir, -60);
    lightCamera.target = (Vector3){0, 0, 0};
    lightCamera.up = (Vector3){0, 1, 0};
    lightCamera.projection = CAMERA_ORTHOGRAPHIC;
    lightCamera.fovy = 70;

    RenderTexture2D shadowMap = LoadShadowmapRenderTexture(SHADOWMAP_RESOLUTION, SHADOWMAP_RESOLUTION);

    int lightVPLoc = GetShaderLocation(shadowShader, "lightVP");
    int shadowMapLoc = GetShaderLocation(shadowShader, "shadowMap");
    int shadowResolutionLoc = GetShaderLocation(shadowShader, "shadowMapResolution");

    SetShaderValue(shadowShader, shadowResolutionLoc, &(int){SHADOWMAP_RESOLUTION}, SHADER_UNIFORM_INT);
    
    int textureSlot = 10;
    
    // ---------------------------SOMBRAS -- (CHATGPT) -----------------------------------------------------------


    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginTextureMode(shadowMap);
            ClearBackground(WHITE);

            BeginMode3D(lightCamera);

                Matrix lightView = rlGetMatrixModelview();
                Matrix lightProj = rlGetMatrixProjection();

                DrawWorld(&world);

            EndMode3D();
        EndTextureMode();

        Matrix lightVP = MatrixMultiply(lightView, lightProj);


        BeginDrawing();
            ClearBackground(BLACK);
            SetShaderValueMatrix(shadowShader, lightVPLoc, lightVP);
            SetShaderValue(shadowShader, GetShaderLocation(shadowShader, "viewPos"), &camera.position, SHADER_UNIFORM_VEC3);
            BeginShaderMode(shadowShader);
            rlActiveTextureSlot(textureSlot);
            rlEnableTexture(shadowMap.depth.id);


            rlSetUniform(shadowMapLoc, &textureSlot, SHADER_UNIFORM_INT, 1);

            BeginMode3D(camera);

                DrawWorld(&world);

                DrawGrid(30, 1.0f);

            EndMode3D();

            DrawText(worldInfo, 50 / 2, 50 / 2, 24, WHITE);

            EndShaderMode();

        EndDrawing();
    }

    CloseWindow();

    limparMemoria(&world);

    UnloadShader(shadowShader);
    UnloadShadowmapRenderTexture(shadowMap);

    return 0;
}