#include <stdbool.h>
#include "world.h"
#include "../Memoria/memoria.h"
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>

Block Air = (Block){-1, "", {}, -1, {}, true, {}};


const char *GetBlockNameByID(int ID) {
    static const char names[3][20] = {"Grass", "Dirt"};
    return names[ID];
}

Block GenerateBlock(int ID, Vector3 Position, int ChunkMom) {
    AmbientOcclusion AO = (AmbientOcclusion){0};


    return (Block){
        ID,
        GetBlockNameByID(ID),
        Position,
        ChunkMom,
        (ShadowedFaces){0},
        false,
        AO
    };
}

Chunk GenerateChunk(int ID, Vector3 Position, const World *World) {
    Chunk chunk = {0};
    chunk.Blocks = calloc(290, sizeof(Block));
    chunk.Size = 0;
    chunk.ChunkID = ID;
    chunk.Position = Position;
    chunk.World = World;

    for (int x = -8; x < 8; x++) {
        for (int z = -8; z < 8; z++) {
            Vector3 finalPosition = Vector3Add((Vector3){x, 0, z}, Position);

            Block block = GenerateBlock(0, finalPosition, ID);
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

            world.Chunks[world.Size] = GenerateChunk(world.Size, finalPosition, &world);
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


    for (unsigned int i = 0; i < world->Size; i++) {
        for (unsigned int j = 0; j < world->Chunks[i].Size; j++) {

            Block cube = world->Chunks[i].Blocks[j];

            if (!cube.IsAir) {
                SetShaderValue(*Shader, shadowTopLoc, &cube.ShadowedFaces.Top, SHADER_UNIFORM_INT);
                SetShaderValue(*Shader, shadowBottomLoc, &cube.ShadowedFaces.Bottom, SHADER_UNIFORM_INT);
                SetShaderValue(*Shader, shadowRightLoc, &cube.ShadowedFaces.Right, SHADER_UNIFORM_INT);
                SetShaderValue(*Shader, shadowLeftLoc, &cube.ShadowedFaces.Left, SHADER_UNIFORM_INT);
                SetShaderValue(*Shader, shadowFrontLoc, &cube.ShadowedFaces.Front, SHADER_UNIFORM_INT);
                SetShaderValue(*Shader, shadowBackLoc, &cube.ShadowedFaces.Back, SHADER_UNIFORM_INT);

                BeginShaderMode(*Shader);
                    DrawModel(TextureAtlas->Models[cube.ID], cube.Position, 1, WHITE);
                EndShaderMode();
            }
        }
    }

}

void IsBlocksShadowed(const World *world, Vector3 lightDir) {
    for (unsigned int k = 0; k < world->Size; k++) {
        for (unsigned int r = 0; r < world->Chunks[k].Size; r++) {
            Block *actualBlock = &world->Chunks[k].Blocks[r];
            Vector3 actualP = actualBlock->Position;

            for (int i = 0; i < world->Size; i++) {
                for (int j = 0; j < world->Chunks[i].Size; j++) {
                    Block other = world->Chunks[i].Blocks[j];
                    Vector3 otherP = other.Position;

                    if (other.ID != 0) {
                        if (lightDir.x > 0) {
                            if (otherP.x > actualP.x && otherP.y == actualP.y && otherP.z == actualP.z) {
                                actualBlock->ShadowedFaces.Right = 1;
                            }
                        }
                        if (lightDir.x < 0) {
                            if (otherP.x < actualP.x && otherP.y == actualP.y && otherP.z == actualP.z) {
                                actualBlock->ShadowedFaces.Left = 1;
                            }
                        }
                        if (lightDir.y > 0) {
                            if (otherP.y > actualP.y && otherP.x == actualP.x && otherP.z == actualP.z) {
                                actualBlock->ShadowedFaces.Top = 1;
                            }
                        }
                        if (lightDir.y < 0) {
                            if (otherP.y < actualP.y && otherP.x == actualP.x && otherP.z == actualP.z) {
                                actualBlock->ShadowedFaces.Bottom = 1;
                            }
                        }
                        if (lightDir.z > 0) {
                            if (otherP.z > actualP.z && otherP.y == actualP.y && otherP.x == actualP.x) {
                                actualBlock->ShadowedFaces.Front = 1;
                            }
                        }
                        if (lightDir.z < 0) {
                            if (otherP.z < actualP.z && otherP.y == actualP.y && otherP.x == actualP.x) {
                                actualBlock->ShadowedFaces.Back = 1;
                            }
                        }
                    }
                }

            }
        }
    }
}


Block *GetBlockProperties(const World *world, Vector3 Position) {
    for (unsigned int i = 0; i < world->Size; i++) {
        for (unsigned int j = 0; j < world->Chunks[i].Size; j++) {
            if (Vector3Equals(world->Chunks[i].Blocks[j].Position, Position) == 1) {
                return &world->Chunks[i].Blocks[j];
            }
        }
    }

    return &Air;
}

BlockList GetBlockNeighbors(const World *world, Vector3 Position, bool Corners) {
    int index = 0;

    BlockList neighbors = {0};
    neighbors.Blocks = calloc(30, sizeof(Block));

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            for (int z = -1; z <= 1; z++) {

                if (!Corners && !(
                    (x == -1 && y == 0 && z == 0) ||
                    (x == 1 && y == 0 && z == 0) ||
                    (x == 0 && y == -1 && z == 0) ||
                    (x == 0 && y == 1 && z == 0) ||
                    (x == 0 && y == 0 && z == -1) ||
                    (x == 0 && y == 0 && z == 1)
                )) {continue;}

                if (Vector3Equals(Vector3Add(Position, (Vector3){x, y, z}), Position) == 0) {
                    Block *target = GetBlockProperties(world, Vector3Add(Position, (Vector3){x, y, z}));

                    if (!target->IsAir) neighbors.Blocks[index] = *target;

                    index++;
                    neighbors.Size++;
                }
            }
        }
    }

    return neighbors;
}

