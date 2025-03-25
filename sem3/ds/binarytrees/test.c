#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node next;
    struct node prev;
}node;

node* sortedinsert(node* head, int ele)
{
    node *new =(node*)malloc(sizeof(node));
    new->data = ele;
    new->next = NULL;
    new->prev = NULL;

    node*p = head;

    while(p!=NULL)
    {
        while(p->data<ele)
        {
            p = p->next;
        }

        new->next = p->next;
        new->prev = p;
        p->next->prev = new;
        p->next = new;
        break;
    }
}

char* rev(char w[])
{
    int n = strlen(w);
    char reve[n];

    for(int i=0; i<n; i++)
    {
        reve[i] = w[n-i-1];
    }
    reve[n] = '\0';

    for(int i=0; i<n; i++)
    {
        if(reve[i]=='(')
            reve[i] = ')';
        else if(reve[i]==')')
            reve[i] = '(';
    }
}

void preftopost(char w[])
{
    stack *s;
    int i = 0;

    while(w[i] != '\0')
    {
        char x = w[i];

        if(isalnum(x))
        {
            char* wo = (char*)malloc(2*sizeof(char));
            wo[0] = x;
            wo[1] = '\0';
            push(s, wo);
        }

        else
        {
            int l;
            char x2[20], x1[20];
            strcpy(x1, pop(s));
            strcpy(x2, pop(s));

            l = strlen(x1) + strlen(x2) + 3;
            char* res = (char*)malloc(l*sizeof(char));
            strcat(res, x1);
            strcat(res, x2);
            strcat(res, pop(s));
            res[strlen(x1) + strlen(x2)] = '\0';

            push(s, res);
        }
    }

    char r[20] = pop(s);
}
