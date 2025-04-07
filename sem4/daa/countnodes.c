#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    struct node* right;
    struct node* left;
} node;

node* new(int key)
{
    node* new = (node*)malloc(sizeof(node));
    new->key = key;
    return new;
}

node* insert(node* root, int key)
{
    if(root==NULL)
        return new(key);

    if(key<root->key)
        root->left = insert(root->left, key);
    else if(key>root->key)
        root->right = insert(root->right, key);
    
    return root;
}

int countnodes(node* root)
{
    if(root==NULL)
        return 0;

    return 1+ countnodes(root->left) + countnodes(root->right);
}

void inorder(node* root)
{
    while(root)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }

    return;
}