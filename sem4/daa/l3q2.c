#include <stdio.h>
#include <string.h>

int strmat(char w[], char sen[100])
{
    int nw = strlen(w);
    int ns = strlen(sen);

    for(int i=0; i<=(ns-nw); i++)
    {
        if(sen[i]==w[0])
        {
            int cnt = 0;
            for(int k =0; k<nw; k++)
            {
                if(sen[i+k] == w[k])
                {
                    cnt++;
                }
            }
             if(cnt == nw)
                    return i;
        }
    }
    return -1;
}

int main()
{
    char w[50], sen[100];

    printf("enter the string to be found\n");
    scanf("%s", w);
    while (getchar() != '\n'); 

    printf("enter the string to be looked from\n");
    // gets(sen);
    fgets(sen, sizeof(sen), stdin);

    size_t len = strlen(sen);
    if (len > 0 && sen[len - 1] == '\n') {
        sen[len - 1] = '\0';
    }

    printf("string found at index %d", strmat(w, sen));
}