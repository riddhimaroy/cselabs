//polynomial menu driven addition sub mul div

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int c;
    int e;
    struct node* link;
}node;

node* insert(node* head, int c, int e)
{
    node *new = (node*)malloc(sizeof(node));
    new->c = c;
    new->e = e;
    new->link = NULL;

    if(head==NULL)
    {
        new->link = new;
        return new;
    }

    node*p = head;

    do
    {
        p = p->link;
    }while(p->link!=head);
    p->link = new;
    new->link = head;
    return head;
}

void display(node* head)
{
    if(head == NULL)
    {
        printf("nothing to show\n");
        return;
    }

    node* p = head;

    do
    {
        printf("%dx^%d + ", p->c, p->e);
        p = p->link;
    } while(p!=head);
}

node* add(node* h1, node* h2)
{

    if (!h1 && !h2) return NULL; // If both lists are empty, return NULL.
    if (!h1) return h2;         // If h1 is empty, return h2.
    if (!h2) return h1;

    node* p1 = h1;
    node* p2 = h2;

    node* ad = NULL;

    do
    {
        p2 = h2;
        int f = 0;

        do
        {
            if(p1->e == p2->e)
            {
                int x = p1->c + p2->c;
                ad = insert(ad, x, p1->e);
                f = 1;
                break;
            }
            // else
            // {
            //     insert(ad, p1->c, p1->e);
            // }
            p2 = p2->link;
        } while(p2 != h2);

        if(f==0)
        {
            ad = insert(ad, p1->c, p1->e);
        }
        p1 = p1->link;
    } while(p1 != h1);

    node*pd = ad;

    do
    {
        int f = 0;
        pd = ad;
        do{
            if(p2->e == pd->e)
            {
                f = 1;
            }
            pd = pd->link;
        }while(pd != ad);

        if(f==0)
        {
            ad = insert(ad, p2->c, p2->e);
        }
        p2 = p2->link;
    } while (p2 != h2);

    return ad;
}

node* multiply(node* h1, node* h2)
{
    node* p1 = h1;
    node* p2 = h2;

    node* mul = NULL;

    do
    {
        p2 = h2;
        do
        {
            int x = p1->c*p2->c;
            int y = p2->e + p1->e;
            mul = insert(mul, x, y);

            p2 = p2->link;
        } while (p2 != h2);
        
        p1 = p1->link;
    } while (p1 != h1);

    node* m1 = mul;
    node* m2 = mul;

    do
    {
        m2 = mul;
        node* tail = mul;
        tail->link = m2;
        do{
            if(m1==m2)
            {
                continue;
            }
            else if(m1->e == m2->e)
            {
                m1->c = m1->c + m2->c;

                tail->link = m2->link;
                m2 = tail;
            }
            m2 = m2->link;
            tail = tail->link;
        }while(m2 != mul);
        m1 = m1->link;
    } while (m1 != mul);

    return mul;
}

int main()
{
    node* h1 = NULL;
    node *h2 = NULL;
    h1 = insert(h1, 1, 2);
    h2 = insert(h2, 2, 3);
    h1 = insert(h1, 1, 4);
    h2 = insert(h2, 3, 2);
    node* ad = add(h1, h2);
    node* mul = multiply(h1, h2);
    display(mul);
}

