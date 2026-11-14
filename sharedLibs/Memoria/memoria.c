#include "memoria.h"
#include <raylib.h>
#include <stdlib.h>
#include "../World/world.h"


#define ACTUAL_TEXTURES 2

bool AtlasCarregado = false;

void limparMemoria(const World *world) {
    for (int i = 0; i < world->Size; i++) {
        free(world->Chunks[i].Blocks);
    }
}

AtlasInfo BuildAtlas() {
    return (AtlasInfo){0};
}

AtlasInfo LoadResources() {
    if (AtlasCarregado) return (AtlasInfo){0};

    AtlasInfo Atlas = BuildAtlas();

    Image atlasImagem = GenImageColor(256, 256, BLACK);

    int posX = 0, posY = 0, tile = 16;

    char *texturesLoc[ACTUAL_TEXTURES] = {
        "../Assets/Textures/Blocks/Grass/grass.png",
        "../Assets/Textures/Blocks/Dirt/dirt.png"
    };

    for (int i = 0; i < ACTUAL_TEXTURES; i++) {
        Image img = LoadImage(texturesLoc[i]);

        if (img.data == NULL) {
            img = GenImageColor(1, 1, WHITE);
        }

        posX = (i % (256 / tile)) * tile;
        posY = (i / (256 / tile)) * tile;

        ImageDrawImage(&atlasImagem, img, posX, posY, WHITE);

        Atlas.AtlasUVs[i] = (Rectangle){posX, posY, img.width, img.height};

        Model textureModel = LoadModelFromMesh(GenMeshCube(1, 1, 1));
        textureModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTextureFromImage(img);

        Atlas.Models[i] = textureModel;

        UnloadImage(img);
    }

    Atlas.TextureAtlas = LoadTextureFromImage(atlasImagem);

    UnloadImage(atlasImagem);

    AtlasCarregado = true;

    return Atlas;
}
