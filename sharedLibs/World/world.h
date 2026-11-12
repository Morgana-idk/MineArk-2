#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include "../Memoria/memoria.h"

typedef  struct {
    int Top;
    int Bottom;
    int Right;
    int Left;
    int Front;
    int Back;
} ShadowedFaces;

typedef struct {
    int ID;
    const char *Name;
    Vector3 Position;
    int chunkMom;
    ShadowedFaces ShadowedFaces;
    bool IsAir;
} Block;

typedef struct {
    Block *Blocks;
    int Size;
    int ChunkID;
    Vector3 Position;
} Chunk;

typedef struct World {
    Chunk *Chunks;
    int Size;
} World;

World GenerateWorld();

Chunk GenerateChunk(int ID, Vector3 Position);

Block GenerateBlock(int ID, Vector3 Position, int ChunkMom);

const char *GetBlockNameByID(int ID);

void DrawWorld(const World *world, Shader *Shader, AtlasInfo *TextureAtlas);

void IsBlocksShadowed(const World *world, Vector3 lightDir);

Block *GetBlockProperties(const World *world, Vector3 Position);

#endif