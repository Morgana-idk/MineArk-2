#ifndef MEMORIA_H
#define MEMORIA_H

#define ACTUAL_TEXTURES 1

#include <raylib.h>
#include "../World/world.h"

typedef struct {
    Model Models[ACTUAL_TEXTURES];
    Rectangle AtlasUVs[ACTUAL_TEXTURES];
} AtlasInfo;

void limparMemoria(const World *world);

AtlasInfo LoadResources();

AtlasInfo BuildAtlas();

#endif