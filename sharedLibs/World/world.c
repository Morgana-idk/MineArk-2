#include <stdbool.h>
#include "world.h"
#include "../Memoria/memoria.h"
#include <stdlib.h>
#include <raylib.h>
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
        (ShadowedFaces){0}
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

void DrawWorld(const World *world, Shader *Shader, AtlasInfo *TextureAtlas) {

    int shadowTopLoc = GetShaderLocation(*Shader, "shadowTop");
    int shadowBottomLoc = GetShaderLocation(*Shader, "shadowBottom");
    int shadowRightLoc = GetShaderLocation(*Shader, "shadowRight");
    int shadowLeftLoc = GetShaderLocation(*Shader, "shadowLeft");
    int shadowFrontLoc = GetShaderLocation(*Shader, "shadowFront");
    int shadowBackLoc = GetShaderLocation(*Shader, "shadowBack");


    for (int i = 0; i < world->Size; i++) {
        for (int j = 0; j < world->Chunks[i].Size; j++) {

            Block cube = world->Chunks[i].Blocks[j];

            if (cube.ID != 0) {
                SetShaderValue(*Shader, shadowTopLoc, &cube.ShadowedFaces.Top, SHADER_UNIFORM_INT);
                SetShaderValue(*Shader, shadowBottomLoc, &cube.ShadowedFaces.Bottom, SHADER_UNIFORM_INT);
                SetShaderValue(*Shader, shadowRightLoc, &cube.ShadowedFaces.Right, SHADER_UNIFORM_INT);
                SetShaderValue(*Shader, shadowLeftLoc, &cube.ShadowedFaces.Left, SHADER_UNIFORM_INT);
                SetShaderValue(*Shader, shadowFrontLoc, &cube.ShadowedFaces.Front, SHADER_UNIFORM_INT);
                SetShaderValue(*Shader, shadowBackLoc, &cube.ShadowedFaces.Back, SHADER_UNIFORM_INT);

                BeginShaderMode(*Shader);
                    DrawCube(cube.Position, 1, 1, 1, GREEN);
                EndShaderMode();
            }
        }
    }

}

void IsBlocksShadowed(const World *world, Vector3 lightDir) {
    for (int k = 0; k < world->Size; k++) {
        for (int r = 0; r < world->Chunks[k].Size; r++) {
            Block *actualBlock = &world->Chunks[k].Blocks[r];
            Vector3 actualP = actualBlock->Position;

            for (int i = 0; i < world->Size; i++) {
                for (int j = 0; j < world->Chunks[i].Size; j++) {
                    Block other = world->Chunks[i].Blocks[j];
                    Vector3 otherP = other.Position;

                    if (other.ID != 0) {
                        if (lightDir.x > 0) {
                            if (otherP.x > actualP.x && otherP.y == actualP.y && otherP.z == actualP.z) {
                                actualBlock->ShadowedFaces.Right = true;
                            }
                        }
                        if (lightDir.x < 0) {
                            if (otherP.x < actualP.x && otherP.y == actualP.y && otherP.z == actualP.z) {
                                actualBlock->ShadowedFaces.Left = true;
                            }
                        }
                        if (lightDir.y > 0) {
                            if (otherP.y > actualP.y && otherP.x == actualP.x && otherP.z == actualP.z) {
                                actualBlock->ShadowedFaces.Top = true;
                            }
                        }
                        if (lightDir.y < 0) {
                            if (otherP.y < actualP.y && otherP.x == actualP.x && otherP.z == actualP.z) {
                                actualBlock->ShadowedFaces.Bottom = true;
                            }
                        }
                        if (lightDir.z > 0) {
                            if (otherP.z > actualP.z && otherP.y == actualP.y && otherP.x == actualP.x) {
                                actualBlock->ShadowedFaces.Front = true;
                            }
                        }
                        if (lightDir.z < 0) {
                            if (otherP.z < actualP.z && otherP.y == actualP.y && otherP.x == actualP.x) {
                                actualBlock->ShadowedFaces.Back = true;
                            }
                        }
                    }
                }

            }
        }
    }
}


/*  else {
                    EndShaderMode();

                    SetShaderValue(*Shader, shadowLoc, &shadow, SHADER_UNIFORM_INT);

                    BeginShaderMode(*Shader);

                    DrawCube(cube.Position, 1, 1, 1, GREEN);

                    EndShaderMode();

                    SetShaderValue(*Shader, shadowLoc, &unshadow, SHADER_UNIFORM_INT);

                    BeginShaderMode(*Shader);

                }
                    
                
if (!cube.ShadowedFaces.Top && !cube.ShadowedFaces.Bottom && !cube.ShadowedFaces.Left && !cube.ShadowedFaces.Right && !cube.ShadowedFaces.Front && !cube.ShadowedFaces.Back) {
                    DrawCube(cube.Position, 1, 1, 1, GREEN);
                }
                
                
*/