#include "raycast.h"
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdio.h>
#include "../World/world.h"

bool Raycast(Vector3 Origin, Vector3 Direction, int Scale, const World *world, bool debug) {
    for (int s = 1; s < Scale + 1; s++) {
        Vector3 rayFinalPosition = Vector3Add(Origin, Vector3Scale(Direction, s));

        if (debug) {
            printf("RayFinalPosition = %.1f, %.1f, %.1f\n", rayFinalPosition.x, rayFinalPosition.y, rayFinalPosition.z);
        }

        for (int i = 0; i < world->Size; i++) {
            for (int j = 0; j < world->Chunks[i].Size; j++) {
                if (Vector3Equals(world->Chunks[i].Blocks[j].Position, rayFinalPosition) == 1) {
                    if (debug) {
                        printf("Raio atingiu bloco!\n");
                    }

                    return true;
                }
            }
        }
    }
    if (debug) {
        printf("Raio não atingiu bloco.\n");
    }
    return false;
}
