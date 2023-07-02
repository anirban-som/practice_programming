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

void remove_loop(mylist_t **head, mylist_t **node_inside_loop)
{
    mylist_t *curr=NULL;
    mylist_t *temp_head=*head;

    while (1) {
        curr = *node_inside_loop;
        while ((curr->next != *node_inside_loop) &&
                (curr->next != temp_head)) {
            printf("node_inside_loop->data=[%u], curr->next->data=[%u], temp_head->data=[%u]\n",
                    (*node_inside_loop)->data,
                    curr->next->data,
                    temp_head->data);
            curr = curr->next;
        }
        if (curr->next == temp_head)
        {
            printf("curr->next = temp_head, found the culprit!!\n"
                    "node_inside_loop->data=[%u], curr->next->data=[%u], temp_head->data=[%u]\n",
                    (*node_inside_loop)->data,
                    curr->next->data,
                    temp_head->data);
            /*remove loop*/
            curr->next = NULL;
            printf("Loop is removed. Your linked_list is clean now!!\n");
            return;
        }
        temp_head = temp_head->next;
    }
}

void detect_and_remove_loop(mylist_t **head)
{
    mylist_t *fast=*head, *slow=*head;

    while (fast && slow && (fast->next)) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            printf("loop detected\n");
            remove_loop(head, &slow);
            return;
        }
    }

    /*came outside of while, means there is no loop in the linked list*/
    printf("No loop detected in linked list. out of danger!!\n");
}

int main()
{
    mylist_t *head=NULL, *curr=NULL;
    uint16_t i=0;

    for (i=0; i <10; i++) {
        insert_node_end(&head, i);
    }

    print_list(&head);

    /*create loop*/
    curr = head;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = head->next->next->next;
    //curr->next = head; /*this case also passed*/

    detect_and_remove_loop(&head);

    print_list(&head);

    return SUCCESS;
}
