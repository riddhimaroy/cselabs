#include<stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    int day;
    char* month;
    int year;
}DOB;

typedef struct
{
    DOB *dob;
   // STU_INFO stu;
  //  COLLEGE college;
}STUDENT;

int main()
{
    int n, i; STUDENT*s;

    printf("enter number of students\n");
    scanf("%d", &n);

    s = (STUDENT*)calloc(n, sizeof(STUDENT));
    s->dob=(DOB*)calloc(n, sizeof(DOB));
    s->dob->month = (char*)calloc(20,sizeof(char));

    for(i=0; i<n; i++)
    {
        printf("For student %d", i+1);
        printf("Enter date\n");
        scanf("%d", &((s+i)->dob->day));
        printf("Enter month\n");
        scanf("%s", ((s+i)->dob->month));

      //  gets((s+i)->dob->month);
        printf("Enter year\n");
        scanf("%d", &((s+i)->dob->year));
    }

    for(i=0; i<n; i++)
    {
        printf("\nThe date of birth is %d %s %d",(s+i)->dob->day,(s+i)->dob->month, (s+i)->dob->year);
    }
}




