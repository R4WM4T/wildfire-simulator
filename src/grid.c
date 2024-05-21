#include "grid.h"

#include <stdio.h>

int in_grid(struct gridInstance *my_grid, size_t i, size_t j)
{
    return i < my_grid->h && j < my_grid->l;
}

int extend_fire(struct gridInstance *my_grid,
        struct burning_list **next_tick_burnings, size_t i, size_t j)
{
    if (my_grid->grid[i * my_grid->l + j] == Ashes)
    {
        return 0;
    }

    struct burning_list* new_burning_tile = new_burning_item(i, j);
    if (!new_burning_tile)
    {
        // Case failed alloc
        fprintf(stderr, "Error while allocating a burning tile\n");
        return -1;
    }

    my_grid->grid[i * my_grid->l + j] = Burning;
    my_grid->nb_burnings += 1;
    return push_back(next_tick_burnings, new_burning_tile);
}

