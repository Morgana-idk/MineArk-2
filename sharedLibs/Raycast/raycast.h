#ifndef RAYCAST_H
#define RAYCAST_H
#include <raylib.h>
#include <stdbool.h>
#include "../World/world.h"

bool Raycast(Vector3 Origin, Vector3 Direction, int Scale, const World *world, bool debug);

#endif