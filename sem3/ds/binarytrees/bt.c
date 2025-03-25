#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node *nodeptr;

struct node
{
    char data;
    nodeptr rchild;
    nodeptr lchild;
    int rightThread;
    int leftThread;
};

typedef struct
{
    nodeptr data[100];
    int top;
}stack;

stack* creates(stack* s)
{
    s = (stack*)malloc(sizeof(stack));
    s->top = -1;
    return s;
}

int isFull(stack *s)
{
    return (s->top == 100 -1);
}

int isEmpty(stack *s)
{
    return (s->top == -1);
}

void push(stack*s, nodeptr x)
{
    if(isFull(s))
    {
        printf("stack overflow !!\n");
        return;
    }
    s->top++;
    s->data[s->top] = x;
}

nodeptr pop(stack *s)
{
    if(isEmpty(s))
    {
        printf("stack underflow !!\n");
        return 0;
    }

    nodeptr x = s->data[s->top];
    s->top--;
    return x;
}


nodeptr getnode()
{
    nodeptr x = (nodeptr)malloc(sizeof(struct node));
    return x;
}

nodeptr createbt(int item)
{
    int x;

    if(item!=-1)
    {
        nodeptr temp = getnode();
        temp->data = item;

        printf("enter the left child of %d\n", item);
        scanf("%d", &x);
        temp->lchild = createbt(x);

        printf("enter the right child of %d\n", item);
        scanf("%d", &x);
        temp->rchild = createbt(x);

        return temp;
    }

    return NULL;
}

