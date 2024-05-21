#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grid.h"
#include "grid_display.h"
#include "grid_init_destroy.h"
#include "grid_iterator.h"

int main(void)
{
    // Init pseudo random number generator
    srand(time(NULL));

    struct gridInstance* myGrid = create_new_grid(9, 9);

    printf("INIT\n");
    display_grid(myGrid);
    printf("\n");

    init_burning_tiles(myGrid, 2);

    size_t nb_max_gen = 50;
    size_t i = 0;
    while (i < nb_max_gen && myGrid->nb_burnings > 0)
    {
        printf("TICK %zu -- %zu tiles burning\n", i, myGrid->nb_burnings);
        display_grid(myGrid);

        next_tick(myGrid);

        printf("\n");

        i += 1;
    }

    printf("END\n");
    display_grid(myGrid);
    printf("\n");

    // Clean exit
    clear_grid_instance(myGrid);

    return 0;
}
