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

nodeptr createbt(int item)
{
    int x;

    if(item != -1)
    {
        nodeptr temp = getnode();
        temp->data = item;
        temp->lchild = temp->rchild = NULL;

        printf("enter the lchild of the %d\n", temp->data);
        scanf("%d", &x);
        temp->lchild = createbt(x);

        printf("enter the rchild of the %d\n", temp->data);
        scanf("%d", &x);
        temp->rchild = createbt(x);

        return temp;
    }

    return NULL;
}

void display(nodeptr root, int space)
{
    if(root)
    {
        space += 5;
        display(root->rchild, space);

        printf("\n");
        for(int i=0; i<space; i++)
            printf(" ");
        printf("%d\n", root->data);

        display(root->lchild, space);
    }
}

void inorder(nodeptr root)
{
    if(root)
    {
        inorder(root->lchild);
        printf("%d ", root->data);
        inorder(root->rchild);
    }
}

void preorder(nodeptr root)
{
    if(root)
    {
        printf("%d ", root->data);
        preorder(root->lchild);
        preorder(root->rchild);
    }
}

void postorder(nodeptr root)
{
    if(root)
    {
        postorder(root->lchild);
        postorder(root->rchild);
        printf("%d ", root->data);
    }
}

// int fis(nodeptr root, int key)
// {
//     nodeptr par;
//     if(root)
//     {
//         par = root;
//         fis(root->lchild, key);
//         if(root)
//     }
// }

int search(nodeptr root, int x)
{
    static int t = 0;
    if(root)
    {
        if(root->data == x)
        {
            t++;
            return t;
        }

        if(t==0) search(root->rchild, x);
        if(t==0) search(root->lchild, x);
    }
}

void insert(char dir[], int ele, nodeptr root)
{
    nodeptr temp = getnode();
    temp->data = ele;
    temp->lchild = temp->rchild = NULL;
    nodeptr par, cur;
    int i = 0;

    par = NULL;
    cur = root;

    while(dir[i] && cur)
    {
        par = cur;
        if(dir[i]=='L')
            cur = cur->lchild;
        else
            cur = cur->rchild;
        i++;
    }

    if(dir[i] != '\0' || cur != NULL)
    {
        printf("no hoe\n");
        return;
    }

    else
    {
        if(dir[i-1]=='L')
            par->lchild = temp;
        else
            par->rchild = temp;
    }
}

nodeptr copy(nodeptr root)
{
    nodeptr temp = getnode();

    if(root == NULL)
        return NULL;
    else
    {
        temp->data = root->data;
        temp->lchild = copy(root->lchild);
        temp->rchild = copy(root->rchild);
    }
    return temp;
}

int max(int a, int b)
{
    if(a>=b)
        return a;
    else
        return b;
}

int height(nodeptr root)
{
    if(root==NULL)
        return 0;
    return(1 + max(height(root->rchild), height(root->lchild)));
}

int count(nodeptr root)
{
    static int c = 0, d = 0;
    if(root)
    {
        count(root->lchild);
        c++;
        if(root->lchild == NULL && root->rchild ==NULL)
        d++;
        count(root->rchild);
    }
    return c;
}

int equal(nodeptr r1, nodeptr r2)
{
    if(!r1 && !r2)
        return 1;
    if(!r1 || !r2)
    return 0;
    
    return(((r1->data == r2->data && equal(r1->rchild, r2->rchild) && equal(r1->lchild, r2->lchild))));

}

typedef struct
{
    nodeptr data;
    int top;
}stack;

nodeptr createposttree(char p[])
{
    int i=0;
    nodeptr temp;
    stack *s;
    s->top = -1;

    while(p[i] != '\0')
    {
        temp = getnode();
        temp->data = p[i];
        temp->lchild = temp->rchild = NULL;

        if(isalnum(p[i]))
            push(s, temp);
        else
        {
            temp->rchild = pop(s);
            temp->lchild = pop(s);
            push(s, temp);
        }
        i++;
    }
    return pop(s);
}

int eval(nodeptr root)
{
    if(root == NULL)
        return NULL;
    
    switch(root->data)
    {
        case '+' : return (eval(root->lchild) + eval(root->rchild));
        default: return (root->data -'0');
    }
}

void iterin(nodeptr root)
{
    stack *s;
    s->top = -1;
    nodeptr cur = root;
    int done = 0;

    if(root==NULL)
    {
        printf("nuh");
        return;
    }

    while(!done)
    {
        while(cur != NULL)
        {
            push(s, cur);
            cur = cur->lchild;
        }

        if(!isEmpty(s))
        {
            cur = pop(s);
            printf("%d ", cur->data);
            cur = cur->rchild;
        }

        else
        {
            done = 1;
        }
    }
}

void iterpre(nodeptr root)
{

    if(root==NULL)
        return;
    
    stack *s;
    s->top = -1;

    push(s, root);

    if(!isEmpty(s))
    {
        nodeptr cur = pop(s);
        printf("%d ", cur->data);
        
        if(cur->rchild) push(s, cur->rchild);
        if(cur->lchild) push(s, cur->lchild);
    }
}

void iterpost(nodeptr root)
{
    stack* s1, *s2;
    s1->top = -1;
    s2->top = -1;

    push(s1, root);

    if(!isEmpty(s1))
    {
        nodeptr cur = pop(s1);
        push(s2, cur);

        if(cur->lchild) push(s1, cur->lchild);
        if(cur->rchild) push(s1, cur->rchild);
    }

    if(!isEmpty(s2))
    {
        nodeptr cur = pop(s2);
        printf("%d ", cur->data);
    }
}

void inarr(nodeptr root, int* i, nodeptr arr[])
{
    if(root)
    {
        inarr(root->lchild, i, arr);
        arr[(*i)++] = root;
        inarr(root->rchild, i, arr);
    }
}

nodeptr succ(nodeptr root, nodeptr key)
{
    nodeptr arr[20];
    int i = 0;

    inarr(root, &i, arr);
    int j;

    for(j=0; j<i; j++)
    {
        if(arr[j]==key)
            break;
    }

    return arr[j+1];
}

int findpath(nodeptr root, nodeptr key, nodeptr arr[], int* i)
{
    if(root==NULL)
        return 0;

    arr[(*i)++] = root; 

    if(root==key)
        return 1;

    if(findpath(root->lchild, key, arr, i) || findpath(root->rchild, key, arr, i))
        return 1;
    
    (*i)--;
    return 0;
}

void levelorder(nodeptr root)
{
    q *p;
    insertq(p, root);

    while(!inEmpty(p))
    {
        nodeptr cur = deleteq(p);
        printf("%d ", cur->data);

        if(cur->lchild) insertq(p, cur->lchild);
        if(cur->rchild) insertq(p, cur->rchild);
    }
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

    //display(root, 0);

    printf("Inorder: \n");
    inorder(root);

    printf("\nPreorder: \n");
    preorder(root);

    printf("\nPostorder: \n");
    postorder(root);

    nodeptr root1 = copy(root);
    //insert("LLR", 49, root);

    display(root1, 0);

    printf("\nheight: %d", height(root1));
    int c, d;
    c = count(root);
    printf("\nnodes = %d\nleaves = d\n", c);

    printf("equal = %d", equal(root, root1));
    
}