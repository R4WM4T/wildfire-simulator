#ifndef GRID_GENERATION_H
#define GRID_GENERATION_H

#include <stddef.h>

struct gridInstance* create_new_grid(size_t h, size_t l);

int init_burning_tiles(struct gridInstance *grid_instance, unsigned long initially_burning);

void clear_grid_instance(struct gridInstance *grid_instance);

#endif /* ! GRID_GENERATION_H */
