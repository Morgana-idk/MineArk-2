#include <stdio.h>
#include <stdlib.h>
#include "../sharedLibs/World/world.h"
#include "../sharedLibs/Memoria/memoria.h"

int main() {
    World world = GenerateWorld();
    int blocos = 0;
    
    for (int i = 0; i < world.Size; i++) blocos += world.Chunks[i].Size;

    printf("Worlds: 1\nChunks: %d\nBlocks: %d", world.Size, blocos);

    limparMemoria(&world);

    return 0;
}