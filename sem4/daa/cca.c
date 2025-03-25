#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Function to find the Closest Common Ancestor (CCA)
struct Node* findCCA(struct Node* root, int n1, int n2) {
    if (root == NULL) return NULL;  // Base case

    // If root is n1 or n2, then root is the CCA
    if (root->data == n1 || root->data == n2)
        return root;

    // Search in left and right subtrees
    struct Node* leftCCA = findCCA(root->left, n1, n2);
    struct Node* rightCCA = findCCA(root->right, n1, n2);

    // If both left and right returned non-NULL, this root is the CCA
    if (leftCCA != NULL && rightCCA != NULL)
        return root;

    // Otherwise, return the non-null subtree result
    return (leftCCA != NULL) ? leftCCA : rightCCA;
}

int main() {
    // Example tree:
    //        1
    //       / \
    //      2   3
    //     / \   \
    //    4   5   6
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->right = newNode(6);

    int n1 = 4, n2 = 5;
    struct Node* ancestor = findCCA(root, n1, n2);

    if (ancestor)
        printf("Closest Common Ancestor of %d and %d is: %d\n", n1, n2, ancestor->data);
    else
        printf("No common ancestor found.\n");

    return 0;
}
