#ifndef SKIP_LIST
#define SKIP_LIST

#define MAX_LEVEL 5


typedef struct node {
  int value;
  struct node **next;
} Node;


typedef struct skip_list {
  int size, level;
  Node *head;
} SkipList;


Node* new_node(int value, int level);
SkipList* new_list();
void free_node(Node *node);
Node* find_node(SkipList *list, int value);
void insert(SkipList *list, int value);
void del(SkipList *list, int value);
void print_list(SkipList *list);
void dtr_lst(Node* node, int i);
void dtr(SkipList* list);


#endif //skip_list.h