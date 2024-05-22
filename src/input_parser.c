#define _POSIX_C_SOURCE 200809L

#include "input_parser.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

int parse_list(struct inputValues *input_values, char *line)
{
    char *save_ptr = NULL;
    char* seps = ";\n";
    char *token = strtok_r(line, seps, &save_ptr);
    while (token != NULL)
    {
        if (token[0] == '\0')
        {
            token = strtok_r(NULL, seps, &save_ptr);
            continue;
        }

        char *sep = strchr(token, ',');
        if (!sep)
        {
            fprintf(stderr, "Error while parsing initial burning tiles\n");
            return -1;
        }
        *sep = '\0'; // For parsing purposes

        errno = 0;
        struct burning_list* new_burning_tile =
            new_burning_item(strtoul(token, NULL, 10),
                    strtoul(sep + 1, NULL, 10));
        if (!new_burning_tile)
        {
            // Case failed alloc
            fprintf(stderr, "Error while allocating a burning tile\n");
            return -1;
        }

        push_back(&input_values->burning_tiles, new_burning_tile);

        token = strtok_r(NULL, seps, &save_ptr);
    }

    return 1;
}

int parse_line(struct inputValues *input_values, int all_params[], char* line)
{
    errno = 0; // Mandatory for error checking
    if (!strncmp(line, "h=", 2))
    {
        if (atoi(line + 2) < 0)
        {
            fprintf(stderr, "Error while parsing a negative height\n");
            return -1;
        }

        input_values->h = strtoul(line + 2, NULL, 10);
        if (errno == 0)
            all_params[0] = 1;
    }
    else if (!strncmp(line, "l=", 2))
    {
        if (atoi(line + 2) < 0)
        {
            fprintf(stderr, "Error while parsing a negative length\n");
            return -1;
        }

        input_values->l = strtoul(line + 2, NULL, 10);
        if (errno == 0)
            all_params[1] = 1;
    }
    else if (!strncmp(line, "p=", 2))
    {
        if (atoi(line + 2) < 0)
        {
            fprintf(stderr, "Error while parsing a negative probability\n");
            return -1;
        }

        input_values->p = strtod(line + 2, NULL);
        if (errno == 0)
            all_params[2] = 1;
    }
    else if (!strncmp(line, "f=", 2))
    {
        int res = parse_list(input_values, line + 2);
        if (errno == 0)
            all_params[3] = 1;
        return res;
    }

    return 1;
}

int parse_inputfile(char* filename, struct inputValues *input_values)
{
    FILE *fd = fopen(filename, "r");
    if (!fd)
    {
        fprintf(stderr, "Could not open the given input file\n");
        return -1;
    }

    int all_params[] = {0, 0, 0, 0};

    char* line = NULL;
    size_t len = 0;
    size_t line_nb = 1;
    while(getline(&line, &len, fd) != -1)
    {
        if (len <= 2)
        {
            fprintf(stderr, "Invalid input at line %zu\n", line_nb);
            fclose(fd);
            free(line);
            return -1;
        }

        // Parse Line
        if ((parse_line(input_values, all_params, line) == -1) || errno != 0)
        {
            // If error while parsing
            fprintf(stderr, "Error while parsing line %zu\n", line_nb);
            fclose(fd);
            free(line);
            return -1;
        }

        line_nb += 1;
    }

    free(line);
    fclose(fd);
    return all_params[0] && all_params[1] && all_params[2] && all_params[3];
}
