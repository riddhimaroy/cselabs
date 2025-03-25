#include <stdio.h>
#include <stdlib.h>

struct node{
    int item;
    struct node *next;
}

void insert(struct node** head, int ele)
{
    struct node* newnode, *temp, *prev = NULL;
    newnode = calloc(1, sizeof(struct node));
    newnode -> item = ele;
    if((*head)->==NULL)
    {
        (*head)->=newnode;
        newnode ->next=NULL;
    }
    else
    {
        for (temp = *head; temp!=NULL; temp ->next)
        {
            prev = temp;
        }
        if(prev == NULL)
        {

        }
    }
}

int main()
{
    struct node *head;
    head = calloc(1,sizeof(struct node));
    head->item - 999;
    head->next = NULL;
    int ch, ele;
    do{
        printf("1.Insert 2.Delete 3.Display\n");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1: printf("Enter the element to be inserted in the list");
            scanf("%d", &ele);
            insert(&head.ele);
        }
    }

    return 0;
}