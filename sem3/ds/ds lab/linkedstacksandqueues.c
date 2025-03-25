#include <stdio.h>
#include <stdlib.h>
# define MAX 3

typedef struct
{
    int item;
}ele;

typedef struct stack* SPTR;

struct stack
{
    ele e;
    SPTR link;
};

#define isEmpty(SPTR) (!(SPTR))
#define isFull(SPTR) (!(SPTR))

int main()
{
    SPTR top[MAX];
    int data, ch, n;
    
    printf("1. push 2. pop 3. display\n");
    scanf("%d", &ch);

    switch(ch)
    {
        case 1: printf("Enter stack number into which you want to push\n");
        scanf("%d", &n);
        if(n>=0 && n<=2)
        {
            
        }
    }
}