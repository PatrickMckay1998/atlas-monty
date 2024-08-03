#include "monty.h"

int status = 0;  // Global variable to keep track of status

void usage_error(void)
{
    fprintf(stderr, "USAGE: monty file\n");
    exit(EXIT_FAILURE);
}

void file_error(char *filename)
{
    fprintf(stderr, "Error: Can't open file %s\n", filename);
    exit(EXIT_FAILURE);
}

void malloc_error(void)
{
    fprintf(stderr, "Error: malloc failed\n");
    exit(EXIT_FAILURE);
}

void unknown_instruction_error(unsigned int line_number, char *opcode)
{
    fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
    exit(EXIT_FAILURE);
}

void push_error(unsigned int line_number)
{
    fprintf(stderr, "L%u: usage: push integer\n", line_number);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        usage_error();
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        file_error(argv[1]);
    }

    stack_t *stack = NULL;
    char *line = NULL;
    size_t len = 0;
    unsigned int line_number = 0;

    while (getline(&line, &len, file) != -1)
    {
        line_number++;
        char *opcode = strtok(line, " \t\n");
        char *arg = strtok(NULL, " \t\n");

        if (opcode && opcode[0] != '#')
        {
            execute_instruction(opcode, &stack, line_number, arg);
        }
    }

    free(line);
    free_stack(stack);
    fclose(file);

    return 0;
}