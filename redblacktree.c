#include <stdio.h>
#include <stdlib.h>

// Colours
#define RED 1
#define BLACK 0

// Node Structure
typedef struct Node Node;
struct Node {
    int key;
    int val;
    int colour;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

// sentinel node
struct Node *NIL;

// Search through tree to find value searching for
int search(struct Node *root, int key) {
    if (root == NULL) {
        return -1;
    }

    if (root->key == key) {
        return root->val;
    }
    else if (root->key > key) {
        return search(root->left, key);
    }
    else {
        return search(root->right, key);
    }
}

// Rotates tree left, swapping nodes to balance
void rotate_left(Node **root, Node *node) {
    Node *right_child = node->right;
    node->right = right_child->left;
    if (right_child->left != NULL) {
        right_child->left->parent = node;
    }
    right_child->parent = node->parent;
    if (node->parent == NULL) {
        *root = right_child;
    } else if (node == node->parent->left) {
        node->parent->left = right_child;
    } else {
        node->parent->right = right_child;
    }
    right_child->left = node;
    node->parent = right_child;
}

// Rotates tree right, swapping nodes to balance
void rotate_right(Node **root, Node *node) {
    Node *left_child = node->left;
    node->left = left_child->right;
    if (left_child->right != NULL) {
        left_child->right->parent = node;
    }
    left_child->parent = node->parent;
    if (node->parent == NULL) {
        *root = left_child;
    } else if (node == node->parent->right) {
        node->parent->right = left_child;
    } else {
        node->parent->left = left_child;
    }
    left_child->right = node;
    node->parent = left_child;
}

// Fixed any issues caused by insert
void insert_fixup(Node **root, Node *node) {
    // Set root colour as black
    if (node == *root) {
        node->colour = BLACK;
    } else {
       // Repeatedly apply fixups if rules are broken.
        while (node != *root && node->parent->colour == RED) {
            Node *uncle;

            // Parent is left child
            if (node->parent == node->parent->parent->left) {
                uncle = node->parent->parent->right;

                // Red uncle rule applies
                if (uncle != NULL && uncle->colour == RED) {
                    node->parent->colour = BLACK;
                    uncle->colour = BLACK;
                    node->parent->parent->colour = RED;
                    node = node->parent->parent;

                // Uncle is black and rotation required
                } else {
                    if (node == node->parent->right) {
                        // The new node is the right child of its parent and left rotation is needed
                        node = node->parent;
                        rotate_left(root, node);
                    } else if (node == node->parent->left) {
                        // The new node is the left child of its parent and right rotation is needed
                        node->parent->colour = BLACK;
                        node->parent->parent->colour = RED;
                        rotate_right(root, node->parent->parent);
                    }
                }

            // Parent is right child
            } else {
                uncle = node->parent->parent->left;

                // Red uncle rule applies
                if (uncle != NULL && uncle->colour == RED) {
                    node->parent->colour = BLACK;
                    uncle->colour = BLACK;
                    node->parent->parent->colour = RED;
                    node = node->parent->parent;
                // Uncle is black and rotation required
                } else {
                    if (node == node->parent->left) {
                        // The new node is the left child of its parent and right rotation is needed
                        node = node->parent;
                        rotate_right(root, node);
                    } else if (node == node->parent->right) {
                    // The new node is the right child of its parent and left rotation is needed
                    node->parent->colour = BLACK;
                    node->parent->parent->colour = RED;
                    rotate_left(root, node->parent->parent);
                }
            }
        }
    }

    // Set root colour to black if changed
    (*root)->colour = BLACK;
}

// Insert node with key-value pairing and fix any issues caused
void insert(Node **root, int key, int val) {
    // Create a new node
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    new_node->colour = RED;

    // Find the correct position for the new node
    Node *current_node = *root;
    Node *parent_node = NULL;
    while (current_node != NULL) {
        parent_node = current_node;
        if (key < current_node->key) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }

    // Insert the new node in the correct position
    new_node->parent = parent_node;
    if (parent_node == NULL) {
        *root = new_node;
    } else if (key < parent_node->key) {
        parent_node->left = new_node;
    } else {
        parent_node->right = new_node;
    }

    // Fix any violations of the red-black tree properties
    insert_fixup(root, new_node);
}

int main() {
    Node *root = NULL;

    insert(&root, 10, 10);
    insert(&root, 5, 5);
    insert(&root, 15, 15);
    insert(&root, 3, 3);
    insert(&root, 7, 7);
    insert(&root, 12, 12);
    insert(&root, 17, 17);
    insert(&root, 1, 1);
    insert(&root, 9, 9);
    insert(&root, 14, 14);
    insert(&root, 20, 20);
    insert(&root, 8, 8);
    insert(&root, 11, 11);
    insert(&root, 18, 18);
    insert(&root, 6, 6);
    insert(&root, 2, 2);

    return 0;
}