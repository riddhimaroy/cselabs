#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum to differentiate between file and directory
typedef enum { FILE_NODE, DIRECTORY_NODE } NodeType;

// Structure to represent a file or directory node in the tree
typedef struct Node {
    char name[50];           // Name of the file or directory
    NodeType type;           // Type: FILE_NODE or DIRECTORY_NODE
    int size;                // Size of the file (0 for directories)
    struct Node* parent;     // Pointer to the parent node
    struct Node* children;   // Pointer to the first child (for directories)
    struct Node* sibling;    // Pointer to the next sibling (for both files and directories)
} Node;

Node* createNode(const char* name, NodeType type, int size) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->type = type;
    newNode->size = size;
    newNode->parent = NULL;
    newNode->children = NULL;
    newNode->sibling = NULL;
    return newNode;
}

void addChild(Node* parent, Node* child) {
    child->parent = parent;
    child->sibling = parent->children;
    parent->children = child;
}

void create(Node* parent, const char* name, NodeType type, int size) {
    Node* newNode = createNode(name, type, size);
    addChild(parent, newNode);
}

void deleteNode(Node* node) {
    if (node->type == DIRECTORY_NODE) {
        Node* child = node->children;
        while (child) {
            Node* next = child->sibling;
            deleteNode(child);
            child = next;
        }
    }
    free(node);
}

void deleteByName(Node* parent, const char* name) {
    Node* prev = NULL;
    Node* curr = parent->children;

    while (curr && strcmp(curr->name, name) != 0) {
        prev = curr;
        curr = curr->sibling;
    }

    if (curr) {
        if (prev) {
            prev->sibling = curr->sibling;
        } else {
            parent->children = curr->sibling;
        }
        deleteNode(curr);
    } else {
        printf("Node not found: %s\n", name);
    }
}

void listContents(Node* dir) {
    if (dir->type != DIRECTORY_NODE) {
        printf("%s is not a directory\n", dir->name);
        return;
    }

    Node* child = dir->children;
    while (child) {
        printf("%s (%s)\n", child->name, child->type == FILE_NODE ? "File" : "Directory");
        child = child->sibling;
    }
}

void move(Node* sourceParent, const char* name, Node* dest) {
    Node* prev = NULL;
    Node* curr = sourceParent->children;

    while (curr && strcmp(curr->name, name) != 0) {
        prev = curr;
        curr = curr->sibling;
    }

    if (!curr) {
        printf("Node not found: %s\n", name);
        return;
    }

    if (prev) {
        prev->sibling = curr->sibling;
    } else {
        sourceParent->children = curr->sibling;
    }

    addChild(dest, curr);
}

Node* find(Node* root, const char* name) {
    if (strcmp(root->name, name) == 0) {
        return root;
    }

    Node* child = root->children;
    while (child) {
        Node* found = find(child, name);
        if (found) return found;
        child = child->sibling;
    }

    return NULL;
}

int calculateSize(Node* dir) {
    if (dir->type == FILE_NODE) {
        return dir->size;
    }

    int totalSize = 0;
    Node* child = dir->children;
    while (child) {
        totalSize += calculateSize(child);
        child = child->sibling;
    }
    return totalSize;
}

int main() {
    Node* root = createNode("root", DIRECTORY_NODE, 0);
    int choice;
    char name[50], parentName[50];
    NodeType type;
    int size;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create File/Directory\n");
        printf("2. Delete by Name\n");
        printf("3. List Directory Contents\n");
        printf("4. Move File/Directory\n");
        printf("5. Find File/Directory\n");
        printf("6. Calculate Directory Size\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter parent directory name: ");
                scanf("%s", parentName);
                Node* parent = find(root, parentName);
                if (!parent || parent->type != DIRECTORY_NODE) {
                    printf("Invalid parent directory");
                    break;
                }
                printf("Enter name of the file/directory: ");
                scanf("%s", name);
                printf("Enter type (0 for File, 1 for Directory): ");
                scanf("%d", (int*)&type);
                size = (type == FILE_NODE) ? 0 : -1;  // Size for directories is 0
                if (type == FILE_NODE) {
                    printf("Enter file size: ");
                    scanf("%d", &size);
                }
                create(parent, name, type, size);
                break;

            case 2:
                printf("Enter parent directory name: ");
                scanf("%s", parentName);
                parent = find(root, parentName);
                if (!parent || parent->type != DIRECTORY_NODE) {
                    printf("Invalid parent directory");
                    break;
                }
                printf("Enter name to delete: ");
                scanf("%s", name);
                deleteByName(parent, name);
                break;

            case 3:
                printf("Enter directory name to list contents: ");
                scanf("%s", name);
                Node* dir = find(root, name);
                if (!dir || dir->type != DIRECTORY_NODE) {
                    printf("Invalid directory");
                    break;
                }
                listContents(dir);
                break;

            case 4:
                printf("Enter source parent directory: ");
                scanf("%s", parentName);
                parent = find(root, parentName);
                if (!parent || parent->type != DIRECTORY_NODE) {
                    printf("Invalid source directory: %s\n", parentName);
                    break;
                }
                printf("Enter name to move: ");
                scanf("%s", name);
                printf("Enter destination directory: ");
                scanf("%s", name);
                Node* dest = find(root, name);
                if (!dest || dest->type != DIRECTORY_NODE) {
                    printf("Invalid destination directory: %s\n", name);
                    break;
                }
                move(parent, name, dest);
                break;

            case 5:
                printf("Enter name to find: ");
                scanf("%s", name);
                Node* found = find(root, name);
                if (found) {
                    printf("Found: %s\n", found->name);
                } else {
                    printf("Not found: %s\n", name);
                }
                break;

            case 6:
                printf("Enter directory name: ");
                scanf("%s", name);
                dir = find(root, name);
                if (!dir || dir->type != DIRECTORY_NODE) {
                    printf("Invalid directory: %s\n", name);
                    break;
                }
                printf("Total size: %d bytes\n", calculateSize(dir));
                break;

            case 7:
                deleteNode(root);
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}