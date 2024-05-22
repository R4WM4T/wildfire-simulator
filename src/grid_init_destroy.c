#include "grid_init_destroy.h"
#include <stdio.h>
#include <stdlib.h>

#include "grid.h"
#include "input_parser.h"
#include "llist.h"

struct gridInstance* create_new_grid(struct inputValues *input_values)
{
    // Returns a dynamicly-allocated grid
    struct gridInstance *res = malloc(sizeof(struct gridInstance));
    if (!res)
    {
        fprintf(stderr, "Could not allocate a new grid instance\n");
        return NULL;
    }

    // Calloc grid in order to get Woodland(= 0) at first
    int *grid = calloc(input_values->h * input_values->l, sizeof(int));
    if (!grid)
    {
        fprintf(stderr, "Could not allocate a grid array\n");
        free(res); // Clean exit on error
        return NULL;
    }

    // In case everything successfull
    res->grid = grid;
    res->h = input_values->h;
    res->l = input_values->l;
    // Probability
    res->p = input_values->p;

    res->nb_burnings = 0;
    res->total_size = input_values->h * input_values->l;

    res->burning_tiles = input_values->burning_tiles;
    input_values->burning_tiles = NULL;

    init_burning_tiles(res);

    return res;
}

int init_burning_tiles(struct gridInstance *grid_instance)
{

    struct burning_list *prev = NULL;
    struct burning_list *cur = grid_instance->burning_tiles;

    while (cur)
    {
        // Place and decrement
        if (in_grid(grid_instance, cur->i, cur->j))
        {
            if (grid_instance->grid[cur->i * grid_instance->l + cur->j]!= Burning)
            {
                grid_instance->grid[cur->i * grid_instance->l + cur->j] = Burning;
                grid_instance->nb_burnings += 1;
            }
        }
        else
        {
            // Remove invalid coordinates
            if (!prev)
                grid_instance->burning_tiles = cur->next;
            else
                prev->next = cur->next;

            // Destroy it
            struct burning_list *to_free = cur;
            cur = cur->next;
            free(to_free);
            continue;
        }

        prev = cur;
        cur = cur->next;
    }

    // Return total initially burning tiles
    return grid_instance->nb_burnings;
}

void clear_grid_instance(struct gridInstance *grid_instance)
{
    free(grid_instance->grid);
    clear_burning_list(grid_instance->burning_tiles);
    free(grid_instance);
}
