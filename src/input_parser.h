#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

struct inputValues
{
    unsigned long h;
    unsigned long l;
    double p;
    struct burning_list *burning_tiles;
};

int parse_inputfile(char* filename, struct inputValues *input_values);

#endif /* !INPUT_PARSER_H */
