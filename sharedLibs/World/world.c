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
        ChunkMom,
        false
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

void DrawWorld(const World *world, Shader *Shader) {

    for (int i = 0; i < world->Size; i++) {
        for (int j = 0; j < world->Chunks[i].Size; j++) {

            Block cube = world->Chunks[i].Blocks[j];

            if (cube.ID == 2) {
                if (!cube.IsShadowed) {
                    DrawCube(cube.Position, 1, 1, 1, GREEN);
                } else {
                    EndShaderMode();
                        DrawCube(cube.Position, 1, 1, 1, (Color){10, 60, 10, 255});
                    BeginShaderMode(*Shader);
                }
            }
        }
    }

}

void IsBlocksShadowed(const World *world) {
    for (int k = 0; k < world->Size; k++) {
        for (int r = 0; r < world->Chunks[k].Size; r++) {
            Block *actualBlock = &world->Chunks[k].Blocks[r];
            bool isShadow = false;

            for (int i = 0; i < world->Size; i++) {
                for (int j = 0; j < world->Chunks[i].Size; j++) {
                    Block other = world->Chunks[i].Blocks[j];

                    if (other.ID != 0 && other.Position.x == actualBlock->Position.x && other.Position.z == actualBlock->Position.z && other.Position.y > actualBlock->Position.y) {
                        isShadow = true;
                        break;
                    }
                }

                if (isShadow) break;
            }

            actualBlock->IsShadowed = isShadow;
        }
    }
}