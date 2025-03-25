#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structure for a node in the doubly linked list
typedef struct Node {
    char tag[10];        // Tag or expression type (<POSTFIX>, <PREFIX>, etc.)
    char expression[50]; // Store the expression
    int result;          // Store result for expression node
    struct Node* prev;
    struct Node* next;
} Node;

// Function to insert a new expression node in the list
void Insert(Node** head, char* tag, char* expr) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->tag, tag);
    strcpy(newNode->expression, expr);
    newNode->result = 0; // Initialize result to 0

    newNode->prev = NULL;
    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Function to display the linked list contents
void Display(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("Tag: %s, Expression: %s, Result: %d\n",
               temp->tag, temp->expression, temp->result);
        temp = temp->next;
    }
}

// Function to check if parentheses in an expression are balanced
int CheckExpression(char* expr) {
    int balance = 0;
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(') balance++;
        else if (expr[i] == ')') balance--;
        if (balance < 0) return 0; // Unbalanced
    }
    return balance == 0;
}

// Function to compute the result of a postfix expression
int ComputePostfix(char* expr) {
    int stack[50], top = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isdigit(expr[i])) {
            stack[++top] = expr[i] - '0';  // Push digit to stack
        } else {
            int val2 = stack[top--];
            int val1 = stack[top--];

            switch (expr[i]) {
                case '+': stack[++top] = val1 + val2; break;
                case '-': stack[++top] = val1 - val2; break;
                case '*': stack[++top] = val1 * val2; break;
                case '/': stack[++top] = val1 / val2; break;
            }
        }
    }
    return stack[top];
}

// Function to compute the result of a prefix expression
int ComputePrefix(char* expr) {
    int stack[50], top = -1;
    int len = strlen(expr);

    // Traverse the expression from right to left
    for (int i = len - 1; i >= 0; i--) {
        if (isdigit(expr[i])) {
            stack[++top] = expr[i] - '0';  // Push digit to stack
        } else {
            int val1 = stack[top--];
            int val2 = stack[top--];

            switch (expr[i]) {
                case '+': stack[++top] = val1 + val2; break;
                case '-': stack[++top] = val1 - val2; break;
                case '*': stack[++top] = val1 * val2; break;
                case '/': stack[++top] = val1 / val2; break;
            }
        }
    }
    return stack[top];
}

// Main function to demonstrate the system
int main() {
    Node* head = NULL;
    int choice;
    char tag[10], expr[50];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Expression\n");
        printf("2. Display List\n");
        printf("3. Check Expression\n");
        printf("4. Compute Result\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter tag (e.g., <POSTFIX>, <PREFIX>): ");
                scanf("%s", tag);
                printf("Enter expression: ");
                scanf("%s", expr);
                Insert(&head, tag, expr);
                break;

            case 2:
                Display(head);
                break;

            case 3:
                printf("Enter expression to check: ");
                scanf("%s", expr);
                if (CheckExpression(expr)) {
                    printf("Expression is valid.\n");
                } else {
                    printf("Expression is invalid.\n");
                }
                break;

            case 4:
                printf("Enter expression type (POSTFIX or PREFIX): ");
                scanf("%s", tag);
                printf("Enter expression to compute: ");
                scanf("%s", expr);

                if (strcmp(tag, "POSTFIX") == 0) {
                    printf("Result: %d\n", ComputePostfix(expr));
                } else if (strcmp(tag, "PREFIX") == 0) {
                    printf("Result: %d\n", ComputePrefix(expr));
                } else {
                    printf("Invalid expression type.\n");
                }
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}