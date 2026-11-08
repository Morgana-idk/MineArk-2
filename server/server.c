#include <stdio.h>
#include "../sharedLibs/World/world.h"

int main() {
    World world = GenerateWorld();

    printf(`Worlds: 1\nChunks: ${world.Size}\nBlocks: ${world.Chunks.Size}`);

    return 0;
}