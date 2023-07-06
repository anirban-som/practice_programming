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

mylist_t *__find_intersecting_node(mylist_t **longer_list_head, mylist_t **shorter_list_head, int diff_len)
{
    int i=0;
    mylist_t *long_curr = *longer_list_head;
    mylist_t *short_curr = *shorter_list_head;

    for (i=0; i<diff_len; i++) {
        long_curr = long_curr->next;  
    }
    while (long_curr && short_curr) {
        if (long_curr == short_curr) {
            return long_curr;
        }
        long_curr = long_curr->next;
        short_curr = short_curr->next;
    }
    return NULL;
}

mylist_t *find_intersecting_node(mylist_t **head1, mylist_t **head2)
{
    mylist_t *curr1=NULL, *curr2=NULL;
    curr1 = *head1;
    curr2 = *head2;
    int len1=0, len2=0;

    while(curr1) {
        curr1 = curr1->next;
        len1++;
    }
    while(curr2) {
        curr2 = curr2->next;
        len2++;
    }
    if (len1>len2) {
        return __find_intersecting_node(head1, head2, (len1-len2));
    } else {
        return __find_intersecting_node(head2, head1, (len2-len1));
    }
#if 0
#endif
	return NULL;
}

int main()
{
    mylist_t *head1=NULL, *head2=NULL;
    mylist_t *curr1=NULL, *curr2=NULL;
    mylist_t *intersecting_node=NULL;
    uint16_t i=0;
    /*create list1*/
    for(i=0; i<20; i++) {
        insert_node_end(&head1, i);
    }
    print_list(&head1);

    /*create list2*/
    for(i=30; i<38; i++) {
        insert_node_end(&head2, i);
    }

    /*make them intersecting*/
    curr1 = head1;
    /*traverser till 10th node of list1*/
    for (i=0; i<10; i++) {
        curr1 = curr1->next;
    }
    curr2 = head2;

    /*traverser till last node of list2*/
    while (curr2->next) {
        curr2 = curr2->next;
    }

    /* make the 'next' of last node of list2, point to the 10th node of list1.
     * that's how they intersect.
     * */
    curr2->next = curr1;
    print_list(&head2);

    intersecting_node = find_intersecting_node(&head1, &head2);

    if (intersecting_node) {
        printf("intersecting node found: [%u]\n", intersecting_node->data);
    } else {
        printf("there is no intersection between the two lists\n");
    }

    return SUCCESS;
}
