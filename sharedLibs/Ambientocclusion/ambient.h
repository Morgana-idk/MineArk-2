#ifndef AMBIENT_H
#define AMBIENT_H

typedef struct World World;
typedef struct Block Block;

typedef struct {
    int AO[6][4];
} AmbientOcclusion;

int CalcAO(Block block);

#endif