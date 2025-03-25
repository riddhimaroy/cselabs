#include <stdio.h>
#include <stdlib.h>

#define MAX 3
typedef struct
{
    int arr[MAX];
    int rear;
    int front;
}DQ;

void AddRear(DQ *q, int item)
{
    if(q->rear==-1 &&q->front==-1)
    {
        q->rear = q->rear +1;
        q->front = q->front +1;
        q->arr[q->rear] = item;
    }
    else
    {
        q->rear = q->rear +1;
        q->arr[q->rear] = item;
    }
}

void AddFront(DQ *q, int item)
{
    if(q->rear==-1 &&q->front==-1)
    {
        q->rear = q->rear +1;
        q->front = q->front +1;
        q->arr[q->front] = item;
    }
    else
    {
        q->front--;
        q->arr[q->front] = item;
    }
}

int DelRear(DQ *q)
{
    int d;

    if(q->rear == q->front)
    {
        d = q->arr[q->rear];
        q->rear = -1;
        q->front = -1;
    }
    else
    {
        d = q->arr[q->rear];
        q->rear = q->rear -1;
    }
    return d;
}

int main() 
{
    DQ *q;
    q = calloc(1, sizeof(DQ));
    q->rear = -1;
    q->front = -1;
    int item, ch, i, j, del, c;
    do
    {
        printf("1.Insertrear 2.Insertfront 3.Deleterear 4.Deletefront 5.Display 6.Exit\n");
        scanf("%d", &c);
        switch(ch)
        {
            case 1: if(q->rear + 1 != MAX -1)
                printf("Can't insert at rear");
                else
                {
                    printf("Enter the element to be inserted at the rear");
                    scanf("%d", &item);
                    AddRear(q, item);
                } break;

                case 2: if(q->front == 0)
                    printf("Cannot insert at front");
                    else
                    {
                        printf("Enter the element to be inserted at the rear");
                        scanf("%d", &item);
                        AddFront(q, item);
                    }break;
                case 3: if(q->rear ==-1 && q->front==-1)
                    printf("DQ is empty");
                    else
                    {
                        del=DelRear(q);
                        printf("The element deleted from rear is %d\n", del);
                    }break;
                case 4: if(q->rear ==-1 && q->front==-1)
                    printf("DQ is empty");
                    else
                    {
                    //    del=DelFront(q);
                        printf("The element deleted from front is %d\n", del);
                    }break;
                case 5: printf("The elements of DQ are \n");
                    for(int i=q->front; i<=q->rear; i++)
                    {
                        printf("%d", q->arr[i]);
                    }break;
        }
    }while (ch!=6);
    // {};
}