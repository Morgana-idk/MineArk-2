#include "ambient.h"
#include "../World/world.h"
#include <raylib.h>
#include <raymath.h>

int CalcAO(Block block, Vector3 Vertex, const World *world) {
    Vector3 BlockPos = block.Position;

    bool side1 = false;
    bool side2 = false;
    bool corner = !GetBlockProperties(world, Vector3Add(BlockPos, Vertex))->IsAir;

    Vector3 side1Pos;
    Vector3 side2Pos;

    // Side1 = <--
    // Side2 = -->
    if (Vector3Equals(Vertex, (Vector3){1, 1, 1}) == 1) { // Vertice Superior Direito Cima
        side1Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){-1, 0, 0}));
        side2Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){0, 0, -1}));

        side1 = !GetBlockProperties(world, side1Pos)->IsAir;
        side2 = !GetBlockProperties(world, side2Pos)->IsAir;
    } else if (Vector3Equals(Vertex, (Vector3){-1, 1, 1}) == 1) { // Vertice Superior Esquerdo Cima
        side1Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){0, 0, -1}));
        side2Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){1, 0, 0}));

        side1 = !GetBlockProperties(world, side1Pos)->IsAir;
        side2 = !GetBlockProperties(world, side2Pos)->IsAir;
    } else if (Vector3Equals(Vertex, (Vector3){-1, 1, -1}) == 1) { // Vertice Superior Esquerdo Baixo
        side1Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){0, 0, 1}));
        side2Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){1, 0, 0}));

        side1 = !GetBlockProperties(world, side1Pos)->IsAir;
        side2 = !GetBlockProperties(world, side2Pos)->IsAir;
    } else if (Vector3Equals(Vertex, (Vector3){1, 1, -1}) == 1) { // Vertice Superior Direito Baixo
        side1Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){-1, 0, 0}));
        side2Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){0, 0, 1}));

        side1 = !GetBlockProperties(world, side1Pos)->IsAir;
        side2 = !GetBlockProperties(world, side2Pos)->IsAir;
    } else if (Vector3Equals(Vertex, (Vector3){1, -1, 1}) == 1) { // Vertice Inferior Direito Cima
        side1Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){-1, 0, 0}));
        side2Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){0, 0, -1}));

        side1 = !GetBlockProperties(world, side1Pos)->IsAir;
        side2 = !GetBlockProperties(world, side2Pos)->IsAir;
    } else if (Vector3Equals(Vertex, (Vector3){-1, -1, 1}) == 1) { // Vertice Inferior Esquerdo Cima
        side1Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){0, 0, -1}));
        side2Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){1, 0, 0}));

        side1 = !GetBlockProperties(world, side1Pos)->IsAir;
        side2 = !GetBlockProperties(world, side2Pos)->IsAir;
    } else if (Vector3Equals(Vertex, (Vector3){-1, -1, -1}) == 1) { // Vertice Inferior Esquerdo Baixo
        side1Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){0, 0, 1}));
        side2Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){1, 0, 0}));

        side1 = !GetBlockProperties(world, side1Pos)->IsAir;
        side2 = !GetBlockProperties(world, side2Pos)->IsAir;
    } else if (Vector3Equals(Vertex, (Vector3){1, -1, -1}) == 1) { // Vertice Inferior Direito Baixo
        side1Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){-1, 0, 0}));
        side2Pos = Vector3Add(BlockPos, Vector3Add(Vertex, (Vector3){0, 0, 1}));

        side1 = !GetBlockProperties(world, side1Pos)->IsAir;
        side2 = !GetBlockProperties(world, side2Pos)->IsAir;
    }

    if (side1 && side2) {
        return 0;
    } else {
        return 3 - (side1 + corner + side2);
    }
}

