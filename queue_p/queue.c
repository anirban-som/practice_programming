#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1
/*
 * In this implementation, we have to traverse the entire
 * queue for each node insertion.
 * In stead, we can have one extra pointer 'rear', which 
 * would point to the last inserted node, that is the last
 * node in the queue. And we need to insert the new node to 
 * the next pointer of 'rear' node.
 * */
typedef struct my_queue {
    uint16_t data;
    struct my_queue *next;
}my_queue_t;

void insert_to_queue(my_queue_t **queue_head, uint16_t data)
{
    my_queue_t *temp=NULL, *curr=NULL;
    temp=(my_queue_t *)malloc(sizeof(my_queue_t ));

    if (!temp) {
        printf("malloc failed\n");
        exit(FAILURE);
    }
    temp->data = data;
    temp->next = NULL;
    if (!(*queue_head)) {
        *queue_head=temp;
    } else {
        curr = *queue_head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = temp;
    }
}
    

int16_t remove_from_queue(my_queue_t **queue_head)
{
    my_queue_t *temp=*queue_head;
    uint16_t pop_data=0;

    if (!temp) {
        printf("queue is empty");
        return FAILURE;
    }

    *queue_head = temp->next;
    pop_data = temp->data;
    free(temp);
    return pop_data;
}

void print_queue(my_queue_t **queue_head)
{
    my_queue_t *curr=*queue_head;

    printf("\ncurrent queue=[");
    while(curr) {
        printf(" %u", curr->data);
        curr=curr->next;
    }
    printf("]\n");
}

int main()
{
    int i=0;
    my_queue_t *head=NULL;
    /*create/push into queue*/
    while (i<10) {
        insert_to_queue(&head, i);
        i++;
    }

    print_queue(&head);

    /*pop from queue*/
    while (head) {
        printf("pop=[%u]\n", remove_from_queue(&head));
    }

    print_queue(&head);

    return SUCCESS;
}
