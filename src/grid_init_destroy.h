#ifndef GRID_GENERATION_H
#define GRID_GENERATION_H

#include <stddef.h>

#include "input_parser.h"

struct gridInstance* create_new_grid(struct inputValues *input_values);

int init_burning_tiles(struct gridInstance *grid_instance);

void clear_grid_instance(struct gridInstance *grid_instance);

#endif /* ! GRID_GENERATION_H */
