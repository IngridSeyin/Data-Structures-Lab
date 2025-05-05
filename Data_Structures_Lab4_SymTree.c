#include <stdio.h>              // for input/output functions like printf
#include <stdlib.h>             // for dynamic memory allocation functions like malloc and free
#include <stdbool.h>            // for the bool type and constants true/false

// definition for a binary tree node
struct TreeNode {
    int val;                    // value of the node
    struct TreeNode* left;      // pointer to the left child
    struct TreeNode* right;     // pointer to the right child
};

// definition for a queue node
struct QueueNode {
    struct TreeNode* node1;     // pointer to the first tree node in the pair
    struct TreeNode* node2;     // pointer to the second tree node in the pair
    struct QueueNode* next;     // pointer to the next node in the queue
};

// queue implementation
struct Queue {
    struct QueueNode* front;    // pointer to the front of the queue
    struct QueueNode* rear;     // pointer to the rear of the queue
};

// function to create a new queue
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue)); // allocate memory for the queue
    q->front = q->rear = NULL;                                     // initialize front and rear to null
    return q;                                                      // return the created queue
}

// function to enqueue a pair of tree nodes into the queue
void enqueue(struct Queue* q, struct TreeNode* node1, struct TreeNode* node2) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode)); // allocate memory for a new queue node
    newNode->node1 = node1;                                                         // set the first tree node
    newNode->node2 = node2;                                                         // set the second tree node
    newNode->next = NULL;                                                           // set the next pointer to null
    if (q->rear == NULL) {                                                          // if the queue is empty
        q->front = q->rear = newNode;                                               // set both front and rear to the new node
        return;
    }
    q->rear->next = newNode;                                                        // link the new node to the end of the queue
    q->rear = newNode;                                                              // update the rear pointer
}

// function to dequeue a pair of tree nodes from the queue
void dequeue(struct Queue* q) {
    if (q->front == NULL) {                                                         // if the queue is empty
        return;                                                                     // do nothing
    }
    struct QueueNode* temp = q->front;                                              // store the front node temprarily
    q->front = q->front->next;                                                      // move the front pointer to the next node
    if (q->front == NULL) {                                                         // if the queue is now empty
        q->rear = NULL;                                                             // set the rear pointer to null
    }
    free(temp);                                                                     // free the memory of the dequeued node
}

// function to check if the queue is empty
bool isQueueEmpty(struct Queue* q) {
    return q->front == NULL;                                                        // return true if the front pointer is null
}

// iterative function to check if the tree is symmetric
bool isSymmetricIterative(struct TreeNode* root) {
    if (root == NULL) {                                                             // if the tree is empty
        return true;                                                                // an empty tree is symmetric
    }

    struct Queue* q = createQueue();                                                // create a queue
    enqueue(q, root->left, root->right);                                            // enqueue the left and right children of the root

    while (!isQueueEmpty(q)) {                                                      // while the queue is not empty
        struct TreeNode* t1 = q->front->node1;                                      // get the first tree node in the pair
        struct TreeNode* t2 = q->front->node2;                                      // get the second tree node in the pair
        dequeue(q);                                                                 // dequeue the pair

        if (t1 == NULL && t2 == NULL) {                                             // if both nodes are null
            continue;                                                               // continue to the next pair
        }
        if (t1 == NULL || t2 == NULL || t1->val != t2->val) {                       // if one node is null or their values are not equal
            return false;                                                           // the tree is not symmetric
        }

        // enqueue the children in mirror order
        enqueue(q, t1->left, t2->right);                                            // enqueue the left child of t1 and the right child of t2
        enqueue(q, t1->right, t2->left);                                            // enqueue the right child of t1 and the left child of t2
    }

    free(q);                                                                        // free the queue
    return true;                                                                    // the tree is symmetric
}

// helper function to create a new tree node
struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));   // allocate memory for a new tree node
    newNode->val = val;                                                             // set the value of the node
    newNode->left = NULL;                                                           // initialize the left child to null
    newNode->right = NULL;                                                          // initialize the right child to null
    return newNode;                                                                 // return the created node
}

// example usage
int main() {
    // example 1: symmetric tree
    struct TreeNode* root1 = createNode(1);                                         // create the root node
    root1->left = createNode(2);                                                    // create the left child
    root1->right = createNode(2);                                                   // create the right child
    root1->left->left = createNode(3);                                              // create the left-left grandchild
    root1->left->right = createNode(4);                                             // create the left-right grandchild
    root1->right->left = createNode(4);                                             // create the right-left grandchild
    root1->right->right = createNode(3);                                            // create the right-right grandchild

    printf("tree 1 is symmetric: %s\n", isSymmetricIterative(root1) ? "true" : "false"); // check if the tree is symmetric

    // example 2: non-symmetric tree
    struct TreeNode* root2 = createNode(1);                                         // create the root node
    root2->left = createNode(2);                                                    // create the left child
    root2->right = createNode(2);                                                   // create the right child
    root2->left->right = createNode(3);                                             // create the left-right grandchild
    root2->right->right = createNode(3);                                            // create the right-right grandchild

    printf("tree 2 is symmetric: %s\n", isSymmetricIterative(root2) ? "true" : "false"); // check if the tree is symmetric

    return 0;                                                                       // exit the program
}