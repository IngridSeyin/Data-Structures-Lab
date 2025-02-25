#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
struct ListNode {
    int data;
    struct ListNode *next;
};

// Function to create a new node
struct ListNode* createNode(int data) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = data; // Assign data to the new node
    newNode->next = NULL; // Initialize next as NULL
    return newNode; // Return the new node
}

// Function to append a node to the end of the list
void appendNode(struct ListNode** head, int data) {
    struct ListNode* newNode = createNode(data);
    if (*head == NULL) { // If the list is empty, set the new node as the head
        *head = newNode;
        return;
    }
    struct ListNode* temp = *head;
    while (temp->next != NULL) { // Traverse to the end of the list
        temp = temp->next;
    }
    temp->next = newNode; // Append the new node at the end
}

// Function to reverse the linked list
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* current = head;
    struct ListNode* next = NULL;
    while (current != NULL) { // Iterate through the list
        next = current->next; // Store the next node
        current->next = prev; // Reverse the current node's pointer
        prev = current; // Move the prev pointer one step forward
        current = next; // Move the current pointer one step forward
    }
    return prev; // Return the new head of the reversed list
}

// Function to print the linked list
void printList(struct ListNode* head) {
    struct ListNode* temp = head;
    while (temp != NULL) { // Traverse through the list
        printf("%d -> ", temp->data); // Print the data of each node
        temp = temp->next; // Move to the next node
    }
    printf("NULL\n"); // Indicate the end of the list
}

int main() {
    struct ListNode* head = NULL;

    // Add nodes to the list
    appendNode(&head, 1);
    appendNode(&head, 2);
    appendNode(&head, 3);
    appendNode(&head, 4);
    appendNode(&head, 5);

    // Print the original list
    printf("Original List:\n");
    printList(head);

    // Reverse the list
    head = reverseList(head);

    // Print the reversed list
    printf("Reversed List:\n");
    printList(head);

    return 0;
}