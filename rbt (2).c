#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

typedef struct Node {
    int data;
    int color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

void insert(Node **root, int data);
void fixViolation(Node **root, Node *node);
void rotateLeft(Node **root, Node *node);
void rotateRight(Node **root, Node *node);
void swapColors(Node *node1, Node *node2);
void printTree(Node *root);

int main() {
    Node *root = NULL;
    insert(&root, 7);
    insert(&root, 3);
    insert(&root, 18);
    insert(&root, 10);
    insert(&root, 22);
    insert(&root, 8);
    insert(&root, 11);
    insert(&root, 26);
    printTree(root);
    return 0;
}

void insert(Node **root, int data) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    Node *parent = NULL;
    Node *current = *root;

    while (current != NULL) {
        parent = current;
        if (node->data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    node->parent = parent;
    if (parent == NULL)
        *root = node;
    else if (node->data < parent->data)
        parent->left = node;
    else
        parent->right = node;
    fixViolation(root, node);
}

void fixViolation(Node **root, Node *node) {
    while (node != *root && node->parent->color == RED) {
        Node *parent = node->parent;
        Node *grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    rotateLeft(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(root, grandparent);
                swapColors(parent, grandparent);
                node = parent;
            }
        } else {
            Node *uncle = grandparent->left;
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rotateRight(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(root, grandparent);
                swapColors(parent, grandparent);
                node = parent;
            }
        }
    }

    (*root)->color = BLACK;
}

void rotateLeft(Node **root, Node *node) {
    Node *y = node->right;
    node->right = y->left;
    if (y->left != NULL)
        y->left->parent = node;
    y->parent = node->parent;
    if (node->parent == NULL)
        *root = y;
    else if (node == node->parent->left)
        node->parent->left = y;
    else
        node->parent->right = y;
    y->left = node;
    node->parent = y;
}

void rotateRight(Node **root, Node *node) {
    Node *y = node->left;
    node->left = y->right;
    if (y->right != NULL)
        y->right->parent = node;
    y->parent = node->parent;
    if (node->parent == NULL)
        *root = y;
    else if (node == node->parent->right)
        node->parent->right = y;
    else
        node->parent->left = y;
    y->right = node;
    node->parent = y;
}

void swapColors(Node *x, Node *y) {
    int temp = x->color;
    x->color = y->color;
    y->color = temp;
}

void printTree(Node *node) {
    if (node != NULL) {
        printTree(node->left);
        printf("%d ", node->data);
        printTree(node->right);
    }
}