void GenerateChunkMesh(Chunk *Chunk) {
    int vertexCount = Chunk->Size * 24;
    int indexCount = Chunk->Size * 36;

    Chunk->Mesh.vertexCount = vertexCount;
    Chunk->Mesh.triangleCount = indexCount / 3;

    Chunk->Mesh.vertices = calloc(vertexCount * 3, sizeof(float));
    Chunk->Mesh.texcoords = calloc(vertexCount * 2, sizeof(float));
    Chunk->Mesh.normals = calloc(vertexCount * 3, sizeof(float));
    Chunk->Mesh.colors = calloc(vertexCount * 4, sizeof(unsigned char));
    Chunk->Mesh.indices = calloc(indexCount, sizeof(unsigned short));


    for (unsigned int i = 0; i < Chunk->Size; i++) {
        Block *block = &Chunk->Blocks[i];

        // VERTEX ------------------------------

        // UP ^^^^^
        Vector3 Vertex0 = Vector3Add(block->Position, (Vector3){0.5, 0.5, 0.5}); // X + Y + Z +
        Vector3 Vertex1 = Vector3Add(block->Position, (Vector3){-0.5, 0.5, 0.5}); // X - Y + Z +
        Vector3 Vertex2 = Vector3Add(block->Position, (Vector3){-0.5, 0.5, -0.5}); // X - Y + Z -
        Vector3 Vertex3 = Vector3Add(block->Position, (Vector3){0.5, 0.5, -0.5}); // X + Y + Z -
        Vector3 Vertex4 = Vector3Add(block->Position, (Vector3){0.5, -0.5, 0.5}); // X + Y - Z +
        Vector3 Vertex5 = Vector3Add(block->Position, (Vector3){-0.5, -0.5, 0.5}); // X - Y - Z +
        Vector3 Vertex6 = Vector3Add(block->Position, (Vector3){-0.5, -0.5, -0.5}); // X - Y - Z -
        Vector3 Vertex7 = Vector3Add(block->Position, (Vector3){0.5, -0.5, -0.5}); // X + Y - Z -

        Vector3 faceVertices[6][4] = {
            // UP
            {Vertex0, Vertex1, Vertex2, Vertex3},

            // DOWN
            {Vertex4, Vertex5, Vertex6, Vertex7},

            // FRONT
            {Vertex0, Vertex1, Vertex4, Vertex5},

            // BACK
            {Vertex2, Vertex3, Vertex6, Vertex7},

            // RIGHT
            {Vertex0, Vertex3, Vertex4, Vertex7},

            // LEFT
            {Vertex1, Vertex2, Vertex5, Vertex6}
        };

        for (unsigned int face = 0; face < 6; face++) {
            for (unsigned int vertex = 0; vertex < 4; vertex++) {
                unsigned int vertexIndex = face * 4 + vertex;
                unsigned int index = (i * 24 + vertexIndex) * 3;

                Chunk->Mesh.vertices[index] = faceVertices[face][vertex].x;
                Chunk->Mesh.vertices[index + 1] = faceVertices[face][vertex].y;
                Chunk->Mesh.vertices[index + 2] = faceVertices[face][vertex].z;
            }
        }

        // INDEX --------------------------------
        unsigned char faceIndices[6] = {
            0, 1, 2,
            0, 2, 3,
        };

        for (unsigned char face = 0;  face < 6; face++) {
            unsigned int firstVertex = i * 24 + face * 4;

            for (unsigned int j = 0; j < 6; j++) {
                Chunk->Mesh.indices[i * 36 + face * 6 + j] = firstVertex + faceIndices[j];
            }
        }

    }
}