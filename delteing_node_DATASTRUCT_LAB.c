#include <stdio.h>
#include <stdlib.h>

struct ListNode {    //defining a structure
    int data;            //data=int
    struct ListNode *next;  
};

// Function to create a new node 1. Allocate memory 
struct ListNode* createNode(int data) { 
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = data; //2.assign data
    newNode->next = NULL;  //3. Initialize next as NULL
    return newNode;  //returning the new node
}

// Append a node to the end of the list
void appendNode(struct ListNode** head, int data) { //adding new node
    struct ListNode* newNode = createNode(data);
    if (*head == NULL) {    //checking if list is empty
        *head = newNode;
        return;
    }
    struct ListNode* temp = *head;
    while (temp->next != NULL) {    // temp traverses the linked list 
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to delete a node with a specific value
struct ListNode* deleteNode(struct ListNode* head, int value) {
    struct ListNode* temp = head;
    struct ListNode* prev = NULL;

    // If the head node itself holds the value to be deleted
    if (temp != NULL && temp->data == value) {
        head = temp->next; // Changed head
        free(temp); // Free old head
        return head;
    }

    // Search for the value to be deleted, keep track of the previous node
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    // If value was not present in the list
    if (temp == NULL) {
        printf("\nValue %d not found in the list\n", value);
        return head;
    }

    // Unlink the node from the linked list
    prev->next = temp->next;

    free(temp); // Free memory
    return head;
}

// Function to print the linked list
void printList(struct ListNode* head) {
    struct ListNode* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
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

    // Delete the node with value 3
    head = deleteNode(head, 3);

    // Print the new list
    printf("List after deleting node with value 3:\n");
    printList(head);

    return 0;
}