#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node *nodeptr;

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

//doesnt take into cons
nodeptr createbst(nodeptr root, int ele)
{
    if(root==NULL)
    {
        root = getnode();
        root->data = ele;
        root->rchild = root->lchild = NULL;
        return root;
    }

    else if(ele>root->data)
    {
        root->rchild = createbst(root->rchild, ele);
    }

    else if(ele<root->data)
    {
        root->lchild = createbst(root->lchild, ele);
    }
    else{
        printf("duplicates not allowed\n");
    }
    return root;
}

void search(int key, nodeptr root)
{
    if(root == NULL)
    {
        printf("not found\n");
        return NULL;
    }
    else if(key == root->data)
    {
        printf("found\n");
        return;
    }
    else if(key>root->data)
        search(key, root->rchild);
    else
        search(key, root->lchild);

}

void itersearch(nodeptr root, int key)
{
    while(root)
    {
        if(key==root->data)
        {
            printf("found\n");
            return;
        }
        else if(key>root->data)
            root = root->rchild;
        else
            root = root->lchild;    
    }
    printf("not found\n");
    return;
}

void insert(nodeptr root, int key)
{
    nodeptr temp = getnode();
    temp->data = key;
    temp->lchild = temp->rchild = NULL;

    nodeptr parent, cur;

    parent = NULL;
    cur = root;

    if(root==NULL)
    {
        root = temp;
        return root;
    }

    while(cur)
    {
        parent = cur;
        if(cur==key)
        {
            printf("duplicates not allowed\n");
            return;
        }
        else if(cur>key)
            cur = cur->lchild;
        else
            cur = cur->rchild;
    }

    if(key>parent->data)
        parent->lchild = key;
    else if(key<parent->data)
        parent->rchild = key;

}

nodeptr deleteNode(nodeptr root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->lchild = deleteNode(root->lchild, key);
    else if (key > root->data)
        root->rchild = deleteNode(root->rchild, key);
    else {
        if (root->lchild == NULL && root->rchild == NULL) {
            free(root);
            return NULL;
        } else if (root->lchild == NULL) {
            nodeptr temp = root;
            root = root->rchild;
            free(temp);
            return root;
        } else if (root->rchild == NULL) {
            nodeptr temp = root;
            root = root->lchild;
            free(temp);
            return root;
        } else {
            nodeptr temp = root->rchild;
            while (temp && temp->lchild != NULL)
                temp = temp->lchild;
            root->data = temp->data;
            root->rchild = deleteNode(root->rchild, temp->data);
        }
    }
    return root;
}

bool printAncestors(nodeptr root, int target)
{
if (root == NULL)
return false;
if (root->data == target)
return true;
if ( printAncestors(root->lchild, target) ||
printAncestors(root->rchild, target) )
{
printf("%d ", root->data);
return true;
}
return false;
}

void display(nodeptr root, int space)
{
    if(root)
    {
        space = space + 5;
        display(root->rchild, space);
        printf("\n");
        for(int i=0; i<space; i++)
        {
            printf(" ");
        }
        printf("%d", root->data);
        display(root->lchild, space);
    }
}

nodeptr buildfromprein(int* in, int* pre, int inStart, int inEnd, int* preIndex) {
    if (inStart > inEnd) return NULL;

    int rootVal = pre[*preIndex];
    (*preIndex)++;

    nodeptr root = createbst(rootVal);

    int rootIdx = inStart;
    while (in[rootIdx] != rootVal) rootIdx++;

    root->lchild = buildfromprein(in, pre, inStart, rootIdx - 1, preIndex);
    root->rchild = buildfromprein(in, pre, rootIdx + 1, inEnd, preIndex);

    return root;
}


nodeptr buildTreeFromPostIn(int* in, int* post, int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd) return NULL;

    int rootVal = post[*postIndex];
    (*postIndex)--;

    nodeptr root = createNode(rootVal);

    int rootIdx = inStart;
    while (in[rootIdx] != rootVal) rootIdx++;

    root->rchild = buildTreeFromPostIn(in, post, rootIdx + 1, inEnd, postIndex);
    root->lchild = buildTreeFromPostIn(in, post, inStart, rootIdx - 1, postIndex);

    return root;
}

nodeptr inosucc(nodeptr root, nodeptr temp)
{
    if(temp->rchild)
    {
        nodeptr cur = temp->rchild;

        while(cur && cur->lchild)
        {
            cur = cur->lchild;
        }
        return cur;
    }

    nodeptr succ = NULL;

    while(root)
    {
        if(temp->data>root->data)
        {
            root = root->lchild;
            succ = root;
        }

        else if(temp->data<root->data)
            root = root->rchild;

        else
            break;
    }
}

nodeptr succ(nodeptr key)
{
    key = key->rchild;

    while(key && key->lchild)
    {
        key = key->lchild;
    }
    return key;
}

nodeptr delete(nodeptr root, int key)
{
    if(root==NULL)
        return NULL;

    if(key>root->data)
    {
        root->rchild = deletenode(root->rchild, key);
    }
    else if(key<root->data)
    {
        root->lchild = deletenode(root->lchild, key);
    }
    else
    {
        if(root->lchild == NULL)
        {
            nodeptr temp = root->rchild;
            free(root);
            return temp;
        }

        else if(root->rchild == NULL)
        {
            nodeptr temp = root->lchild;
            free(root);
            return temp;
        }

        else
        {
            nodeptr temp = succ(root);
            root->data = temp->data;
            root->rchild = delete(root->rchild, temp->data);
        }
    }
    return root;
}

int main()
{
    nodeptr root = getnode();
    root = NULL;
    root = createbst(root, 4);
    root = createbst(root, 1);
    root = createbst(root, 2);
    root = createbst(root, 3);

    display(root, 0);

}

