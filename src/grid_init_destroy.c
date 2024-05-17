#include <stdio.h>
#include <stdlib.h>

#include "grid.h"

struct gridInstance* create_new_grid(size_t h, size_t l)
{
    // Returns a dynamicly-allocated grid
    struct gridInstance *res = malloc(sizeof(struct gridInstance));
    if (!res)
    {
        fprintf(stderr, "Could not allocate a new grid instance\n");
        return NULL;
    }

    // Calloc grid in order to get Woodland(= 0) at first
    int *grid = calloc(h * l, sizeof(int));
    if (!grid)
    {
        fprintf(stderr, "Could not allocate a grid array\n");
        free(res); // Clean exit on error
        return NULL;
    }

    // In case everything successfull
    res->grid = grid;
    res->h = h;
    res->l = l;
    res->total_size = h * l;

    return res;
}

int init_burning_tiles(struct gridInstance *grid_instance, unsigned long initially_burning)
{
    if (grid_instance->h * grid_instance->l < initially_burning)
    {
        fprintf(stderr, "Too much initially burning tiles\n");
        return 0;
    }

    unsigned long to_put = initially_burning;
    while (to_put > 0)
    {
        // RAND_MAX big enough by default (>= 32767)
        int rand_pos = rand() % grid_instance->total_size;

        while (grid_instance->grid[rand_pos] == Burning)
        {
            // If already burning, avoid endless random calls
            rand_pos = (rand_pos + 1) % grid_instance->total_size;
        }

        // Place and decrement
        grid_instance->grid[rand_pos] = Burning;
        to_put -= 1;
    }

    // Return total initially burning tiles
    return initially_burning;
}
