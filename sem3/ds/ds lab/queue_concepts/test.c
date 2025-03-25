#include <stdio.h>
#define MAX 4
typedef struct{
	int element;
}q;
q Q[MAX]; //global struct array

int IsFull(int *f, int *r)
{
	if(*r == MAX-1)
		return 1;
	else
		return 0;
}

void ADDQ(int *r, int item)
{
	*r = *r+1;
	Q[*r].element = item;
}

int isEmpty(int *f, int *r)
{
	if(*f == *r)
		return 1;
	else
		return 0;
}

int DELQ(int *f)
{
	int d;
	*f = *f+1;
	d=Q[*f].element;
	return d;
}

int main()
{
	int rear=-1, front= -1, f;
	int choice, item, del;

	do{
		printf("1. ADDQ 2.DELQ 3.DISPLAY 4.QUIT\n");
		scanf("%d", &choice);

		switch(choice)
		{
		case 1: f=IsFull(&front, &rear);
			if(f==1)
				printf("Q is full. Cannot insert\n");
			else
			{
				printf("Enter the element to be added to the Q\n");
				scanf("%d", &item);
				ADDQ(&rear, item);
			}
			break;
		case 2: f = isEmpty(&front, &rear);
			if(f==1)
				printf("Sorry Q is empty. Cannot delete\n");
			else
			{
				del = DELQ(&front);
				printf("The deleted element is %d\n", del);
			}
			break;
		case 3: printf("The Q contents are");
			for(int i = front +1; i<=rear; i++)
			printf(" %d\n", Q[i].element);
		break;
		}
	}while(choice!=4);
}