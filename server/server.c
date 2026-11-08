#include <stdio.h>
#include "../sharedLibs/World/world.h"

int main() {
    World world = GenerateWorld();
    int blocos = 0;
    
    for (int i = 0; i < world.Size; i++) {
        blocos += world.Chunks[i].Size;
    }

    printf("Worlds: 1\nChunks: %d\nBlocks: %d", world.Size, blocos);

    return 0;
}