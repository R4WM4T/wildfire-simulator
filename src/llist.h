#ifndef LLIST_H
#define LLIST_H

#include <stddef.h>

struct burning_list
{
    size_t i;
    size_t j;
    struct burning_list *next;
};

struct burning_list *new_burning_item(size_t i, size_t j);

void clear_burning_list(struct burning_list *item);

int push_back(struct burning_list **list, struct burning_list *to_add);

#endif /* ! LLIST_H */
