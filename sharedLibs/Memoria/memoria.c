#include "memoria.h"
#include <stdlib.h>

void limparMemoria(World *world) {
    for (int i = 0; i < world->Size; i++) {
        free(world->Chunks[i].Blocks);
    }
}