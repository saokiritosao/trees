#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "timer.h"

typedef struct Node
{

    int key;
    struct Node* par;
    struct Node* left;
    struct Node* right;


} Node;



struct timeval tv1,tv2,dtv;

struct timezone tz;

void time_start()
{

    gettimeofday(&tv1, &tz);

}

long time_stop()
{
    gettimeofday(&tv2, &tz);

    dtv.tv_sec= tv2.tv_sec -tv1.tv_sec;
    dtv.tv_usec=tv2.tv_usec-tv1.tv_usec;

    if(dtv.tv_usec<0) { dtv.tv_sec--; dtv.tv_usec+=1000000; }

    return dtv.tv_sec*1000+dtv.tv_usec/1000;

}


void tree_print(struct Node * tr) {
    if (tr == NULL)
          return;   // дальше ничего не делать
    tree_print(tr->left);     // печатаем левое поддерево (меньшие числа)
    printf("%d ", tr->key);  // печатаем корень
    tree_print(tr->right);     // печатаем правое поддерево (большие числа)
}

void print_key(Node* node)
{

    if (node == NULL) printf("NULL");
    else printf("%d", node->key);

}


void print_tree(Node* tr)
{

    if (tr == NULL) return;

    print_tree(tr->left);
    print_tree(tr->right);

    print_key(tr->par);
    printf(" ");
    print_key(tr->left);
    printf(" ");
    print_key(tr->right);
    printf(" ");
    print_key(tr);
    printf("\n");

}


Node* creat_node(int key, Node* par)
{

    Node* node = (Node*) malloc(sizeof(Node));
    node->key = key;
    node->par = par;
    node->left = NULL;
    node->right = NULL;

}


void zig(Node** tr, Node* node)
{

    node->par->left = node->right;
    if (node->par->left != NULL)
    {
        node->par->left->par = node->par;
    }
    node->right = node->par;
    if (node->par->par != NULL)
    {

        if (node->par == node->par->par->left)
        {

            node->par->par->left = node;

        }
        else
        {

            node->par->par->right = node;

        }

    }
    Node* par_par = node->par->par;

    node->par->par = node;
    node->par = par_par;

    if (node->right == *tr)
    {

        *tr = node;

    }


}


void zag(Node** tr, Node* node)
{

    node->par->right = node->left;
    if (node->par->right != NULL)
    {
        node->par->right->par = node->par;
    }
    node->left = node->par;
    if (node->par->par != NULL)
    {

        if (node->par == node->par->par->right)
        {

            node->par->par->right = node;

        }
        else
        {

            node->par->par->left = node;

        }

    }
    Node* par_par = node->par->par;

    node->par->par = node;
    node->par = par_par;


    if (node->left == *tr)
    {

        *tr = node;

    }

}


void splay(Node** tr, Node* node)
{

    while(node->par != NULL)
    {
        if (node->par->left == node)
        {

            if (node->par->par == NULL)
            {

                zig(tr, node);

            }
            else
            {

                if (node->par->par->left == node->par)
                {

                    zig(tr, node->par);
                    zig(tr, node);

                }
                else
                {

                    zig(tr, node);
                    zag(tr, node);

                }

            }


        }
        else
        {

            if (node->par->par == NULL)
            {

                zag(tr, node);

            }
            else
            {

                if (node->par->par->right == node->par)
                {

                    zag(tr, node->par);
                    zag(tr, node);

                }
                else
                {

                    zag(tr, node);
                    zig(tr, node);

                }

            }


        }


    }

}


Node* find(Node* tr, int key, Node** root)
{
    if (tr == NULL)
    {

        return NULL;

    }

    if (key == tr->key)
    {
        splay(root, tr);
        return tr;

    }
    else if (key < tr->key)
    {

        return find(tr->left, key, root);

    }
    else
    {

        return find(tr->right, key, root);

    }

}


void insert(Node* tr, int key, Node** root)
{
    if (tr == NULL)
    {

        *root = creat_node(key, NULL);
        return;

    }
    if (key == tr->key)
    {

        return;

    }
    else if (key < tr->key)
    {

        if (tr->left == NULL)
        {

            tr->left = creat_node(key, tr);
            splay(root, tr->left);
            return;

        }

        insert(tr->left, key, root);
        return;
    }
    else
    {

        if (tr->right == NULL)
        {

            tr->right = creat_node(key, tr);
            splay(root, tr->right);
            return;

        }
        insert(tr->right, key, root);
        return;

    }
}


void del(Node* tr, int key, Node** root)
{

    Node* x = find(tr, key, root);

    if (x == NULL)
    {

        return;

    }

    splay(root, x);

    Node* n1 = *root;
    if ((*root)->right == NULL)
    {
        if ((*root)->left != NULL)
        {

            (*root)->left->par = NULL;

        }

        Node* r_l = (*root)->left;

        (*root)->par = NULL;
        (*root)->left = NULL;
        (*root)->right = NULL;

        free(*root);

        *root = r_l;
        return;

    }

    Node* n2 = (*root)->right;
    while (n2->left != NULL)
    {

        n2 = n2->left;

    }

    Node* n3 = (*root)->right;

    splay(&n3, n2);

    n3->left = (*root)->left;
    if ((*root)->left != NULL)
    {

        (*root)->left->par = n3;

    }


    (*root)->par = NULL;
    (*root)->left = NULL;
    (*root)->right = NULL;

    free(*root);

    *root = n3;

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

#define SPLAY

#ifdef SPLAY

    char FILE_NAME_INSERT_RAND[50] = "test_splay_insert_rand.txt";
    char FILE_NAME_INSERT_SORT[50] = "test_splay_insert_sort.txt";
    char FILE_NAME_DEL_RAND[50] = "test_splay_del_rand.txt";
    char FILE_NAME_DEL_SORT[50] = "test_splay_del_sort.txt";

    #define insert(tr, k) insert(tr, k, &tr)
    #define del(tr, k) del(tr, k, &tr)

#endif


char FILE_NAME_RAND_ARR[20] = "rand_arr.txt";


int* creat_rand_arr(int size, int range, char* file_name)
{

    char com[1000] = "/usr/bin/python3 creat_rand_arr.py ";
    char si[100];
    char ra[100];
    sprintf(si, "%d", size);
    sprintf(ra, "%d", range);
    strcat(com, si);
    strcat(com, " ");
    strcat(com, ra);
    strcat(com, " ");
    strcat(com, file_name);
    strcat(com, "\n");
    system(com);

    int* b = (int*) malloc(size * sizeof(int));

    FILE* fp = fopen(file_name, "r");

    for (int i = 0; i < size; i++)
    {

        fscanf(fp, "%d", &b[i]);

    }

    fclose(fp);

    return b;

}


int main()
{
    Node* tr = NULL;

    insert(tr, 3585);
    insert(tr, 5819);
    insert(tr, 3442);
    insert(tr, 4169);
    insert(tr, 2390);
    insert(tr, 7538);

    print_tree(tr);
    printf("\n");

    del(tr, 4169);
    print_tree(tr);
    printf("\n");

    del(tr, 5819);
    print_tree(tr);
    printf("\n");

    del(tr, 3442);
    print_tree(tr);
    printf("\n");

}
