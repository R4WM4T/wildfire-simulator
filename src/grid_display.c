#include <stdio.h>

#include "grid.h"

void display_grid(struct gridInstance *grid_instance)
{
    if (!grid_instance)
    {
        fprintf(stderr, "There is no grid to display\n");
        return;
    }

    char* states_format[] =
    {
        [Woodland] = "T",
        [Burning] = "#",
        [Ashes] = ".",
    };

    printf("|");
    for (size_t j = 0; j < grid_instance->l; j++)
    {
        printf("---");
    }
    printf("|\n");

    for (size_t i = 0; i < grid_instance->h; i++)
    {
        printf("|");
        for (size_t j = 0; j < grid_instance->l; j++)
        {
            printf(" %s ", states_format[grid_instance->grid[i * grid_instance->l + j]]);
        }

        printf("|\n");
    }

    printf("|");
    for (size_t j = 0; j < grid_instance->l; j++)
    {
        printf("---");
    }
    printf("|\n");
}
