#include <stdio.h>  // Include standard input/output library for functions like printf
#include <stdlib.h> // Include standard library for functions like malloc
//fIFO Queue using 2 stacks
// Define the stack structure
typedef struct Stack {
    int *data;      // Pointer to the array holding the stack elements
    int top;        // Index of the top element
    int capacity;   // Maximum capacity of the stack
} Stack;

// Function to create a stack
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack)); // Allocate memory for the stack structure
    stack->capacity = capacity;                   // Set the capacity of the stack
    stack->top = -1;                              // Initialize the top index to -1 (indicating an empty stack)
    stack->data = (int*)malloc(stack->capacity * sizeof(int)); // Allocate memory for the stack elements
    return stack;                                 // Return the created stack
}

// Function to push an element onto the stack
void push(Stack* stack, int item) {
    if (stack->top == stack->capacity - 1) { // Check if the stack is full
        printf("Stack overflow\n");          // Print an error message if the stack is full
        return;                              // Exit the function
    }
    stack->data[++stack->top] = item;        // Increment the top index and add the item to the stack
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    if (stack->top == -1) {                  // Check if the stack is empty
        printf("Stack underflow\n");         // Print an error message if the stack is empty
        return -1;                           // Return -1 to indicate an error
    }
    return stack->data[stack->top--];        // Return the top element and decrement the top index
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;                 // Return true if the top index is -1, otherwise false
}

// Define the queue structure using two stacks
typedef struct Queue {
    Stack* stack1; // First stack
    Stack* stack2; // Second stack
} Queue;

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue)); // Allocate memory for the queue structure
    queue->stack1 = createStack(capacity);        // Create the first stack with the given capacity
    queue->stack2 = createStack(capacity);        // Create the second stack with the given capacity
    return queue;                                 // Return the created queue
}

// Function to push an element onto the queue
void enqueue(Queue* queue, int item) {
    push(queue->stack1, item); // Add the element to the first stack
}

// Function to pop an element from the queue
int dequeue(Queue* queue) {
    if (isEmpty(queue->stack2)) { // Check if the second stack is empty
        while (!isEmpty(queue->stack1)) { // Transfer all elements from the first stack to the second stack
            push(queue->stack2, pop(queue->stack1));
        }
    }
    return pop(queue->stack2); // Pop and return the top element from the second stack
}

// Function to get the front element of the queue
int peek(Queue* queue) {
    if (isEmpty(queue->stack2)) { // Check if the second stack is empty
        while (!isEmpty(queue->stack1)) { // Transfer all elements from the first stack to the second stack
            push(queue->stack2, pop(queue->stack1));
        }
    }
    return queue->stack2->data[queue->stack2->top]; // Return the top element from the second stack
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* queue) {
    return isEmpty(queue->stack1) && isEmpty(queue->stack2); // Return true if both stacks are empty, otherwise false
}

// Main function to test the queue implementation
int main() {
    Queue* queue = createQueue(10); // Create a queue with capacity 10

    enqueue(queue, 1); // Enqueue 1 onto the queue
    enqueue(queue, 2); // Enqueue 2 onto the queue
    enqueue(queue, 3); // Enqueue 3 onto the queue

    printf("Front element is %d\n", peek(queue)); // Print the front element (should be 1)
    printf("Removed element is %d\n", dequeue(queue)); // Dequeue and print the front element (should be 1)
    printf("Front element is %d\n", peek(queue)); // Print the new front element (should be 2)
    printf("Queue is empty: %d\n", isQueueEmpty(queue)); // Check if the queue is empty (should be 0, meaning false)

    return 0; // Return 0 to indicate successful execution
}