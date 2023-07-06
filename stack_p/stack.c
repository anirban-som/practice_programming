#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct my_stack {
    uint16_t data;
    struct my_stack *next;
}my_stack_t;

void push(my_stack_t **stack_head, uint16_t data)
{
    my_stack_t *temp=NULL;
    temp=(my_stack_t *)malloc(sizeof(my_stack_t ));

    if (!temp) {
        printf("malloc failed\n");
        exit(FAILURE);
    }
    temp->data = data;
    temp->next = *stack_head;
    *stack_head = temp;
}
    

int16_t pop(my_stack_t **stack_head)
{
    my_stack_t *temp=*stack_head;
    uint16_t pop_data=0;

    if (!temp) {
        printf("stack is empty");
        return FAILURE;
    }

    *stack_head = temp->next;
    pop_data = temp->data;
    free(temp);
    return pop_data;
}

void print_stack(my_stack_t **stack_head)
{
    my_stack_t *curr=*stack_head;

    printf("\ncurrent stack=[");
    while(curr) {
        printf(" %u", curr->data);
        curr=curr->next;
    }
    printf("]\n");
}

int main()
{
    int i=0;
    my_stack_t *head=NULL;
    /*create/push into stack*/
    while (i<10) {
        push(&head, i);
        i++;
    }

    print_stack(&head);

    /*pop from stack*/
    while (head) {
        printf("pop=[%u]\n", pop(&head));
    }

    print_stack(&head);

    return SUCCESS;
}
