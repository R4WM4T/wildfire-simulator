#include <stdio.h>
#include <stdlib.h>

#include "grid.h"
#include "llist.h"

int rand_P(double p)
{
    return (rand() % 100) < (p * 100);
}

int next_tick(struct gridInstance *my_grid)
{
    struct burning_list *next_tick_burnings = NULL;
    struct burning_list *current = my_grid->burning_tiles;

    while (current)
    {
        size_t i = current->i;
        size_t j = current->j;

        // Check the 4 tiles around here
        if (in_grid(my_grid, i + 1, j) && rand_P(my_grid->p))
        {
            if (extend_fire(my_grid, &next_tick_burnings, i + 1, j) == -1)
                return -1;
        }

        if (in_grid(my_grid, i - 1, j) && rand_P(my_grid->p))
        {
            if (extend_fire(my_grid, &next_tick_burnings, i - 1, j) == -1)
                return -1;
        }
        if (in_grid(my_grid, i, j + 1) && rand_P(my_grid->p))
        {
            if (extend_fire(my_grid, &next_tick_burnings, i, j + 1) == -1)
                return -1;
        }

        if (in_grid(my_grid, i, j - 1) && rand_P(my_grid->p))
        {
            if (extend_fire(my_grid, &next_tick_burnings, i, j - 1) == -1)
                return -1;
        }

        my_grid->grid[i * my_grid->l + j] = Ashes;
        my_grid->nb_burnings -= 1;

        current = current->next;
    }

    clear_burning_list(my_grid->burning_tiles);
    my_grid->burning_tiles = next_tick_burnings;

    return 1;
}
