#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Helper function to create a new tree node
struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->val = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Inorder traversal function
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Traverse the left subtree
    inorderTraversal(root->left);

    // Visit the root node
    printf("%d ", root->val);

    // Traverse the right subtree
    inorderTraversal(root->right);
}

// Function to free the binary tree
void freeTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Example usage
int main() {
    // Create a sample binary tree:
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    // Free the allocated memory
    freeTree(root);

    return 0;
}