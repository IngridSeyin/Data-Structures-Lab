#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the queue structure
typedef struct Queue {
    int *data;       // Pointer to the array holding the queue elements
    int front;       // Index of the front element
    int rear;        // Index of the rear element
    int size;        // Current size of the queue
    int capacity;    // Maximum capacity of the queue
} Queue;

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue)); // Allocate memory for the queue structure
    queue->capacity = capacity;                   // Set the capacity of the queue
    queue->front = 0;                             // Initialize the front index to 0
    queue->size = 0;                              // Initialize the size to 0
    queue->rear = capacity - 1;                   // Initialize the rear index to capacity - 1
    queue->data = (int*)malloc(queue->capacity * sizeof(int)); // Allocate memory for the queue elements
    return queue;                                 // Return the created queue
}

// Function to check if the queue is empty
bool isQueueEmpty(Queue* queue) {
    return (queue->size == 0); // Return true if the size is 0, otherwise false
}

// Function to check if the queue is full
bool isQueueFull(Queue* queue) {
    return (queue->size == queue->capacity); // Return true if the size equals the capacity, otherwise false
}

// Function to add an item to the queue
void enqueue(Queue* queue, int item) {
    if (isQueueFull(queue)) { // Check if the queue is full
        return;               // If full, do nothing
    }
    queue->rear = (queue->rear + 1) % queue->capacity; // Update the rear index in a circular manner
    queue->data[queue->rear] = item;                   // Add the item to the rear of the queue
    queue->size = queue->size + 1;                     // Increment the size of the queue
}

// Function to remove an item from the queue
int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) { // Check if the queue is empty
        return -1;             // If empty, return -1
    }
    int item = queue->data[queue->front]; // Get the front item
    queue->front = (queue->front + 1) % queue->capacity; // Update the front index in a circular manner
    queue->size = queue->size - 1;                       // Decrement the size of the queue
    return item;                                         // Return the front item
}

// Function to get the front item from the queue
int front(Queue* queue) {
    if (isQueueEmpty(queue)) { // Check if the queue is empty
        return -1;             // If empty, return -1
    }
    return queue->data[queue->front]; // Return the front item
}

// Define the stack structure using two queues
typedef struct MyStack {
    Queue* queue1; // First queue
    Queue* queue2; // Second queue
} MyStack;

// Function to create a stack
MyStack* createStack(int capacity) {
    MyStack* stack = (MyStack*)malloc(sizeof(MyStack)); // Allocate memory for the stack structure
    stack->queue1 = createQueue(capacity);              // Create the first queue with the given capacity
    stack->queue2 = createQueue(capacity);              // Create the second queue with the given capacity
    return stack;                                       // Return the created stack
}

// Function to push an element onto the stack
void push(MyStack* stack, int x) {
    enqueue(stack->queue1, x); // Add the element to the first queue
}

// Function to pop an element from the stack
int pop(MyStack* stack) {
    while (stack->queue1->size > 1) { // Transfer all elements except the last one from queue1 to queue2
        enqueue(stack->queue2, dequeue(stack->queue1));
    }
    int topElement = dequeue(stack->queue1); // Dequeue the last element from queue1
    Queue* temp = stack->queue1;             // Swap the names of queue1 and queue2
    stack->queue1 = stack->queue2;
    stack->queue2 = temp;
    return topElement;                       // Return the popped element
}

// Function to get the top element of the stack
int top(MyStack* stack) {
    while (stack->queue1->size > 1) { // Transfer all elements except the last one from queue1 to queue2
        enqueue(stack->queue2, dequeue(stack->queue1));
    }
    int topElement = dequeue(stack->queue1); // Dequeue the last element from queue1
    enqueue(stack->queue2, topElement);      // Enqueue the last element back to queue2
    Queue* temp = stack->queue1;             // Swap the names of queue1 and queue2
    stack->queue1 = stack->queue2;
    stack->queue2 = temp;
    return topElement;                       // Return the top element
}

// Function to check if the stack is empty
bool empty(MyStack* stack) {
    return isQueueEmpty(stack->queue1); // Return true if queue1 is empty, otherwise false
}

// Main function to test the stack implementation
int main() {
    MyStack* stack = createStack(10); // Create a stack with capacity 10

    push(stack, 1); // Push 1 onto the stack
    push(stack, 2); // Push 2 onto the stack
    push(stack, 3); // Push 3 onto the stack

    printf("Top element is %d\n", top(stack)); // Print the top element (should be 3)
    printf("Removed element is %d\n", pop(stack)); // Pop and print the top element (should be 3)
    printf("Top element is %d\n", top(stack)); // Print the new top element (should be 2)
    printf("Stack is empty: %d\n", empty(stack)); // Check if the stack is empty (should be 0, meaning false)

    return 0; // Return 0 to indicate successful execution
}