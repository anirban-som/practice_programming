#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct mylist {
    uint16_t data;
    struct mylist *next;
}mylist_t;


void insert_node_end(mylist_t **head, uint16_t data)
{
    mylist_t *temp=NULL, *curr=NULL;

    temp = (mylist_t * ) malloc(sizeof(mylist_t ));
    if (!temp) {
        printf("malloc failed\n");
        exit(FAILURE );
    }
    temp->data = data;
    temp->next = NULL;

    if (*head) {
        curr = *head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = temp;
    } else {
        *head = temp;
    }
}


void print_list(mylist_t **head)
{
    mylist_t *curr = *head;
    printf("List: ");
    while(curr) {
        printf("[%u]->", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void reverse_list(mylist_t **head)
{
    mylist_t *prev=NULL, *next=NULL;
    mylist_t *curr = *head;

    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

int main()
{
    mylist_t *list_head=NULL;
    int i=0;

    for (i=0; i<10; i++) {
        insert_node_end(&list_head, i);
    }
    print_list(&list_head);

    reverse_list(&list_head);
    printf("After reverse:\n");
    print_list(&list_head);

    return SUCCESS ;
}


