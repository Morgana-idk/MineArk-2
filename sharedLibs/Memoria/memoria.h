#ifndef MEMORIA_H
#define MEMORIA_H

#define ACTUAL_TEXTURES 1

#include <raylib.h>

typedef struct World World;

typedef struct {
    Model Models[ACTUAL_TEXTURES];
    Rectangle AtlasUVs[ACTUAL_TEXTURES];
} AtlasInfo;

void limparMemoria(const World *world);

AtlasInfo LoadResources();

AtlasInfo BuildAtlas();

#endif