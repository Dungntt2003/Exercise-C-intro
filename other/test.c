#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
    char name[30];
    char password[30];
} data;

typedef struct node_s {
  data key;
  struct node_s *left;
  struct node_s *right;
} node_t;

typedef node_t *tree_t;

tree_t Search(char pass[], tree_t Root) {
  if (Root == NULL)
    return NULL;           // not found
  else if (strcmp(Root->key.password,pass)==0) /* found x */
    return Root;
  else if (strcmp(Root->key.password,pass)<0)
    // continue searching in the right sub tree
    return Search(pass, Root->right);
  else {
    // continue searching in the left sub tree
    return Search(pass, Root->left);
  }
}

void Insertnode_t(char name[],char pass[], tree_t *pRoot) {
  if (*pRoot == NULL) {
    /* Create a new node for key x */
    *pRoot = (node_t *)malloc(sizeof(node_t));
    strcpy((*pRoot)->key.name,name);
    strcpy((*pRoot)->key.password,pass);
    (*pRoot)->left = NULL;
    (*pRoot)->right = NULL;
  } else if (strcmp(pass,(*pRoot)->key.password)<0)
    Insertnode_t(name,pass, &((*pRoot)->left));
  else if (strcmp(pass,(*pRoot)->key.password)>0)
    Insertnode_t(name,pass, &((*pRoot)->right));
}


void freetree(tree_t tree) {
  if (tree != NULL) {
    freetree(tree->left);
    freetree(tree->right);
    free((void *)tree);
  }
}


int main(){
    data a[100];
    data admin;
    int n;
    int count=0;
    tree_t t = NULL;
    tree_t tree=NULL;
    char name[30];
    char password[30];
    printf("Hay nhap thong tin cho admin\n");
    printf("Hay nhap ten : ");
    scanf("%s",admin.name);
    printf("Hay nhap password cho admin : ");
    scanf("%s",admin.password);
    printf("Hay nhap vao so user hien tai : ");
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        printf("Hay nhap username va password cho cac user : ");
        scanf("%s %s",a[i].name,a[i].password);
        Insertnode_t(a[i].name,a[i].password,&tree);
    }
    while (1){
        printf("Hay nhap user muon tim : ");
        scanf("%s %s",name,password);
        if (strcmp(name,admin.name)==0){
            printf("Dang nhap thanh cong\n");
            printf("MENU\n");
            printf("1. Them 1 user vao he thong\n");
            printf("2. Doi mat khau cho 1 tai khoan\n");
            printf("3.In ra danh sach nguoi dung theo username\n");
            
        }
    }
}