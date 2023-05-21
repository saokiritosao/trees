#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    int color;  // 1 = red, 0 = black
    struct node *left, *right, *parent;
};

struct node *root = NULL;

// Создание нового узла
struct node *new_node(int item) {
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->color = 1;  // новый узел всегда красный
    temp->left = temp->right = temp->parent = NULL;
    return temp;
}

// Определение цвета узла
int color(struct node *node) {
    if (node == NULL)
        return 0; // пустой узел - черный
    else
        return node->color;
}

// Поворот вправо
struct node *rotate_right(struct node *x) {
    struct node *y = x->left;
    x->left = y->right;

    if (y->right != NULL)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;

    return y;
}

// Поворот влево
struct node *rotate_left(struct node *x) {
    struct node *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;

    return y;
}

// Основная функция для вставки нового узла
struct node *insert(struct node *node, int key) {
    if (node == NULL)
        return new_node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    // Выполнение поворотов
    if (color(node->right) == 1 && color(node->left) == 0)
        node = rotate_left(node);

    if (color(node->left) == 1 && color(node->left->left) == 1)
        node = rotate_right(node);

    if (color(node->left) == 1 && color(node->right) == 1) {
        node->color = 1;
        node->left->color = 0;
        node->right->color = 0;
    }

    return node;
}

// Поиск узла
struct node* search(struct node* node, int key) {
    if (node == NULL || node->key == key)
        return node;

    if (node->key < key)
        return search(node->right, key);

    return search(node->left, key);
}

// Вывод дерева на экран
void print(struct node *node, int level) {
    if (node == NULL)
        return;

    print(node->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("    ");

    printf("%d %s\n", node->key, node->color == 1 ? "R" : "B");
    print(node->left, level + 1);
}

// Тестирование работы дерева
int main() {
    int arr[] = {7, 5, 8, 3, 6, 1, 9, 4, 2, 0};

    for (int i = 0; i < 10; i++) {
        root = insert(root, arr[i]);
        printf("Вставляем узел %d:\n", arr[i]);
        print(root, 0);
        printf("\n");
    }

    struct node *n = search(root, 5);
    if (n != NULL)
        printf("Ключ %d найден\n", n->key);
    else
        printf("Ключ не найден\n");

    return 0;
}