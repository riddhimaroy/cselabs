#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int coeff;
    int exp;
    struct node* link;
}node;

node* insertnodeprev (node *prev, node* new)
{
    //node *new = (node*)malloc(sizeof(node));
    new->link = prev->link;
    prev->link = new;
    new->link = NULL;

    return new;
}

node* sort(node* front)
{
    node* p = front;
    node* q = front;
    int temp;

    for(p = front; p->link != NULL; p = p->link)
    {
       // q = p->link;
        for(q = p->link; q->link != NULL; q = q->link)
        {
            if(q->exp<p->exp)
            {
                temp = q->coeff;
                q->coeff = p->coeff;
                p->coeff = temp;

                temp = q->exp;
                q->exp = p->exp;
                p->exp = temp;
            }
         //   q = q->link;
        }
       // p = p->link;
    }

    return front;
}

node* add(node* h, node* h2)
{
    h = sort(h);
    h2 = sort(h2);
//printf("0");
    node* res = (node*)malloc(sizeof(node));
    node *p = res;
//printf("1");
    while(h->link != NULL && h2->link != NULL)
    {
    if(h->exp==h2->exp)
    {
        node* new = (node*)malloc(sizeof(node));
        new->coeff = h->coeff + h2->coeff;
        new->exp = h->exp;
        insertnodeprev(p, new);
        h = h->link;
        h2 = h2 ->link;
        p= p->link;
    }

    else if(h->exp > h2->exp)
    {
        insertnodeprev(p, h);
        p=p->link;
        h=h->link;
    }

    else if(h2->exp > h->exp)
    {
        insertnodeprev(p, h2);
        p=p->link;
        h2=h2->link;
    }
    else
    printf("LOL");
    }

    if(h->link == NULL)
    {
        while(h2->link != NULL)
        {
            insertnodeprev(p, h2);
            p = p->link;
            h2 = h2-> link;
        }
    }
    else if(h2->link == NULL)
    {
        while(h->link != NULL)
        {
            insertnodeprev(p, h);
            p = p->link;
            h = h-> link;
        }
    }
    else
    printf("FUCKING LOSER");

}

void display(node* res)
{
    printf("The added polynomial is: \n");
    node *p = res;

    while(p != NULL)
    {
        printf("%dx ^ %d + ", p->coeff, p->exp);
        p = p->link;
    }
     printf("%dx ^ %d", p->coeff, p->exp);
}

int main()
{
    node* h = (node*)malloc(sizeof(node));
    node* h1 = (node*)malloc(sizeof(node));
    node *p = h;
    node *p1 = h1;
    int i, j;

    int n1, n2;

    printf("Enter the number of elements in first polynomial\n");
    scanf("%d", &n1);
    printf("Enter the number of elements in second polynomial\n");
    scanf("%d", &n2);

    printf("Enter the coeff and exp for the terms:\n");

    for(i=0; i<n1; i++)
    {
        scanf("%d", &(p->coeff));
        scanf("%d", &(p->exp));

        p->link = (node*)malloc(sizeof(node));
        p = p->link;
    }

    printf("Enter the coeff and exp for the terms:\n");
    for(i=0; i<n2; i++)
    {
        scanf("%d", &(p1->coeff));
        scanf("%d", &(p1->exp));
        p1->link = (node*)malloc(sizeof(node));
        p1 = p1->link;
    }

    node *res = add(h, h1);
    display(res);
}
