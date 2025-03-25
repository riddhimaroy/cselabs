// Find the maximum and minimum value in a binary tree.

#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodeptr;

struct node
{
    int data;
    nodeptr rchild;
    nodeptr lchild;
};

nodeptr getnode()
{
    nodeptr x = (nodeptr)malloc(sizeof(struct node));
    return x;
}

void insert(char w[], int x, nodeptr root)
{
    nodeptr temp, par, cur;

    temp = getnode();

    temp->data = x;
    temp->lchild = NULL;
    temp->rchild = NULL;

    par = NULL;
    cur = root;
    int i = 0;

    if(root==NULL)
    {
        root = temp;
    }

    while(cur && w[i])
    {
        par = cur;

        if(w[i]=='L')
        {
            cur = cur->lchild;
        }
        else
        {
            cur = cur->rchild;
        }
        i++;
    }

    if(w[i] != '\0' && cur!=NULL)
    {
        printf("wrong");
        return;
    }

    if(w[i-1]=='L')
    {
        par->lchild = temp;
    }
    else
    {
        par->rchild = temp;
    }
}

int max(int m, nodeptr root)
{
    if(root)
    {
        m = max(m, root->lchild);
        if(root->data > m)
            m = root->data;
        m = max(m, root->rchild);
    }
    return m;
}

int min(int m, nodeptr root)
{
    if(root)
    {
        m = min(m, root->lchild);
        if(m>root->data)
            m = root->data;
        m = min(m, root->rchild);
    }
    return m;
}

//Find the path from the root to a given node.

int path(nodeptr root, nodeptr x, int i)
{
    int arr[30];
    if(root == NULL)
    {
        //printf("empty tree");
        return 0;
    }

    arr[i] = root;
    i++;

    if(root == x)
    {
        return 1;
    }
    if(path(root->lchild, x, i) || path(root->rchild, x, i))
        return 1;

    i--;
    
}

nodeptr mirror (nodeptr root)
{
    if(root == NULL)
        return;
    nodeptr temp = getnode();

    temp->data = root->data;
    temp->rchild = mirror(temp->lchild);
    temp->lchild = mirror(temp->rchild);

    return temp; 
}

int main()
{
    nodeptr root = getnode();
    root->data = 1;
    root->rchild = root->lchild = NULL;
    insert("L", 2, root);
    insert("LL", 3, root);
    insert("LR", 4, root);
    insert("R", 5, root);
    insert("RL", 6, root);
    insert("RR", 7, root);

    printf("%d", min(100000, root));
}