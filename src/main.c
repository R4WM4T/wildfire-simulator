#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grid.h"
#include "grid_display.h"
#include "grid_init_destroy.h"
#include "grid_iterator.h"
#include "input_parser.h"
#include "llist.h"

int main(int argc, char *argv[])
{
    // Init pseudo random number generator
    srand(time(NULL));

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return -1;
    }

    // Parse input file
    struct inputValues input_values;
    int parse_status = parse_inputfile(argv[1], &input_values);
    if (parse_status == -1)
    {
        clear_burning_list(input_values.burning_tiles);
        return -1;
    }
    if (!parse_status)
    {
        fprintf(stderr, "Missing parameters in input file\n");
        clear_burning_list(input_values.burning_tiles);
        return -1;
    }
    // printf("Running with config: (h=%zu , l=%zu , p=%f)\n", input_values.h,
    //         input_values.l, input_values.p);

    // Initializatin of the grid
    struct gridInstance* myGrid = create_new_grid(&input_values);

    launch_simulation(myGrid);

    printf("END\n");
    display_grid(myGrid);
    printf("\n");

    // Clean exit
    clear_grid_instance(myGrid);

    return 0;
}
