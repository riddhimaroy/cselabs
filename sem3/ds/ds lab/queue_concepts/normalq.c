#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Queue {
    int arr[MAX];
    int front, rear;
} Queue;

// Function prototypes
void Insertq(Queue *q, int x);
int Deleteq(Queue *q);
void Display(Queue *q);
void Reverse(Queue *q);

// Queue initialization
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if queue is empty
int isEmpty(Queue *q) {
    return (q->front == -1 || q->front > q->rear);
}

// Check if queue is full
int isFull(Queue *q) {
    return (q->rear == MAX - 1);
}

// Insert element into the queue
void Insertq(Queue *q, int x) {
    if (isFull(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (q->front == -1) // First element
        q->front = 0;
    q->rear++;
    q->arr[q->rear] = x;
}

// Delete element from the queue
int Deleteq(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    int data = q->arr[q->front];
    q->front++;
    if (q->front > q->rear) // Reset queue after last element
        q->front = q->rear = -1;
    return data;
}

// Display elements of the queue
void Display(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = q->front; i <= q->rear; i++) 
    {
        printf("%d ", q->arr[i]);
    }
    printf("\n");
}

// Reverse the queue using recursion
void Reverse(Queue *q) {
    if (isEmpty(q)) {
        return;
    }
    
        int data = Deleteq(q);
        Reverse(q);
        Insertq(q, data);
}

// Main function
int main() {
    Queue q;
    initQueue(&q);

    // Insert elements into the queue
    Insertq(&q, 10);
    Insertq(&q, 20);
    Insertq(&q, 30);
    Insertq(&q, 40);

    printf("Original Queue:\n");
    Display(&q);

    // Reverse the queue
    Reverse(&q);

    printf("Reversed Queue:\n");
    Display(&q);

    return 0;
}
