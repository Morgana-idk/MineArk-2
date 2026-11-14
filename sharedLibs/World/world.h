#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include "../Memoria/memoria.h"
#include "../Ambientocclusion/ambient.h"

typedef struct ShadowedFaces{
    int Top;
    int Bottom;
    int Right;
    int Left;
    int Front;
    int Back;
} ShadowedFaces;

typedef struct Block {
    int ID;
    const char *Name;
    Vector3 Position;
    int chunkMom;
    ShadowedFaces ShadowedFaces;
    bool IsAir;
    AmbientOcclusion AO;
} Block;

typedef struct BlockList {
    Block *Blocks;
    int Size;
} BlockList;

typedef struct Chunk {
    Block *Blocks;
    int Size;
    int ChunkID;
    Vector3 Position;

    Mesh Mesh;
    const World *World;
} Chunk;

typedef struct World {
    Chunk *Chunks;
    int Size;
} World;

World GenerateWorld(AtlasInfo *Atlas);

Chunk GenerateChunk(int ID, Vector3 Position, const World *World);

Block GenerateBlock(int ID, Vector3 Position, int ChunkMom);

const char *GetBlockNameByID(int ID);

void DrawWorld(const World *world, Material *Material);

void IsBlocksShadowed(const World *world, Vector3 lightDir);

Block *GetBlockProperties(const World *world, Vector3 Position);

BlockList GetBlockNeighbors(const World *world, Vector3 Position, bool Corners);

void GenerateChunkMesh(Chunk *Chunk, AtlasInfo *Atlas);

#endif