#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    char word[30];
    int count;
} key_t;
typedef struct node_s
{
    key_t key;
    struct node_s *left;
    struct node_s *right;
} node_t;

typedef node_t *tree_t;

tree_t Search(char word[], tree_t Root)
{
    if (Root == NULL)
        return NULL;                            // not found
    else if (strcmp(Root->key.word, word) == 0) /* found x */
        return Root;
    else if (strcmp(Root->key.word, word) < 0)
        // continue searching in the right sub tree
        return Search(word, Root->right);
    else
    {
        // continue searching in the left sub tree
        return Search(word, Root->left);
    }
}

void Insertnode_t(char word[], tree_t *pRoot)
{
    if (*pRoot == NULL)
    {
        /* Create a new node for key x */
        *pRoot = (node_t *)malloc(sizeof(node_t));
        strcpy((*pRoot)->key.word, word);
        (*pRoot)->key.count = 1;
        (*pRoot)->left = NULL;
        (*pRoot)->right = NULL;
    }
    else if (strcmp(word, (*pRoot)->key.word) < 0)
        Insertnode_t(word, &((*pRoot)->left));
    else if (strcmp(word, (*pRoot)->key.word) > 0)
        Insertnode_t(word, &((*pRoot)->right));
}

void freetree(tree_t tree)
{
    if (tree != NULL)
    {
        freetree(tree->left);
        freetree(tree->right);
        free((void *)tree);
    }
}

void inorderprint(tree_t tree)
{
    if (tree != NULL)
    {
        inorderprint(tree->left);
        printf("%s\t%d\n", tree->key.word, tree->key.count);
        inorderprint(tree->right);
    }
}

int main(int argc, char* argv[]){
    tree_t tree=NULL;
    tree_t s=NULL;
    FILE *p;
    int key;
    char word[30];
    char filename[30];
    if (argc<2)
    {
        printf("Khong du tham so\n");
        return 1;
    }
    strcpy(filename,argv[1]);
    while (1){
        printf("Menu\n");
        printf("1.In noi dung file\n");
        printf("2.In ra tan suat xuat hien\n");
        printf("3.In ra thong ke\n");
        printf("4.Thoat\n");
        printf("Hay chon : ");
        scanf("%d",&key);
        switch (key){
            case 1:
                p =fopen(filename,"r");
                if (p==NULL){
                    printf("Can not open file\n");
                    return 1;
                }
                while (!feof(p)){
                    fscanf(p,"%s",word);
                    printf("%s ",word);
                    s=Search(word,tree);
                    if (s==NULL){
                        Insertnode_t(word,&tree);
                    }
                    else {
                        s->key.count++;
                    }
                }
                printf("\n");
                fclose(p);
                break;
            case 2 :
                printf("Hay nhap vao 1 tu : ");
                scanf("%s",word);
                s=Search(word,tree);
                if (s==NULL){
                    printf("The times : 0 \n");
                }
                else {
                    printf("The times : %d\n",s->key.count);
                }
                break;
            case 3:
                inorderprint(tree);
                break;
            case 4:
                break;

        }
    }
    return 0;
}