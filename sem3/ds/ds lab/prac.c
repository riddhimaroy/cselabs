#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void posttoin(char[] h)
{
    int i =0;
    int n = strlen(h);
    char c;
    int j = 0;
    stack *s = creates(s);

    char* res = (char*)calloc(30, sizeof(char));

    while (i!=n)
    {
        c = h[i];

        if(isalnum(c))
        {
            res[j++] = c;
        }
        else if(c=="(")
        {
            push(s,c);
        }
        else if (c==")")
        {
            while(s->item[s->top] != '(')
            {
                res[j++] = pop(s);
            }
            char xx = pop(s);
        }
        else
        {
            while(prec(c)<=prec(s[item]))
            {
                pop
            }
            push
        }
        i++;
    }

    
}
