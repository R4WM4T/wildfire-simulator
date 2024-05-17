#ifndef GRID_H
#define GRID_H

#include <stddef.h>

enum tile_states
{
    Woodland = 0,
    Burning,
    Ashes,
};

struct gridInstance
{
    int *grid;
    size_t h;
    size_t l;
    size_t total_size;
};

#endif /* ! GRID_H */
