#ifndef SPLAY_TREE
#define SPLAY_TREE

typedef struct Node
{

    int key;
    struct Node* par;
    struct Node* left;
    struct Node* right;
    

} Node;


Node* creat_node(int key, Node* par);
void zig(Node** tr, Node* node);
void zag(Node** tr, Node* node);
void splay(Node** tr, Node* node);
Node* find(Node* tr, int key, Node** root);
void insert(Node* tr, int key, Node** root);
void del(Node* tr, int key, Node** root);
void dtr(Node* tr);


#endif //splay_tree.h