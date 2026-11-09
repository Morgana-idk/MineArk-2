#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>

typedef struct {
    int ID;
    const char *Name;
    Vector3 Position;
    int chunkMom;
} Block;

typedef struct {
    Block *Blocks;
    int Size;
    int ChunkID;
    Vector3 Position;
} Chunk;

typedef struct {
    Chunk *Chunks;
    int Size;
} World;

World GenerateWorld();

Chunk GenerateChunk(int ID, Vector3 Position);

Block GenerateBlock(int ID, Vector3 Position, int ChunkMom);

const char *GetBlockNameByID(int ID);

void DrawWorld(const World *world);

#endif