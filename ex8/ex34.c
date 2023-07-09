#include<stdio.h>
#include<stdlib.h>
#include<string.h>




typedef struct
{
    char word[30];
    char meaning[30];
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

void Insertnode_t(char word[],char meaning[], tree_t *pRoot)
{
    if (*pRoot == NULL)
    {
        /* Create a new node for key x */
        *pRoot = (node_t *)malloc(sizeof(node_t));
        strcpy((*pRoot)->key.word, word);
        strcpy((*pRoot)->key.meaning, meaning);
        (*pRoot)->left = NULL;
        (*pRoot)->right = NULL;
    }
    else if (strcmp(word, (*pRoot)->key.word) < 0)
        Insertnode_t(word,meaning, &((*pRoot)->left));
    else if (strcmp(word, (*pRoot)->key.word) > 0)
        Insertnode_t(word,meaning, &((*pRoot)->right));
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
        printf("%s\t%s\n", tree->key.word, tree->key.meaning);
        inorderprint(tree->right);
    }
}


void fix (char* meaning){
    if (meaning != NULL && meaning[strlen(meaning)-1] == '\n')
    meaning[strlen(meaning)-1] = '\0';
}

void uppercase (char* meaning){
    int i;
    for (i=0;i<strlen(meaning);i++){
        if (meaning[i] >= 'A' && meaning[i] <= 'Z'){
            meaning[i] = meaning[i]+32;
        }
    }
}


int main(){
    tree_t tree = NULL;
    tree_t s=NULL;
    FILE *p;
    FILE *m;
    char c;
    char str[200];
    key_t a[100];
    int i,n;
    FILE *f;
    int key;
    char word[30];
    char meaning[30];
    while (1){
        printf("Menu\n");
        printf("1.Get the information from file\n");
        printf("2.Print all trees\n");
        printf("3.Translate a sentence\n");
        printf("4.Exit\n");
        printf("Choose : ");
        scanf("%d",&key);
        switch (key){
            case 1:
                p=fopen("data.txt", "r");
                if (p==NULL){
                    printf("Can not open file\n");
                    return 1;
                }
                while (!feof(p)){
                    fscanf(p,"%s",word);
                    c= fgetc(p);
                    fgets(meaning,100,p);
                    fix(meaning);
                    Insertnode_t(word,meaning,&tree);
                }
                fclose(p);
                break;
            case 2:
                inorderprint(tree);
                break;

            case 3:
                m= fopen("test.txt","w+");
                if (m==NULL){
                    printf("Can not open file\n");
                    return 1;
                }
                i=0,n=0;
                fflush(stdin);
                fgets(str,100,stdin);
                uppercase(str);
                fprintf(m,"%s",str);
                fseek(m,0,SEEK_SET);
                while (!feof(m)){
                    fscanf(m,"%s",a[i].word);
                    i++;
                    n++;
                }
                for (int j =0 ;j<n-1;j++){
                    printf("%s\n",a[j].word);
                }
                for (int j=0;j<n-1;j++){
                    s= Search(a[j].word,tree);
                    if (s==NULL){
                        printf("thieu tu\t");
                    }
                    else printf("%s\t",s->key.meaning);
                }
                printf("\n");
                fclose(m);
                break;
            case 4:
                return 1;
        }
    }
    freetree(tree);
    return 0;
}