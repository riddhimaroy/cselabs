#include <stdio.h>

typedef struct Node
{
    int key;
    struct Node* right, left;
    int height;
} Node;

int max(int a, int b)
{
    if(a>b)
        return a;
    return b;
}

int upheight(Node* root)
{
    if(root==NULL)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}

Node* ll(Node* y)
{
    Node* x = y->right;
    Node* T2 = x->left;

    x->left = y;
    y->right = T2;

    x->height=upheight(x);
    y->height=upheight(y);

    return x;
}

Node* rr(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    x->height=upheight(x);
    y->height=upheight(y);

    return x;
}

int balance(Node* root)
{
    return upheight(root->left)-upheight(root->right);
}

Node* insert(Node* root, int key)
{
    Node* curr = root;
    Node* parent = NULL;
    Node* x = NULL;
    x->key = key;
    x->left = x->right = NULL;
    x->height = 1;

    while(curr)
    {
        if(key>curr->key)
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
        parent = curr;
    }

    if(key> parent->key)
    {
        parent->right = x;
    }
    else
    {
        parent->left = x;
    }

    x->height=upheight(x);

    while(parent!=NULL)
    {
        parent->height = upheight(parent);

        int bal = balance(parent);

        if(bal>1 && parent->left<key)
            parent = rr(parent);
        else if(bal>1 && parent->left>key)
        {
            parent->left = ll(parent->left);
            parent = rr(parent);
        }
        else if(bal<-1 && parent->right>key)
        {
            parent = ll(parent);
        }
        else if (bal<-1 && parent->right<key)
        {
            parent->right = rr(parent->right);
            parent = ll(parent);
        }

        parent = parent->left ? parent->left : parent->right;
    }

    return root;
}