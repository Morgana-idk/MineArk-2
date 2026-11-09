#include <stdlib.h>
#include <raylib.h>
#include "world.h"
#include <raymath.h>


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

Chunk GenerateChunk(int ID, Vector3 Position) {
    Chunk chunk = {0};
    chunk.Blocks = calloc(290, sizeof(Block));
    chunk.Size = 0;
    chunk.ChunkID = ID;
    chunk.Position = Position;

    for (int x = -8; x < 8; x++) {
        for (int z = -8; z < 8; z++) {
            Vector3 finalPosition = Vector3Add((Vector3){x, 0, z}, Position);

            Block block = GenerateBlock(2, finalPosition, ID);
            chunk.Blocks[chunk.Size] = block;
            chunk.Size++;
        }
    }

    return chunk;
}

World GenerateWorld() {
    World world = {0};
    world.Chunks = calloc(50, sizeof(Chunk));
    world.Size = 0;

    for (int x = -1; x <= 1; x++) {
        for (int z = -1; z <= 1; z++) {

            Vector3 finalPosition = {
                x * 16,
                0,
                z * 16
            };

            world.Chunks[world.Size] = GenerateChunk(world.Size, finalPosition);
            world.Size++;
        }
    }

    return world;
}
