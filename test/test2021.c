#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct {
 	char name[30];
    float open[10];
    float close[10];
    int count;
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

void Insertnode_t(char name[],float open, float close, tree_t *pRoot) {
  if (*pRoot == NULL) {
    /* Create a new node for key x */
    *pRoot = (node_t *)malloc(sizeof(node_t));
    strcpy((*pRoot)->key.name,name);
    (*pRoot)->key.open[0] = open;
    (*pRoot)->key.close[0] = close;
    (*pRoot)->key.count=0;
    (*pRoot)->left = NULL;
    (*pRoot)->right = NULL;
  } else if (strcmp(name,(*pRoot)->key.name)<0)
    Insertnode_t(name,open,close, &((*pRoot)->left));
  else if (strcmp(name,(*pRoot)->key.name)>0)
    Insertnode_t(name,open,close, &((*pRoot)->right));
}


void freetree(tree_t tree) {
  if (tree != NULL) {
    freetree(tree->left);
    freetree(tree->right);
    free((void *)tree);
  }
}


float ava (float a[]){
    float sum=0;
    for (int i=0;i<10;i++){
        sum=sum +a[i];
    }
    return sum/10;
}


float find_max(float a[]){
    float max=0;
    for (int i=0;i<10;i++){
        if (a[i]>max){
            max=a[i];
        }
    }
    return max;
}

void inorderprint(tree_t tree){
    if (tree!=NULL){
        inorderprint(tree->left);
        printf("%s\t%.3f\t%.3f\n",tree->key.name,ava(tree->key.open),ava(tree->key.close));
        inorderprint(tree->right);
    }
}


int check (float open[],float close[]){
    if (open[1]<close[1]&& open[0]<close[0])
    return 1;
}

void Find_raise(tree_t tree){
    if (tree!=NULL){
        if (check(tree->key.open, tree->key.close)==1)
        printf("%s\n",tree->key.name);
        Find_raise(tree->left);
        Find_raise(tree->right);
    }
}

int quantity(float a[],float b[]){
    int count=0;
    for (int i=0;i<10;i++){
        if (a[i]<b[i]) count++;
    }
    return count;
}


int case4(tree_t tree){
    int max=0;
    if (tree !=NULL){
        if (quantity(tree->key.open,tree->key.close)>max)
        max=quantity(tree->key.open,tree->key.close);
        case4(tree->left);
        case4(tree->right);
    }
    return max;
}

void final (tree_t tree){
    if (tree!=NULL){
        if (case4(tree)==quantity(tree->key.open,tree->key.close))
        printf("%s\n",tree->key.name);
        final(tree->left);
        final(tree->right);
    }
}

int main(){
    tree_t tree = NULL;
    int key;
    int n;
    FILE *p;
    char name[30];
    float open,close;
    tree_t s=NULL;
    char str[200];
    while (1){
        printf("Menu\n");
        printf("1.Doc file\n");
        printf("2.Tim kiem theo ma chung khoan\n");
        printf("3.Tim kiem ma chung khoan co xu huong tang\n");
        printf("4.Tim ma co so ngay tang lon nhat\n");
        printf("5.Thoat chuong trinh\n");
        printf("Chon  : ");
        scanf("%d",&key);
            switch (key){
                case 1:
                    p=fopen("data.txt","r");
                    if (p==NULL){
                        printf("Can not open file\n");
                        return 1;
                    }
                    fgets(str,200,p);
                    sscanf(str,"%d",&n);
                    while (!feof(p)){
                        fgets(str,200,p);
                        sscanf(str,"%s %f %f",name,&open,&close);
                        s=Search(name,tree);
                        if (s==NULL){
                            Insertnode_t(name,open,close,&tree);
                        } 
                        else {
                            s->key.count++;
                            s->key.open[s->key.count] = open;
                            s->key.close[s->key.count] = close; 
                        }
                    }
                    inorderprint(tree);
                    fclose(p);
                    break;
                case 2:
                    printf("Hay nhp vao 1 ma chung khoan\n");
                    scanf("%s",name);
                    s=Search(name,tree);
                    if (s==NULL){
                        printf("Can not found\n");
                        return 1;
                    }
                    else {
                        printf("%f\t%f\n",find_max(s->key.open),find_max(s->key.close));
                    }
                    break;
                case 3:
                    Find_raise(tree);
                    break;
                case 4:
                    final(tree);
                    break;
                case 5:
                printf("Nguyen Thi Thuy Dung - 20215009\n");
                    return 1;
            }
    }
    return 0;
}