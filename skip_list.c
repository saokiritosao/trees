#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "skip_list.h"


#ifndef SKIP_LIST

#define MAX_LEVEL 5

typedef struct node {
  int value;
  struct node **next;
} Node;


typedef struct skip_list {
  int size, level;
  Node *head;
} SkipList;

#endif


Node* new_node(int value, int level) {
  Node *node = (Node *) malloc(sizeof(Node));
  node->value = value;
  node->next = (Node **) calloc(level, sizeof(Node *));
  return node;
}


SkipList* new_list() {
  SkipList *list = (SkipList *) malloc(sizeof(SkipList));
  list->size = 0;
  list->level = 1;
  list->head = new_node(INT_MIN, MAX_LEVEL);
  return list;
}


void free_node(Node *node) {
  free(node->next);
  free(node);
}


Node* find_node(SkipList *list, int value) {
  Node *node = list->head;
  int i;
  for (i = list->level - 1; i >= 0; i--) {
    while (node->next[i] != NULL && node->next[i]->value < value) {
      node = node->next[i];
    }
  }
  node = node->next[0];
  if (node != NULL && node->value == value) {
    return node;
  } else {
    return NULL;
  }
}


void insert(SkipList *list, int value) {
  Node *node = list->head;
  Node *update[MAX_LEVEL];
  int i, new_level;
  for (i = list->level - 1; i >= 0; i--) {
    while (node->next[i] != NULL && node->next[i]->value < value) {
      node = node->next[i];
    }
    update[i] = node;
  }
  node = node->next[0];
  if (node == NULL || node->value != value) {
    new_level = 1;
    while (rand() < RAND_MAX / 2 && new_level < MAX_LEVEL) {
      new_level++;
    }
    if (new_level > list->level) {
      for (i = list->level; i < new_level; i++) {
        update[i] = list->head;
      }
      list->level = new_level;
    }
    node = new_node(value, new_level);
    for (i = 0; i < new_level; i++) {
      node->next[i] = update[i]->next[i];
      update[i]->next[i] = node;
    }
    list->size++;
  }
}

// Удаление элемента из списка
void del(SkipList *list, int value) {
  Node *node = list->head;
  Node *update[MAX_LEVEL];
  int i;
  for (i = list->level - 1; i >= 0; i--) {
    while (node->next[i] != NULL && node->next[i]->value < value) {
      node = node->next[i];
    }
    update[i] = node;
  }
  node = node->next[0];
  if (node != NULL && node->value == value) {
    for (i = 0; i < list->level; i++) {
      if (update[i]->next[i] != node) {
        break;
      }
      update[i]->next[i] = node->next[i];
    }
    free_node(node);
    while (list->level > 1 && list->head->next[list->level - 1] == NULL) {
      list->level--;
    }
    list->size--;
  }
}


/*int dtr(SkipList *list, int key) {
    int i;
    Node *update[MAX_LEVEL + 1];
    Node *x = list->head;
    for (i = list->level; i >= 1; i--) {
        while (x->next[i]->value < key)
            x = x->next[i];
        update[i] = x;
    }
 
    x = x->next[1];
    if (x->value == key) {
        for (i = 1; i <= list->level; i++) {
            if (update[i]->next[i] != x)
                break;
            update[i]->next[1] = x->next[i];
        }
        skiplist_node_free(x);
 
        while (list->level > 1 && list->head->next[list->level]
                == list->head)
            list->level--;
        return 0;
    }
    return 1;
}*/


void dtr_lst(Node* node, int i)
{

    if (node == NULL)
    {

        return;

    }

    dtr_lst(node->next[i], i);
    free(node);

}


void dtr(SkipList* list)
{

    dtr_lst(list->head, list->level - 1);
    free(list);
    

}

// Вывод списка на экран
void print_list(SkipList *list) {
  Node *node = list->head->next[0];
  while (node != NULL) {
    printf("%d ", node->value);
    node = node->next[0];
  }
  printf("\n");
}

/*int main() {
  SkipList *list = new_list();
  insert(list, 1);
  insert(list, 2);
  insert(list, 3);
  insert(list, 4);
  insert(list, 5);
  print_list(list);
  del(list, 3);
  print_list(list);

  print_list(list);

  dtr(list);

  return 0;
}*/