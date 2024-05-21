#ifndef GRID_H
#define GRID_H

#include <stddef.h>

#include "llist.h"

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
    double p;
    size_t total_size;
    unsigned long nb_burnings;
    struct burning_list *burning_tiles;
};

int in_grid(struct gridInstance *my_grid, size_t i, size_t j);

int extend_fire(struct gridInstance *my_grid,
        struct burning_list **next_tick_burnings, size_t i, size_t j);

#endif /* ! GRID_H */
