#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splay_tree.h"
#include <sys/time.h>
#include "timer.h"




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
    //printf("b1\n");
    if (tr == NULL)
    {

        *root = creat_node(key, NULL);
        return;

    }
    //printf("b2\n");
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
    //printf("b3\n");
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


/*int main()
{
    Node* tr = NULL;

    /*for (int i = 0; i < 10; i++)
    {

        insert(tr, i, &tr);
        //tree_print(tr);
        //printf(" %d\n", tr->key);

        printf("\n");
        print_tree(tr);
    }

    insert(tr, 3903, &tr);
    insert(tr, 2259, &tr);

    dtr(tr);   

}*/
