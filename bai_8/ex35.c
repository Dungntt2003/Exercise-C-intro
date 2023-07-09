#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    char name[30];
    char pass[30];
} key_t;
typedef struct node_s
{
    key_t key;
    struct node_s *left;
    struct node_s *right;
} node_t;

typedef node_t *tree_t;

tree_t Search(char name[], tree_t Root)
{
    if (Root == NULL)
        return NULL;                            // not found
    else if (strcmp(Root->key.name, name) == 0) /* found x */
        return Root;
    else if (strcmp(Root->key.name, name) < 0)
        // continue searching in the right sub tree
        return Search(name, Root->right);
    else
    {
        // continue searching in the left sub tree
        return Search(name, Root->left);
    }
}

void Insertnode_t(char name[],char pass[], tree_t *pRoot)
{
    if (*pRoot == NULL)
    {
        /* Create a new node for key x */
        *pRoot = (node_t *)malloc(sizeof(node_t));
        strcpy((*pRoot)->key.name, name);
        strcpy((*pRoot)->key.pass, pass);
        (*pRoot)->left = NULL;
        (*pRoot)->right = NULL;
    }
    else if (strcmp(name, (*pRoot)->key.name) < 0)
        Insertnode_t(name,pass, &((*pRoot)->left));
    else if (strcmp(name, (*pRoot)->key.name) > 0)
        Insertnode_t(name,pass, &((*pRoot)->right));
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
        printf("%s\t%s\n", tree->key.name, tree->key.pass);
        inorderprint(tree->right);
    }
}

void inorderprint_file(tree_t tree,FILE *p)
{
    if (tree != NULL)
    {
        inorderprint_file(tree->left,p);
        fprintf(p,"%s\t%s\n", tree->key.name, tree->key.pass);
        inorderprint_file(tree->right,p);
    }
}


int main(){
    int count=0;
    FILE *p;
    FILE *f;
    tree_t tree=NULL;
    tree_t s=NULL;
    int key;
    char str[200];
    char name[30], pass[30];
    key_t admin;
    int n=0,i=0;
    printf("Please enter the name and the password of admin : ");
    scanf("%s %s",admin.name,admin.pass);
    while (1){
        p=fopen("data.txt","r");
        if (p==NULL){
            printf("File not found\n");
            return 1;
        }
        while (!feof(p)){
            fgets(str,200,p);
            sscanf(str,"%s %s",name,pass);
            Insertnode_t(name,pass,&tree);
        }
        fclose(p);
        printf("Please enter a name and a password : ");
        scanf("%s %s",name,pass);
        if (strcmp(name,admin.name)==0 && strcmp(pass,admin.pass)==0){
            while (1){
                printf("Menu\n");
                printf("1.Add a user to the list\n");
                printf("2.Change the password\n");
                printf("3.Print the list of users\n");
                printf("4.Exit\n");
                printf("Choose : ");
                scanf("%d",&key);
                switch (key){
                    case 1:
                        printf("Enter a name and a password : ");
                        scanf("%s %s",name,pass);
                        Insertnode_t(name,pass,&tree);
                        break;
                    case 2:
                        printf("Please enter a name : ");
                        scanf("%s",name);
                        s=Search(name,tree);
                        if (s==NULL){
                            printf("Can not find this name in the list\n");

                        }
                        else 
                        {
                            printf("Please enter a pass to change : ");
                            scanf("%s",pass);
                            strcpy(s->key.pass,pass);
                        }
                        break;
                    case 3:
                        inorderprint(tree);
                        break;
                    
                }
            }

        }
        else {
            s=Search(name,tree);
            if (s=NULL){
                printf("Log in failed\n");
                count++;
            }
            else if (strcmp(s->key.pass,pass)!=0)
            {
                printf("Password is incorrect\n");
                count++;
            }
            else if (strcmp(s->key.pass,pass)==0){
                printf("Please enter a password\n");
                scanf("%s",pass);
                strcpy(s->key.pass,pass);
                printf("Change password successfully\n");
            }
            else if (count>3)
            {
                printf("Failed more 3 times\n");
                return 1;
            }
        }
        f=fopen("data.txt","w");
        if (f==NULL){
            printf("Failed to open data.txt\n");
            return 1;
        }
        inorderprint_file(tree,f);
        fclose(f);
    }
    freetree(tree);
    return 0;
}