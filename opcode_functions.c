#include "monty.h"

int status;

void push(stack_t **stack, unsigned int line_number)
{
    (void)line_number;

    stack_t *new_node = malloc(sizeof(stack_t));
    if (!new_node)
    {
        malloc_error();
    }

    new_node->n = status;
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

void pint(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }
    
    printf("%d\n", (*stack)->n);
}

void pop(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;

    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
        exit(EXIT_FAILURE);
    }

    temp = *stack;
    *stack = (*stack)->next;

    if(*stack != NULL)
    {
        (*stack)->prev = NULL;
    }
    free(temp);
}

void swap(stack_t **stack, unsigned int line_number)
{
    int temp;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    temp = (*stack)->n;
    (*stack)->n = (*stack)->next->n;
    (*stack)->next->n = temp;
}

void add(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    temp = *stack; /* Temp to store top element */

    (*stack)->next->n += (*stack)->n; /* add the top element to the second top element */

    *stack = (*stack)->next; /* Move the stack pointer to the next element */

    free(temp); /* Free the memory of the top element */
    (*stack)->prev = NULL; /* Set the prev pointer of the new top element to NULL */
}

void nop(stack_t **stack, unsigned int line_number)
{
    (void)stack;
    (void)line_number;
}

void execute_instruction(char *opcode, stack_t **stack, unsigned int line_number, char *arg)
{
    instruction_t instructions[] = 
    {
        {"push", push},
        {"pall", pall},
        {"pint", pint},
        {"pop", pop},
        {"swap", swap},
        {"add", add},
        {"nop", nop},
        {NULL, NULL}
    };

    if (strcmp(opcode, "push") == 0)
    {
        if (!arg || !isdigit(arg[0]))
        {
            push_error(line_number);
        }
        status = atoi(arg); 
        /* store the integer value in the extern variable */
    }

    for (int i = 0; instructions[i].opcode; i++)
    {
            if (strcmp(opcode, instructions[i].opcode) == 0)
            {
                instructions[i].f(stack, line_number);
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