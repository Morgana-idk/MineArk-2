#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "world.h"


const char *GetBlockNameByID(int ID) {
    static const char names[3][20] = {"Air", "Dirt", "Grass"};
    return names[ID];
}

Block GenerateBlock(int ID, Vector3 Position, int ChunkMom) {
    return (Block){
        ID,
        GetBlockNameByID(ID),
        Position,
        ChunkMom
    };
}

Chunk GenerateChunk(int ID) {
    Chunk chunk = {0};
    chunk.Blocks = calloc(290, sizeof(Block));
    chunk.Size = 0;
    chunk.ChunkID = ID;

    for (int x = -8; x < 8; x++) {
        for (int z = -8; z < 8; z++) {
            Block block = GenerateBlock(2, (Vector3){x, 0, z}, ID);
            chunk.Blocks[chunk.Size] = block;
            chunk.Size++;
        }
    }

    return chunk;
}

World GenerateWorld() {
    World world = {0};
    world.Chunks = calloc(20, sizeof(Chunk));
    world.Size = 0;

    world.Chunks[0] = GenerateChunk(world.Size);
    world.Size++;

    return world;
}
