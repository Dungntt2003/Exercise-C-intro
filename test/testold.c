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
    (*pRoot)->key.grade=grade;
    (*pRoot)->left = NULL;
    (*pRoot)->right = NULL;
  } else if (strcmp(name,(*pRoot)->key.name)<0)
    Insertnode_t(name,pass,grade, &((*pRoot)->left));
  else if (strcmp(name,(*pRoot)->key.name)>0)
    Insertnode_t(name,pass,grade, &((*pRoot)->right));
}


key_t DeleteMin(tree_t *Root) {
  key_t k;
  if ((*Root)->left == NULL) {
    k = (*Root)->key;
    (*Root) = (*Root)->right;
    return k;
  } else
    return DeleteMin(&(*Root)->left);
}

void Deletenode_t(char name[], tree_t *Root) {
  if (*Root != NULL)
    if (strcmp(name,(*Root)->key.name) < 0)
      Deletenode_t(name, &(*Root)->left);
    else if (strcmp(name,(*Root)->key.name)>0)
      Deletenode_t(name, &(*Root)->right);
    else if (((*Root)->left == NULL) && ((*Root)->right == NULL))
      *Root = NULL;
    else if ((*Root)->left == NULL)
      *Root = (*Root)->right;
    else if ((*Root)->right == NULL)
      *Root = (*Root)->left;
    else
      (*Root)->key = DeleteMin(&(*Root)->right);
}


void freetree(tree_t tree) {
  if (tree != NULL) {
    freetree(tree->left);
    freetree(tree->right);
    free((void *)tree);
  }
}


void inorderprint(tree_t tree){
    if (tree!=NULL){
        inorderprint(tree->left);
        printf("%s %s %g\n",tree->key.name,tree->key.pass,tree->key.grade);
        inorderprint(tree->right);
    }
}


void inorderprint_File (tree_t tree,FILE *p){
    if (tree!=NULL){
        
    }
}


int main(){
    tree_t tree=NULL;
    tree_t s=NULL;
    int key,key1;
    FILE *p;
    char name[30],pass[30];
    float grade;
    char str[200];
    key_t admin;
    while (1){
        p=fopen("data.txt","r");
        if (p==NULL){
            printf("Can't open data.txt\n");
            return 1;
        }
        fgets(str,200,p);
        sscanf(str,"%s %s %f",admin.name,admin.pass,&admin.grade);
        while (!feof(p)){
            fgets(str,200,p);
            sscanf(str,"%s %s %f",name,pass,&grade);
            Insertnode_t(name,pass,grade, &tree);
        }
        fclose(p);
        printf("Menu\n");
        printf("1.Dang nhap\n");
        printf("2.Thoat\n");
        scanf("%d",&key);
        switch (key){
            case 1:
                printf("Hay nhap nhap : ");
                scanf("%s %s",name,pass);
                if (strcmp(name,admin.name)==0 && strcmp(pass,admin.pass)==0)
                {
                    while (1){
                        printf("Ban da dang nhap thanh cong voi admin\n");
                        printf("Menu\n");
                        printf("1.Them mot sinh vien \n");
                        printf("2.In ra danh sach sin vien\n");
                        printf("3.Xoa sinh vien\n");
                        printf("4.Ghi lai thong tin vao file\n");
                        printf("Chon : ");
                        scanf("%d",&key1);
                        switch (key1){
                            case 1:
                                printf("Hay nhap ten , pass, diem cho sinh vien muon them\n");
                                scanf("%s %s %f",name,pass,&grade);
                                Insertnode_t(name,pass,grade, &tree);
                                break;
                            case 2:
                                inorderprint(tree);
                                break;
                            case 3:
                                printf("Hay nhap vao user muon xoa : ");
                                scanf("%s",name);
                                s=Search(name,tree);
                                if (s==NULL){
                                    printf("Can found user \n");

                                }
                                else {
                                    printf("%s %s %g\n",s->key.name,s->key.pass,s->key.grade);
                                    Deletenode_t(name,&tree);
                                }
                                break;
                            case 4:
                                p=fopen("data.txt","w");
                                if (p==NULL)
                                printf("Can open\n");
                                else {

                                }
                        }
                    }
                }
        }
    }

}