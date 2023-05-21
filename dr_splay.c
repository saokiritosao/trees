#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "splay_tree.h"
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
    // "после return жизни нет" - далее код
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
#define SPLAY

#ifdef SPLAY

    //#include "splay_tree.h"

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
    //printf("si = %s\n", si);
    strcat(com, " ");
    strcat(com, file_name);
    strcat(com, "\n");
    //printf("com = %s\n", com);
    //system("pwd");
    //system("which python3");
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

    int l = 10000;
    int r = 100000;
    int step = 10000;

    printf("ewe\n");

    int n_tests = 5;
    int n_steps = (r - l) / step + 1;
    int n_del = 50000;

    //int* b = (int*) malloc(r * sizeof(int));
    printf("n_steps = %d\n", n_steps);
    long times[n_steps + 5];
    long ti = 0;
    long ti_del = 0;
    memset(times, 0, (n_steps + 5) * sizeof(long int));

    for (int i = 0; i < n_steps; i++)
    {

        printf("%ld ", times[i]);

    }

    printf("\n");

    printf("dsd\n");

    for (int len = l, j = 0; len <= r; len += step, j++)
    {
        for (int p = 0; p < n_tests; p++)
        {
            Node* tr = NULL;
            printf("len = %d\n", len);
            
            int* b = creat_rand_arr(len, len, FILE_NAME_RAND_ARR);
            
            printf("44545\n");
            time_start();
            for (int k = 0; k < len; k++)
            {
                //if (k <= 5)
                //{

                    //int o = 0;
                    //tree_print(tr);
                    //printf("\n");
                    

                //}
                //printf("k = %d\n", k);
                //printf("b[k] = %d\n", b[k]);
                int h = b[k];
                insert(tr, h);
                //print_tree(tr);
                //print_tree(tr);
                //printf("\n");
                //printf("insert\n");
                //tree_print(tr);
                //printf("\n");

            }
            //tree_print(tr);
            //printf("\n");
            times[j] += time_stop();

            free(b);

            printf("times[%d] = %ld rand\n", j, times[j]);
            if (len == len)
            {
                //TODO rand_arr
                int* b = creat_rand_arr(len / 2, len, FILE_NAME_RAND_ARR);
                time_start();
                for (int k = 0; k < len / 2; k++)
                {
                    int h = b[k];
                    del(tr, h);
                    print_tree(tr);
                    //printf("nooo = %d\n", k);

                }
                ti_del += time_stop();
                printf("ti_del = %ld\n", ti_del);
                free(b);

            }
            dtr(tr);
        }
    }

    ti_del /= n_tests;

    /*FILE* fp = fopen(FILE_NAME_INSERT_RAND, "w");
    
    for (int len = l; len <= r; len += step)
    {

        fprintf(fp, "%d ", len);

    }

    fprintf(fp, "\n");

    for (int j = 0; j < n_steps; j++)
    {

        fprintf(fp, "%ld ", times[j] / n_tests);

    }*/

    //fprintf(fp, "\n");
    //free(b);
    //fclose(fp);
    

    //fp = fopen(FILE_NAME_DEL_RAND, "w");
    //fprintf(fp, "Время удаления рандомной последовательности %ld мс.\n", ti_del);
    //fclose(fp);
    
    memset(times, 0, (n_steps + 5) * sizeof(long int));
    ti_del = 0;

    for (int len = l, j = 0; len <= r; len += step, j++)
    {
        for (int p = 0; p < n_tests; p++)
        {
            Node* tr = NULL;
            printf("len = %d\n", len);

            time_start();
            for (int k = 0; k < len; k++)
            {

                insert(tr, k);

            }
            times[j] += time_stop();
            printf("times[%d] = %ld sort\n", j, times[j]);
            if (len == len)
            {
                time_start();
                for (int k = 0; k < len / 2; k++)
                {

                    del(tr, k);
                    //printf("k = %d tr = %p\n", k, tr);

                }
                ti_del += time_stop();

            }
            printf("del done\n");
            dtr(tr);
        }
    }

    ti_del /= n_tests;

    /*fp = fopen(FILE_NAME_INSERT_SORT, "w");
    
    for (int len = l; len <= r; len += step)
    {

        fprintf(fp, "%d ", len);

    }

    fprintf(fp, "\n");

    for (int j = 0; j < n_steps; j++)
    {

        fprintf(fp, "%ld ", times[j] / n_tests);

    }

    fprintf(fp, "\n");

    fclose(fp);

    fp = fopen(FILE_NAME_DEL_SORT, "w");
    fprintf(fp, "Время удаления отсортированной последовательности %ld мс.\n", ti_del);
    fclose(fp);*/

    return 0;

}
