#include <stdio.h>
#include <stdlib.h>
#include "naive_tree.h"


void tree_print(struct Node * tr) {
    if (tr == NULL)
          return;   // дальше ничего не делать
    tree_print(tr->left);     // печатаем левое поддерево (меньшие числа)
    printf("%d ", tr->key);  // печатаем корень
    tree_print(tr->right);     // печатаем правое поддерево (большие числа)
}



Node* creat_node(int key)
{

    Node* tr = (Node*) calloc(1, sizeof(Node));
    tr->key = key;
    tr->left = NULL;
    tr->right = NULL;

    return tr;

}


Node* insert(Node* tr, int key)
{

    if (tr == NULL)
    {

        return creat_node(key);

    }

    if (key < tr->key)
    {

        tr->left = insert(tr->left, key);
        return tr;

    }
    else
    if (key > tr->key);
    {

        tr->right = insert(tr->right, key);
        return tr;

    }

    return tr;

}


Node* del(Node* tr, int key)
{
    if (tr == NULL)
    {

        return NULL;

    }
    if (tr->key == key)
    {

        Node* tr_l = tr->left;
        Node* tr_r = tr->right;
        Node* tmp = tr_r;

        if (tr_r == NULL)
        {

            free(tr);
            return tr_l;

        }

        while (tmp->left != NULL)
        {

            tmp = tmp->left;

        }

        tmp->left = tr_l;

        free(tr);

        return tr_r;

    }

    if (key < tr->key)
    {

        tr->left = del(tr->left, key);

    }
    else
    {

        tr->right = del(tr->right, key);

    }

    return tr;

}


void dtr(Node* tr)
{

    if (tr == NULL)
    {

        return;

    }

    dtr(tr->left);
    dtr(tr->right);

    free(tr);

    return;

}
