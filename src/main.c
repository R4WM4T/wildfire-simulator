#include <stdlib.h>

#include "grid.h"
#include "grid_display.h"
#include "grid_init_destroy.h"

int main(void)
{
    struct gridInstance* myGrid = create_new_grid(4, 10);

    init_burning_tiles(myGrid, 15);

    display_grid(myGrid);

    // Clean exit
    free(myGrid->grid);
    free(myGrid);

    return 0;
}
