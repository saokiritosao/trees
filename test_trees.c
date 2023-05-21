#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timer.h"

//#define AVL
//#define NAIVE
//#define AVL_SPLIT_MERGE
#define DEC
//#define SPLAY
//#define SKIP


#ifdef AVL

    #include "avl_tree.h"

    char FILE_NAME_INSERT_RAND[50] = "test_avl_insert_rand.txt";
    char FILE_NAME_INSERT_SORT[50] = "test_avl_insert_sort.txt";
    char FILE_NAME_DEL_RAND[50] = "test_avl_del_rand.txt";
    char FILE_NAME_DEL_SORT[50] = "test_avl_del_sort.txt";


#endif

#ifdef AVL_SPLIT_MERGE

    #include "avl_tree.h"

    char FILE_NAME_INSERT_RAND[50] = "test_avl_sp_mr_insert_rand.txt";
    char FILE_NAME_INSERT_SORT[50] = "test_avl_sp_mr_insert_sort.txt";
    char FILE_NAME_DEL_RAND[50] = "test_avl_sp_mr_del_rand.txt";
    char FILE_NAME_DEL_SORT[50] = "test_avl_del_sp_mr_sort.txt";

    #define insert(tr, k) insert2(tr, k)
    #define del(tr, k) del2(tr, k)

#endif


#ifdef NAIVE
    
    #include "naive_tree.h"

    char FILE_NAME_INSERT_RAND[50] = "test_naive_insert_rand.txt";
    char FILE_NAME_INSERT_SORT[50] = "test_naive_insert_sort.txt";
    char FILE_NAME_DEL_RAND[50] = "test_naive_del_rand.txt";
    char FILE_NAME_DEL_SORT[50] = "test_naive_del_sort.txt";

#endif


#ifdef DEC

    #include "dec_tree.h"

    char FILE_NAME_INSERT_RAND[50] = "test_dec_insert_rand.txt";
    char FILE_NAME_INSERT_SORT[50] = "test_dec_insert_sort.txt";
    char FILE_NAME_DEL_RAND[50] = "test_dec_del_rand.txt";
    char FILE_NAME_DEL_SORT[50] = "test_dec_del_sort.txt"; 

#endif


#ifdef SPLAY

    #include "splay_tree.h"

    char FILE_NAME_INSERT_RAND[50] = "test_splay_insert_rand.txt";
    char FILE_NAME_INSERT_SORT[50] = "test_splay_insert_sort.txt";
    char FILE_NAME_DEL_RAND[50] = "test_splay_del_rand.txt";
    char FILE_NAME_DEL_SORT[50] = "test_splay_del_sort.txt";

    #define insert(tr, k) insert(tr, k, &tr)   
    #define del(tr, k) del(tr, k, &tr)  

#endif


#ifdef SKIP

    #include "skip_list.h"

    char FILE_NAME_INSERT_RAND[50] = "test_skip_list_insert_rand.txt";
    char FILE_NAME_INSERT_SORT[50] = "test_skip_list_insert_sort.txt";
    char FILE_NAME_DEL_RAND[50] = "test_skip_list_del_rand.txt";
    char FILE_NAME_DEL_SORT[50] = "test_skip_list_del_sort.txt"; 


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
    long times_del[n_steps + 5];
    memset(times, 0, (n_steps + 5) * sizeof(long int));
    memset(times_del, 0, (n_steps + 5) * sizeof(long int));

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
                tr = insert(tr, h);
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
                    tr = del(tr, h);
                    //printf("nooo = %d\n", k);

                }
                times_del[j] += time_stop();
                printf("ti_del = %ld\n", ti_del);
                free(b);

            }
            dtr(tr);
        }
    }

    ti_del /= n_tests;

    FILE* fp = fopen(FILE_NAME_INSERT_RAND, "w");
    FILE *fp1 = fopen(FILE_NAME_DEL_RAND, "w");
    
    for (int len = l; len <= r; len += step)
    {

        fprintf(fp, "%d ", len);
        fprintf(fp1, "%d ", len / 2);

    }

    fprintf(fp, "\n");
    fprintf(fp1, "\n");

    for (int j = 0; j < n_steps; j++)
    {

        fprintf(fp, "%ld ", times[j] / n_tests);
        fprintf(fp1, "%ld ", times_del[j] / n_tests);

    }

    fprintf(fp, "\n");
    fprintf(fp1, "\n");
    //free(b);
    fclose(fp);
    fclose(fp1);
    

    //fp = fopen(FILE_NAME_DEL_RAND, "w");
    //fprintf(fp, "Время удаления рандомной последовательности %ld мс.\n", ti_del);
    //fclose(fp);
    
    memset(times, 0, (n_steps + 5) * sizeof(long int));
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

                tr = insert(tr, k);

            }
            times[j] += time_stop();
            printf("times[%d] = %ld sort\n", j, times[j]);
            
            time_start();
            for (int k = 0; k < len / 2; k++)
            {

                tr = del(tr, k);
                //printf("k = %d tr = %p\n", k, tr);

            }
            times_del[j] += time_stop();

            
            printf("del done\n");
            dtr(tr);
        }
    }

    ti_del /= n_tests;

    fp = fopen(FILE_NAME_INSERT_SORT, "w");
    fp1 = fopen(FILE_NAME_DEL_SORT, "w");

    for (int len = l; len <= r; len += step)
    {

        fprintf(fp, "%d ", len);
        fprintf(fp1, "%d ", len / 2);

    }

    fprintf(fp, "\n");
    fprintf(fp1, "\n");

    for (int j = 0; j < n_steps; j++)
    {

        fprintf(fp, "%ld ", times[j] / n_tests);
        fprintf(fp1, "%ld ", times_del[j] / n_tests);

    }

    fprintf(fp, "\n");
    fprintf(fp1, "\n");

    fclose(fp);
    fclose(fp1);

    //fp = fopen(FILE_NAME_DEL_SORT, "w");
    //fprintf(fp, "Время удаления отсортированной последовательности %ld мс.\n", ti_del);
    //fclose(fp);

    return 0;

}
