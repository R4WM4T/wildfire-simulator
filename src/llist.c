#include "llist.h"

#include <stdio.h>
#include <stdlib.h>

struct burning_list *new_burning_item(size_t i, size_t j)
{
    struct burning_list* res = calloc(1, sizeof(struct burning_list));

    if (res)
    {
        res->i = i;
        res->j = j;
    }

    return res;
}

void clear_burning_list(struct burning_list *item)
{
    if (!item)
        return;
    if (item->next)
        clear_burning_list(item->next);
    free(item);
}

int push_back(struct burning_list **list, struct burning_list *to_add)
{
    if (!(*list))
    {
        *list = to_add;
        return 1;
    }

    struct burning_list *cur = *list;
    while (cur->next) {
        cur = cur->next;
    }

    cur->next = to_add;

    return 1;
}
