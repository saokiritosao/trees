#include <stdio.h> 
#include <stdlib.h> 

#define RED 1 
#define BLACK 0 

typedef struct node { 
  int key, color; 
  struct node *left, *right, *parent; 
} Node; 

void rotateLeft(Node **root, Node *node) { 
  Node *rightChild = node->right; 

  node->right = rightChild->left; 

  if (node->right != NULL) 
    node->right->parent = node; 

  rightChild->parent = node->parent; 

  if (node->parent == NULL) 
    *root = rightChild; 
  else if (node == node->parent->left) 
    node->parent->left = rightChild; 
  else 
    node->parent->right = rightChild; 

  rightChild->left = node; 
  node->parent = rightChild; 
} 

void rotateRight(Node **root, Node *node) { 
  Node *leftChild = node->left; 

  node->left = leftChild->right; 

  if (node->left != NULL) 
    node->left->parent = node; 

  leftChild->parent = node->parent; 

  if (node->parent == NULL) 
    *root = leftChild; 
  else if (node == node->parent->left) 
    node->parent->left = leftChild; 
  else 
    node->parent->right = leftChild; 

  leftChild->right = node; 
  node->parent = leftChild; 
} 

void fixViolation(Node **root, Node *node) { 
  Node *parent = NULL; 
  Node *grandparent = NULL; 

  while ((node != *root) && (node->color != BLACK) && (node->parent->color == RED)) { 
    parent = node->parent; 
    grandparent = node->parent->parent; 

    if (parent == grandparent->left) { 
      Node *uncle = grandparent->right; 

      if ((uncle != NULL) && (uncle->color == RED)) { 
        grandparent->color = RED; 
        parent->color = BLACK; 
        uncle->color = BLACK; 
        node = grandparent; 
      } else { 
        if (node == parent->right) { 
          rotateLeft(root, parent); 
          node = parent; 
          parent = node->parent; 
        } 

        rotateRight(root, grandparent); 
        int tempColor = parent->color; 
        parent->color = grandparent->color; 
        grandparent->color = tempColor; 
        node = parent; 
      } 
    } else { 
      Node *uncle = grandparent->left; 

      if ((uncle != NULL) && (uncle->color == RED)) { 
        grandparent->color = RED; 
        parent->color = BLACK; 
        uncle->color = BLACK; 
        node = grandparent; 
      } else { 
        if (node == parent->left) { 
          rotateRight(root, parent); 
          node = parent; 
          parent = node->parent; 
        } 

        rotateLeft(root, grandparent); 
        int tempColor = parent->color; 
        parent->color = grandparent->color; 
        grandparent->color = tempColor; 
        node = parent; 
      } 
    } 
  } 

  (*root)->color = BLACK; 
} 

Node *createNode(int key) { 
  Node *node = (Node *)malloc(sizeof(Node)); 
  node->key = key; 
  node->left = node->right = node->parent = NULL; 
  node->color = RED;
  node->right = NULL;
  return node; 
} 

void insertNode(Node **root, int key) { 
  Node *node = createNode(key); 
  Node *parent = NULL; 
  Node *current = *root; 

  while (current != NULL) { 
    parent = current; 

    if (key < current->key) 
      current = current->left; 
    else if (key > current->key) 
      current = current->right; 
    else
      return; 
  } 

  node->parent = parent; 

  if (parent == NULL) 
    *root = node; 
  else if (key < parent->key) 
    parent->left = node; 
  else 
    parent->right = node; 

  fixViolation(root, node); 
} 

Node *minValueNode(Node *node) { 
  Node *current = node; 

  while (current->left != NULL) 
    current = current->left; 

  return current; 
} 

void deleteNode(Node **root, int key) { 
  Node *current = *root; 

  while ((current != NULL) && (current->key != key)) { 
    if (key < current->key) 
      current = current->left; 
    else if (key > current->key) 
      current = current->right; 
  } 

  if (current == NULL) 
    return; 

  Node *deletedNode = current; 
  int deletedNodeColor = deletedNode->color; 
  Node *replacingNode = NULL; 

  if (current->left == NULL) { 
    replacingNode = current->right; 
    if (current->parent == NULL) { 
      *root = current->right; 
      current->right->parent = NULL; 
    } else { 
      if (current == current->parent->left)
        current->parent->left = current->right; 
      else 
        current->parent->right = current->right; 

        replacingNode->parent = current->parent; 
    } 
  } else if (current->right == NULL) { 
    replacingNode = current->left; 
    if (current->parent == NULL) { 
      *root = current->left; 
      current->left->parent = NULL; 
    } else { 
      if (current == current->parent->left) 
        current->parent->left = current->left; 
      else 
        current->parent->right = current->left; 

      replacingNode->parent = current->parent; 
    } 
  } else { 
    deletedNode = minValueNode(current->right); 
    deletedNodeColor = deletedNode->color; 
    replacingNode = deletedNode->right; 
    if (deletedNode->parent == current) { 
      replacingNode->parent = deletedNode; 
    } else { 
      if (deletedNode->right != NULL) 
        deletedNode->right->parent = deletedNode->parent; 

      deletedNode->parent->left = deletedNode->right; 
      deletedNode->right = current->right; 
      deletedNode->right->parent = deletedNode; 
    } 

    if (current->parent == NULL) { 
      *root = deletedNode; 
      deletedNode->parent = NULL; 
    } else { 
      deletedNode->parent = current->parent; 

      if (current == current->parent->left) 
        current->parent->left = deletedNode; 
      else 
        current->parent->right = deletedNode; 
    } 

    deletedNode->right = current->right; 
    deletedNode->right->parent = deletedNode; 
    deletedNode->left = current->left; 
    deletedNode->left->parent = deletedNode; 
    deletedNode->color = current->color; 
  } 

  if (deletedNodeColor == BLACK) 
    fixViolation(root, replacingNode); 

  free(current); 
} 

Node *search(Node *node, int key) { 
  if (node == NULL || node->key == key) 
    return node; 

  if (node->key < key) 
    return search(node->right, key); 
  return search(node->left, key); 
} 

void inorder(Node *node) { 
  if (node == NULL) 
    return; 

  inorder(node->left); 
  printf("%d ", node->key); 
  inorder(node->right); 
} 

int main() { 
  Node *root = NULL; 

  insertNode(&root, 7); 
  insertNode(&root, 3); 
  insertNode(&root, 18); 
  insertNode(&root, 10); 
  insertNode(&root, 22); 
  insertNode(&root, 8); 
  insertNode(&root, 11); 
  insertNode(&root, 26); 

  printf("Inorder traversal of the given tree: \n"); 
  inorder(root); 

  printf("\n\nDeleting 18...\n"); 
  deleteNode(&root, 18); 

  printf("Inorder traversal of the modified tree:\n"); 
  inorder(root); 

  printf("\n\nSearching for key 10: "); 
  if (search(root, 10) != NULL) 
    printf("Found\n"); 
  else
    printf("Not Found\n"); 

  printf("Searching for key 18: "); 
  if (search(root, 18) != NULL) 
    printf("Found\n"); 
  else
    printf("Not Found\n"); 

  return 0; 
} 