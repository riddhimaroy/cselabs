#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    struct Node* right;
    struct Node* left;
    int height;
}Node;

Node* ll(Node* y)
{
    Node* x = y->right;
    Node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

Node* rr(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

Node* pred (Node* root, int key)
{
    Node* y = NULL;

    while(root)
    {
        if(key > root->key)
        {
            y = root;
            root = root->right;
        }
        else
            root = root->left;
    }

    return y;
}

Node* succ(Node* root, int key)
{
    Node* y = NULL;

    while(root)
    {
        if(root->key > key)
        {
            y = root;
            root = root->left;
        }

        else
        {
            root = root->right;
        }
    }

    return y;
}

int main()
{}