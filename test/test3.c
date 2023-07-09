#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct {
 	char name[30];
    char pass[30];
    float grade;
} key_t;
typedef struct node_s {
  key_t key;
  struct node_s *left;
  struct node_s *right;
} node_t;

typedef node_t *tree_t;

tree_t Search(char name[], tree_t Root) {
  if (Root == NULL)
    return NULL;           // not found
  else if (strcmp(Root->key.name,name)==0) /* found x */
    return Root;
  else if (strcmp(Root->key.name,name)<0)
    // continue searching in the right sub tree
    return Search(name, Root->right);
  else {
    // continue searching in the left sub tree
    return Search(name, Root->left);
  }
}

void Insertnode_t(char name[],char pass[],float grade, tree_t *pRoot) {
  if (*pRoot == NULL) {
    /* Create a new node for key x */
    *pRoot = (node_t *)malloc(sizeof(node_t));
    strcpy((*pRoot)->key.name,name);
    strcpy((*pRoot)->key.pass,pass);
    (*pRoot)->key.grade = grade;
    (*pRoot)->left = NULL;
    (*pRoot)->right = NULL;
  } else if (strcmp(name,(*pRoot)->key.name)<0)
    Insertnode_t(name,pass,grade, &((*pRoot)->left));
  else if (strcmp(name,(*pRoot)->key.name)>0)
    Insertnode_t(name, pass,grade, &((*pRoot)->right));
}


void freetree(tree_t tree) {
  if (tree != NULL) {
    freetree(tree->left);
    freetree(tree->right);
    free((void *)tree);
  }
}

int main(){
    tree_t tree=NULL;
    FILE *p;
    key_t admin;
    char str[100];
    char name[30],pass[30];
    float grade;
    int key;
    while (1){
        p=fopen("thisinh.txt","r");
        if (p==NULL){
            printf("Loi\n");
            return 1;
        }
        fgets(str,100,p);
        sscanf(str,"%s %s %f",admin.name,admin.pass,&admin.grade);
        while (!feof(p)){
            fgets(str,100,p);
            sscanf(str,"%s %s %f",name,pass,&grade);
            Insertnode_t(name,pass,grade,&tree);
        }
        printf("Menu\n");
        printf("1.Dang nhap\n");
        printf("2.Thoat\n");
        printf("Chon : ");
        scanf("%d",&key);
        switch (key){
            case 1:
                printf("Hay nhap ten va mat khau dang nhap\n");
                scanf("%s %s",name,pass);
                if (strcmp(name,admin.name)==0 && strcmp(pass,admin.pass)==0){
                }
        }
    }
}