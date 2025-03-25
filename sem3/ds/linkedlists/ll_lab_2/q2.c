// Add two long positive integers represented using circular doubly linked list with 
//header node. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct node
{
    char data[MAX];
    struct node* next;
    struct node* prev;
}node;

node* insertbeg(node* head, char x)
{
    char w[MAX];
    w[0] = x;
    w[1] = '\0';

    node* new = (node*)malloc(sizeof(node));
    //strcpy(new->data, w);
    new->data[0] = x;
    new->data[1] = '\0';
    new->prev = NULL;
    new->next = NULL;

    if(head == NULL)
    {
        new->next = new;
        new->prev = new;
        return new;
    }

    new->next = head;
    new->prev = head->prev;
    head->prev->next = new;
    head->prev = new;
    head = new;
    return head;
}

node* insertend(node* head, char x)
{
    node* p;
    node* new = (node*)malloc(sizeof(node));
    //strcpy(new->data, w);
    new->data[0] = x;
    new->data[1] = '\0';

    if(head == NULL)
    {
        new->next = new;
        new->prev = new;
        return new;
    }

    new->next = head;
    new->prev = head->prev;
    head->prev->next = new;
    head->prev = new;
    return head;
}

node* create (char w[])
{
    node* head = NULL;
    int wn = strlen(w);

    for(int i=0; i<wn; i++)
    {
        head = insertbeg(head, w[i]);
    }

    return head;
}

void display(node* head)
{
    if(head==NULL)
    {
        printf("nothing to show\n");
        return;
    }

    node*p = head;
    char w[10];

    strcpy(w, p->data);   
    p = p->prev;

    while(p!=head)
    {
        printf("%s", p->data);
        p = p->prev;
    }

    printf("%s", w);
}

// node* add(node* h1, node* h2)
// {
//     node *p1 = h1;
//     node *p2 = h2;

//     node* ad = NULL;
//     int c = 0; int x1, x2, x3;
    
//     x1 = p1->data[0] - '0';
//     x2 = p2->data[0] - '0';
//     x3 = x1+x2;
//     if(x3>9)
//     {
//         c = 1;
//         x3 = x3%10;
//     }
//     ad = insertend(ad, (char)(x3 + '0'));


//     p1 = p1->next;
//     p2 = p2->next;

//     while(p1!= h1 && p2!=h2)
//     {    
//         x1 = p1->data[0] - '0';
//         x2 = p2->data[0] - '0';
//         x3 = x1+x2;

//         if(c==1) x3 = x3 + 1;
//         c=0;
//         if(x3>9)
//         {
//             c = 1;
//             x3 = x3%10;
//         }

//         p1 = p1->next;
//         p2 = p2->next;
//         ad = insertend(ad, (char)(x3 + '0'));

//     }

//     if(p1 != h1)
//     {
//         int x = p1->data[0] - '0';
//         if (c==1)
//             x=x+1;
//         ad = insertend(ad, (char)(x+'0'));
//         p1 = p1->next;

//         while(p1 != h1)
//         {
//             x = p1->data[0] - '0';
//             ad = insertend(ad, (char)(x+'0'));
//             p1 = p1->next;
//         }
//     }

//     if(p2 != h2)
//     {
//         int x = p2->data[0] - '0';
//         if (c==1)
//             x=x+1;
//         ad = insertend(ad, (char)(x+'0'));
//         p2 = p2->next;

//         while(p2 != h2)
//         {
//             x = p2->data[0] - '0';
//             ad = insertend(ad, (char)(x+'0'));
//             p2 = p2->next;
//         }
//     }

//     return ad;
// }

// node* add(node* h1, node* h2) {
//     node *p1 = h1, *p2 = h2;
//     node* ad = NULL;
//     int carry = 0;

//     do {
//         int x1 = p1 ? p1->data[0] - '0' : 0;
//         int x2 = p2 ? p2->data[0] - '0' : 0;

//         int sum = x1 + x2 + carry;
//         carry = sum / 10;

//         ad = insertend(ad, (char)((sum % 10) + '0'));

//         p1 = (p1 && p1->next != h1) ? p1->next : NULL;
//         p2 = (p2 && p2->next != h2) ? p2->next : NULL;
//     } while (p1 || p2 || carry > 0);

//     return ad;
// }


node* add(node* h1, node* h2)
{
    node *p1 = h1;
    node *p2 = h2;

    node* ad = NULL;
    int c = 0; int x1, x2, x3;

    do
    {    
        x1 = p1->data[0] - '0';
        x2 = p2->data[0] - '0';
        x3 = x1+x2;

        if(c==1) x3 = x3 + 1;
        c=0;
        if(x3>9)
        {
            c = 1;
            x3 = x3%10;
        }

        p1 = p1->next;
        p2 = p2->next;
        ad = insertend(ad, (char)(x3 + '0'));

    } while(p1!= h1 && p2!=h2);

    if(p1 != h1)
    {
        int x = p1->data[0] - '0';
        
        ad = insertend(ad, (char)(x+'0'));
        p1 = p1->next;

        while(p1 != h1)
        {
            if(p1==h1)
            {
                if (c==1)
                x=x+1;
            }
            x = p1->data[0] - '0';
            ad = insertend(ad, (char)(x+'0'));
            p1 = p1->next;
        }
    }

    if(p2 != h2)
    {
        int x = p2->data[0] - '0';
        if (c==1)
            x=x+1;
        ad = insertend(ad, (char)(x+'0'));
        p2 = p2->next;

        while(p2 != h2)
        {
            x = p2->data[0] - '0';
            ad = insertend(ad, (char)(x+'0'));
            p2 = p2->next;
        }
    }

    return ad;
}

int main()
{
    node* h2  = create("12345");
    node* h1 = create("67");

    node* ad = add(h1, h2);

    display(ad);
}
