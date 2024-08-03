#include "monty.h"

void push(stack_t **stack, unsigned int line_number, char *arg)
{
    if (!arg || !isdigit(arg[0]))
    {
        push_error(line_number);
    }

    int n = atoi(arg);
    stack_t *new_node = malloc(sizeof(stack_t));
    if (!new_node)
    {
        malloc_error();
    }

    new_node->n = n;
    new_node->prev = NULL;
    new_node->next = *stack;
    if (*stack)
    {
        (*stack)->prev = new_node;
    }
    *stack = new_node;
}

void pall(stack_t **stack, unsigned int line_number)
{
    (void)line_number;
    stack_t *current = *stack;

    while (current)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}

void execute_instruction(char *opcode, stack_t **stack, unsigned int line_number, char *arg)
{
    instruction_t instructions[] = {
        {"push", push},
        {"pall", pall},
        {NULL, NULL}
    };

    for (int i = 0; instructions[i].opcode; i++)
    {
        if (strcmp(opcode, instructions[i].opcode) == 0)
        {
            if (strcmp(opcode, "push") == 0)
            {
                push(stack, line_number, arg);
            }
            else
            {
                instructions[i].f(stack, line_number);
            }
            return;
        }
    }

    unknown_instruction_error(line_number, opcode);
}

void free_stack(stack_t *stack)
{
    while (stack)
    {
        stack_t *temp = stack;
        stack = stack->next;
        free(temp);
    }
}