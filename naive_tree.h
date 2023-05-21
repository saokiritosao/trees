#ifndef NAIVE_TREE
#define NAIVE_TREE

typedef struct Node
{

    int key;
    struct Node* left;
    struct Node* right;

} Node;

void tree_print(struct Node * tr);
Node* creat_node(int key);
Node* insert(Node* tr, int key);
Node* del(Node* tr, int key);
void dtr(Node* tr);


#endif //naive_tree.h
