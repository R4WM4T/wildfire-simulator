#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

#include "../src/grid.h"
#include "../src/grid_init_destroy.h"

Test(Grid_init_destroy, basic_4x4)
{
    struct gridInstance* myGrid = create_new_grid(4, 4);
    cr_assert(myGrid);
    cr_assert(myGrid->h == 4 && myGrid->l == 4);
}

Test(Grid_init_destroy, basic_init_fire)
{
    struct gridInstance* myGrid = create_new_grid(6, 10);
    cr_assert(myGrid);

    init_burning_tiles(myGrid, 15);

    int counter = 0;

    for (size_t i = 0; i < myGrid->total_size; i++)
    {
        if (myGrid->grid[i] == Burning)
            counter += 1;
    }

    cr_assert(counter == 15);
}
