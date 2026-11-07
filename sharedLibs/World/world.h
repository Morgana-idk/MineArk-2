#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>

typedef struct {
    int ID;
    char *Name;
    Vector3 Position;
    int chunkMom;
} Block;

typedef struct {
    Block *Blocks;
    size_t Size;
    int ChunkID;
} Chunk;

typedef struct {
    Chunk *Chunks;
    size_t Size;
} World;

World GenerateWorld();

Chunk GenerateChunk();

Block GenerateBlock(int ID);

char *GetBlockNameByID(int ID);

#endif