//display in opposite of inorder form(inorder is l to r this is r to l)
void displaytreei(nodeptr root, int space)
{
    if(root)
    {
        space = space + 5;
        displaytreei(root->rchild, space);
        printf("\n");
        for(int i=0; i<space; i++)
        {
            printf(" ");
        }
        printf("%d", root->data);
        displaytreei(root->lchild, space);
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

void insert(char dir[], nodeptr root, int ele)
{
    nodeptr temp, cur, par;
    int i = 0;

    temp = getnode();
    temp->data = ele;
    temp->rchild = NULL;
    temp->lchild = NULL;
    cur = root;
    par = NULL;

    while(cur && dir[i])
    {
        par = cur;
        if(dir[i]=='L' || dir[i]=='l')
        {
            cur = cur->lchild;
        }
        else
        {
            cur = cur->rchild;
        }
        i++;
    }

    if(cur!= NULL || dir[i] != '\0')
    {
        printf("nah wrong");
        return;
    }
    else
    {
        if(dir[i-1]=='L' || dir[i-1] == 'l')
        {
            par->lchild = temp;
        }
        else
            par->rchild = temp;
    }
}

nodeptr copy(nodeptr root)
{
    nodeptr temp = getnode();
    if(root==NULL)
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
    if (a>=b)
        return a;
    else
        return b;
}

int height(nodeptr root)
{
    if(root==NULL)
        return 0;
    return(1+max(height(root->rchild), height(root->lchild)));
}

int countnodes(nodeptr root)
{
    static int c = 0;

    if(root)
    {
        countnodes(root->lchild);
        c++;
        countnodes(root->rchild);
    }
    return c;
}

int countleaves(nodeptr root)
{
    static int c = 0;

    if(root)
    {
        countleaves(root->lchild);
        if(root->rchild == NULL && root->lchild == NULL)
        c++;
        countleaves(root->rchild);
    }
    return c;
}

int equal(nodeptr root1, nodeptr root2)
{
    return ((!root1 && !root2) || (root1==root2 && root1->data==root2->data && 
    equal(root1->rchild, root2->lchild) && equal(root1->rchild, root2->lchild)));
}

void printKthLevel(nodeptr* root, int k) {
    if (root == NULL)
        return;
    
    if (k == 0) {
        printf("%d ", root->data);  // Print the data of the current node
    } else {
        // Recursively print the nodes at the (k-1)th level for left and right children
        printKthLevel(root->lchild, k - 1);
        printKthLevel(root->rchild, k - 1);
    }
}

nodeptr createposttree(char postfix[])
{
    stack *s;
    s->top =-1;
    int i=0, k =0;
    nodeptr temp;

    while(postfix[i++]!='\0')
    {
        temp = getnode();
        temp->data = postfix[i];
        temp->rchild = temp->lchild = NULL;

        if(isalnum(postfix[i]))
            push(s, temp);
        else
        {
            temp->rchild = pop(s);
            temp->lchild = pop(s);
            push(s, temp);
        }
    }
    return pop(s);
}

nodeptr createpreftree(char prefix[]) {
    stack* s = creates(s);
    s->top = -1;

    int n = strlen(prefix);

    char rev[n];

    for(int i=0; i<n; i++)
    {
        rev[i] = prefix[n-i-1];
    }
    rev[n] = '\0';

    nodeptr x = createposttree(rev);
    return x;
}



int eval(nodeptr root)
{
if(root == NULL)
    return NULL;
switch(root->data)
{
case '+':return eval(root->lchild)+ eval(root->rchild);
case '-' :return eval(root-> lchild)- eval(root->rchild);
case '/':return eval(root->lchild)/ eval(root->rchild);
case '*' :return eval(root-> lchild)* eval(root->rchild);
case '^':return pow(eval(root->lchild),
eval(root->rchild));
default :return(root->data-'0'); //base case
}
}

void iterin(nodeptr root)
{
    nodeptr cur; int done = 0; stack *s; s->top =-1;
    cur = root;

    if(root == NULL)
    {
        printf("tree is empty");
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
            printf("%d", cur->data);
            cur = cur->rchild;
        }

        else
            done = 1;
    }
}

void iterpre(nodeptr root) {
    if (root == NULL) {
        printf("Empty tree\n");
        return;
    }

    stack* s = (stack*)malloc(sizeof(stack));  
    s->top = -1; 

    push(s, root);  

    while (!isEmpty(s)) {
        nodeptr cur = pop(s);  
        printf("%d ", cur->data); 

        if (cur->rchild != NULL) {
            push(s, cur->rchild);
        }
        
        if (cur->lchild != NULL) {
            push(s, cur->lchild);
        }
    }

}

void postorder(nodeptr root) {
    if (!root) 
        return;
    stack *s1, *s2; // Stacks for nodes
    s1->top = -1;
    s2->top = -1;
    push(s1, root);

    while (!isEmpty(s1)) {
        nodeptr cur = pop(s1);
        push(s2, cur);
        if (cur->lchild) push(s1, cur->lchild);
        if (cur->rchild) push(s1, cur->rchild);
    }
    while (!isEmpty(s2))
        printf("%d ", pop(s)->data);
}

void postorder(nodeptr root) {
    Stack stack = {.top = -1};
    nodeptr lastVisited = NULL;

    while (root || !isEmpty(&stack)) {
        if (root) {
            push(&stack, root);
            root = root->lchild; // Go to left child
        } else {
            nodeptr peekNode = peek(&stack);
            if (peekNode->rchild && lastVisited != peekNode->rchild) {
                root = peekNode->rchild; // Visit right child
            } else {
                printf("%d ", peekNode->data); // Process node
                lastVisited = pop(&stack);
            }
        }
    }
}

//for bst
nodeptr inorderSuccessor(nodeptr root, nodeptr n) {
    // Case 1: If the node has a right child, the successor is the leftmost node in the right subtree
    if (n->rchild != NULL) {
        nodeptr temp = n->rchild;
        while (temp->lchild != NULL) {
            temp = temp->lchild;
        }
        return temp;
    }

    // Case 2: If the node does not have a right child, the successor is one of its ancestors
    nodeptr successor = NULL;
    while (root != NULL) 
    {
        if (n->data < root->data) {
            successor = root;  // This node is a potential successor
            root = root->lchild;
        } else if (n->data > root->data) {
            root = root->rchild;
        } else {
            break;
        }
    }
    return successor;
}

void inorderTraversal(nodeptr root, nodeptr inorderArray[], int* index) {
    if (root == NULL) return;
    inorderTraversal(root->lchild, inorderArray, index);
    inorderArray[(*index)++] = root;
    inorderTraversal(root->rchild, inorderArray, index);
}

nodeptr inorderSuccessor(nodeptr root, nodeptr target) {
    if (!root || !target) return NULL;
    nodeptr inorderArray[100];
    int index = 0;
    inorderTraversal(root, inorderArray, &index);
    for (int i = 0; i < index - 1; i++) {
        if (inorderArray[i] == target) {
            return inorderArray[i + 1];
        }
    }
    return NULL;
}

int findPath(nodeptr root, nodeptr target, nodeptr path[], int* pathIndex) {
    if (root == NULL) return 0;
    path[(*pathIndex)++] = root; // Add the current node to the path
    if (root == target) return 1; // Stop when the target is found
    if (findPath(root->lchild, target, path, pathIndex) || 
        findPath(root->rchild, target, path, pathIndex)) {
        return 1;
    }
    (*pathIndex)--; // Backtrack if the current node is not on the path
    return 0;
}

// int tree_path(Node* root, int target, int path[], int *pathIndex) {
//     if (root == NULL) return 0;
//     path[(*pathIndex)++] = root->data; // Add current node to path
//     if (root->data == target) return 1; // Found target
//     if (tree_path(root->left, target, path, pathIndex))
//         {root = root->lchild;
//         return 1;}
//     if (tree_path(root->right, target, path, pathIndex))
//         {
//             root = rchild;
//             return 1;} // Continue if target found in subtree
// // Backtrack
//     return 0;
// }



void levelorder(nodeptr root) {
    if (root == NULL) {
        printf("empty tree\n");
        return;
    }

    Queue* q = createQueue(100); 
    insertq(q, root);  

    while (!isEmpty(q)) {
        nodeptr temp = deleteq(q);  
        printf("%d ", temp->data);  

        if (temp->lchild) insertq(q, temp->lchild);  
        if (temp->rchild) insertq(q, temp->rchild);  
    }
}

//find inorder successoor of threaded tree

nodeptr insucc(nodeptr node)
{//Return the inorder successor of node
nodeptr temp = node-> rchild;
if (node->rightThread==FALSE)
while (temp->leftThread==FALSE)
temp = temp -> lchild;
return temp;
}

//inorder traversal of threaded tree

void tinorder(nodeptr treehead)
{
nodeptr temp = treehead;
while(1){
temp = insucc(temp);
if (temp == treehead) break;
printf("%c", temp->data);
}
}

int main()
{
    int x; char dir[10];

    printf("enter the root of the tree\n");
    scanf("%d", &x);
    nodeptr root = createbt(x);

    // printf("enter direction bro");
    // scanf("%s", dir);
    // insert(dir, root, 50);
    nodeptr root1 = copy(root);
    displaytreei(root1, 0);
    printf("\n%d", countleaves(root));
}